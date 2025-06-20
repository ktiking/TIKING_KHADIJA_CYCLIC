#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

const int N = 7;

int graph[N][N] = {
    {0, 0, 1, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0}, 
    {1, 1, 0, 0, 0, 1, 0}, 
    {1, 0, 0, 0, 1, 0, 0}, 
    {0, 0, 1, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0}  
};

char nodeLabel(int i) {
    return 'A' + i;
}
bool detectCycleBFS(int start) {
    vector<bool> visited(N, false);
    vector<int> parent(N, -1);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front(); q.pop();

        for (int neighbor = 0; neighbor < N; ++neighbor) {
            if (graph[current][neighbor]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                } else {
                    cout << "Cycle detected (BFS): ";

                    vector<int> cycle;
                    cycle.push_back(neighbor);

                    int trace = current;
                    while (trace != neighbor && trace != -1) {
                        cycle.push_back(trace);
                        trace = parent[trace];
                    }
                    cycle.push_back(neighbor);

                    for (int i = 0; i < cycle.size(); ++i) {
                        cout << nodeLabel(cycle[i]);
                        if (i < cycle.size() - 1)
                            cout << " -> ";
                    }
                    cout << endl;
                    return true;
                }
            }
        }
    }

    cout << "No cycle found (BFS).\n";
    return false;
}

void bfsTraversal(int start) {
    vector<bool> visited(N, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "BFS Traversal from " << nodeLabel(start) << ": ";
    while (!q.empty()) {
        int node = q.front(); q.pop();
        cout << nodeLabel(node) << " ";

        for (int i = 0; i < N; i++) {
            if (graph[node][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

int main() {
    int start = 3;
    bfsTraversal(start);
    detectCycleBFS(start);
    return 0;
}
