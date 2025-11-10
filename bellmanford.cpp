#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

void bellmanFord(int V, int E, int src, vector<Edge>& edges) {
    // Step 1: Initialize distances
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Step 2: Relax all edges (V-1) times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            // This is the "relaxation" step
            // If we found a path to 'u' AND
            // a shorter path to 'v' *through* 'u'
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Step 3: Check for negative weight cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "\nGraph contains a negative weight cycle!\n";
            return;
        }
    }

    // Step 4: Print the shortest distances
    cout << "\nVertex\tDistance from Source\n";
    for (int i = 0; i < V; i++)
        cout << i << "\t" << dist[i] << endl;
}

int main() {
    int V, E, src;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);
    cout << "Enter " << E << " edges (format: source destination weight):" << endl;
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    cout << "Enter source vertex: ";
    cin >> src;

    bellmanFord(V, E, src, edges);

    cout << "\nTime Complexity: O("<< V*E <<")" << endl;
    return 0;
}
