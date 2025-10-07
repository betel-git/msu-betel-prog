#include <iostream>
using namespace std;


struct Stack{
    int *arr;
    int size, maxsize;
    Stack() {
        arr = new int[10];
        if (arr == NULL) exit(1);
        maxsize = 10;
        size = 0;
    }
    Stack(int count) {
        maxsize = count;
        arr = new int[maxsize];
        if (arr == NULL) exit(1);
        size = 0;
    }
    ~Stack() = default;                                      
    int push(int x) {
        if (size < maxsize) {
            arr[size] = x;
            size++;
            return 0; 
        }
        int *narr = new int[2 * maxsize];
        if (narr == NULL) return -1;
        for (int i = 0; i < maxsize; i++) narr[i] = arr[i];
        maxsize *= 2;
        delete arr;
        arr = narr;
        arr[size++] = x;
        return 0;
    }
    void show();
    int top();
    int del();
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

void Stack::show() {   
	int i;
	for (i = 0; i < size; i++) {
        cout  << arr[i]  << "  ";
    }
    cout << "\n";
}

int Stack::top() {
    if (size > 0) return arr[size - 1];
    else return 0;
}

int Stack::del() {
    if (size > 0) {
        size--;
        arr[size] = 0;
        return 0;
    }
    else return -1;
}


int main() {
    Stack a, b;
    int n, k, m = 1;

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> k;
        if (k == 1) {if (a.push(m++) == -1) return -1;}
        if (k == 2) {if (b.push(m++) == -1) return -1;}
        if (k == 3) {
            if (a.top() == 0 && b.top() != 0) b.del();
            else if (b.top() == 0 && a.top() != 0) a.del();
            else if (a.top() > b.top()) b.del();
            else if (a.top() < b.top()) a.del();
        }
    }

    cout << a.top() + b.top() << endl;
    return 0;
}