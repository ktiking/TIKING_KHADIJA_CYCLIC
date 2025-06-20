#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

const int MAX = 100;
int graph[MAX][MAX];
int n;
bool isDirected = true;

bool detectCycleDirected() {
    vector<int> inDegree(n, 0);
    vector<int> parent(n, -1);

    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v)
            if (graph[u][v])
                inDegree[v]++;

    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (inDegree[i] == 0)
            q.push(i);

    int processed = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        processed++;

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[current][neighbor]) {
                parent[neighbor] = current;
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }
    }

    if (processed != n) {
        cout << "(DIRECTED) Cycle detected.\nCycle path: ";
        vector<bool> visited(n, false);

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                stack<int> s;
                vector<bool> recStack(n, false);
                s.push(i);

                while (!s.empty()) {
                    int node = s.top(); s.pop();

                    if (!visited[node]) {
                        visited[node] = true;
                        recStack[node] = true;

                        for (int v = 0; v < n; ++v) {
                            if (graph[node][v]) {
                                if (!visited[v]) {
                                    parent[v] = node;
                                    s.push(v);
                                } else if (recStack[v]) {
                                    vector<int> cyclePath;
                                    int temp = node;
                                    cyclePath.push_back(v);
                                    while (temp != v) {
                                        cyclePath.push_back(temp);
                                        temp = parent[temp];
                                    }
                                    cyclePath.push_back(v);

                                    for (int k = cyclePath.size() - 1; k >= 0; --k)
                                        cout << cyclePath[k] << (k != 0 ? " -> " : "");
                                    cout << endl;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    cout << "No cycle in directed graph.\n";
    return false;
}

bool detectCycleUndirected() {
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);

    for (int start = 0; start < n; ++start) {
        if (!visited[start]) {
            queue<int> q;
            visited[start] = true;
            q.push(start);

            while (!q.empty()) {
                int current = q.front();
                q.pop();

                for (int neighbor = 0; neighbor < n; ++neighbor) {
                    if (graph[current][neighbor]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            parent[neighbor] = current;
                            q.push(neighbor);
                        } else if (parent[current] != neighbor) {
                            cout << "(UNDIRECTED) Cycle detected.\nCycle path: ";
                            vector<int> cycle;
                            int a = current, b = neighbor;
                            cycle.push_back(a);
                            while (a != -1 && a != b) {
                                a = parent[a];
                                cycle.push_back(a);
                            }
                            for (int i = cycle.size() - 1; i >= 0; --i)
                                cout << cycle[i] << (i != 0 ? " -> " : "");
                            cout << neighbor << endl;
                            return true;
                        }
                    }
                }
            }
        }
    }

    cout << "No cycle in undirected graph.\n";
    return false;
}

int main() {
    n = 4;
    isDirected = true;

    int directedGraph[4][4] = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };

    int undirectedGraph[4][4] = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}
    };

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            graph[i][j] = isDirected ? directedGraph[i][j] : undirectedGraph[i][j];

    if (isDirected)
        detectCycleDirected();
    else
        detectCycleUndirected();

    return 0;
}
