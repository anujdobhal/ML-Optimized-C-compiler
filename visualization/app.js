// ML-Optimized C Compiler Dashboard Application JS

const API_BASE = "http://localhost:8000";

// Canvas & Tree State
const canvas = document.getElementById('tree-canvas');
const ctx = canvas.getContext('2d');
const container = document.getElementById('tree-container');

let astData = null;
let zoomLevel = 1.0;
let offsetX = 0;
let offsetY = 0;
let isDragging = false;
let startX, startY;
let nodePositions = [];

// Performance Chart reference
let perfChart = null;

// Initialize Canvas Sizing
function resizeCanvas() {
    canvas.width = container.clientWidth;
    canvas.height = container.clientHeight;
    drawTree();
}

window.addEventListener('resize', resizeCanvas);

// Canvas Mouse Events for Dragging & Zooming
canvas.addEventListener('mousedown', (e) => {
    isDragging = true;
    startX = e.clientX - offsetX;
    startY = e.clientY - offsetY;
    canvas.style.cursor = 'grabbing';
});

window.addEventListener('mouseup', () => {
    isDragging = false;
    canvas.style.cursor = 'grab';
});

canvas.addEventListener('mousemove', (e) => {
    if (!isDragging) return;
    offsetX = e.clientX - startX;
    offsetY = e.clientY - startY;
    drawTree();
});

canvas.addEventListener('wheel', (e) => {
    e.preventDefault();
    const zoomIntensity = 0.05;
    const mouseX = e.clientX - canvas.getBoundingClientRect().left;
    const mouseY = e.clientY - canvas.getBoundingClientRect().top;
    
    // Zoom centered on mouse
    const zoomFactor = e.deltaY < 0 ? (1 + zoomIntensity) : (1 - zoomIntensity);
    
    offsetX = mouseX - (mouseX - offsetX) * zoomFactor;
    offsetY = mouseY - (mouseY - offsetY) * zoomFactor;
    zoomLevel *= zoomFactor;
    
    // Boundary check
    zoomLevel = Math.max(0.2, Math.min(zoomLevel, 3.0));
    drawTree();
});

function resetZoom() {
    if (!astData) return;
    zoomLevel = 0.85;
    offsetX = canvas.width / 2;
    offsetY = 40;
    drawTree();
}

// ==================== AST TREE RENDERING ====================

function drawTree() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    if (!astData) return;

    ctx.save();
    ctx.translate(offsetX, offsetY);
    ctx.scale(zoomLevel, zoomLevel);

    nodePositions = [];
    
    // 1. Calculate layout positions
    // Node spacing variables
    const levelHeight = 65;
    const siblingSpacing = 85;
    
    // Helper to calculate subtree width
    function computeSubtreeWidth(node) {
        if (!node.children || node.children.length === 0) {
            node.width = siblingSpacing;
            return node.width;
        }
        let totalWidth = 0;
        for (let child of node.children) {
            totalWidth += computeSubtreeWidth(child);
        }
        node.width = totalWidth;
        return node.width;
    }

    computeSubtreeWidth(astData);

    // Helper to assign positions recursively
    function assignPositions(node, x, depth) {
        node.x = x;
        node.y = depth * levelHeight;
        
        nodePositions.push({
            x: node.x,
            y: node.y,
            name: node.name
        });

        if (node.children && node.children.length > 0) {
            let startX = x - node.width / 2;
            for (let child of node.children) {
                let childX = startX + child.width / 2;
                assignPositions(child, childX, depth + 1);
                startX += child.width;
            }
        }
    }

    assignPositions(astData, 0, 0);

    // 2. Draw connections (lines)
    function drawConnections(node) {
        if (node.children) {
            for (let child of node.children) {
                ctx.beginPath();
                ctx.moveTo(node.x, node.y + 12); // From bottom of parent
                ctx.bezierCurveTo(
                    node.x, node.y + 35,
                    child.x, child.y - 35,
                    child.x, child.y - 12
                );
                ctx.strokeStyle = 'rgba(6, 182, 212, 0.4)';
                ctx.lineWidth = 2;
                ctx.stroke();
                drawConnections(child);
            }
        }
    }
    drawConnections(astData);

    // 3. Draw nodes (rectangles/capsules)
    for (let pos of nodePositions) {
        // Draw capsule background
        ctx.font = 'bold 11px Inter, sans-serif';
        const textWidth = ctx.measureText(pos.name).width;
        const boxWidth = Math.max(textWidth + 24, 70);
        const boxHeight = 24;

        // Gradient for nodes
        const grad = ctx.createLinearGradient(pos.x - boxWidth/2, pos.y, pos.x + boxWidth/2, pos.y);
        if (pos.name.startsWith("FUNCTION")) {
            grad.addColorStop(0, '#8b5cf6'); // Violet
            grad.addColorStop(1, '#ec4899');
        } else if (pos.name.startsWith("WHILE") || pos.name.startsWith("FOR") || pos.name.startsWith("DOWHILE")) {
            grad.addColorStop(0, '#f59e0b'); // Yellow/Amber for loops
            grad.addColorStop(1, '#d97706');
        } else if (pos.name.startsWith("DECL") || pos.name.startsWith("ASSIGN")) {
            grad.addColorStop(0, '#3b82f6'); // Blue
            grad.addColorStop(1, '#1d4ed8');
        } else {
            grad.addColorStop(0, '#1f2937'); // Gray/Dark for rest
            grad.addColorStop(1, '#111827');
        }

        ctx.beginPath();
        ctx.roundRect(pos.x - boxWidth / 2, pos.y - boxHeight / 2, boxWidth, boxHeight, 6);
        ctx.fillStyle = grad;
        ctx.fill();

        // Node border
        ctx.strokeStyle = 'rgba(255, 255, 255, 0.15)';
        ctx.lineWidth = 1;
        ctx.stroke();

        // Node Text
        ctx.fillStyle = '#ffffff';
        ctx.textAlign = 'center';
        ctx.textBaseline = 'middle';
        ctx.fillText(pos.name, pos.x, pos.y + 0.5);
    }

    ctx.restore();
}


