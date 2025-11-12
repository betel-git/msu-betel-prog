// Дан неориентированный граф с n вершинами и m рёбрами. Найти количество его компонент связности.
#include <iostream>
#include <vector>
using std::vector;
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

};


int dfs (Graph &g, int v, bool* used) {
    used[v] = true;
    int sm = 1;
    for (int u: g[v]) {
        if (!used[u]) {
            sm += dfs(g, u, used);
        }
    }
    return sm; // возвращаем количество вершин в компоненте связности
}


int main() {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    int f, t;
    for (int i = 0; i < m; i++) {
        cin >> f >> t;
        g.add_edge(f, t);
    }

    bool* used = new bool[n];
    for (int i = 0; i < n; i++) used[i] = false;

    int res = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            res++; 
            dfs(g, i, used);
        }
    }

    delete[] used;
    cout << res << endl;
    return 0;
}
