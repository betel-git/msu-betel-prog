
template <typename T>
struct Queue {
    Stack<T> leftStack, rightStack;

    Queue() = default;
    ~Queue() = default;

    void move () {
        while (!leftStack.empty()) {
            rightStack.push(leftStack.pop());
        }
    }

    int push_back (const T& x) {
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

    T get_front () {
        if (rightStack.empty()) {
            if (leftStack.empty()) {
                exit(1); //???
            }
            move();
        }
        return rightStack.top();
    }
};