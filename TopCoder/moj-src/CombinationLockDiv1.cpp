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


class CombinationLockDiv1 {
public:
	int minimumMoves(vector <string> P, vector <string> Q);
};

int dp[3000][11][11];

void check(int &a, int b) {
	if(b < a) a = b;
}

int CombinationLockDiv1::minimumMoves(vector <string> P, vector <string> Q) {
	string s1 = "5", s2 = "5";
	rep(i, 0, sz(P)) s1 += P[i];
	rep(i, 0, sz(Q)) s2 += Q[i];

	clr(dp, 0x3f);
	dp[0][0][0] = 0;

	rep(i, 0, sz(s1)-1) rep(x, 0, 11) rep(y, 0, 11) if(dp[i][x][y] < 100000000) {
		int a = s1[i+1] - '0';
		int b = s2[i+1] - '0';
		rep(xx, 0, x+1) rep(yy, 0, y+1) {
			int na = a + xx - yy;
			int axx = (b - na + 100)%10;
			check(dp[i+1][min(10, xx+axx)][yy], dp[i][x][y] + axx);

			int ayy = (na - b + 100)%10;
			check(dp[i+1][xx][min(10, yy+ayy)], dp[i][x][y] + ayy);
		}
	}
	int ret = 1000000;
	rep(x, 0, 11) rep(y, 0, 11) check(ret, dp[sz(s1)-1][x][y]);
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
			string P[]                = {"123"};
			string Q[]                = {"112"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string P[]                = {"1"};
			string Q[]                = {"7"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string P[]                = {"6","07"};
			string Q[]                = {"","60","7"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string P[]                = {"1234"};
			string Q[]                = {"4567"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string P[]                = {"020"};
			string Q[]                = {"909"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string P[]                = {"4423232218340"};
			string Q[]                = {"6290421476245"};
			int expected__            = 18;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string P[]                = ;
			string Q[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string P[]                = ;
			string Q[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string P[]                = ;
			string Q[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = CombinationLockDiv1().minimumMoves(vector <string>(P, P + (sizeof P / sizeof P[0])), vector <string>(Q, Q + (sizeof Q / sizeof Q[0])));
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
