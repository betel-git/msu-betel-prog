// Имеется неориентированный граф, состоящий из N вершин и M рёбер. 
// Необходимо проверить, является ли граф деревом. 
// Напомним, что дерево  — это связный граф, в котором нет циклов 
// (следовательно, между любой парой вершин существует ровно один простой путь).
// Граф называется связным, если от одной вершины существует путь до любой другой.
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


void dfs (Graph &g, int v, bool* used) { // просто помечаем посещённые вершины
    used[v] = true;
    for (int u: g[v]) {
        if (!used[u]) {
            dfs(g, u, used);
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;

    if (m != n - 1) { // по определению дерева
        cout << "NO" << endl;
        return 0;
    }

    Graph g(n);
    int f, t;
    for (int i = 0; i < m; i++) {
        cin >> f >> t;
        g.add_edge(f, t);
    }

    bool* used = new bool[n];
    for (int i = 0; i < n; i++) used[i] = false;

    dfs(g, 0, used);
    for (int i = 0; i < n; i++) {
        if (!used[i]) { // если есть хотя бы одна не посещённая вершина, то граф не является связным
            cout << "NO" << endl;
            delete[] used;
            return 0;
        }
    }
    cout << "YES" << endl;

    delete[] used;
    return 0;
}
