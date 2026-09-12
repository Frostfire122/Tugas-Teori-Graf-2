# Informatics ITS Graph Theory class Group 4

### Prim's Algorithm

  Steps:
  
  1. Start with any vertex in the graph
  2. Mark the starting vertex as part of the spanning tree
  3. Look at all edges that connect a vertex inside the tree to a vertex outside the tree.
  4. Choose the edge with the *smallest* weight.
  5. Add the chosen edge and its outside vertex to the spanning tree.
  6. Repeat steps 3–5 until all vertices are included in the spanning tree.
  7. The edges selected during the process form the minimum spanning tree.


### Kruskal's Algorithm

  Steps:
  
  1. Start with all vertices as separate components
  2. Sort all edges in increasing order of their weights
  3. Consider the edge with the *smallest* weight
  4. If adding the edge does not create a cycle:
     
  * add it to the spanning tree.
  - Else
  * skip it.
    
  
  6. Move to the next *smallest* edge.
  7. Repeat steps 4–6 until all vertices are connected.
  8. The edges selected during the process form the minimum spanning tree.

### Reverse-Delete Algorithm

  Steps:
  
  1. Start with the full connected graph containing all its original edges.
  2. Sort all edges in decreasing order of their weights.
  3. Consider the edge with the *largest* weight.
  4. Temporarily remove the edge from the graph and check if the graph remains connected:
     
  * If the graph remains connected, permanently delete the edge.
  * Else, restore the edge back to the graph.
  
  5. Move to the next *largest* edge.
  6. Repeat steps 4–5 until all remaining edges have been evaluated.
  7. The remaining connected graph forms the minimum spanning tree.
