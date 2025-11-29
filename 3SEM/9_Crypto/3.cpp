// BABY-STEP-GIANT-STEP
// даны простое p <= 10^9 + 9 и 0 < a < p, а также число 0 < g < p.
// вывести такое y: g^y = a mod p.
// решить для случая, когда g — первообразный корень.
#include "crypto.h"

ll discrete_log (ll g, ll a, ll p) {
    if (a == 1) {
        return 0;
    }

    ll m = sqrt(p - 1);
    while (m * m < p - 1) {
        m++;
    }

    unordered_map<ll, int> table; // это хеш-таблица

    // baby-steps
    ll cur = a % p;
    for (int j = 0; j < m; j++) {
        table[cur] = j;
        cur = (cur * g) % p;
    }

    // giant-steps
    ll g_m = fast_pow(g, m, p);
    cur = 1;
    for (int i = 0; i <= m; i++) {
        if (table.find(cur) != table.end()) {
            int j = table[cur];
            ll y = (ll)i * m - j;
            if (y >= 0) {
                return y;
            }
        }
        cur = (cur * g_m) % p;
    }
    return -1;
}


int main() {
    ll p, g, a;
    cout << "p a: " << endl;
    cin >> p >> a;
    g = find_root(p);
    ll y = discrete_log(g, a, p);
    cout << y << endl;
    return 0;
}
