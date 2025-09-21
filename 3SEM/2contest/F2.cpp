#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
#include "modular.h"
#include "compl.h"
using namespace std;

template <typename T>
struct Pair {
    T first;
    T second;
    Pair() = default;
    Pair(T f, T s) {
        first = f;
        second = s;
    }
};


template <typename T>
struct Stack {
    Pair<T> *arr;
    int size, maxsize;
    
    Stack() {
        arr = new Pair<T>[10];
        if (arr == NULL) exit(1);
        maxsize = 10;
        size = 0;
    }
    
    Stack(int count) {
        maxsize = count;
        arr = new Pair<T>[maxsize];
        if (arr == NULL) exit(1);
        size = 0;
    }
    
    ~Stack() {
        delete[] arr;
    }
                                          
    int push(const Pair<T>& x) {
        if (size < maxsize) {
            arr[size] = x;
            size++;
            return 0; 
        }
        Pair<T> *narr = new Pair<T>[2 * maxsize];
        if (narr == NULL) return -1;
        for (int i = 0; i < maxsize; i++) narr[i] = arr[i];
        maxsize *= 2;
        delete[] arr;
        arr = narr;
        arr[size++] = x;
        return 0;
    }

    Pair<T> top() {
        if (size > 0) return arr[size - 1];
        exit(1);
    }
    
    int del() {
        if (size > 0) {
            size--;
            return 0;
        }
        else return -1;
    }

    Pair<T> pop() {
        if (size > 0) {
            size--;
            return arr[size];
        }
        else exit(1);
    }

    int empty() {
        return size == 0;
    }
};


template <typename T>
struct MinQueue {
    Stack<T> leftStack, rightStack;

    MinQueue() = default;
    ~MinQueue() = default;

    void move() {
        while (!leftStack.empty()) {
            Pair<T> element = leftStack.pop();
            T current = element.first;
            
            T minVal;
            if (rightStack.empty()) {
                minVal = current;
            } else {
                minVal = min(current, rightStack.top().second);
            }
            
            Pair<T> newElement(current, minVal);
            rightStack.push(newElement);
        }
    }

    int push_back(const T& x) {
        T minVal;
        if (leftStack.empty()) {
            minVal = x;
        } else {
            minVal = min(x, leftStack.top().second);
        }
        
        Pair<T> newElement(x, minVal);
        return leftStack.push(newElement);
    }

    int pop_front() {
        if (rightStack.empty()) {
            if (leftStack.empty()) {
                return -15;
            }
            move();
        }
        return rightStack.del();
    }

    T get_min() {
        T minLeft = leftStack.empty() ? INT_MAX : leftStack.top().second;
        T minRight = rightStack.empty() ? INT_MAX : rightStack.top().second;
        
        if (leftStack.empty() && rightStack.empty()) {
            return 0;
        }
        return min(minLeft, minRight);
    }
};


int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    
    int n;
    fin >> n;
    
    MinQueue<int> q;
    
    for (int i = 0; i < n; i++) {
        int op;
        fin >> op;
        if (op == 0) {
            int x;
            fin >> x;
            int res = q.push_back(x);
            fout << res << endl;
        } else if (op == 1) {
            int res = q.pop_front();
            fout << res << endl;
        } else if (op == 2) {
            int res = q.get_min();
            fout << res << endl;
        }
    }
    
    fin.close();
    fout.close();
    
    return 0;
}