// ==================== API / INTERACTIVE METHODS ====================

function logToTerminal(msg, isError = false) {
    const logger = document.getElementById("compiler-log");
    const timestamp = new Date().toLocaleTimeString();
    const cleanMsg = msg.replace(/\uFFFD/g, '-'); // replace missing glyph symbol if present
    logger.innerHTML = `<span style="color: #6b7280;">[${timestamp}]</span> ` +
        `<span style="color: ${isError ? '#ef4444' : '#22c55e'};">${cleanMsg}</span>`;
}

function updateSyntaxBadge(isValid, text) {
    const badge = document.getElementById("validation-status");
    badge.className = "status-badge " + (isValid ? "badge-valid" : "badge-invalid");
    badge.innerText = text;
}

// 1. Generate Parse Tree Action
async function generateParseTree() {
    logToTerminal("[SYSTEM] Compiling and generating Abstract Syntax Tree...");
    const code = document.getElementById("source-code").value;

    try {
        const res = await fetch(`${API_BASE}/api/compile`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ code })
        });
        const data = await res.json();

        if (data.success) {
            astData = data.ast;
            updateSyntaxBadge(true, "✓ Syntax Valid");
            logToTerminal("Parsing completed successfully. Tree rendered.");
            
            // Hide empty message
            document.getElementById("tree-empty-msg").style.display = "none";
            
            // Draw AST
            resizeCanvas();
            resetZoom();
        } else {
            updateSyntaxBadge(false, "✗ Syntax Invalid");
            logToTerminal("Parsing failed:\n" + data.error, true);
            astData = null;
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            document.getElementById("tree-empty-msg").style.display = "block";
            document.getElementById("tree-empty-msg").innerText = "Syntax Error. See compilation logs.";
        }
    } catch (err) {
        logToTerminal("Network / Server connection failed: " + err.message, true);
    }
}

// 2. Generate IR Action
async function generateIR() {
    logToTerminal("[SYSTEM] Generating Three-Address Intermediate Representation...");
    const code = document.getElementById("source-code").value;

    try {
        const res = await fetch(`${API_BASE}/api/compile`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ code })
        });
        const data = await res.json();

        if (data.success) {
            updateSyntaxBadge(true, "✓ Syntax Valid");
            document.getElementById("ir-output").innerText = data.tac;
            document.getElementById("original-ir-opt").innerText = data.tac;
            logToTerminal("TAC Intermediate Representation generated successfully.");
            
            // Scroll IR element into view
            document.getElementById("ir-output").scrollIntoView({ behavior: 'smooth' });
        } else {
            updateSyntaxBadge(false, "✗ Syntax Invalid");
            logToTerminal("Failed to generate IR. Parsing error:\n" + data.error, true);
            document.getElementById("ir-output").innerText = "; Generation failed. Correct compilation errors first.";
        }
    } catch (err) {
        logToTerminal("Network / Server connection failed: " + err.message, true);
    }
}

