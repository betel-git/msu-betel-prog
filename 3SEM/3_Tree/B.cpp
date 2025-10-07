#include <iostream>
#include <vector>
#include <algorithm>
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

void DFS (Node* v, int level, vector<int>& levels) {
    levels[v->id - 1] = level;
    for (int i = 0; i < (int)(v->sons.size()); ++i) {
        DFS (v->sons[i], level + 1, levels);
    }
}

int main() {
    int n, i, max;
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

    vector<int> levels(n, 0); // сюда складируем уровни сотрудников

    DFS(companyTree.root, 0, levels);
    max = *std::max_element(levels.begin(), levels.end()); // max_element находит именно элемент, а не значение
    // именно поэтому тут звёздочка
    cout << max << endl;
    
    vector<int> levelCount(max + 1, 0); // сюда складируем количество сотрудников в уровнях
    for (int i = 0; i < n; ++i) {
        levelCount[levels[i]]++;
    }

    for (i = 0; i <= max; ++i) {
        cout << levelCount[i] << " ";
    }
    cout << endl;
    
    for (i = 1; i <= n; ++i) {
        delete employees[i];
    }
    
    return 0;
}