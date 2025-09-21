#include <iostream>
#include <fstream>
#include <cmath>
#include "compl.h"
#include "dyn_arr.h"
#include "modular.h"


int main() {
    int n, t, ind;
    Complex x;
    dyn_arr<Complex> arr;

    std::ifstream in ("input.txt");
    if (!in) return -1;

    std::ofstream out ("output.txt");
    if (!out) {
        in.close();
        return -1;
    }

    in >> n;
    
    for (int i = 0; i < n; i++) {
        in >> t;
        if (t == 0) {
            in >> x;
            out << arr.push_back(x) << std::endl;
        } else if (t == 1) {
            out << arr.pop_back() << std::endl;
        } else if (t == 2) {
            in >> ind;
            out << arr[ind] << std::endl;
        }
    }
    
    in.close();
    out.close();
    return 0;
}