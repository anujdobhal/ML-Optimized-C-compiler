import http.server
import socketserver
import json
import subprocess
import os
import re

PORT = 8000
PROJECT_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
COMPILER_DIR = os.path.join(PROJECT_DIR, "Semantic and Syntax Analysis")
ML_DIR = os.path.join(PROJECT_DIR, "ml_module")

# Paths for compiler files
COMPILER_EXE = os.path.join(COMPILER_DIR, "compiler.exe")
TEMP_C = os.path.join(COMPILER_DIR, "web_temp.c")
TAC_TXT = os.path.join(COMPILER_DIR, "tac.txt")
OPTIMIZER_PY = os.path.join(ML_DIR, "optimizer.py")

class CompilerAppHandler(http.server.SimpleHTTPRequestHandler):
    def end_headers(self):
        # Allow CORS for easy debugging if accessed across origins
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        super().end_headers()

    def do_OPTIONS(self):
        self.send_response(200, "ok")
        self.end_headers()

    def do_POST(self):
        if self.path == '/api/compile':
            self.handle_compile()
        elif self.path == '/api/optimize':
            self.handle_optimize()
        else:
            self.send_error(404, "Not Found")

    def handle_compile(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        req_data = json.loads(post_data.decode('utf-8'))
        code = req_data.get('code', '')

        # Write to temp file in Semantic and Syntax Analysis directory
        try:
            with open(TEMP_C, "w") as f:
                f.write(code)
        except Exception as e:
            self.respond_json({"success": False, "error": f"Failed to write temp C file: {str(e)}"}, 500)
            return

        # Execute compiler
        try:
            # Run compiler inside its folder so it outputs tac.txt there
            result = subprocess.run(
                [COMPILER_EXE, "web_temp.c"],
                cwd=COMPILER_DIR,
                capture_output=True,
                text=True,
                timeout=5
            )
            stdout = result.stdout
            stderr = result.stderr
        except subprocess.TimeoutExpired:
            self.respond_json({"success": False, "error": "Compilation timed out"}, 500)
            return
        except Exception as e:
            self.respond_json({"success": False, "error": f"Failed to run compiler binary: {str(e)}"}, 500)
            return

        # Check if compilation succeeded
        success = "Parsing Completed" in stdout and result.returncode == 0

        # Clean up temp file
        if os.path.exists(TEMP_C):
            try:
                os.remove(TEMP_C)
            except:
                pass

        if not success:
            self.respond_json({
                "success": False,
                "error": stdout if stdout else stderr
            })
            return

        # Extract AST structure from stdout
        ast_tree = self.parse_ast(stdout)
        
        # Read generated TAC
        tac_code = ""
        if os.path.exists(TAC_TXT):
            with open(TAC_TXT, "r") as f:
                tac_code = f.read()

        self.respond_json({
            "success": True,
            "stdout": stdout,
            "ast": ast_tree,
            "tac": tac_code
        })

    def handle_optimize(self):
        # Run ML Optimizer script
        try:
            result = subprocess.run(
                ["python", OPTIMIZER_PY, TAC_TXT],
                cwd=PROJECT_DIR,
                capture_output=True,
                text=True,
                timeout=5
            )
            stdout = result.stdout
            stderr = result.stderr
        except subprocess.TimeoutExpired:
            self.respond_json({"success": False, "error": "ML Optimization timed out"}, 500)
            return
        except Exception as e:
            self.respond_json({"success": False, "error": f"Failed to run ML optimizer script: {str(e)}"}, 500)
            return

        if result.returncode != 0:
            self.respond_json({"success": False, "error": stdout if stdout else stderr})
            return

        # Parse loop predictions and features from optimizer output
        predictions = self.parse_optimizer_output(stdout)
        
        # Read optimized TAC
        optimized_tac = ""
        opt_tac_file = os.path.join(COMPILER_DIR, "tac_optimized.txt")
        if os.path.exists(opt_tac_file):
            with open(opt_tac_file, "r") as f:
                optimized_tac = f.read()

        # Generate actual unrolled IR representation & stats for comparison
        unrolled_ir, comparison_stats = self.generate_unrolled_ir_and_stats(optimized_tac, predictions)

        self.respond_json({
            "success": True,
            "stdout": stdout,
            "predictions": predictions,
            "optimized_tac": optimized_tac,
            "unrolled_ir": unrolled_ir,
            "comparison_stats": comparison_stats
        })

    def respond_json(self, data, status=200):
        self.send_response(status)
        self.send_header('Content-Type', 'application/json')
        response_bytes = json.dumps(data).encode('utf-8')
        self.send_header('Content-Length', str(len(response_bytes)))
        self.end_headers()
        self.wfile.write(response_bytes)

    def parse_ast(self, compiler_stdout):
        """
        Parse AST printout from compiler stdout.
        Indented structure:
        Abstract Syntax Tree (AST):
        FUNCTION (main)
          DECL (=)
            ID (i)
            NUM (0)
        """
        lines = compiler_stdout.split('\n')
        ast_start = -1
        for idx, line in enumerate(lines):
            if "Abstract Syntax Tree (AST):" in line:
                ast_start = idx + 1
                break
        
        if ast_start == -1 or ast_start >= len(lines):
            return {"name": "Empty or Invalid AST"}

        # Extract AST lines
        ast_lines = []
        for line in lines[ast_start:]:
            if "Three Address Code:" in line or "Symbol Table:" in line or "Parsing Failed" in line:
                break
            if line.strip():
                ast_lines.append(line)

        if not ast_lines:
            return {"name": "Empty AST"}

        # Helper to compute indent levels
        def get_indent(line):
            return len(line) - len(line.lstrip())

        root = {"name": ast_lines[0].strip(), "children": []}
        stack = [(get_indent(ast_lines[0]), root)]

        for line in ast_lines[1:]:
            indent = get_indent(line)
            node_name = line.strip()
            node = {"name": node_name, "children": []}

            # Pop stack until we find the parent (indent must be strictly less than current node)
            while stack and stack[-1][0] >= indent:
                stack.pop()

            if stack:
                stack[-1][1]["children"].append(node)
            else:
                # If stack is empty, this is another root or top-level element, link it to the main root
                root["children"].append(node)
            stack.append((indent, node))

        return root

    def parse_optimizer_output(self, optimizer_stdout):
        """
        Extract predicted loops and features from optimizer output, e.g.:
          Loop 1  (Label: L2)
          ----------------------------------------
            Nesting Depth       : 2
            Total Instructions  : 5
            Memory Operations   : 3
            Branch Instructions : 2
            Input Dependencies  : 3
            >> Predicted Unroll Factor : 32
        """
        loops = []
        # Find loops using regex on the output text
        loop_blocks = re.split(r'Loop \d+\s+\(Label:', optimizer_stdout)
        
        # The first item is everything before the first loop block
        for block in loop_blocks[1:]:
            label_match = re.match(r'\s*(\w+)\)', block)
            if not label_match:
                continue
            label = label_match.group(1)
            
            # Extract features using regex
            depth = int(re.search(r'Nesting Depth\s*:\s*(\d+)', block).group(1))
            instructions = int(re.search(r'Total Instructions\s*:\s*(\d+)', block).group(1))
            mem_ops = int(re.search(r'Memory Operations\s*:\s*(\d+)', block).group(1))
            branches = int(re.search(r'Branch Instructions\s*:\s*(\d+)', block).group(1))
            deps = int(re.search(r'Input Dependencies\s*:\s*(\d+)', block).group(1))
            unroll_factor = int(re.search(r'>> Predicted Unroll Factor\s*:\s*(\d+)', block).group(1))
            
            loops.append({
                "label": label,
                "depth": depth,
                "instructions": instructions,
                "mem_ops": mem_ops,
                "branches": branches,
                "dependencies": deps,
                "unroll_factor": unroll_factor
            })
            
        return loops

    def generate_unrolled_ir_and_stats(self, optimized_tac, predictions):
        """
        Produce a visualized representation of the Unrolled TAC IR
        and simulate performance changes.
        """
        lines = [l.strip() for l in optimized_tac.split('\n') if l.strip()]
        unrolled_lines = []
        
        # Build lookup table of loop predictions by label
        pred_map = {p["label"]: p for p in predictions}

        i = 0
        while i < len(lines):
            line = lines[i]
            
            # Check if this line marks the start of a loop optimization annotation
            opt_match = re.match(r'^;\s*\[OPTIMIZE\]\s*Unroll loop at\s+(\w+)\s+by factor\s+(\d+)', line)
            if opt_match:
                label = opt_match.group(1)
                factor = int(opt_match.group(2))
                unrolled_lines.append(f"; === UNROLLED LOOP AT {label} BY FACTOR {factor} ===")
                
                # Advance to skip the annotation
                i += 1
                if i >= len(lines): break
                label_line = lines[i]
                unrolled_lines.append(label_line) # e.g. "L2:"
                
                # Capture loop body until we find the jump back
                body = []
                i += 1
                while i < len(lines):
                    body_line = lines[i]
                    # Check for back-edge jump back to the label
                    if body_line == f"goto {label}":
                        break
                    body.append(body_line)
                    i += 1
                
                # Replicate the core loop body operations (excluding branch/jumps) multiple times
                core_body = [line for line in body if not line.startswith("ifFalse ") and not line.startswith("goto ")]
                loop_branch = [line for line in body if line.startswith("ifFalse ") or line.startswith("goto ")]
                
                # Append unrolled segments
                for f in range(factor):
                    unrolled_lines.append(f";   --- Iteration Unroll Segment {f+1} ---")
                    for body_inst in core_body:
                        # Append a suffix to temporary variables to show unrolling progression
                        if f > 0:
                            updated_inst = re.sub(r'\b(t\d+)\b', r'\1_' + str(f), body_inst)
                            unrolled_lines.append("  " + updated_inst)
                        else:
                            unrolled_lines.append("  " + body_inst)
                
                # Re-add loop condition check at the end of the unrolled block
                unrolled_lines.append(";   --- Unrolled Loop Condition & Jump Back ---")
                for branch_inst in loop_branch:
                    unrolled_lines.append("  " + branch_inst)
                unrolled_lines.append(f"  goto {label} ; (Unrolled Back-Edge)")
                
                i += 1 # Advance past the original 'goto label'
                continue
            
            unrolled_lines.append(line)
            i += 1

        unrolled_ir_text = '\n'.join(unrolled_lines)

        # Estimate statistics
        # Assume a base of 100 original loop iterations for comparison
        original_iterations = 100
        comparison_stats = []
        
        for p in predictions:
            factor = p["unroll_factor"]
            orig_branches = original_iterations + 1
            unrolled_branches = (original_iterations // factor) + 1
            
            # Assume 1 cycle per instructions, 5 cycles for a branch/jump
            orig_runtime_cycles = (original_iterations * p["instructions"]) + (orig_branches * 5)
            unrolled_runtime_cycles = (original_iterations * p["instructions"]) + (unrolled_branches * 5)
            
            # Unrolled savings include loop index updates reduction (approx 1 instruction per iteration factor)
            overhead_reduction = (original_iterations - (original_iterations // factor)) * 1
            unrolled_runtime_cycles = max(10, unrolled_runtime_cycles - overhead_reduction)
            
            speedup = (orig_runtime_cycles - unrolled_runtime_cycles) / orig_runtime_cycles * 100
            
            comparison_stats.append({
                "label": p["label"],
                "unroll_factor": factor,
                "orig_iterations": original_iterations,
                "unrolled_iterations": original_iterations // factor,
                "orig_branches": orig_branches,
                "unrolled_branches": unrolled_branches,
                "orig_cycles": orig_runtime_cycles,
                "unrolled_cycles": unrolled_runtime_cycles,
                "speedup": round(speedup, 1)
            })

        return unrolled_ir_text, comparison_stats

# Main server initialization
def run():
    # Force the server to run from the visualization directory for relative assets
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    server_address = ('', PORT)
    httpd = socketserver.TCPServer(server_address, CompilerAppHandler)
    print(f"[SERVER] ML-Compiler Web Server running at http://localhost:{PORT}")
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\n[SERVER] Server stopped.")
        httpd.server_close()

if __name__ == '__main__':
    run()
