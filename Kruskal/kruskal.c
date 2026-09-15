#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 7 // Total vertices: A=0, B=1, C=2, D=3, E=4, F=5, G=6
#define E 12 // Total edges in the graph

// Structure to represent an edge with source, destination, and weight
typedef struct {
    int src, dest, weight;
} Edge;

// Structure for Disjoint Set Union (DSU) to track connected components
typedef struct {
    int parent[V];
    int rank[V];
} DisjointSet;

// Converts a zero-based node index to a corresponding letter ('A', 'B', etc.)
char nodeName(int i) {
    return 'A' + i;
}

// Initializes each node to be its own parent with a rank of 0
void makeSet(DisjointSet *ds) {
    for (int i = 0; i < V; i++) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
}

// Finds the root representative of a set containing node i (uses path compression)
int find(DisjointSet *ds, int i) {
    if (ds->parent[i] != i) {
        ds->parent[i] = find(ds, ds->parent[i]); // Flatten path directly to root
    }
    return ds->parent[i];
}

// Unites two disjoint sets by rank to keep the tree shallow
void unionSets(DisjointSet *ds, int x, int y) {
    int rootX = find(ds, x);
    int rootY = find(ds, y);

    if (rootX == rootY) return; // Already in the same component

    // Attach smaller rank tree under root of higher rank tree
    if (ds->rank[rootX] < ds->rank[rootY]) {
        ds->parent[rootX] = rootY;
    } else if (ds->rank[rootX] > ds->rank[rootY]) {
        ds->parent[rootY] = rootX;
    } else {
        ds->parent[rootY] = rootX;
        ds->rank[rootX]++;
    }
}

// Comparator function for qsort to order edges in ASCENDING weight order
int compareEdges(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;

    // Primary sort: Lightest weight first
    if (edgeA->weight != edgeB->weight) {
        return edgeA->weight - edgeB->weight;
    }
    // Secondary tie-breaker: Compare source node index
    if (edgeA->src != edgeB->src) {
        return edgeA->src - edgeB->src;
    }
    // Tertiary tie-breaker: Compare destination node index
    return edgeA->dest - edgeB->dest;
}

// Executes Kruskal's MST algorithm
void kruskalMST(Edge edges[]) {
    // 1. Sort edges by weight ascending with stable tie-breaking
    qsort(edges, E, sizeof(Edge), compareEdges);

    DisjointSet ds;
    makeSet(&ds);

    int resultCount = 0;
    int totalWeight = 0;

    printf("Edge \tWeight\n");
    printf("-----------------\n");

    // 2. Process sorted edges in order, adding valid non-cycling edges to MST
    for (int i = 0; i < E && resultCount < V - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;

        int rootU = find(&ds, u);
        int rootV = find(&ds, v);

        // If roots are different, adding this edge will not form a cycle
        if (rootU != rootV) {
            // Print edge in real-time as it is accepted into the tree
            printf("%c - %c \t%d\n", nodeName(u), nodeName(v), edges[i].weight);
            totalWeight += edges[i].weight;
            resultCount++;
            unionSets(&ds, rootU, rootV);
        }
    }

    // Check if a complete spanning tree was successfully built
    if (resultCount < V - 1) {
        printf("Graph is disconnected. MST cannot include all nodes.\n");
    }

    printf("-----------------\n");
    printf("Total MST weight: %d\n", totalWeight);
}

// Main entry point
int main() {
    // Initial edge list: {source, destination, weight}
    Edge edges[E] = {
        {0, 1, 7},  // A-B
        {0, 2, 6},  // A-C
        {0, 5, 10}, // A-F
        {0, 6, 5},  // A-G
        {6, 5, 6},  // G-F
        {5, 2, 9},  // F-C
        {1, 3, 7},  // B-D
        {1, 4, 9},  // B-E
        {2, 4, 7},  // C-E
        {4, 3, 5},  // E-D
        {5, 4, 5},  // F-E
        {1, 2, 5}   // B-C
    };

    printf("Kruskal's MST Traversal Order:\n\n");
    kruskalMST(edges);

    return 0;
}