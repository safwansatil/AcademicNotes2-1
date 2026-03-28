# B-Tree Simulation Documentation

This CLI tool simulates the step-by-step insertion of values into a B-Tree and prints every root-to-leaf path after each insertion.

## Code Explanation

The implementation uses a dynamic B-Tree data structure where nodes are allocated on the heap based on the user-defined order `m`.

### 1. Data Structures
- **`struct Node`**:
  - `int *keys`: An array containing the keys stored in the node.
  - `struct Node **children`: An array of pointers to the child nodes.
  - `int num_keys`: The current count of keys in the node.
  - `int is_leaf`: A flag (1 for leaf nodes, 0 for internal).

### 2. Key Algorithms

#### A. Insertion and Splitting
The simulation follows the **Lazy Splitting** approach (similar to common pedagogical implementations) to match the provided sample output:
- Values are inserted into the appropriate leaf node.
- After insertion, if a node exceeds the capacity (i.e., `num_keys == m`), it is split.
- **`splitChild`**: 
  - Calculates the median index (`(m-1)/2`).
  - Creates a new node to hold the keys and children to the right of the median.
  - Moves the median key up into the parent node.
  - Adjusts the original child node to hold keys to the left of the median.

#### B. Path Printing (`printPaths`)
A recursive function that traverses the tree:
- Builds a string representation of the current node in the format `[k1|k2|...|kn]`.
- If the node is a leaf, it prints the accumulated path.
- If not, it recursively calls itself for each child, appending ` -> ` to the path string.

### 3. Usage

1. **Compilation**:
   ```bash
   gcc BtreeSim.c -o BtreeSim
   ```
2. **Execution**:
   Run the executable and provide input in the following order:
   - Number of values `n`.
   - The `n` values themselves.
   - The order of the B-tree `m`.

**Example Input**:
```text
10
1 2 3 4 5 6 7 8 9 10
3
```

## Implementation Notes
- **Memory Management**: Nodes are allocated using `malloc`.
- **No External Libraries**: The code uses only standard I/O and memory management (`stdio.h`, `stdlib.h`), satisfying the requirement to avoid external library functions.

## Manim Animation (`simulation.py`)

A Python script is provided to visualize the B-Tree insertion process using the [Manim](https://www.manim.community/) animation engine.

### Features
- **Visual Nodes**: Each B-Tree node is represented as a series of connected rectangles.
- **Dynamic Layout**: The tree automatically repositions nodes as they split and grow.
- **Step-by-Step Animation**: Each insertion is highlighted, showing the transformation of the tree structure.

### Prerequisites
- Python 3.7+
- Manim (Install via `pip install manim`)
- FFmpeg (Required by Manim)

### Usage
Run the following command in your terminal:
```bash
manim -pql simulation.py BTreeSimulation
```
- `-p`: Preview the animation after rendering.
- `-ql`: Render in low quality for faster processing (use `-qh` for high quality).
