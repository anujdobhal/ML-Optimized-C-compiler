"""
optimizer.py - Bridge between the C compiler's TAC output and the ML model.

Reads Three-Address Code (TAC) from tac.txt, detects loops, extracts features
(Depth, TotalInstructions, MemoryOperations, BranchInstructions, InputDeps),
and uses the trained Random Forest model to predict optimal unroll factors.
"""

import sys
import os
import re
import joblib
import pandas as pd


# ======================== TAC PARSING ========================

def parse_tac(tac_file):
    """Read and return non-empty, stripped lines from the TAC file."""
    with open(tac_file, "r") as f:
        lines = [line.strip() for line in f.readlines()]
    return [l for l in lines if l]


# ======================== LOOP DETECTION ========================

def detect_loops(lines):
    """
    Detect loops by finding back-edges in the TAC.

    A back-edge is a 'goto Lx' where label Lx appears *before* the goto,
    indicating a loop (the jump goes backward). This correctly identifies
    while-loops, for-loops, and do-while loops in the TAC.

    Returns a list of loop dicts with start/end indices and body lines.
    """
    # Map each label to its line index
    label_positions = {}
    for i, line in enumerate(lines):
        match = re.match(r"^(L\d+):$", line)
        if match:
            label_positions[match.group(1)] = i

    loops = []
    for i, line in enumerate(lines):
        match = re.match(r"^goto (L\d+)$", line)
        if match:
            target = match.group(1)
            if target in label_positions and label_positions[target] < i:
                # Back-edge found -> this is a loop
                loop_start = label_positions[target]
                loop_end = i
                loops.append({
                    "start_label": target,
                    "start_idx": loop_start,
                    "end_idx": loop_end,
                    "body": lines[loop_start : loop_end + 1],
                })

    return loops


def compute_nesting_depth(loops):
    """
    Compute nesting depth for each loop.

    A loop's depth is 1 + the number of other loops that fully enclose it.
    """
    for i, loop in enumerate(loops):
        depth = 1
        for j, other in enumerate(loops):
            if i != j:
                # Check if 'other' fully encloses 'loop'
                if (other["start_idx"] < loop["start_idx"]
                        and other["end_idx"] > loop["end_idx"]):
                    depth += 1
        loop["depth"] = depth


# ======================== FEATURE EXTRACTION ========================

def extract_features(loop):
    """
    Extract ML features from a single loop's TAC body.

    Features (matching the training dataset columns):
      - Depth:              loop nesting depth (set by compute_nesting_depth)
      - TotalInstructions:  count of executable instructions (excluding labels)
      - MemoryOperations:   count of assignment / load-store instructions
      - BranchInstructions: count of conditional + unconditional jumps
      - InputDeps:          count of unique variable references in the body
                            (approximates data dependencies)
    """
    body = loop["body"]

    total_instructions = 0
    memory_ops = 0
    branch_instructions = 0
    all_variable_refs = set()

    for line in body:
        # Skip labels — they aren't instructions
        if re.match(r"^(L\d+):$", line):
            continue

        # Skip FUNC headers
        if re.match(r"^FUNC\s+", line):
            continue

        total_instructions += 1

        # --- Branch instructions ---
        if line.startswith("ifFalse ") or line.startswith("goto "):
            branch_instructions += 1
            # Collect variables from conditional  (e.g. "ifFalse t0 goto L1")
            tokens = re.findall(r"\b([a-zA-Z_]\w*)\b", line)
            for t in tokens:
                if t not in ("ifFalse", "goto") and not re.match(r"^L\d+$", t):
                    all_variable_refs.add(t)
            continue

        # --- Return / Print (not memory ops, but are instructions) ---
        if line.startswith("return ") or line.startswith("print "):
            tokens = re.findall(r"\b([a-zA-Z_]\w*)\b", line)
            for t in tokens:
                if t not in ("return", "print"):
                    all_variable_refs.add(t)
            continue

        # --- Assignment instructions: LHS = RHS ---
        assign_match = re.match(r"^(\w+)\s*=\s*(.+)$", line)
        if assign_match:
            memory_ops += 1
            lhs = assign_match.group(1)
            rhs = assign_match.group(2)
            all_variable_refs.add(lhs)
            # Collect all variable tokens from RHS
            tokens = re.findall(r"\b([a-zA-Z_]\w*)\b", rhs)
            for t in tokens:
                if t not in ("call",):
                    all_variable_refs.add(t)

    return {
        "Depth": loop["depth"],
        "TotalInstructions": total_instructions,
        "MemoryOperations": memory_ops,
        "BranchInstructions": branch_instructions,
        "InputDeps": len(all_variable_refs),
    }


