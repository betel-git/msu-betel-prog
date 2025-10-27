#include <iostream>
#include <random>
#include <climits>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>
#include "Treap.h"
using std::pair;
using std::cout;
using std::cin;
using std::endl;
using std::sort;
using std::vector;

std::mt19937 rd(time(NULL));

struct Node {
    int id;
    Node* l;
    Node* r;
    int h;
    Node () = default;
    Node (int x) {
        id = x;
        h = 1;
        l = r = nullptr;
    }
};


struct AVL {
    Node* root;
    AVL () {root = nullptr;}
    ~AVL () {clear(root);}

    Node* _insert (Node* v, int x) { // как в BST + балансировка
        if (v == nullptr) {
            Node* nnode = new Node();
            nnode->id = x;
            return nnode;
        }
        if (v->id == x) {return v;}
        if (v->id < x) {
            v->r = _insert(v->r, x);
        }
        if (v->id > x) {
            v->l = _insert(v->l, x);
        }
        return balance(v);
    }

    Node* _erase (Node* v, int x) {
        if (!v) return nullptr;

        if (x < v->id)
            v->l = _erase(v->l, x);
        else if (x > v->id)
            v->r = _erase(v->r, x);
        else { // нашли элемент, который хотим удалить
            if (!v->l || !v->r) { // 1 или 0 потомков
                Node* temp = v->l ? v->l : v->r;
                if (!temp) { // нет потомков
                    temp = v;
                    v = nullptr;
                }
                else *v = *temp; // один потомок
                delete temp;
            } 
            else { // 2 потомка
                // нам надо найти элемент с как можно более близким значением к x
                // находим минимум в правом поддереве — это и будет нужный элемент
                Node* temp = _find_min(v->r);
                v->id = temp->id;
                v->r = _erase(v->r, temp->id);
            }
        }

        return balance(v);
    }

    int _search (Node* v, int x) {
        if (!v) return 0;
        if (x == v->id) return 1;
        return x < v->id ? _search(v->l, x) : _search(v->r, x);
    }

    Node* _find_min (Node* v) {
        return v->l ? _find_min(v->l) : v;
    }

    int height (Node* v) {
        if (v) return v->h;
        return 0;
    }

    void upd_height (Node* v) {
        if (v) {
            v->h = 1 + std::max(height(v->l), height(v->r));
        }
    }

    int diff (Node* v) {
        return v ? height(v->l) - height(v->r) : 0;
    }

    Node* rotate_left (Node* v) {
        if (!v || !v->r) return v;
        Node* w = v->r;
        v->r = w->l;
        w->l = v;

        upd_height(v);
        upd_height(w);
        return w;
    }

    Node* rotate_right (Node* v) {
        if (!v || !v->r) return v;
        Node* w = v->l;
        v->l = w->r;
        w->r = v;

        upd_height(v);
        upd_height(w);
        return w;
    }

    Node* big_rotate_left (Node* v) {
        if (!v) return nullptr;
        v->r = rotate_right(v->r);
        return rotate_left(v);
    }

    Node* big_rotate_right (Node* v) {
        if (!v) return nullptr;
        v->l = rotate_left(v->l);
        return rotate_right(v);
    }

    Node* balance (Node* v) {
        if (!v) return nullptr;
        upd_height(v);
        if (diff(v) == -2) { // правое поддерево тяжелее
            if (diff(v->r) <= 0) { // правое поддерево правого поддерева тяжелее
                return rotate_left(v);
            }
            return big_rotate_left(v); // левое поддерево правого поддерева тяжелее
        }
        if (diff(v) == 2) { // левое поддерево тяжелее
            if (diff(v->l) >= 0) { // левое поддерево левого поддерева тяжелее
                return rotate_right(v);
            }
            return big_rotate_right(v); // правое поддерево левого поддерева тяжелее
        }
        return v;
    }

    void clear (Node* v) {
        if (v) {
            clear(v->l);
            clear(v->r);
            delete v;
        }
    }


    //-------------------------------------------
    void insert (int x) {root = _insert(root, x);}
    void erase (int x) {root = _erase(root, x);}
    int search (int x) {return _search(root, x);}

};


int StressTest (long long int n) {
    Treap t1;
    AVL t2;
    vector<int> lst;

    for (int i = 0; i < n; i++) {
        int typ = rd() % 3;
        if (typ == 0) {
            int x = rd() % (int)pow(10, 8);
            t1.insert(x);
            t2.insert(x);
            lst.push_back(x);
        }
        if (typ == 1 && !lst.empty()) {
            std::swap(lst[rd() % lst.size()], lst.back());
            t1.erase(lst.back());
            t2.erase(lst.back());
            lst.pop_back();
        }
        if (typ == 2) {
            int x;
            if (lst.empty()) {
                x = rd() % (int)pow(10, 8);
            } 
            else {
                x = (rd() % 2) ? rd() % (int)pow(10, 8) : lst[rd() % lst.size()];
            }
            if (t1.search(x) != t2.search(x)) {
                cout << "Всё поломалось в поиске :(" << endl;
                return 0;
            }
        }
    }
    cout << "Успех!" << endl;
    return 1;
}


int main() {
    long long int m;
    int q;
    cout << "Введите количество операций (дальше 10^7 слишком долго): ";
    cin >> m;
    cout << "Сколько раз повторить тест?" << endl;
    cin >> q;
    for (int i = 0; i < q; i++) {
        auto start = std::clock();
        StressTest(m);
        auto time = std::clock() - start;
        cout << (double)time / CLOCKS_PER_SEC << " сек" << endl;
    }

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Хотите получить своё АВЛ-дерево? (YES / NO): ";
    std::string str;
    cin >> str;
    if (str == "NO") return 0;

    AVL tree;
    int n, in;
    cout << "Введите количество операций: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            cin >> in;
            tree.insert(in);
        }
        else if (type == 2) {
            cin >> in;
            tree.erase(in);
        }
        else {
            cin >> in;
            cout << tree.search(in) << endl;
        }
    }
    return 0;
}
