#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Edge structure
struct Edge {
    int source, destination, weight;
};

// Comparison function for sorting edges
bool compareEdges(Edge a, Edge b) { 
    return a.weight < b.weight; 
}

// Find function for Union-Find
int find(vector<int>& parent, int vertex) {
    if (parent[vertex] != vertex) {
        parent[vertex] = find(parent, parent[vertex]);
    }
    return parent[vertex];
}

// Union function for Union-Find
void unionSet(vector<int>& parent, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    parent[xroot] = yroot;
}

// Kruskal's Algorithm
vector<Edge> kruskalMST(vector<Edge>& edges, int numVertices) 
{
    // Sort the edges in ascending order of their weights
    sort(edges.begin(), edges.end(), compareEdges);

    // Initialize the parent array for Union-Find
    vector<int> parent(numVertices);
    for (int i = 0; i < numVertices; i++) {
        parent[i] = i;
    }

    // Initialize the MST vector
    vector<Edge> mst;

    // Iterate through the sorted edges and add them to the MST
    for (const auto& edge : edges) {
        int sourceRoot = find(parent, edge.source);
        int destinationRoot = find(parent, edge.destination);
        if (sourceRoot != destinationRoot) {
            mst.push_back(edge);
            unionSet(parent, sourceRoot, destinationRoot);
        }
    }
    return mst;
}

int main() {
    // Example graph edges
    vector<Edge> edges = {
        {0, 1, 3}, {0, 3, 5}, {1, 3, 2}, {3, 4, 4}, {1, 4, 1}, 
        {1, 2, 9}, {2, 4, 8}, {2, 5, 3}, {4, 5, 1}
    };
    
    int numVertices = 6;  // Correct number of vertices
    
    // Find the MST
    vector<Edge> mst = kruskalMST(edges, numVertices);

    // Print the MST
    cout << "Minimum Spanning Tree:\n";
    for (const auto& edge : mst) {
        cout << "Edge: " << edge.source << " - " << edge.destination << ", Weight: " << edge.weight << "\n";
    }
    
    return 0;
}
