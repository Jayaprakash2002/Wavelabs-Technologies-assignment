
#include <iostream>
#include <vector>

using namespace std;

void dfs(int node, int parent, int& time, vector<vector<int>>& graph, vector<int>& disc, vector<int>& low, vector<vector<int>>& result) {
    disc[node] = low[node] = ++time;

    for (int neighbor : graph[node]) {
        if (neighbor == parent)
            continue; 

        if (disc[neighbor] == 0) {
            dfs(neighbor, node, time, graph, disc, low, result);
            low[node] = min(low[node], low[neighbor]);

            if (low[neighbor] > disc[node]) {
                result.push_back({node, neighbor});
            }
        } else {
            low[node] = min(low[node], disc[neighbor]);
        }
    }
}

vector<vector<int>> findCriticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> graph(n);
    vector<int> disc(n, 0);
    vector<int> low(n, 0);
    vector<vector<int>> result;

    for (const auto& conn : connections) {
        int u = conn[0];
        int v = conn[1];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int time = 0;
    dfs(0, -1, time, graph, disc, low, result);

    return result;
}

int main() {
    int n = 4;
    vector<vector<int>> connections{{0, 1}, {1, 2}, {2, 0}, {1, 3}};

    vector<vector<int>> criticalConnections = findCriticalConnections(n, connections);

    cout << "Critical Connections:\n";
    for (const auto& conn : criticalConnections) {
        cout << conn[0] << " -- " << conn[1] << "\n";
    }

    return 0;
}
