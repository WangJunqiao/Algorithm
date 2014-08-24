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


class SwitchingGame {
public:
	int timeToWin(vector <string> states);
};

int dp[55][55][55];

void check(int &a, int b) {
	a = min(a, b);
}

int SwitchingGame::timeToWin(vector <string> states) {
	int n = sz(states), m = states[0].length();
	states.insert(states.begin(), string(m, '-'));
	cout<<states[0]<<endl;

	clr(dp, 0x3f);
	dp[0][0][0] = 0;
	rep(i, 0, n) rep(x, 0, i+1) rep(y, 0, i+1) {
		bool mustOn = false, mustOff = false;
		for(int j=0;j<m;j++) {
			if(states[i+1][j]=='+') {
				int k = i;
				while(states[k][j]=='?') k--;
				if(states[k][j]=='+') continue;
				if(x>k) continue;
				mustOn = true;
			} else if(states[i+1][j]=='-') {
				int k = i;
				while(states[k][j]=='?') k--;
				if(states[k][j]=='-') continue;
				if(y>k) continue;
				mustOff = true;
			} 
		}
		if(mustOn && mustOff) {
			check(dp[i+1][i+1][i+1], dp[i][x][y]+2);
		} else if(mustOn) {
			check(dp[i+1][i+1][y], dp[i][x][y]+1);
			check(dp[i+1][i+1][i+1], dp[i][x][y]+2);
		} else if(mustOff) {
			check(dp[i+1][x][i+1], dp[i][x][y]+1);
			check(dp[i+1][i+1][i+1], dp[i][x][y]+2);
		} else {
			check(dp[i+1][x][y], dp[i][x][y]);
			check(dp[i+1][i+1][y], dp[i][x][y]+1);
			check(dp[i+1][x][i+1], dp[i][x][y]+1);
			check(dp[i+1][i+1][i+1], dp[i][x][y]+2);
		}
	}
	int ret = 1000000;
	rep(x, 0, n+1) rep(y, 0, n+1) check(ret, dp[n][x][y]);
	return ret + n;
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
			string states[]           = {"++--",
 "--++"};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = SwitchingGame().timeToWin(vector <string>(states, states + (sizeof states / sizeof states[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string states[]           = {"+-++",
 "+-++"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = SwitchingGame().timeToWin(vector <string>(states, states + (sizeof states / sizeof states[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string states[]           = {"++",
 "+?",
 "?+",
 "++"};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = SwitchingGame().timeToWin(vector <string>(states, states + (sizeof states / sizeof states[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string states[]           = {"+", 
 "?",
 "?",
 "?",
 "-"};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = SwitchingGame().timeToWin(vector <string>(states, states + (sizeof states / sizeof states[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string states[]           = {"+??+++",
 "++??+-",
 "?++??+",
 "?-+-??",
 "??+?++",
 "++-?+?",
 "?++?-+",
 "?--+++",
 "-??-?+"}
;
			int expected__            = 20;

			clock_t start__           = clock();
			int received__            = SwitchingGame().timeToWin(vector <string>(states, states + (sizeof states / sizeof states[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string states[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SwitchingGame().timeToWin(vector <string>(states, states + (sizeof states / sizeof states[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string states[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SwitchingGame().timeToWin(vector <string>(states, states + (sizeof states / sizeof states[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string states[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SwitchingGame().timeToWin(vector <string>(states, states + (sizeof states / sizeof states[0])));
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
