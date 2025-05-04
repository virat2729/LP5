#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

// Graph class representing an undirected graph using adjacency list representation
class Graph {
private:
    int numVertices;          // Number of vertices
    vector<vector<int>> adj;  // Adjacency list

public:
    Graph(int vertices) : numVertices(vertices), adj(vertices) {}

    // Add an edge between two vertices
    void addEdge(int src, int dest) {
        adj[src].push_back(dest);
        adj[dest].push_back(src);
    }

    // View the graph
    void viewGraph() {
        cout << "Graph:\n";
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << " -> ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Perform Depth First Search (DFS) in parallel
    void dfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        stack<int> s;

        // Mark the start vertex as visited and push it onto the stack
        visited[startVertex] = true;
        s.push(startVertex);

        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();
            cout << currentVertex << " ";

            // Push all adjacent unvisited vertices onto the stack
            #pragma omp parallel for
            for (int neighbor : adj[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int numVertices;
    cout << "Enter the number of vertices in the graph: ";
    cin >> numVertices;

    // Create a graph with the specified number of vertices
    Graph graph(numVertices);

    int numEdges;
    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    cout << "Enter the edges (source destination):\n";
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        cin >> src >> dest;
        graph.addEdge(src, dest);
    }

    // View the graph
    graph.viewGraph();

    int startVertex;
    cout << "Enter the starting vertex for DFS: ";
    cin >> startVertex;

    cout << "Depth First Search (DFS): ";
    graph.dfs(startVertex);
    cout << endl;

    return 0;
}




// Output
// Enter the number of vertices in the graph: 6
// Enter the number of edges in the graph: 5
// Enter the edges (source destination):
// 0 1
// 0 2
// 1 3
// 2 4
// 3 5
// Graph:
// Vertex 0 -> 1 2 
// Vertex 1 -> 0 3 
// Vertex 2 -> 0 4 
// Vertex 3 -> 1 5 
// Vertex 4 -> 2 
// Vertex 5 -> 3 
// Enter the starting vertex for DFS: 2
// Depth First Search (DFS): 2 4 0 1 3 5 