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


class DrivingPlans {
public:
	int count(int N, vector <int> A, vector <int> B, vector <int> C);
};

#define MAXN 11000
#define inf 0x3fffffff //最大值
typedef int ValueT;
typedef pair<int, ValueT> Edge;
vector<Edge> adj[MAXN];


struct DD{
	int v;
	ValueT dis;
	DD(int _v=0, ValueT _dis=0):v(_v),dis(_dis){};
	bool operator<(const DD &b)const{
		return dis > b.dis;
	}
};
void dijkstra(int source, ValueT *dis){//源点为source
	for(int i=0;i<MAXN;i++) dis[i] = inf;
	priority_queue<DD> pq;
	dis[source]=0;
	pq.push(DD(source, 0));
	while(!pq.empty()){
		DD temp = pq.top();
		pq.pop();
		int u = temp.v;
		if(temp.dis > dis[u]) continue; //之前扩展过
		for(int p = 0;p < (int)adj[u].size();p++){
			int v = adj[u][p].first;
			if(dis[v] > dis[u] + adj[u][p].second){
				dis[v] = dis[u] + adj[u][p].second;
				pq.push(DD(v, dis[v]));
			}
		}
	}
}

void init(int n) {
	for(int i=0;i<=n;i++) {
		adj[i].clear();
	}
}

void addEdge(int u, int v, ValueT val) { //插入单向边
	adj[u].push_back(Edge(v, val));
}

ValueT dis[MAXN], dis2[MAXN];

int ways[MAXN];
const int mod = 1000000009;

int dfs(int u, int N) {
	if(ways[u]) return ways[u];
	if(u==N) {
		return ways[u] = 1;
	}
	int ret = 0;
	rep(i, 0, sz(adj[u])) {
		int v = adj[u][i].first;
		if(dis[u] + adj[u][i].second + dis2[v] == dis[N]) {
			ret = (ret + dfs(v, N)) % mod;
		}
	}
	//cout<<u<<' '<<ret<<endl;
	return ways[u] = ret;
}

int DrivingPlans::count(int N, vector <int> A, vector <int> B, vector <int> C) {
	init(N);
	rep(i, 0, sz(A)) {
		addEdge(A[i], B[i], C[i]);
		addEdge(B[i], A[i], C[i]);
	}
	dijkstra(1, dis);
	dijkstra(N, dis2);
	//cout<<dis[N]<<' '<<dis2[1]<<endl;
	
	rep(i, 0, sz(A)) if(C[i]==0) {
		if(dis[A[i]] + C[i] + dis2[B[i]] == dis[N]) return -1;
		if(dis[B[i]] + C[i] + dis2[A[i]] == dis[N]) return -1;
	}
	clr(ways, 0);
	return dfs(1, N);
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
			int N                     = 4;
			int A[]                   = {1,1,2,3};
			int B[]                   = {2,3,4,4};
			int C[]                   = {1,1,1,1};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DrivingPlans().count(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 4;
			int A[]                   = {1,1,2,3};
			int B[]                   = {2,3,4,4};
			int C[]                   = {1,1,1,0};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = DrivingPlans().count(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 7;
			int A[]                   = {1,1,2,3,4,4,5,6};
			int B[]                   = {2,3,4,4,5,6,7,7};
			int C[]                   = {1,1,2,2,3,3,4,4};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = DrivingPlans().count(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 3: {
			int N                     = ;
			int A[]                   = ;
			int B[]                   = ;
			int C[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DrivingPlans().count(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 4: {
			int N                     = ;
			int A[]                   = ;
			int B[]                   = ;
			int C[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DrivingPlans().count(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int N                     = ;
			int A[]                   = ;
			int B[]                   = ;
			int C[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DrivingPlans().count(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(C, C + (sizeof C / sizeof C[0])));
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
