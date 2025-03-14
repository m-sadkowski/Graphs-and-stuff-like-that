# Graphs and staff like that

This project is a **Graphs and staff like that** implemented in **C++** without using the Standard Template Library (STL). It processes graphs provided in a specific input format and computes various graph parameters, such as degree sequence, number of components, bipartiteness, eccentricity, planarity, vertex coloring, and more.

---

## Input Format

The input consists of multiple graphs. The format is as follows:

1. The first line contains an integer **𝑘**, the number of graphs.
2. For each graph:
   - The first line contains an integer **𝑛**, the number of vertices.
   - The next **𝑛** lines contain the adjacency list for each vertex. Each line starts with an integer **𝑠** (the number of neighbors), followed by **𝑠** integers representing the neighbors of the vertex.

### Example Input

```
2
4
2 1 2
2 0 3
2 0 3
2 1 2
3
1 1
1 0
0
```

---

## Output Format

For each graph, the output contains the following parameters in order:

1. **Degree Sequence**: A sequence of **𝑛** numbers representing the degree of each vertex.
2. **Number of Components**: The number of connected components in the graph.
3. **Bipartiteness**: `True` if the graph is bipartite, otherwise `False`.
4. **Eccentricity of Vertices**: The eccentricity of each vertex within its component.
5. **Planarity**: `True` if the graph is planar, otherwise `False`.
6. **Vertex Colors**:
   - **Greedy**: A sequence of **𝑛** numbers representing vertex colors using the Greedy algorithm.
   - **Largest First (LF)**: A sequence of **𝑛** numbers representing vertex colors using the LF method.
   - **Smallest Last First (SLF)**: A sequence of **𝑛** numbers representing vertex colors using the SLF method.
7. **Number of 𝐶4 Subgraphs**: The number of distinct 4-cycle subgraphs in the graph.
8. **Number of Graph Complement's Edges**: The number of edges in the complement of the graph.

If a parameter is not implemented, output a single `?` character for that parameter.

### Example Output

```
4 4 4 4
1
True
2 2 2 2
True
0 1 2 3
0 1 2 3
0 1 2 3
2
2
3
1
True
1 1 1
?
?
?
?
?
```

---

## Getting Started

### Prerequisites

- A C++ compiler (e.g., `g++`).
- Basic knowledge of graph theory and algorithms.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/m-sadkowski/Graph-Analyzer.git
   cd Graph-Analyzer
   ```

2. Compile the program:
   ```bash
   g++ -o graph_analyzer main.cpp
   ```

3. Run the program:
   ```bash
   ./graph_analyzer
   ```

---

## Usage

1. Provide the input in the specified format.
2. The program will compute and output the required graph parameters.

### Example Input

```
2
4
2 1 2
2 0 3
2 0 3
2 1 2
3
1 1
1 0
0
```

### Example Output

```
4 4 4 4
1
True
2 2 2 2
True
0 1 2 3
0 1 2 3
0 1 2 3
2
2
3
1
True
1 1 1
?
?
?
?
?
```

---

## Notes

- **No STL Usage**: The project avoids using the C++ Standard Template Library (STL) as per the requirements.
- **Efficiency**: Ensure all implemented algorithms are efficient and handle input constraints effectively.
- **Contributions**: Contributions are welcome! Please create a pull request for any enhancements or bug fixes.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Contact

For questions or feedback, please reach out to [m-sadkowski](https://github.com/m-sadkowski).

---

Enjoy analyzing graphs with this tool! 📊