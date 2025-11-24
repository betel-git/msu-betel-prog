// Bellman-Ford
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>
using std::pair;
using std::vector;
using std::queue;
using std::cout;
using std::cin;
using std::endl;
using std::min;


struct Graph {
    vector<vector<pair<int, int>>> g;

    Graph (int n = 1) {g.resize(n);}
    ~Graph () = default;

    void add_edge (int f, int t, int w) {
        f--; t--;
        g[f].emplace_back(t, w);
        //g[t].emplace_back(f, w);
    }

    vector<pair<int, int>>& operator [] (int v) {
        return g[v];
    }

    int size() {return g.size();}
};


bool bellman (Graph& g) {
    vector<int> dist(g.size(), 0);
    dist[0] = 0;
    for (int iter = 0; iter < g.size(); iter++) {
        for (int v = 0; v < g.size(); v++) {
            if (dist[v] == INT_MAX) continue;
            for (pair<int, int> u: g[v]) {
                if (dist[v] + u.second < dist[u.first]) {
                    dist[u.first] = dist[v] + u.second;
                    if (iter == g.size() - 1) {
                        return true;
                    }
                }
                //dist[u.first] = min(dist[u.first], dist[v] + u.second);
            }
        }
    }
    return false;
}


int main() {
    int n, m;
    cin >> n >> m;

    int u, v, w;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }

    if (bellman(g)) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}