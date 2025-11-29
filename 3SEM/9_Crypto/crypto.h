#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include <unordered_map>
#include <algorithm>
#include <numeric>
using namespace std;
using ll = long long;


ll fast_pow (ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return res;
}


ll fast_pow_without_mod (ll base, ll exp) {
    ll res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base);
        }
        base = (base * base);
        exp = exp / 2;
    }
    return res;
}


int legendre (ll a, ll p) {
    if (fast_pow(a, (p - 1) / 2, p) == 1) return 1;
    else return -1;
}


vector<ll> factorize (ll n) {
    vector<ll> factors;
    
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    
    for (ll i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    
    if (n > 1) {
        factors.push_back(n);
    }
    return factors;
}


ll find_root (ll p) {
    if (p == 2) {
        return 1;
    }
    vector<ll> factors = factorize(p - 1);
    
    for (ll i = 2; i < p; i++) {
        bool ok = true;
        for (ll q : factors) {
            if (fast_pow(i, (p - 1) / q, p) == 1) {
                ok = false;
            }
        }
        if (ok) {
            return i;
        }
    }
    return -1;
}
