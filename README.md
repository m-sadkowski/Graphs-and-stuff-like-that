----- Graphs and stuff like that -----

--- Input Format ---
The first line contains an integer 𝑘, the number of graphs.
The following lines contain k graph data sets.
Each graph data set begins with an integer n, the number of vertices in the graph.
The next 𝑛 lines contain the adjacency list for each vertex. 
Each line starts with an integer 𝑠 (the number of neighbors), followed by s integers representing the neighbors of the vertex.

--- Output Format ---
For each graph, the output should contain the designated parameters in the following order:

Degree sequence (sequence of n numbers)
Number of components (number)
Bipartiteness (True/False)
Eccentricity of vertices (within the components) (True/False)
Planarity (True/False)
Vertex colors using three algorithms:
Greedy (sequence of n numbers)
Largest First (LF) (sequence of n numbers)
Smallest Last First (SLF) (sequence of n numbers)
Number of different 𝐶4 subgraphs (number)
Number of edges in the graph complement (number)
If a parameter is not implemented, output a single '?' character for that parameter.

--- Implementation Details ---
Degree Sequence
Number of Components
Bipartiteness
Eccentricity of Vertices
Planarity
Vertex Colors:
- Greedy
- LF Method
- SLF Method
Number of 𝐶4Subgraphs
Number of Graph Complement's Edges

--- Notes ---
The project avoids using the Standard Template Library (STL) as per the given requirements.
Ensure all implemented algorithms and functions are efficient and handle the input constraints effectively.
Contributions are welcome; please create a pull request for any enhancements or bug fixes.

--- License ---
This project is licensed under the MIT License. See the LICENSE file for details.