// 3. Run ML Optimization Action
async function runMLOptimization() {
    logToTerminal("[SYSTEM] Triggering compilation and initiating ML Loop Optimization...");
    const code = document.getElementById("source-code").value;

    try {
        // Step A: Re-compile first to make sure tac.txt matches current editor state
        const compRes = await fetch(`${API_BASE}/api/compile`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ code })
        });
        const compData = await compRes.json();

        if (!compData.success) {
            updateSyntaxBadge(false, "✗ Syntax Invalid");
            logToTerminal("ML Optimization cancelled due to compilation failure:\n" + compData.error, true);
            return;
        }

        // Step B: Run ML Optimizer
        logToTerminal("[SYSTEM] Running Random Forest classifier on compiler features...");
        const optRes = await fetch(`${API_BASE}/api/optimize`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' }
        });
        const optData = await optRes.json();

        if (optData.success) {
            logToTerminal("ML Optimization complete. Loop parameters resolved.");
            
            // Populate Feature Table
            populateFeatureTable(optData.predictions);
            
            // Populate IR Displays
            document.getElementById("original-ir-opt").innerText = compData.tac;
            document.getElementById("unrolled-ir-opt").innerText = optData.unrolled_ir;
            
            // Populate Comparison Table
            populateComparisonTable(optData.comparison_stats);
            
            // Render Graph
            renderPerformanceChart(optData.comparison_stats);
            
            // Scroll to comparison section
            document.getElementById("unrolled-ir-opt").scrollIntoView({ behavior: 'smooth' });
        } else {
            logToTerminal("ML Optimizer failed:\n" + optData.error, true);
        }
    } catch (err) {
        logToTerminal("Network / Server connection failed: " + err.message, true);
    }
}

// Helper to fill static feature table
function populateFeatureTable(predictions) {
    const tbody = document.getElementById("feature-table-body");
    tbody.innerHTML = "";

    if (!predictions || predictions.length === 0) {
        tbody.innerHTML = `<tr><td colspan="6" style="text-align: center; font-style: italic;">No loops found in code to extract features from.</td></tr>`;
        return;
    }

    predictions.forEach(p => {
        tbody.innerHTML += `
            <tr>
                <td style="color: #ffffff; font-weight: 600;">Loop ${p.label}</td>
                <td class="highlight-val">${p.depth}</td>
                <td>${p.instructions}</td>
                <td>${p.mem_ops}</td>
                <td>${p.branches}</td>
                <td>${p.dependencies}</td>
            </tr>
        `;
    });
}

// Helper to fill before/after comparison table
function populateComparisonTable(stats) {
    const tbody = document.getElementById("comparison-table-body");
    tbody.innerHTML = "";

    if (!stats || stats.length === 0) {
        tbody.innerHTML = `<tr><td colspan="9" style="text-align: center; font-style: italic;">No comparison metrics available.</td></tr>`;
        return;
    }

    stats.forEach(s => {
        tbody.innerHTML += `
            <tr>
                <td style="color: #ffffff; font-weight: 600;">Loop ${s.label}</td>
                <td class="highlight-val">${s.unroll_factor}x</td>
                <td>${s.orig_iterations}</td>
                <td style="color: #10b981;">${s.unrolled_iterations}</td>
                <td>${s.orig_branches}</td>
                <td style="color: #10b981;">${s.unrolled_branches}</td>
                <td>${s.orig_cycles}</td>
                <td style="color: #10b981; font-weight: 600;">${s.unrolled_cycles}</td>
                <td><span class="speedup-badge">+${s.speedup}% Speedup</span></td>
            </tr>
        `;
    });
}

// Render dynamic performance comparison bar chart
function renderPerformanceChart(stats) {
    const ctxChart = document.getElementById('performance-chart').getContext('2d');
    
    if (perfChart) {
        perfChart.destroy();
    }

    if (!stats || stats.length === 0) {
        return;
    }

    const labels = stats.map(s => `Loop ${s.label} (${s.unroll_factor}x)`);
    const origData = stats.map(s => s.orig_cycles);
    const unrolledData = stats.map(s => s.unrolled_cycles);

    perfChart = new Chart(ctxChart, {
        type: 'bar',
        data: {
            labels: labels,
            datasets: [
                {
                    label: 'Original Execution Cost (Est. Cycles)',
                    data: origData,
                    backgroundColor: 'rgba(239, 68, 68, 0.65)',
                    borderColor: 'rgba(239, 68, 68, 1)',
                    borderWidth: 1.5,
                    borderRadius: 4
                },
                {
                    label: 'ML-Unrolled Execution Cost (Est. Cycles)',
                    data: unrolledData,
                    backgroundColor: 'rgba(16, 185, 129, 0.65)',
                    borderColor: 'rgba(16, 185, 129, 1)',
                    borderWidth: 1.5,
                    borderRadius: 4
                }
            ]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            scales: {
                y: {
                    beginAtZero: true,
                    grid: {
                        color: 'rgba(255, 255, 255, 0.05)'
                    },
                    ticks: {
                        color: '#9ca3af'
                    }
                },
                x: {
                    grid: {
                        color: 'rgba(255, 255, 255, 0.05)'
                    },
                    ticks: {
                        color: '#9ca3af'
                    }
                }
            },
            plugins: {
                legend: {
                    labels: {
                        color: '#f3f4f6',
                        font: {
                            family: 'Outfit'
                        }
                    }
                },
                tooltip: {
                    callbacks: {
                        label: function(context) {
                            let label = context.dataset.label || '';
                            if (label) {
                                label += ': ';
                            }
                            if (context.parsed.y !== null) {
                                label += context.parsed.y + ' cycles';
                            }
                            return label;
                        }
                    }
                }
            }
        }
    });
}
