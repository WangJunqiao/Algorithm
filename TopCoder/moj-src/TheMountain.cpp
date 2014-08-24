#include <vector>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <cassert>

using namespace std;

#define sz(X) ((int)(X.size()))
#define all(x) x.begin(),x.end()
#define clr(x,c) memset(x,c,sizeof(x))
#define rep(i,st,ed) for(int i=st;i<ed;i++)

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;
//--------------------------------------------


class TheMountain {
public:
	int minSum(int n, int m, vector <int> rowIndex, vector <int> columnIndex, vector <int> element);
};


#define maxn 210 * 210

const int inf = 1<<30;
int n, m;
VI R, C, ele;


vector<PII> adj[maxn];
int id[210][210];
int dis[maxn];
bool inq[maxn];
queue<int> q;
int ttt[maxn];

void update(int x, int d){
	if(dis[x] >= d) return;
	dis[x] = d;
	if(inq[x] == false){
		q.push(x);
		inq[x] = true;
	}
}



int get(int A, int B) {
	//printf("A = %d, B = %d\n", A, B);
	int cnt = 0;
	rep(i, 0, n) rep(j, 0, m){
		id[i][j] = ++cnt;
	}
	rep(i, 0, cnt+1) adj[i].clear();
	rep(i, 0, n) {
		adj[0].push_back(PII(id[i][0], 1));
		adj[0].push_back(PII(id[i][m-1], 1));
	}
	rep(j, 0, m){
		adj[0].push_back(PII(id[0][j], 1));
		adj[0].push_back(PII(id[n-1][j], 1));
	}
	rep(i, 0, n) {
		rep(j, 0, B) {
			adj[ id[i][j] ].push_back(PII(id[i][j+1], 1));
		}
		rep(j, B+1, m){
			adj[ id[i][j] ].push_back(PII(id[i][j-1], 1));
		}
	}
	rep(j, 0, m) {
		rep(i, 0, A) {
			adj[ id[i][j] ].push_back(PII(id[i+1][j], 1));
		}
		rep(i, A+1, n) {
			adj[ id[i][j] ].push_back(PII(id[i-1][j], 1));
		}
	}
	rep(i, 0, sz(R)) {
		adj[0].push_back(PII(id[R[i]][C[i]], ele[i]));
	}

	rep(i, 0, cnt+1) dis[i] = -inf;
	clr(inq, false);
	while(!q.empty()) q.pop();

	update(0, 0);
	while(!q.empty()) {
		int x= q.front(); q.pop();
		inq[x] = false;
		rep(i, 0, sz(adj[x])) {
			int y = adj[x][i].first;
			int d = dis[x] + adj[x][i].second;
			update(y, d);
		}
	}

	rep(i, 0, sz(R)) {
		if(dis[id[R[i]][C[i]]] != ele[i]) return inf;
	}

	int ret = 0;
	for(int i=1;i<=cnt;i++) {
		ret += dis[i];
	}
	return ret;
}

bool vst[55][55];


