#include <iostream>
#include <fstream>
#include <cmath>
#include "stack.h"
#include "queue.h"
#include "modular.h"
#include "compl.h"
using namespace std;



int main() {
    int i, j, n;
    int val;
    Queue<int> q;

    ifstream in ("input.txt");
    if (!in) return -1;

    ofstream out ("output.txt");
    if (!out) {
        in.close();
        return -1;
    }

    in >> n;

    for (i = 0; i < n; i++) {
        in >> j;
        if (j == 0) {
            in >> val;
            out << q.push_back(val) << endl;
        } 
        else if (j == 1) {
            out << q.pop_front() << endl;
        } 
        else if (j == 2) {
            out << q.get_front() << endl;
        }
    }

    in.close();
    out.close();
    return 0;
}