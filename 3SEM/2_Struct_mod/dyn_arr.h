
template <typename T>
struct dyn_arr {
    T *arr;
    int mx_sz, cur_sz;
    dyn_arr () {
        arr = new T[4];
        mx_sz = 4;
        cur_sz = 0;
    }
    ~dyn_arr () {
        delete arr;
    }
    int push_back (const T& x) {
        if (cur_sz < mx_sz) {
            arr[cur_sz++] = x;
            return 0;
        }
        T *narr = new T[2 * mx_sz];
        if (narr == NULL) return -1;
        for (int i = 0; i < mx_sz; i++) {
            narr[i] = arr[i];
        }
        mx_sz *= 2;
        delete arr;
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
    T& operator [] (int i) {
        if (i < 0 || i >= cur_sz) {
            std::cout << "out of range" << std::endl;
            exit(1);
        }
        return arr[i];
    }
};