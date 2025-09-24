#include <iostream>
#include <vector>
using std::endl;
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::vector;

int n;
vector<int> value;
vector<int> left;
vector<int> right;

bool _checkBST(int v, int& min_val, int& max_val) {
    if (v == 0) return true;
    
    int lmin, lmax, rmin, rmax;
    lmin = lmax = rmin = rmax = value[v];
    
    bool lval = true;
    bool rval = true;

    if (left[v] != 0) {
        lval = _checkBST(left[v], lmin, lmax);
        if (lmax >= value[v]) {
            lval = false;
        }
    }

    if (right[v] != 0) {
        rval = _checkBST(right[v], rmin, rmax);
        if (rmin <= value[v]) {
            rval = false;
        }
    }
    
    min_val = min(lmin, value[v]);
    max_val = max(rmax, value[v]);
    
    return lval && rval;
}

int main() {
    int i;
    cin >> n;
    
    value.resize(n + 1);
    left.resize(n + 1);
    right.resize(n + 1);
    
    for (i = 1; i <= n; i++) {
        cin >> value[i];
    }
    
    for (i = 1; i <= n; i++) {
        cin >> left[i] >> right[i];
    }
    
    int min_val, max_val;
    if (_checkBST(1, min_val, max_val)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    
    return 0;
}