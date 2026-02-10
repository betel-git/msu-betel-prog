#include <iostream>
using namespace std;

template <class T>
class Stack {
private:
	T *mem, *top;
	int size;
public:
	Stack () {mem = top = NULL; size = 0;}
	~Stack () {if (mem) delete [] mem;}
	
	int SetSize (int maxsize) {
		if (mem) return -1;
		try {
			mem = new T[maxsize];
			top = mem + maxsize;
			size = 0;
			return (mem) ? 0 : -1;
		}
		catch (...) {return -1;}
	}
	int Push (T val) {return (mem && top && top != mem) ? *(--top) = val, ++size : -1;}
	int Pop (T& dst) {if (top && size) ? dst = *(top++), --size : -1;}
	int Del () {if (size) ? ++top, --size : -1;}
	int SetTop (T val) {return (size) ? *top = val, size : -1;}
	int GetTop (T *dst) {return (size) ? *dst = *top, size : -1;}
	int Size () {return size;}
	int Room () {return top - mem;}
	void Clear () {top += size;}
};

int main() {
    Stack ob(3); // Создали стек на 3 элемента (конструктор с параметром)

    // Кладем в стек несколько элементов:
    if(ob.push(1)!=0) cout << "стек полон\n";
    ob.show();
    cout << "\n-------------------------------\n";
    if(ob.push(2)!=0) cout << "стек полон\n";
    ob.show();
    cout << "\n-------------------------------\n";
    if(ob.push(3)!=0) cout << "стек полон\n";
    ob.show();
    cout << "\n-------------------------------\n";
    if(ob.push(4)!=0) cout << "стек полон\n";
    ob.show();
    cout << "\n-------------------------------\n";

    return 0;
}