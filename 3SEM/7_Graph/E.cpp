// Дан ориентированный граф. Требуется определить, есть ли в нем цикл.
#include <iostream>
#include <fstream>
#include <vector>
using std::vector;
using std::cout;
using std::cin;
using std::endl;


bool dfs (vector<vector<int>> &g, int v, int* used) {
	used[v] = 1; // 1 - сейчас находимся, 2 - уже вышли, 0 - ещё не вошли
	//for (int u: g[v]) {
    for (int u = 0; u < (int)g.size(); u++) {
        if (g[v][u] == 1) {
            if (used[u] == 1) {
                return true;
            }
            else if (used[u] == 2) {
                continue;
            }
            if (dfs(g, u, used)) {
                return true;
            }
        }
	}
	used[v] = 2;
	return false;
}


int main() {
    std::ifstream fin ("cycle.in");
    if (!fin) return -1;

    std::ofstream fout ("cycle.out");
    if (!fout) {
        fin.close();
        return -1;
    }

    int n;
    fin >> n;

    vector<vector<int>> g(n, vector<int>(n));

    int i, j, v;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fin >> v;
            g[i][j] = v;
        }
    }

    int* used = new int[n];
    for (int i = 0; i < n; i++) used[i] = 0;

    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            if (dfs(g, i, used)) {
                fout << 1 << endl;
                delete[] used;
                fin.close();
                fout.close();
                return 0;
            }
        }
    }
    fout << 0 << endl;

    delete[] used;
    fin.close();
    fout.close();
    return 0;
}