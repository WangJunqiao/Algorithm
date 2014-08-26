#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

struct DD {
	static double t1, t2;

	int u, v, a, b;
	DD(int _u = 0, int _v = 0, int _a = 0, int _b = 0) {
		u = _u;
		v = _v;
		a = _a;
		b = _b;
	}
	bool opearator<(const DD &x) const {
		return a + b * (t1 + t2) / 2.0 > x.a + x.b * (t1 + t2) / 2.0; 
	}
};

vector<DD> adj[55];

pair<int, int> dis[55];

class CMP {
	public:
		double t1, t2;
		CMP(double t1, double t2) {
			this->t1 = t1;
			this->t2 = t2;
		}
		bool operator()(const DD &p1, const DD &p2) {
			double mid = (t1 + t2) / 2.0;
			return p1.a + p1.b * mid < p2.a + p2.b * mid;
		}
};


int pa[55];
void init(int n) {
	for (int i = 1; i <= n; i ++) {
		pa[i] = i;
		adj[i].clear();
	}
}

int find(int u) {
	return pa[u] == u ? u : find(pa[u]);
}

int main() {
	int C;
	scanf("%d", &C);
	for (int te = 1; te <= C; te ++) {
		int n, m, T;
		scanf("%d %d %d", &n, &m, &T);
		for (int i = 1; i <= n; i ++) {
			adj[i].clear();
		}
		vector<DD> vps;
		for (int i = 1; i <= m; i ++) {
			int u, v, a, b;
			scanf("%d %d %d %d", &u, &v, &a, &b);
			DD tmp(u, v, a, b);
			vps.push_back(tmp);
		}
		set<double> st;
		for (int i = 0; i < vps.size(); i ++) {
			for (int j = i + 1; j < vps.size(); j ++) {
				if (vps[i].second == vps[j].second) 
					continue;
				double t = (vps[i].first - vps[j].first) / (double)(vps[j].second - vps[i].second);
				if (t >= 0 && t <= T) st.insert(t);
			}
		}
		st.insert(0);
		st.insert(T);
		vector<double> points(st.begin(), st.end());

		for (int x = 0; x < points.size() - 1; x ++) {
			double t1 = points[x], t2 = points[x + 1];
			DD::t1 = t1;
			DD::t2 = t2;
			sort(vps.begin(), vps.end());
			init(n);
			for (int i = 0; i < vps.size(); i ++) {
				int fu = find(vps[i].u);
				int fv = find(vps[i].v);
				if (fu != fv) {
					adj[vps[i].u].push_back(vps[i]);
					adj[vps[i].v].push_back(vps[i]);
					pa[fu] = fv;
				}
			}
		}
	}
}