# ======================== ML PREDICTION ========================

def predict_unroll(features, model):
    """Feed extracted features into the trained model and return the prediction."""
    df = pd.DataFrame([features])
    prediction = model.predict(df)
    return int(prediction[0])


# ======================== MAIN ========================

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # --- Resolve TAC file path ---
    if len(sys.argv) > 1:
        tac_file = sys.argv[1]
    else:
        tac_file = os.path.join(
            script_dir, "..", "Semantic and Syntax Analysis", "tac.txt"
        )
    tac_file = os.path.normpath(tac_file)

    # --- Resolve model path ---
    model_file = os.path.join(script_dir, "model.pkl")

    # --- Validate inputs ---
    if not os.path.exists(tac_file):
        print(f"Error: TAC file not found: {tac_file}")
        sys.exit(1)
    if not os.path.exists(model_file):
        print(f"Error: Model file not found: {model_file}")
        sys.exit(1)

    # --- Load model ---
    print("[ML] Loading trained model...")
    model = joblib.load(model_file)
    print("[ML] Model loaded successfully.\n")

    # --- Read TAC ---
    lines = parse_tac(tac_file)
    if not lines:
        print("Error: TAC file is empty.")
        sys.exit(1)

    print("=" * 60)
    print("  THREE-ADDRESS CODE (from compiler)")
    print("=" * 60)
    for line in lines:
        print(f"  {line}")

    # --- Detect loops ---
    loops = detect_loops(lines)
    if not loops:
        print("\n[ML] No loops detected in TAC - nothing to optimize.")
        return

    compute_nesting_depth(loops)

    # --- Analyze and predict ---
    print("\n" + "=" * 60)
    print("  LOOP ANALYSIS & ML PREDICTIONS")
    print("=" * 60)

    loop_predictions = []
    for i, loop in enumerate(loops):
        features = extract_features(loop)
        unroll_factor = predict_unroll(features, model)
        loop_predictions.append((loop, features, unroll_factor))

        print(f"\n  Loop {i + 1}  (Label: {loop['start_label']})")
        print(f"  {'-' * 40}")
        print(f"    Nesting Depth       : {features['Depth']}")
        print(f"    Total Instructions  : {features['TotalInstructions']}")
        print(f"    Memory Operations   : {features['MemoryOperations']}")
        print(f"    Branch Instructions : {features['BranchInstructions']}")
        print(f"    Input Dependencies  : {features['InputDeps']}")
        print(f"    >> Predicted Unroll Factor : {unroll_factor}")

    # --- Generate optimized TAC with annotations ---
    print("\n" + "=" * 60)
    print("  OPTIMIZED THREE-ADDRESS CODE")
    print("=" * 60)

    # Build lookup: start_label -> (features, unroll_factor)
    loop_info = {
        lp["start_label"]: (feat, uf)
        for lp, feat, uf in loop_predictions
    }

    optimized_lines = []
    for line in lines:
        label_match = re.match(r"^(L\d+):$", line)
        if label_match and label_match.group(1) in loop_info:
            _, uf = loop_info[label_match.group(1)]
            annotation = f"; [OPTIMIZE] Unroll loop at {label_match.group(1)} by factor {uf}"
            optimized_lines.append(annotation)
            print(f"  {annotation}")
        optimized_lines.append(line)
        print(f"  {line}")

    # --- Save optimized TAC ---
    output_file = tac_file.replace(".txt", "_optimized.txt")
    with open(output_file, "w") as f:
        for line in optimized_lines:
            f.write(line + "\n")

    print(f"\n[ML] Optimized TAC saved to: {output_file}")
    print("[ML] Done.\n")


if __name__ == "__main__":
    main()
