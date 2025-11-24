// BFS
#include <iostream>
#include <vector>
#include <queue>
using std::vector;
using std::queue;
using std::cout;
using std::cin;
using std::endl;


struct Graph {
    vector<vector<int>> g;

    Graph (int n = 1) {g.resize(n);}
    ~Graph () = default;

    void add_edge (int f, int t) {
        f--; t--;
        g[f].push_back(t);
        g[t].push_back(f);
    }

    vector<int>& operator [] (int v) {
        return g[v];
    }

    int size() {return g.size();}
};


void bfs (Graph& g, vector<int>& dist) {
    int s = 0;
	vector<bool> used(g.size());
	queue<int> q;
	q.push(s);
	used[s] = true;
	while (q.size() > 0) {
		int v = q.front();
		q.pop();
		for (int u: g[v]) {
			if (!used[u]) {
				dist[u] = dist[v] + 1;
				q.push(u);
				used[u] = true;
			}
		}
	}
    for (int i = 0; i < g.size(); i++) {
        if (!used[i]) dist[i] = -1;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    int u, v;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        g.add_edge(u, v);
    }

    vector<int> dist(g.size(), 0);
    bfs(g, dist);
    for (int j = 0; j < n; j++) {
        cout << dist[j] << " ";
    }
    cout << endl;

    return 0;
}