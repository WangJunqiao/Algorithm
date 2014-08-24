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


class Ethernet {
public:
	int connect(vector <int> parent, vector <int> dist, int maxDist);
};


vector<PII> adj[55];
int ret, maxD;

int dfs(int u) {
	vector<int> dd;
	rep(i, 0, sz(adj[u])) {
		int v = adj[u][i].first;
		dd.push_back(dfs(v) + adj[u][i].second);
	}
	sort(all(dd));
	int i = sz(dd) - 1;
	while(i>=0 && dd[i]>maxD) {
		ret ++;
		i--;
	}
	while(i>=1 && dd[i]+dd[i-1]>maxD) {
		ret ++;
		i--;
	}
	return i>=0 ? dd[i] : 0;
}

int Ethernet::connect(vector <int> parent, vector <int> dist, int maxDist) {
	int n = sz(parent) + 1;
	rep(i, 0, n) adj[i].clear();
	rep(i, 0, sz(parent)) {
		adj[parent[i]].push_back(PII(i+1, dist[i]));
	}
	ret = 1;
	maxD = maxDist;
	dfs(0);
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
			int parent[]              = {0,0,0};
			int dist[]                = {1,1,1};
			int maxDist               = 2;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = Ethernet().connect(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int parent[]              = {0,0,0,0,0,0,0};
			int dist[]                = {1,2,3,4,5,6,7};
			int maxDist               = 8;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = Ethernet().connect(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int parent[]              = {0,1,2,3,4,5};
			int dist[]                = {1,2,3,4,5,6};
			int maxDist               = 6;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = Ethernet().connect(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int parent[]              = {0,0,0,1,1};
			int dist[]                = {1,1,1,1,1};
			int maxDist               = 2;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = Ethernet().connect(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int parent[]              = {0,1,0,3,0,5,0,6,0,6,0,6,4,6,9,4,5,5,2,5,2};
			int dist[]                = {93,42,104,105,59,73,161,130,30,81,62,93,131,133,139,5,13,34,25,111,4};
			int maxDist               = 162;
			int expected__            = 11;

			clock_t start__           = clock();
			int received__            = Ethernet().connect(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int parent[]              = ;
			int dist[]                = ;
			int maxDist               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Ethernet().connect(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int parent[]              = ;
			int dist[]                = ;
			int maxDist               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Ethernet().connect(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int parent[]              = ;
			int dist[]                = ;
			int maxDist               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Ethernet().connect(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(dist, dist + (sizeof dist / sizeof dist[0])), maxDist);
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
