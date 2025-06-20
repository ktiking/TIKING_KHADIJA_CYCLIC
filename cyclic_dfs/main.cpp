#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
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

char nodeLabel(int index) {
    return 'A' + index;
}

void dfsTraversal(int start) {
    vector<bool> visited(N, false);
    stack<int> s;
    s.push(start);

    cout << "DFS Traversal from " << nodeLabel(start) << ": ";
    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            visited[node] = true;
            cout << nodeLabel(node) << " ";

            for (int i = N - 1; i >= 0; --i) {
                if (graph[node][i] && !visited[i])
                    s.push(i);
            }
        }
    }
    cout << endl;
}

bool dfsCycleHelper(int node, vector<bool>& visited, vector<bool>& recStack, vector<int>& path) {
    visited[node] = true;
    recStack[node] = true;
    path.push_back(node);

    for (int i = 0; i < N; ++i) {
        if (graph[node][i]) {
            if (!visited[i]) {
                if (dfsCycleHelper(i, visited, recStack, path))
                    return true;
            } else if (recStack[i]) {
                // Found cycle
                cout << "Cycle detected (DFS): ";
                auto it = find(path.begin(), path.end(), i);
                while (it != path.end())
                    cout << nodeLabel(*it++) << " -> ";
                cout << nodeLabel(i) << endl;
                return true;
            }
        }
    }

    recStack[node] = false;
    path.pop_back();
    return false;
}

bool detectCycleDFS() {
    vector<bool> visited(N, false);
    vector<bool> recStack(N, false);
    vector<int> path;

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            if (dfsCycleHelper(i, visited, recStack, path))
                return true;
        }
    }

    cout << "No cycle found (DFS).\n";
    return false;
}

int main() {
    int start = 3;

    dfsTraversal(start);
    detectCycleDFS();

    return 0;
}
