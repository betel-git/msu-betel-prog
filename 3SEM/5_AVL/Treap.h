using std::pair;
std::mt19937 rnd(time(NULL));

struct NodeTreap {
    int id;
    int prior;
    int size;

    NodeTreap* l;
    NodeTreap* r;
    NodeTreap () = default;
    NodeTreap (int x) {
        id = x;
        prior = rnd();
        size = 1;
        l = NULL;
        r = NULL;
    }
};


struct Treap {
    NodeTreap* root;

    Treap () {root = nullptr;}
    ~Treap () {_clear(root);}

    pair<NodeTreap*, NodeTreap*> split (NodeTreap* v, int x) {
        if (v == nullptr) {
            return {nullptr, nullptr};
        }
        if (v->id <= x) {
            pair<NodeTreap*, NodeTreap*> p = split(v->r, x);
            v->r = p.first;
            update_size(v);
            return {v, p.second};
        }
        pair<NodeTreap*, NodeTreap*> p = split(v->l, x);
        v->l = p.second;
        update_size(v);
        return {p.first, v};
    }

    NodeTreap* merge (NodeTreap* l, NodeTreap* r) {
        if (l == nullptr) {
            return r;
        }
        if (r == nullptr) {
            return l;
        }
        if (l->prior > r->prior) {
            l->r = merge(l->r, r);
            update_size(l);
            return l;
        }
        r->l = merge(l, r->l);
        update_size(r);
        return r;
    }

    NodeTreap* _search (NodeTreap* v, int x) {
        if (v == nullptr) return nullptr;
        if (v->id == x) return v;
        if (x < v->id) return _search(v->l, x);
        return _search(v->r, x);
    }

    void _clear (NodeTreap* v) {
        if (v != nullptr) {
            _clear(v->l);
            _clear(v->r);
            delete v;
        }
    }

    int _lower_bound (NodeTreap* v, int x) {
        if (v == nullptr) {
            return INT_MAX;
        }
        if (v->id == x) {
            return x;
        }
        if (v->id < x) {
            return _lower_bound(v->r, x);
        } 
        else {
            int lres = _lower_bound(v->l, x);
            if (lres != INT_MAX) {
                return lres;
            } else {
                return v->id;
            }
        }
    }

    void printTree (NodeTreap* node, const std::string& prefix = "", bool isLeft = true) {
        if (node != nullptr) {
            std::cout << prefix;
            std::cout << (isLeft ? "├──" : "└──" );
            std::cout << node->id << "[" << node->prior << "]" << std::endl;
            printTree(node->l, prefix + (isLeft ? "│   " : "    "), true);
            printTree(node->r, prefix + (isLeft ? "│   " : "    "), false);
        }
    }

    void update_size (NodeTreap* v) {
        if (v != nullptr) {
            v->size = 1;
            if (v->l != nullptr) v->size += v->l->size;
            if (v->r != nullptr) v->size += v->r->size;
        }
    }

    int _kth_order_statistic (NodeTreap* v, int k) {
        if (v == nullptr || k < 0 || k >= v->size) {
            return INT_MAX;
        }
        
        int left_size = (v->l != nullptr) ? v->l->size : 0;
        
        if (k < left_size) {
            return _kth_order_statistic(v->l, k);
        } 
        else if (k == left_size) {
            return v->id;
        }
        else {
            return _kth_order_statistic(v->r, k - left_size - 1);
        }
    }

    //----------------------------------------------

    void insert (int x) {
        if (search(x)) {return;}
        NodeTreap* newNode = new NodeTreap(x);

        pair<NodeTreap*, NodeTreap*> p = split(root, x);
        
        root = merge(merge(p.first, newNode), p.second);
    }

    void erase (int x) {
        pair<NodeTreap*, NodeTreap*> p1 = split(root, x - 1);
        pair<NodeTreap*, NodeTreap*> p2 = split(p1.second, x);
        if (p2.first != nullptr) {
            delete p2.first;
        }
        root = merge(p1.first, p2.second);
    }

    void print () {
        std::cout << "Дерево:" << std::endl;
        if (root == nullptr) {
            std::cout << "Пустое дерево" << std::endl;
        } else {
            printTree(root);
        }
        std::cout << std::endl;
    }

    int lower_bound (int x) {
        return _lower_bound(root, x);
    }

    bool search (int x) {
        return _search(root, x) != nullptr;
    }

    int kth_order_statistic (int k) {
        return _kth_order_statistic(root, k);
    }

    int count_less_than (int x) {
        pair<NodeTreap*, NodeTreap*> p = split(root, x - 1);
        int result = (p.first != nullptr) ? p.first->size : 0;
        root = merge(p.first, p.second);
        return result;
    }

    int size () {
        return (root != nullptr) ? root->size : 0;
    }

};