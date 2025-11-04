// найти индексы подстрок
#include <iostream>
#include <string>
#include <vector>
#include <utility>
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

void Pows (int n, int x, long long mod, vector<long long>& pow) { // заранее все степени по основанию x по модулю m посчитаем
    pow.resize(n + 1);
    pow[0] = 1;
    
    for (int i = 0; i < n; i++) {
        pow[i + 1] = (pow[i] * x) % mod;
    }
}

void PrefixHashes (const string& s, int x, int mod, vector<long long>& pref) { // считаем префиксные хеши
    int n = s.size();
    pref.resize(n + 1);
    pref[0] = 0;
    
    for (int i = 0; i < n; i++) {
        pref[i + 1] = (pref[i] * x + s[i]) % mod;
    }
}

long long MegaPolyHash (int l, int r, int mod, const vector<long long>& pref, const vector<long long>& pow) { // считаем хеши на отрезке [l,r-1]
    long long res = (pref[r] - pref[l] * pow[r - l]) % mod;
    if (res < 0) res += mod;
    return res;
}

long long PolyHash (int size, int x, int mod, const string& t) { // полиномиальный хеш
    long long thash = 0;
    for (int i = 0; i < size; i++) {
        thash = (thash * x + t[i]) % mod;
    }
    return thash;
}


int main() {
    string s, t;
    cin >> s;
    cin >> t;
    int n = s.size();
    int m = t.size();
    vector<long long> pow1, pow2;
    vector<long long> pref1, pref2;
    int x = 29;
    int mod1 = (int)10e8 + 9;
    int mod2 = (int)10e8 + 7;
    long long thash1 = PolyHash(m, x, mod1, t);
    long long thash2 = PolyHash(m, x, mod2, t);


    Pows(n, x, mod1, pow1);
    Pows(n, x, mod2, pow2);
    PrefixHashes(s, x, mod1, pref1);
    PrefixHashes(s, x, mod2, pref2);


    vector<int> lst;
    for (int i = 0; i <= n - m; i++) {
        if (MegaPolyHash(i, i + m, mod1, pref1, pow1) == thash1 && MegaPolyHash(i, i + m, mod2, pref2, pow2) == thash2) {
            lst.push_back(i);
        }
    }

    for (int i = 0; i < (int)lst.size(); i++) {
        cout << lst[i] << endl;
    }

    return 0;
}
