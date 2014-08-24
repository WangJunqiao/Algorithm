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

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<string> VS;

#define sz(X) ((int)(X.size()))
#define all(x) x.begin(),x.end()
#define clr(x,c) memset(x,c,sizeof(x))
#define rep(i,s,e) for(int i=s;i<e;i++)


class GoodCompanyDivOne {
public:
	int minimumCost(vector <int> superior, vector <int> training);
};


#define maxn 200
#define maxm 4*120*120
const int inf = 0x3f3f3f3f; 
#define th(x) this->x=x;
struct Edge { 
	int v, cap, cost, next, flow;//flow表示已经流过的流量,便于输出方案
	void init(int v, int cap, int cost, int next) { 
		th(v); th(cap);  th(cost);  th(next); 
	} 
}; 
struct ZKW { 
	int nxt[maxn], eid, n;
	int pi[maxn], source, sink, flow, cost;//标号，最大流,最小费 
	bool vis[maxn]; 
	Edge e[maxm];
	void init(int n) { //base0
		th(n); 
		memset(nxt, -1, sizeof(nxt)); 
		eid = 0; 
	} 
	void add_edge(int i, int j, int cap, int cst) { 
		e[eid].init(j, cap, cst, nxt[i]); 
		nxt[i] = eid ++; 
		e[eid].init(i, 0, -cst, nxt[j]); 
		nxt[j] = eid ++; 
	} 
	int _dfs(int idx, int maxCap) { 
		if(idx == sink) { 
			cost += pi[source]*maxCap; 
			flow += maxCap; 
			return maxCap; 
		} 
		vis[idx] = true; 
		for(int i = nxt[idx]; i != -1; i = e[i].next) { 
			Edge & nod = e[i]; 
			if(nod.cap-nod.flow>0 && !vis[nod.v] && pi[nod.v]+nod.cost==pi[idx]){ 
				if(int d = _dfs(nod.v, min(maxCap, nod.cap-nod.flow))) { 
					nod.flow += d; 
					e[i^1].flow -= d; 
					return d; 
				} 
			} 
		} 
		return 0; 
	} 
	bool _modLabel() { 
		int d = inf; 
		for(int i = 0; i < n; i ++) if(vis[i]) { 
			for(int j = nxt[i]; j != -1; j = e[j].next) { 
				Edge & nod = e[j]; 
				if(nod.cap-nod.flow>0 && !vis[nod.v]) { 
					d = min(d, nod.cost-pi[i]+pi[nod.v]); 
				} 
			} 
		} 
		if(d == inf)  return false; 
		for(int i = 0; i < n; i ++) if(vis[i]) pi[i] += d; 
		return true; 
	} 
	void solve(int source, int sink) { 
		th(source); th(sink); 
		flow = cost = 0; 
		memset(pi, 0, sizeof(pi)); 
		for(int i = 0; i < eid; i ++)  e[i].flow = 0; 
		do {
			do { 
				memset(vis, 0, sizeof(vis)); 
			} while(_dfs(source, inf)); 
		} while(_modLabel()); 
	} 
}mc; //mc.init(n); mc.add_edge(..); mc.solve();



int dp[33][33];

vector<int> adj[33], T;


void dfs(int u) {
	for(int i=0;i<adj[u].size();i++) {
		int v = adj[u][i];
		dfs(v);
	}
	

	for(int x=1;x<sz(T);x++) {
		int L = sz(adj[u]) + 1;
		int R = sz(T) - 1;

		int src = 0, sink = L + R + sz(T) + 1;
		mc.init(sink + 1);
		for(int i=1;i<=L;i++) mc.add_edge(src, i, 1, 0);
		mc.add_edge(1, L+x, 1, T[0] + T[x]);
		for(int i=2;i<=L;i++) {
			for(int j=L+1;j<=L+R;j++) {
				mc.add_edge(i, j, 1, dp[adj[u][i-2]][j-L]);
			}
		}
		for(int i=L+1;i<=L+R;i++) {
			mc.add_edge(i, L+R+i-L+1, 1, 0);
			mc.add_edge(i, L+R+1, 1, 0);
		}
		for(int i=L+R+1;i<sink;i++) mc.add_edge(i, sink, 1, 0);

		mc.solve(src, sink);
		if(mc.flow == L) dp[u][x] = mc.cost;
		else dp[u][x] = inf;

// 		//
// 		mc.init(sink + 1);
// 		for(int i=1;i<=L;i++) mc.add_edge(src, i, 1, 0);
// 		for(int i=L+1;i<=L+R;i++) mc.add_edge(i, sink, 1, 0);
// 		mc.add_edge(L+1, sink, 1, 0);
// 		for(int i=0;i<L;i++) {
// 			for(int j=0;j<R;j++) {
// 				mc.add_edge(i+1, L+j+1, 1, dp[adj[u][i]][j+1]);
// 			}
// 		}
// 		mc.solve(src, sink);
// 		if(mc.flow == L) tmp02 = mc.cost;
// 		else tmp02 = inf;	

	//printf("u = %d, tmp = %d\n", u, tmp);
	
	}
// 	for(int i=1;i<sz(T);i++) {
// 		if(sz(adj[u]) == 0) {
// 			dp[u][i] = T[0] + T[i];
// 			continue;
// 		}
// 		if(i==1) dp[u][i] = T[0] + T[i] + tmp01;
// 		else dp[u][i] = T[0] + T[i] + tmp02;
// 	}
}

int GoodCompanyDivOne::minimumCost(vector <int> superior, vector <int> training) {
	for(int i=0;i<33;i++) adj[i].clear();
	for(int i=1;i<sz(superior);i++) {
		adj[superior[i]].push_back(i);
	}
	T = training;
	sort(all(T));
	dfs(0);
	int mi = inf;
	rep(i, 1, sz(T)) mi = min(mi, dp[0][i]);
	if(mi >= inf) return -1;
	return mi;
}

















// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}
	
	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;
		
		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl; 
			cerr << "    Received: " << received << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int superior[]            = {-1};
			int training[]            = {1, 2};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int superior[]            = {-1, 0, 0};
			int training[]            = {1, 2, 3};
			int expected__            = 10;

			clock_t start__           = clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int superior[]            = {-1, 0, 0, 0};
			int training[]            = {1, 2, 3};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int superior[]            = {-1, 0, 0, 2, 2, 2, 1, 1, 6, 0, 5, 4, 11, 10, 3, 6, 11, 7, 0, 2, 13, 14, 2, 10, 9, 11, 22, 10, 3};
			int training[]            = {4, 2, 6, 6, 8, 3, 3, 1, 1, 5, 8, 6, 8, 2, 4};
			int expected__            = 71;

			clock_t start__           = clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int superior[]            = ;
			int training[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int superior[]            = ;
			int training[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int superior[]            = ;
			int training[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GoodCompanyDivOne().minimumCost(vector <int>(superior, superior + (sizeof superior / sizeof superior[0])), vector <int>(training, training + (sizeof training / sizeof training[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}
 

int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
