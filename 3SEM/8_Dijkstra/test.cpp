#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::cin;
using std::endl;

struct Edge {
	int from;
	int to;
    int weight;
    Edge (int f, int t, int w) {
        from = f;
        to = t;
        weight = w;
    }
    Edge () {from = 0; to = 0; weight = 1;} // хз зачем
};

struct Graph {
	vector<vector<Edge>> g;
	
	void add_edge (int f, int t, int w) {
		Edge e(f, t, w);
		g[f].push_back(e);
	}

};