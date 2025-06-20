#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAX = 100;
int graph[MAX][MAX];
int n;
bool isDirected = true;

bool dfsDirected(int node, vector<bool>& visited, vector<bool>& recStack, vector<int>& parent) {
    visited[node] = true;
    recStack[node] = true;

    for (int v = 0; v < n; v++) {
        if (graph[node][v]) {
            if (!visited[v]) {
                parent[v] = node;
                if (dfsDirected(v, visited, recStack, parent))
                    return true;
            } else if (recStack[v]) {
                cout << "(DIRECTED) Cycle detected: ";
                int current = node;
                stack<int> cycleStack;
                cycleStack.push(current);
                while (current != v) {
                    current = parent[current];
                    cycleStack.push(current);
                }
                while (!cycleStack.empty()) {
                    cout << cycleStack.top() << " -> ";
                    cycleStack.pop();
                }
                cout << v << endl;
                return true;
            }
        }
    }

    recStack[node] = false;
    return false;
}

bool dfsUndirected(int node, vector<bool>& visited, int parent) {
    visited[node] = true;
    for (int v = 0; v < n; v++) {
        if (graph[node][v]) {
            if (!visited[v]) {
                if (dfsUndirected(v, visited, node))
                    return true;
            } else if (v != parent) {
                cout << "(UNDIRECTED) Cycle detected: " << node << " -> " << v << endl;
                return true;
            }
        }
    }
    return false;
}

int main() {
    n = 4;
    isDirected = true;
    int sampleDirected[4][4] = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };
    int sampleUndirected[4][4] = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}
    };

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            graph[i][j] = isDirected ? sampleDirected[i][j] : sampleUndirected[i][j];

    if (isDirected) {
        vector<bool> visited(n, false), recStack(n, false);
        vector<int> parent(n, -1);
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                if (dfsDirected(i, visited, recStack, parent))
                    return 0;
            }
        }
        cout << "(DIRECTED) No cycle found.\n";
    } else {
        vector<bool> visited(n, false);
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                if (dfsUndirected(i, visited, -1))
                    return 0;
            }
        }
        cout << "(UNDIRECTED) No cycle found.\n";
    }

    return 0;
}
