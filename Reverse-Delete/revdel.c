#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define V 7  // Total vertices: A=0, B=1, C=2, D=3, E=4, F=5, G=6
#define E 12 // Total edges in the graph

// Structure representing an edge in the graph
typedef struct {
    int src, dest, weight;
    bool removed;  // Flag: true if edge is deleted, false if still active
} Edge;

//Converts a zero-based node index to a corresponding character name.
//Example: 0 -> 'A', 1 -> 'B', etc.

char nodeName(int i) {
    return 'A' + i;
}


//Comparator function for qsort to order edges in DESCENDING weight order.
//Uses source and destination vertex indices as deterministic tie-breakers 
//when weights are identical.

int compareEdgesDesc(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;

    // Primary sort: Heaviest weight first
    if (edgeB->weight != edgeA->weight) {
        return edgeB->weight - edgeA->weight; 
    }
    // Secondary tie-breaker: Compare source index
    if (edgeA->src != edgeB->src) {
        return edgeA->src - edgeB->src;
    }
    // Tertiary tie-breaker: Compare destination index
    return edgeA->dest - edgeB->dest;
}


//Depth-First Search (DFS) traversal to discover reachable vertices.
//Skips any edge where 'removed' is true. 
//@param edges Array of graph edges
//@param start Current vertex index being processed
//@param visited Array tracking visited vertices

void dfs(Edge edges[], int start, bool visited[]) {
    visited[start] = true;
    for (int i = 0; i < E; i++) {
        if (edges[i].removed) continue; // Ignore deleted edges

        int u = edges[i].src;
        int v = edges[i].dest;

        // Traverse adjacent unvisited nodes in either direction (undirected graph)
        if (u == start && !visited[v]) {
            dfs(edges, v, visited);
        } else if (v == start && !visited[u]) {
            dfs(edges, u, visited);
        }
    }
}


//Checks whether the graph remains fully connected using the current active edges.
//@param edges Array of graph edges
//@return true if all vertices are reachable from vertex 0, false otherwise

bool isConnected(Edge edges[]) {
    bool visited[V] = { false };
    
    // Start DFS traversal from node 0 ('A')
    dfs(edges, 0, visited); 

    // Verify if every vertex was reached
    for (int i = 0; i < V; i++) {
        if (!visited[i]) return false;
    }
    return true;
}


//Executes Reverse-Delete MST Algorithm:
//1. Sorts edges descending by weight.
//2. Iteratively attempts to remove each edge (heaviest first).
//3. Keeps the edge if its removal disconnects the graph (i.e., edge is a bridge).
//@param edges Array of graph edges

void reverseDeleteMST(Edge edges[]) {
    // 1. Sort all edges from heaviest to lightest
    qsort(edges, E, sizeof(Edge), compareEdgesDesc);

    printf("Step-by-step Reverse-Delete Evaluation:\n");
    printf("----------------------------------------\n");

    // 2. Process each edge starting from the heaviest
    for (int i = 0; i < E; i++) {
        edges[i].removed = true; // Temporarily remove edge

        // If removing this edge breaks connectivity, restore it
        if (!isConnected(edges)) {
            edges[i].removed = false; // Undo removal (edge is crucial)
            printf("KEPT:    %c - %c (Weight: %d)\n", 
                   nodeName(edges[i].src), nodeName(edges[i].dest), edges[i].weight);
        } else {
            // Graph is still connected without this edge
            printf("REMOVED: %c - %c (Weight: %d)\n", 
                   nodeName(edges[i].src), nodeName(edges[i].dest), edges[i].weight);
        }
    }

    // 3. Output final MST result and calculate total weight
    int totalWeight = 0;
    printf("\nFinal MST Edges:\n");
    printf("Edge \tWeight\n");
    printf("-----------------\n");
    for (int i = 0; i < E; i++) {
        if (!edges[i].removed) {
            printf("%c - %c \t%d\n", nodeName(edges[i].src), nodeName(edges[i].dest), edges[i].weight);
            totalWeight += edges[i].weight;
        }
    }
    printf("-----------------\n");
    printf("Total MST weight: %d\n", totalWeight);
}


//Main function initializes the edge array and runs the algorithm.

int main() {
    // Initial edge list containing {src, dest, weight, removed}
    Edge edges[E] = {
        {0, 1, 7, false},  // A-B
        {0, 2, 6, false},  // A-C
        {0, 5, 10, false}, // A-F
        {0, 6, 5, false},  // A-G
        {6, 5, 6, false},  // G-F
        {5, 2, 9, false},  // F-C
        {1, 3, 7, false},  // B-D
        {1, 4, 9, false},  // B-E
        {2, 4, 7, false},  // C-E
        {4, 3, 5, false},  // E-D
        {5, 4, 5, false},  // F-E
        {1, 2, 5, false}   // B-C
    };

    reverseDeleteMST(edges);

    return 0;
}