#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace std::chrono;

class GraphMatrix {
public:
    vector<vector<int>> matrix;
    int numVertices;

    GraphMatrix(int vertices) {
        numVertices = vertices;
        matrix.assign(vertices, vector<int>(vertices, 0));
    }

    void addVertex() {
        numVertices++;
        for (int i = 0; i < numVertices - 1; i++) {
            matrix[i].push_back(0);
        }
        matrix.push_back(vector<int>(numVertices, 0));
    }

    void removeVertex(int v) {
        if (v >= numVertices) return;
        matrix.erase(matrix.begin() + v);
        for (int i = 0; i < matrix.size(); i++) {
            matrix[i].erase(matrix[i].begin() + v);
        }
        numVertices--;
    }

    void addEdge(int u, int v) {
        if (u < numVertices && v < numVertices) {
            matrix[u][v] = 1;
            matrix[v][u] = 1;
        }
    }

    void removeEdge(int u, int v) {
        if (u < numVertices && v < numVertices) {
            matrix[u][v] = 0;
            matrix[v][u] = 0;
        }
    }

    vector<int> getNeighbors(int v) {
        vector<int> neighbors;
        if (v < numVertices) {
            for (int i = 0; i < numVertices; i++) {
                if (matrix[v][i] == 1) {
                    neighbors.push_back(i);
                }
            }
        }
        return neighbors;
    }
};

class GraphList {
public:
    vector<vector<int>> adjList;
    int numVertices;

    GraphList(int vertices) {
        numVertices = vertices;
        adjList.resize(vertices);
    }

    void addVertex() {
        adjList.push_back({});
        numVertices++;
    }

    void removeVertex(int v) {
        if (v >= numVertices) return;

        adjList.erase(adjList.begin() + v);

        for (int i = 0; i < adjList.size(); i++) {
            adjList[i].erase(remove(adjList[i].begin(), adjList[i].end(), v), adjList[i].end());
            for (int& neighbor : adjList[i]) {
                if (neighbor > v) neighbor--;
            }
        }
        numVertices--;
    }

    void addEdge(int u, int v) {
        if (u < numVertices && v < numVertices) {
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
    }

    void removeEdge(int u, int v) {
        if (u < numVertices && v < numVertices) {
            adjList[u].erase(remove(adjList[u].begin(), adjList[u].end(), v), adjList[u].end());
            adjList[v].erase(remove(adjList[v].begin(), adjList[v].end(), u), adjList[v].end());
        }
    }

    vector<int> getNeighbors(int v) {
        if (v < numVertices) {
            return adjList[v];
        }
        return {};
    }
};

void runBenchmark() {
    int vertices = 2000;

    GraphMatrix gm(vertices);
    GraphList gl(vertices);

    cout << "1. Sparse graph test" << endl;
    cout << "Adding 2000 vertices and 2000 edges" << endl;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < vertices - 1; i++) gm.addEdge(i, i + 1);
    auto end = high_resolution_clock::now();
    cout << "Matrix (Adding): " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < vertices - 1; i++) gl.addEdge(i, i + 1);
    end = high_resolution_clock::now();
    cout << "List    (Adding): " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    cout << "\nFinding neighbors for all 2000 vertices..." << endl;
    start = high_resolution_clock::now();
    for (int i = 0; i < vertices; i++) gm.getNeighbors(i);
    end = high_resolution_clock::now();
    cout << "Matrix (Search):     " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < vertices; i++) gl.getNeighbors(i);
    end = high_resolution_clock::now();
    cout << "List   (Search):     " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    cout << "\n 2. Removing a vertex from the middle of the graph test " << endl;

    start = high_resolution_clock::now();
    gm.removeVertex(1000);
    end = high_resolution_clock::now();
    cout << "Matrix (Removing vertex): " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    gl.removeVertex(1000);
    end = high_resolution_clock::now();
    cout << "List   (Removing vertex): " << duration_cast<microseconds>(end - start).count() << " us" << endl;
    cout << " 3. Dense graph test (Complete Graph)" << endl;

    int denseVertices = 1000;
    GraphMatrix gmDense(denseVertices);
    GraphList glDense(denseVertices);

    cout << "Adding 1000 vertices and 499,500 edges..." << endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < denseVertices; i++) {
        for (int j = i + 1; j < denseVertices; j++) {
            gmDense.addEdge(i, j);
        }
    }
    end = high_resolution_clock::now();
    cout << "Matrix (Adding): " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < denseVertices; i++) {
        for (int j = i + 1; j < denseVertices; j++) {
            glDense.addEdge(i, j);
        }
    }
    end = high_resolution_clock::now();
    cout << "List   (Adding): " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    cout << "\nFinding neighbors for all 1000 vertices in DENSE graph..." << endl;
    start = high_resolution_clock::now();
    for (int i = 0; i < denseVertices; i++) gmDense.getNeighbors(i);
    end = high_resolution_clock::now();
    cout << "Matrix (Search):      " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < denseVertices; i++) glDense.getNeighbors(i);
    end = high_resolution_clock::now();
    cout << "List   (Search):      " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    cout << "\nRemoving a vertex from the middle of the DENSE graph test " << endl;
    start = high_resolution_clock::now();
    gmDense.removeVertex(500);
    end = high_resolution_clock::now();
    cout << "Matrix (Removing vertex): " << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    glDense.removeVertex(500);
    end = high_resolution_clock::now();
    cout << "List   (Removing vertex): " << duration_cast<microseconds>(end - start).count() << " us" << endl;
}

int main() {
    cout << "Laboratory 12 graph representation methods" << endl << endl;
    runBenchmark();
    return 0;
}