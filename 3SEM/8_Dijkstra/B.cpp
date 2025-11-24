// Dijkstra
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
#include <set>
using std::vector;
using std::queue;
using std::pair;
using std::cout;
using std::cin;
using std::endl;
using std::min;
using std::set;


struct Graph {
    vector<vector<pair<int, int>>> g;

    Graph (int n = 1) {g.resize(n);}
    ~Graph () = default;

    void add_edge (int f, int t, int w) {
        f--; t--;
        g[f].emplace_back(t, w);
        g[t].emplace_back(f, w);
    }

    vector<pair<int, int>>& operator [] (int v) {
        return g[v];
    }

    int size() {return g.size();}
};


/* int min_d (vector<int>& d, vector<bool>& used) {
	int ans = -1;
	for (int v = 0; v < d.size(); v++) {
		if (used[v] || d[v] == INF) continue;
		if (ans == -1 || d[ans] > d[v]) {
			ans = v;
		}
	}
	return ans;
} */


/* void dijkstra (Graph& g, vector<int>& dist) {
	vector<bool> used(g.size());
	dist[0] = 0;
	for (int i = 0; i < g.size(); i++) {
		int v = min_d(dist, used);
		used[v] = 1;
		if (v == -1) break;
		for (pair<int, int> u: g[v]) {
			dist[u.first] = min(dist[u.first], dist[v] + u.second);
		}
	}
    
    for (int i = 0; i < g.size(); i++) {
        if (!used[i]) dist[i] = -1;
    }
} */


void dijkstra (Graph& g, vector<int>& dist) {
	set<pair<int, int>> cur;
	dist[0] = 0;
	cur.insert({0, 0});
	while (cur.size() != 0) {
		int v = cur.begin()->second;
		cur.erase({dist[v], v});
		for (pair<int, int> u: g[v]) {
			if (dist[u.first] > dist[v] + u.second) {
				cur.erase({dist[u.first], u.first});
				dist[u.first] = dist[v] + u.second;
				cur.insert({dist[u.first], u.first});
			}
		}
	}
    for (int i = 0; i < g.size(); i++) {
        if (dist[i] == INT_MAX) dist[i] = -1;
    }
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

    vector<int> dist(g.size(), INT_MAX);
    dijkstra(g, dist);
    for (int j = 0; j < n; j++) {
        cout << dist[j] << " ";
    }
    cout << endl;

    return 0;
}
