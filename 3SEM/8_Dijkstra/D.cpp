// Floyd-Warshall
#include <iostream>
#include <vector>
#include <climits>
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::min;


int main() {
    int n;
    cin >> n;
    
    vector<vector<int>> g(n, vector<int>(n, INT_MAX));
    
    int i, j, w;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cin >> w;
            if (w != -1) {
                g[i][j] = w;
            }
        }
        g[i][i] = 0;
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // проверка для защиты от выхода за пределы int, там INT_MAX + что-то даст большое по модулю отрицательное число
                if (g[i][k] < INT_MAX && g[k][j] < INT_MAX) g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (g[i][j] == INT_MAX) {
                cout << -1 << " ";
            } else {
                cout << g[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
