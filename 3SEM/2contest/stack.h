
template <typename T>
struct Stack {
    T *arr;
    int size, maxsize;
    Stack() {
        arr = new T[10];
        if (arr == NULL) exit(1);
        maxsize = 10;
        size = 0;
    }
    Stack(int count) {
        maxsize = count;
        arr = new T[maxsize];
        if (arr == NULL) exit(1);
        size = 0;
    }
    ~Stack() {
        delete arr;
    }
                                          
    int push(const T& x) {
        if (size < maxsize) {
            arr[size] = x;
            size++;
            return 0; 
        }
        T *narr = new T[2 * maxsize];
        if (narr == NULL) return -1;
        for (int i = 0; i < maxsize; i++) narr[i] = arr[i];
        maxsize *= 2;
        delete arr;
        arr = narr;
        arr[size++] = x;
        return 0;
    }

    void show() {   
        int i;
        for (i = 0; i < size; i++) {
            std::cout  << arr[i]  << "  ";
        }
        std::cout << "\n";
    }

    T top() {
        if (size > 0) return arr[size - 1];
        exit(1);
    }
    
    int del() {
        if (size > 0) {
            size--;
            arr[size] = 0;
            return 0;
        }
        else return -1;
    }

    T pop() {
        T x;
        if (size > 0) {
            size--;
            x = arr[size];
            //arr[size] = 0;
            return x;
        }
        else exit(1);
    }

    int empty() {
        if (size == 0) return 1;
        else return 0;
    }
};