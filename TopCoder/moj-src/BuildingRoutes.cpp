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


class BuildingRoutes {
public:
	int build(vector <string> dist, int T);
};


int mat[55][55];
int dis[55][55];

int num[55][55];
bool vst[55][55];


void dfs(int i, int j, int n) {
	rep(k, 0, n) if(i!=k && mat[i][k]+dis[k][j] == dis[i][j]) {
		vst[i][k] = true;
		dfs(k, j, n);
	}
}


int BuildingRoutes::build(vector <string> dist, int T) {
	clr(dis, 0x3f);
	int n = sz(dist);
	rep(i, 0, n) rep(j, 0, n) mat[i][j] = dist[i][j] - '0';
	rep(i, 0, n) rep(j, 0, n) dis[i][j] = mat[i][j];

	rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

	clr(num, 0);
	rep(i, 0, n) rep(j, 0, n) if(i!=j) {
		clr(vst, false);
		dfs(i, j, n);
		rep(x, 0, n) rep(y, 0, n) num[x][y] += vst[x][y];
	}
	int ret = 0;
	rep(i, 0, n) rep(j, 0, n) if(num[i][j] >= T) ret += mat[i][j];
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
			string dist[]             = {"011",
 "101",
 "110"};
			int T                     = 1;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = BuildingRoutes().build(vector <string>(dist, dist + (sizeof dist / sizeof dist[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string dist[]             = {"033",
 "309",
 "390"};
			int T                     = 1;
			int expected__            = 12;

			clock_t start__           = clock();
			int received__            = BuildingRoutes().build(vector <string>(dist, dist + (sizeof dist / sizeof dist[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string dist[]             = {"0123",
 "1023",
 "1203",
 "1230"};
			int T                     = 2;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = BuildingRoutes().build(vector <string>(dist, dist + (sizeof dist / sizeof dist[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string dist[]             = {"05789654",
 "10347583",
 "65085479",
 "55602398",
 "76590934",
 "57939045",
 "12345608",
 "68647640"};
			int T                     = 3;
			int expected__            = 40;

			clock_t start__           = clock();
			int received__            = BuildingRoutes().build(vector <string>(dist, dist + (sizeof dist / sizeof dist[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string dist[]             = ;
			int T                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BuildingRoutes().build(vector <string>(dist, dist + (sizeof dist / sizeof dist[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string dist[]             = ;
			int T                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BuildingRoutes().build(vector <string>(dist, dist + (sizeof dist / sizeof dist[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string dist[]             = ;
			int T                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BuildingRoutes().build(vector <string>(dist, dist + (sizeof dist / sizeof dist[0])), T);
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
