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


class TurnOnLamps {
public:
	int minimize(vector <int> roads, string initState, string isImportant);
};

vector<int> adj[55];
int n;
int dp[55][2];

string init;
string imp;

void check(int &a, int b){
	a = min(a, b);
}

void dfs(int u) {
	if(adj[u].size() == 0) {
		dp[u][0] = 0;
		dp[u][1] = 1;
		return;
	}
	bool first = true;
	rep(i, 0, sz(adj[u])) {
		int v = adj[u][i];
		dfs(v);
		int tmp[2] = {dp[u][0], dp[u][1]};

		rep(j, 0, 2) if(dp[v][j] < 1000000){
			if(imp[v-1]=='1' && init[v-1]=='0' && j==0) continue;
			if(imp[v-1]=='1' && init[v-1]=='1' && j==1) continue;
			if(first) {
				dp[u][j] = dp[v][j];
				continue;
			}
			rep(x, 0, 2) {
				check(dp[u][(x+j)%2], tmp[x]+dp[v][j]);
			}
		}
		first = false;
	}
	check(dp[u][0], dp[u][1]+1);
	check(dp[u][1], dp[u][0]+1);
}

int TurnOnLamps::minimize(vector <int> roads, string initState, string isImportant) {
	n = sz(roads) + 1;
	rep(i, 0, n) adj[i].clear();
	rep(i, 0, sz(roads)) {
		adj[roads[i]].push_back(i+1);
	}
	clr(dp, 0x3f);
	init = initState;
	imp = isImportant;
	dfs(0);
	return dp[0][0]/2;
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
			int roads[]               = {0,0,1,1};
			string initState          = "0001";
			string isImportant        = "0111";
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int roads[]               = {0,0,1,1};
			string initState          = "0000";
			string isImportant        = "0111";
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int roads[]               = {0,0,1,1,4,4};
			string initState          = "000100";
			string isImportant        = "111111";
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int roads[]               = {0,0,1,1,4,4};
			string initState          = "100100";
			string isImportant        = "011101";
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int roads[]               = {0,0,2,2,3,1,6,3,1};
			string initState          = "010001110";
			string isImportant        = "000110100";
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int roads[]               = {0,0,1,2,4,4,6,1,2,5,2,8,8,3,6,4,14,7,18,14,11,7,1,12,7,5,18,23,0,14,11,10,2,2,6,1,30,11,9,12,5,35,25,11,23,17,14,45,15};
			string initState          = "0000000000010000000000000010000010100000000000000";
			string isImportant        = "1010111111111011011111000110111111111111111110111";
			int expected__            = 14;

			clock_t start__           = clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int roads[]               = ;
			string initState          = ;
			string isImportant        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int roads[]               = ;
			string initState          = ;
			string isImportant        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int roads[]               = ;
			string initState          = ;
			string isImportant        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
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
