#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

struct DD {
	double t1, t2;
	int a, b;
	DD(double _t1 = 0, double _t2 = 0, int _a = 0, int _b = 0) {
		t1 = _t1;
		t2 = _t2;
		a = _a;
		b = _b;
	}
	bool operator<(const DD &x) const {
		return t1 < x.t1;
	}
};

vector<DD> funcs[55];

struct Edge{
	int v, a, b;
	Edge(int _v = 0, _a = 0, _b = 0):v(_v), a(_a), b(_b){};
};

vector<Edge> adj[55];

queue<int> q;
bool inq[55];


vector<DD> update(const vector<DD> f, int a, int b) {
	vector<DD> ret;
	for (int i = 0; i < f.size(); i ++) {
		if (b == f[i].b) {
			if (a + b * f[i].t1 > f[i].a + f[i].b * f[i].t1) {
				ret.push_back(DD(f[i].t1, f[i].t2, a, b));
			} else {
				ret.push_back(f[i]);
			}
		} else {
			double p = (a - f[i].a) / (double)(f[i].b - b);
			if (p <= f[i].t1 || p >= f[i].t2) {				
				if (a + b * f[i].t1 > f[i].a + f[i].b * f[i].t1) {
					ret.push_back(DD(f[i].t1, f[i].t2, a, b));
				} else {
					ret.push_back(f[i]);
				}
			} else {
				
				if (a + b * f[i].t1 > f[i].a + f[i].b * f[i].t1) {
					ret.push_back(DD(f[i].t1, p, a, b));
					ret.push_back(DD(p, f[i].t2, f[i].a, f[i].b));
				} else {
					ret.push_back(DD(f[i].t1, p, f[i].a, f[i].b));
					ret.push_back(DD(p, f[i].t2, a, b));
				}
			}
		}
	}
	return ret;
}

int main() {
	int C; scanf("%d", &C);
	for (int te = 1; te <= C; te ++) {
		int n, m, T;
		scanf("%d %d %d", &n, &m, &T);
		for (int i = 1; i <= n; i ++) {
			adj[i].clear();
			funcs[i].clear();
			funcs[i].push_back(DD(0, T, 0, 0));
		}
		for (int i = 1; i <= m; i ++) {
			int u, v, a, b;
			scanf("%d %d %d %d", &u, &v, &a, &b);
			adj[u].push_back(Edge(v, a, b));
			adj[v].push_back(Edge(u, a, b));
		}

		while (!q.empty()) q.pop();
		memset(inq, false, sizeof(inq));
		while (!q.empty()) {
			int u = q.front(); 
			q.pop();
			for (int i = 0; i < adj[u].size(); i ++) {
				int v = adj[u][i].first;
			}
		}
		
	}
}
