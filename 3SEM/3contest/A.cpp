#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::vector;
using std::endl;

struct Node {
	int id;
	vector<Node*> sons;
};

struct Tree {
	Node* root; // указатель на корень дерева
	Tree () {root = nullptr;}
};

/* int dfs (Node *v) {
	int mx = 0;
	for (int i = 0; i < (int)(v->sons.size()); ++i) {
		mx = std::max(mx, dfs(v->sons[i]));
	}
	return mx + 1;
} */

int DFSmod (Node* v, vector<int>& result) {
    int m = 0;
    for (int i = 0; i < (int)(v->sons.size()); ++i) {
        m += DFSmod(v->sons[i], result) + 1;
    }
    result[v->id - 1] = m;
    return m;
}

int main() {
    int n, i;
    cin >> n;
    
    Tree companyTree;
    vector<Node*> employees(n + 1);
    
    for (i = 1; i <= n; ++i) {
        employees[i] = new Node();
        employees[i]->id = i;
    }
    
    companyTree.root = employees[1];
    
    for (i = 2; i <= n; ++i) {
        int bossId;
        cin >> bossId;
        employees[bossId]->sons.push_back(employees[i]);
    }

    vector<int> result(n, 0);
    DFSmod(companyTree.root, result);
    
    for (i = 0; i < n; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    for (i = 1; i <= n; ++i) {
        delete employees[i];
    }
    
    return 0;
}