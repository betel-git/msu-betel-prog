#include <iostream>
using namespace std;


struct Stack {
    int *arr;
    int size, maxsize;
    Stack() {
        arr = (int*)malloc(10 * sizeof(int));
        if (arr == NULL) exit(1);
        maxsize = 10;
        size = 0;
    }
    Stack(int count) {
        maxsize = count;
        arr = (int*)malloc(maxsize * sizeof(int));
        if (arr == NULL) exit(1);
        size = 0;
    }
    ~Stack() {
        free(arr);
    }
                                          
    int push(int x) {
        if (size < maxsize) {
            arr[size] = x;
            size++;
            return 0; 
        }
        int *narr = (int*)malloc(2 * maxsize * sizeof(int));
        if (narr == NULL) return -1;
        for (int i = 0; i < maxsize; i++) narr[i] = arr[i];
        maxsize *= 2;
        free(arr);
        arr = narr;
        arr[size++] = x;
        return 0;
    }

    void show() {   
        int i;
        for (i = 0; i < size; i++) {
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

    int pop() {
        int x;
        if (size > 0) {
            size--;
            x = arr[size];
            arr[size] = 0;
            return x;
        }
        else return -1;
    }

    int empty() {
        if (size == 0) return 1;
        else return 0;
    }
};


struct Queue {
    Stack leftStack, rightStack;

    Queue() = default;
    ~Queue() = default;

    void move () {
        while (!leftStack.empty()) {
            rightStack.push(leftStack.pop());
        }
    }

    int push_back (int x) {
        leftStack.push(x);
        return 0;
    }

    int pop_front () {
        if (rightStack.empty()) {
            if (leftStack.empty()) {
                return -1;
            }
            move();
        }
        rightStack.pop();
        return 0;
    }

    int get_front () {
        if (rightStack.empty()) {
            if (leftStack.empty()) {
                return 0;
            }
            move();
        }
        return rightStack.top();
    }
};


int main() {
    int i, j, n, val;
    FILE *in;
    FILE *out;
    Queue q;

    in = fopen("input.txt", "r");
    if (!in) return -1;

    out = fopen("output.txt", "w");
    if (!out) {
        fclose(in);
        return -1;
    }
    fscanf(in, "%d", &n);

    for (i = 0; i < n; i++) {
        fscanf(in, "%d", &j);
        if (j == 0) {
            fscanf(in, "%d", &val);
            fprintf(out, "%d\n", q.push_back(val));
        } 
        else if (j == 1) {
            fprintf(out, "%d\n", q.pop_front());
        } 
        else if (j == 2) {
            fprintf(out, "%d\n", q.get_front());
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}