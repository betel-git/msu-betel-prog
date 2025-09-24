#include <iostream>
using std::cin;
using std::cout;
using std::endl;


struct Node {
	int id;
	Node *l, *r;
	Node () {l = r = nullptr;}
};

struct BST {
    Node* root;

    BST () {root = nullptr;}
    
    int _find(Node* v, int x) {
        if (v == nullptr) return 0;
        if (v->id == x) return 1;
        if (x < v->id) return _find(v->l, x);
        return _find(v->r, x);
    }
    
    Node* _insert(Node* v, int x, bool& inserted) {
        if (v == nullptr) {
            inserted = true;
            Node* nnode = new Node();
		    nnode->id = x;
		    return nnode;
        }
        if (v->id == x) {
            inserted = false;
            return v;
        }
        if (v->id < x) {
            v->r = _insert(v->r, x, inserted);
        }
        if (v->id > x) {
            v->l = _insert(v->l, x, inserted);
        }
        return v;
    }
    
    Node* _erase(Node* v, int x, bool& removed) {
        if (v == nullptr) {
            removed = false;
            return nullptr;
        }
        if (v->id < x) {
            v->r = _erase(v->r, x, removed);
            return v;
        }
        if (v->id > x) {
            v->l = _erase(v->l, x, removed);
            return v;
        }
        if (v->id == x) {
            removed = true;
		    Node* l = v -> l;
		    Node* r = v -> r;
		    delete v;
		    return _merge(l, r);
        }
        return v;
    }

    Node* _merge (Node* l, Node* r) {
        if (l == nullptr) {return r;}
        if (r == nullptr) {return l;}
        //l -> l = _merge(l -> l, l -> r);
        //l -> r = r;
        l -> r = _merge(l -> r, r);
        return l;
    }


    
    int find(int x) {
        return _find(root, x);
    }
    
    int insert(int x) {
        bool inserted = 0;
        root = _insert(root, x, inserted);
        return inserted;
    }
    
    int erase(int x) {
        bool removed = 0;
        root = _erase(root, x, removed);
        return removed;
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    //int q, n, x;
    int q;
    cin >> q;
    
    BST tree;

    /* int a[1000000], b[1000000];
    for (int i = 0; i < q; ++i) {
        cin >> n >> x;
        a[i] = n;
        b[i] = x;
    } */
    
    for (int i = 0; i < q; ++i) {
        int n, x;
        cin >> n >> x;
        if (n == 1) {
            cout << tree.insert(x) << endl;
        } else if (n == 2) {
            cout << tree.erase(x) << endl;
        } else if (n == 3) {
            cout << tree.find(x) << endl;
        }
    }
    return 0;
}
