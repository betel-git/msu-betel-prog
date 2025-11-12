// Из прямоугольного листа клетчатой бумаги (M строк, N столбцов) удалили некоторые клетки.
// На сколько кусков распадётся оставшаяся часть листа?
// Две клетки не распадаются, если они имеют общую сторону.
#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;


void dfs (vector<string>& g, int i, int j, int m, int n, vector<vector<bool>>& used) {
    if (i < 0 || j < 0 || i >= m || j >= n) return;
    if (g[i][j] == '.') return;
    if (used[i][j] == true) return;

    used[i][j] = true;

    // от вершины проходим вверх / влево / вниз / вправо
    dfs(g, i - 1, j, m, n, used);
    dfs(g, i, j - 1, m, n, used);
    dfs(g, i + 1, j, m, n, used);
    dfs(g, i, j + 1, m, n, used);
}



int main() {
    int n, m;
    cin >> m >> n;

    vector<string> g(m);
    for (int i = 0; i < m; i++) {
        cin >> g[i];
    }

    vector<vector<bool>> used(m, vector<bool>(n, false));
    
    int res = 0;

    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (g[i][j] == 'O' && !used[i][j]) {
                res++;
                dfs(g, i, j, m, n, used);
            }
        }
    }

    cout << res << endl;
    return 0;
}
