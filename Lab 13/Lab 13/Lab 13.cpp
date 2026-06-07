#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace std::chrono;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

    void dfsHelper(int v, vector<bool>& visited, bool print) {
        visited[v] = true;
        if (print) cout << v << " ";

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, visited, print);
            }
        }
    }

    bool cycleHelper(int v, vector<bool>& visited, int parent) {
        visited[v] = true;

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                if (cycleHelper(neighbor, visited, v)) {
                    return true;
                }
            }
            else if (neighbor != parent) {
                return true;
            }
        }
        return false;
    }

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void DFS(int startVertex, bool print = true) {
        vector<bool> visited(V, false);
        dfsHelper(startVertex, visited, print);
        if (print) cout << endl;
    }

    void BFS(int startVertex, bool print = true) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            if (print) cout << current << " ";

            for (int neighbor : adj[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        if (print) cout << endl;
    }

    void findPath(int start, int end) {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        bool found = false;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == end) {
                found = true;
                break;
            }

            for (int neighbor : adj[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }

        if (!found) {
            cout << "No path exists between " << start << " and " << end << "." << endl;
            return;
        }

        vector<int> path;
        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        cout << "Shortest path: ";
        for (int v : path) cout << v << " ";
        cout << endl;
    }

    bool hasCycle() {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (cycleHelper(i, visited, -1)) {
                    return true;
                }
            }
        }
        return false;
    }
};

void runTests() {
    cout << " 1. Tree Test " << endl;
    Graph tree(5);
    tree.addEdge(0, 1);
    tree.addEdge(0, 2);
    tree.addEdge(1, 3);
    tree.addEdge(1, 4);

    cout << "DFS traversal (from vertex 0): "; tree.DFS(0);
    cout << "BFS traversal (from vertex 0): "; tree.BFS(0);
    cout << "Is there a cycle? " << (tree.hasCycle() ? "Yes" : "No") << endl;
    tree.findPath(3, 2);

    cout << "\n 2. Cyclic Graph Test" << endl;
    Graph cyclic(4);
    cyclic.addEdge(0, 1);
    cyclic.addEdge(1, 2);
    cyclic.addEdge(2, 3);
    cyclic.addEdge(3, 0);

    cout << "DFS traversal: "; cyclic.DFS(0);
    cout << "BFS traversal: "; cyclic.BFS(0);
    cout << "Is there a cycle? " << (cyclic.hasCycle() ? "Yes" : "No") << endl;

    cout << "\n 3. Complete Graph Test " << endl;
    Graph complete(4);
    complete.addEdge(0, 1); complete.addEdge(0, 2); complete.addEdge(0, 3);
    complete.addEdge(1, 2); complete.addEdge(1, 3); complete.addEdge(2, 3);

    cout << "Is there a cycle? " << (complete.hasCycle() ? "Yes" : "No") << endl;
    complete.findPath(0, 3);

    cout << "\n 4. Time Benchmark on a large graph" << endl;
    int V = 10000;
    Graph bigGraph(V);
    for (int i = 0; i < V - 1; i++) {
        bigGraph.addEdge(i, i + 1);
    }

    auto startDFS = high_resolution_clock::now();
    bigGraph.DFS(0, false);
    auto endDFS = high_resolution_clock::now();
    cout << "DFS execution time: " << duration_cast<microseconds>(endDFS - startDFS).count() << " us" << endl;

    auto startBFS = high_resolution_clock::now();
    bigGraph.BFS(0, false);
    auto endBFS = high_resolution_clock::now();
    cout << "BFS execution time: " << duration_cast<microseconds>(endBFS - startBFS).count() << " us" << endl;
}

int main() {
    cout << "Lab 13 graph traversal algorithms" << endl << endl;
    runTests();
    return 0;
}