int TheMountain::minSum(int n, int m, vector <int> rowIndex, vector <int> columnIndex, vector <int> element) {
	::n = n;
	::m = m;
	R = rowIndex;
	C = columnIndex;
	ele = element;

	set<PII> st;
	bool vx[222] = {false};
	bool vy[222] = {false};
	rep(i, 0, sz(R)){
		rep(x, -1, 2) rep(y, -1, 2) {
			int tx = R[i]+x;
			int ty = C[i]+y;
			if(tx>=0 && tx<n && ty>=0 && ty<m) {
				st.insert(PII(tx, ty));
				vx[tx] = true;
				vy[ty] = true;
			}
		}
	}
	

	int ret = inf;

	rep(i, 0, n) rep(j, 0, m) {
		bool can = true;
	
		ret = min(ret, get(i, j));
	}
	if(ret >= inf) return -1;
	return ret;
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
			int n                     = 2;
			int m                     = 3;
			int rowIndex[]            = {0, 0, 0, 1, 1, 1};
			int columnIndex[]         = {0, 1, 2, 0, 1, 2};
			int element[]             = {4, 6, 9, 1, 3, 6};
			int expected__            = 29;

			clock_t start__           = clock();
			int received__            = TheMountain().minSum(n, m, vector <int>(rowIndex, rowIndex + (sizeof rowIndex / sizeof rowIndex[0])), vector <int>(columnIndex, columnIndex + (sizeof columnIndex / sizeof columnIndex[0])), vector <int>(element, element + (sizeof element / sizeof element[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 2;
			int m                     = 3;
			int rowIndex[]            = {1, 0, 1};
			int columnIndex[]         = {2, 2, 0};
			int element[]             = {5, 7, 6};
			int expected__            = 40;

			clock_t start__           = clock();
			int received__            = TheMountain().minSum(n, m, vector <int>(rowIndex, rowIndex + (sizeof rowIndex / sizeof rowIndex[0])), vector <int>(columnIndex, columnIndex + (sizeof columnIndex / sizeof columnIndex[0])), vector <int>(element, element + (sizeof element / sizeof element[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 3;
			int m                     = 3;
			int rowIndex[]            = {0, 0, 2, 2};
			int columnIndex[]         = {0, 2, 2, 0};
			int element[]             = {1, 1, 1, 1};
			int expected__            = 15;

			clock_t start__           = clock();
			int received__            = TheMountain().minSum(n, m, vector <int>(rowIndex, rowIndex + (sizeof rowIndex / sizeof rowIndex[0])), vector <int>(columnIndex, columnIndex + (sizeof columnIndex / sizeof columnIndex[0])), vector <int>(element, element + (sizeof element / sizeof element[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 2;
			int m                     = 2;
			int rowIndex[]            = {0, 0, 1, 1};
			int columnIndex[]         = {0, 1, 1, 0};
			int element[]             = {5, 8, 5, 8};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = TheMountain().minSum(n, m, vector <int>(rowIndex, rowIndex + (sizeof rowIndex / sizeof rowIndex[0])), vector <int>(columnIndex, columnIndex + (sizeof columnIndex / sizeof columnIndex[0])), vector <int>(element, element + (sizeof element / sizeof element[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 1;
			int m                     = 3;
			int rowIndex[]            = {0};
			int columnIndex[]         = {1};
			int element[]             = {1};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = TheMountain().minSum(n, m, vector <int>(rowIndex, rowIndex + (sizeof rowIndex / sizeof rowIndex[0])), vector <int>(columnIndex, columnIndex + (sizeof columnIndex / sizeof columnIndex[0])), vector <int>(element, element + (sizeof element / sizeof element[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int n                     = 123;
			int m                     = 45;
			int rowIndex[]            = {2, 3, 5, 7, 11};
			int columnIndex[]         = {13, 17, 19, 23, 29};
			int element[]             = {100, 200, 300, 400, 500};
			int expected__            = 367047;

			clock_t start__           = clock();
			int received__            = TheMountain().minSum(n, m, vector <int>(rowIndex, rowIndex + (sizeof rowIndex / sizeof rowIndex[0])), vector <int>(columnIndex, columnIndex + (sizeof columnIndex / sizeof columnIndex[0])), vector <int>(element, element + (sizeof element / sizeof element[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int n                     = 200;
			int m                     = 200;
			int rowIndex[]            = {5};
			int columnIndex[]         = {8};
			int element[]             = {666};
			int expected__            = 5737554;

			clock_t start__           = clock();
			int received__            = TheMountain().minSum(n, m, vector <int>(rowIndex, rowIndex + (sizeof rowIndex / sizeof rowIndex[0])), vector <int>(columnIndex, columnIndex + (sizeof columnIndex / sizeof columnIndex[0])), vector <int>(element, element + (sizeof element / sizeof element[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			int n                     = 10;
			int m                     = 10;
			int rowIndex[]            = {0, 8, 7};
			int columnIndex[]         = {3, 1, 9};
			int element[]             = {5, 4, 7};
			int expected__            = 593;

			clock_t start__           = clock();
			int received__            = TheMountain().minSum(n, m, vector <int>(rowIndex, rowIndex + (sizeof rowIndex / sizeof rowIndex[0])), vector <int>(columnIndex, columnIndex + (sizeof columnIndex / sizeof columnIndex[0])), vector <int>(element, element + (sizeof element / sizeof element[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 8: {
			int n                     = ;
			int m                     = ;
			int rowIndex[]            = ;
			int columnIndex[]         = ;
			int element[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheMountain().minSum(n, m, vector <int>(rowIndex, rowIndex + (sizeof rowIndex / sizeof rowIndex[0])), vector <int>(columnIndex, columnIndex + (sizeof columnIndex / sizeof columnIndex[0])), vector <int>(element, element + (sizeof element / sizeof element[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int n                     = ;
			int m                     = ;
			int rowIndex[]            = ;
			int columnIndex[]         = ;
			int element[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheMountain().minSum(n, m, vector <int>(rowIndex, rowIndex + (sizeof rowIndex / sizeof rowIndex[0])), vector <int>(columnIndex, columnIndex + (sizeof columnIndex / sizeof columnIndex[0])), vector <int>(element, element + (sizeof element / sizeof element[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			int n                     = ;
			int m                     = ;
			int rowIndex[]            = ;
			int columnIndex[]         = ;
			int element[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheMountain().minSum(n, m, vector <int>(rowIndex, rowIndex + (sizeof rowIndex / sizeof rowIndex[0])), vector <int>(columnIndex, columnIndex + (sizeof columnIndex / sizeof columnIndex[0])), vector <int>(element, element + (sizeof element / sizeof element[0])));
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
