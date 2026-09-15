#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 7 // Total number of vertices: A=0, B=1, C=2, D=3, E=4, F=5, G=6
#define INF INT_MAX

//Converts a 0-based integer index into its corresponding uppercase letter.
//Example: 0 -> 'A', 1 -> 'B', etc.
 
char nodeName(int i) {
    return 'A' + i;
}

//Searches for the unvisited vertex with the minimum key value (cheapest edge).
//@param key Array holding the minimum weight connection for each vertex
//@param mstSet Array tracking which vertices are already included in the MST
//@return Index of the unvisited vertex with the smallest key value, or -1 if unreachable

int minKey(int key[], bool mstSet[]) {
    int min = INF, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

//Constructs and prints the Minimum Spanning Tree (MST) using Prim's algorithm.
//Starting at vertex 0 ('A'), it greedily selects the minimum weight edge 
//connecting the current tree to an unvisited vertex. 
//@param graph 2D adjacency matrix representing weighted edges between vertices

void primMST(int graph[V][V]) {
    int parent[V];  // Stores the parent node for each vertex in the resulting MST
    int key[V];     // Holds the minimum edge weight required to reach each vertex
    bool mstSet[V]; // Keeps track of vertices already added to the MST

    // Initialize all keys as infinity and mark all vertices as unvisited
    for (int i = 0; i < V; i++) {
        key[i] = INF;
        mstSet[i] = false;
        parent[i] = -1;
    }

    // Always start MST construction from Node A (index 0)
    key[0] = 0;

    printf("Edge \tWeight\n");
    printf("-----------------\n");

    int totalWeight = 0;

    // Process all V vertices to build the tree
    for (int count = 0; count < V; count++) {
        // Pick the unvisited vertex with the smallest edge weight connection
        int u = minKey(key, mstSet);

        // If no reachable vertex is found, the graph is disconnected
        if (u == -1) {
            printf("Graph is disconnected.\n");
            break;
        }

        // Mark the chosen vertex as included in the MST
        mstSet[u] = true;

        // Print the edge in real-time as it gets added (skips the root node A)
        if (parent[u] != -1) {
            printf("%c - %c \t%d\n", nodeName(parent[u]), nodeName(u), graph[u][parent[u]]);
            totalWeight += graph[u][parent[u]];
        }

        // Update key values and parent indices for adjacent unvisited vertices
        for (int v = 0; v < V; v++) {
            // graph[u][v] is non-zero only for adjacent vertices
            // Update key only if the edge weight is smaller than the current key[v]
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("-----------------\n");
    printf("Total MST weight: %d\n", totalWeight);
}

    //Main entry point. Defines the graph's adjacency matrix and calls the Prim's MST function.
 
int main() {
    // Adjacency matrix representation of the weighted graph
    int graph[V][V] = {
        // A   B   C   D   E   F   G
        {  0,  7,  6,  0,  0, 10,  5 }, // A
        {  7,  0,  5,  7,  9,  0,  0 }, // B
        {  6,  5,  0,  0,  7,  9,  0 }, // C
        {  0,  7,  0,  0,  5,  0,  0 }, // D
        {  0,  9,  7,  5,  0,  5,  0 }, // E
        { 10,  0,  9,  0,  5,  0,  6 }, // F
        {  5,  0,  0,  0,  0,  6,  0 }  // G
    };

    printf("Prim's MST Traversal Order:\n\n");
    primMST(graph);

    return 0;
}