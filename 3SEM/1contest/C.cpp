#include <iostream>
#include <string>
using namespace std;


struct Stack{
    long int *arr;
    long int *mxarr;
    int size, maxsize;
    Stack() {
        arr = (long int*)malloc(10 * sizeof(long int));
        mxarr = (long int*)malloc(10 * sizeof(long int));
        if (arr == NULL || mxarr == NULL) exit(1);
        maxsize = 10;
        size = 0;
    }
    Stack(int count) {
        maxsize = count;
        arr = (long int*)malloc(maxsize * sizeof(long int));
        mxarr = (long int*)malloc(maxsize * sizeof(long int));
        if (arr == NULL || mxarr == NULL) exit(1);
        size = 0;
    }
    ~Stack() {
        free(arr);
        free(mxarr);
    }                                     
    int push(int x) {
        if (size < maxsize) {
            arr[size] = x;
            if (size == 0) mxarr[size] = x;
            else {
                if (x > mxarr[size - 1]) mxarr[size] = x;
                else mxarr[size] = mxarr[size - 1];
            }
            size++;
            return 0; 
        }
        long int *narr = (long int*)malloc(2 * maxsize * sizeof(long int));
        long int *nmxarr = (long int*)malloc(2 * maxsize * sizeof(long int));
        if (narr == NULL || nmxarr == NULL) return -1;
        for (int i = 0; i < maxsize; i++) {
            narr[i] = arr[i];
            nmxarr[i] = mxarr[i];
        }

        maxsize *= 2;
        free(arr);
        free(mxarr);
        arr = narr;
        mxarr = nmxarr;
        arr[size] = x;
        if (x > mxarr[size - 1]) mxarr[size] = x;
        else mxarr[size] = mxarr[size - 1];
        size++;
        return 0;
    }

    void show() {   
        for (int i = 0; i < size; i++) {
            cout  << arr[i]  << "  ";
        }
        cout << "\n";
    }

    int top() {
        if (size > 0) return arr[size - 1];
        else return 0;
    }

    int del() {
        if (size > 0) {
            size--;
            arr[size] = 0;
            return 0;
        }
        else return -1;
    }

    long long int max() {
        if (size > 0) return mxarr[size - 1];
        else return -1;
    }

    int pop(int *x) {
        if (size > 0) {
            size--;
            *x = arr[size];
            arr[size] = 0;
            return 0;
        }
        else return -1;
    }
};


int main() {
    Stack a;
    int q, v;
    string str;

    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        cin >> str;
        if (str == "push") {
            cin >> v;
            a.push(v);
        } 
        else if (str == "pop") {
            a.del();
        } 
        else if (str == "max") {
            printf("%lld\n", a.max());
        }
    }
    return 0;
}