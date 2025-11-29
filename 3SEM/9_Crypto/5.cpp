// TONELLI-SHANKS ALGORITHM
#include "crypto.h"


ll tonelli_shanks (ll a, ll p) {
    if (a == 0) return 0;
    if (legendre(a, p) != 1) return -1;

    ll Q = p - 1;
    ll S = 0;
    while (Q % 2 == 0) {
        S++;
        Q /= 2;
    }

    if (S == 1) return fast_pow(a, (p - 1) / 4, p);

    ll z = 2;
    while (legendre(z, p) != -1) z++;

    ll M = S;
    ll c = fast_pow(z, Q, p);
    ll R = fast_pow(a, (Q + 1) / 2, p);
    ll t = fast_pow(a, Q, p);

    while (t != 1) {
        int i = 0;
        ll tmp = t;
        while (tmp != 1) {
            tmp = (tmp * tmp) % p;
            i++;
        }
        
        ll b = fast_pow(c, fast_pow_without_mod(2, M - i - 1), p);
        R = (R * b) % p;
        t = (t * b % p * b) % p;
        c = (b * b) % p;
        M = i;
    }
    return R;
}


int main () {
    ll p, a;
    cout << "Введите простое p и число a: ";
    cin >> p >> a;

    if (p == 2) {
        if (a % 2 == 1) 
            cout << "Решения: 1" << endl;
        else 
            cout << "Решения: 0" << endl;
        return 0;
    }

    if (legendre(a, p) != 1) {

    }

    ll x0 = tonelli_shanks(a, p);
    ll x1 = p - x0;

    if (x0 == -1) {
        cout << "Нет решений" << endl;
        return 0;
    }

    cout << "Решения: " << x0 << " и " << x1 << endl;

    return 0;
}
