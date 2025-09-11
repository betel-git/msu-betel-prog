#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct dyn_arr {
    int *arr;
    int mx_sz, cur_sz;
    dyn_arr () {
        arr = (int*)malloc(4 * sizeof(int));
        mx_sz = 4;
        cur_sz = 0;
    }
    ~dyn_arr () {
        free(arr);
    }
    int push_back (int x) {
        if (cur_sz < mx_sz) {
            arr[cur_sz++] = x;
            return 0;
        }
        int *narr = (int*)malloc(2 * mx_sz * sizeof(int));
        if (narr == NULL) return -1;
        for (int i = 0; i < mx_sz; i++) {
            narr[i] = arr[i];
        }
        mx_sz *= 2;
        free(arr);
        arr = narr;
        arr[cur_sz++] = x;
        return 0;
    }
    int pop_back () {
        if (cur_sz == 0) {
            return -1;
        }
        --cur_sz;
        return 0;
    }
    int operator [] (int i) {
        if (i < 0 || i >= cur_sz) {
            return 0;
        }
        return arr[i];
    }
};


int main() {
    int n, t, x;
    dyn_arr arr;
    FILE* in;
    FILE* out;

    in = fopen("input.txt", "r");
    if (!in) return -1;

    out = fopen("output.txt", "w");
    if (!out) {
        fclose(in);
        return -1;
    }

    fscanf(in, "%d", &n);
    
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &t);
        
        if (t == 0) {
            fscanf(in, "%d", &x);
            fprintf(out, "%d\n", arr.push_back(x));
        } else if (t == 1) {
            fprintf(out, "%d\n", arr.pop_back());
        } else if (t == 2) {
            fscanf(in, "%d", &x);;
            fprintf(out, "%d\n", arr[x]);
        }
    }
    
    fclose(in);
    fclose(out);
    return 0;
}