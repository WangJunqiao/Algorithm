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


class RockPaperScissors {
public:
	double bestScore(vector <int> rockProb, vector <int> paperProb, vector <int> scissorsProb);
};


double RockPaperScissors::bestScore(vector <int> rockProb, vector <int> paperProb, vector <int> scissorsProb) {

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
	
	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ(double expected, double result) { if (isnan(expected)) { return isnan(result); } else if (isinf(expected)) { if (expected > 0) { return result > 0 && isinf(result); } else { return result < 0 && isinf(result); } } else if (isnan(result) || isinf(result)) { return false; } else if (fabs(result - expected) < MAX_DOUBLE_ERROR) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }
	
	int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received); 
			if (rerr > 0) {
				sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int rockProb[]            = {100, 100, 100};
			int paperProb[]           = {100, 100, 100};
			int scissorsProb[]        = {100, 100, 100};
			double expected__         = 3.999999999999999;

			clock_t start__           = clock();
			double received__         = RockPaperScissors().bestScore(vector <int>(rockProb, rockProb + (sizeof rockProb / sizeof rockProb[0])), vector <int>(paperProb, paperProb + (sizeof paperProb / sizeof paperProb[0])), vector <int>(scissorsProb, scissorsProb + (sizeof scissorsProb / sizeof scissorsProb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int rockProb[]            = {300};
			int paperProb[]           = {0};
			int scissorsProb[]        = {0};
			double expected__         = 3.0;

			clock_t start__           = clock();
			double received__         = RockPaperScissors().bestScore(vector <int>(rockProb, rockProb + (sizeof rockProb / sizeof rockProb[0])), vector <int>(paperProb, paperProb + (sizeof paperProb / sizeof paperProb[0])), vector <int>(scissorsProb, scissorsProb + (sizeof scissorsProb / sizeof scissorsProb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int rockProb[]            = {300, 0, 0};
			int paperProb[]           = {0, 300, 0};
			int scissorsProb[]        = {0, 0, 300};
			double expected__         = 6.333333333333332;

			clock_t start__           = clock();
			double received__         = RockPaperScissors().bestScore(vector <int>(rockProb, rockProb + (sizeof rockProb / sizeof rockProb[0])), vector <int>(paperProb, paperProb + (sizeof paperProb / sizeof paperProb[0])), vector <int>(scissorsProb, scissorsProb + (sizeof scissorsProb / sizeof scissorsProb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int rockProb[]            = {100, 0};
			int paperProb[]           = {200, 100};
			int scissorsProb[]        = {0, 200};
			double expected__         = 3.7222222222222223;

			clock_t start__           = clock();
			double received__         = RockPaperScissors().bestScore(vector <int>(rockProb, rockProb + (sizeof rockProb / sizeof rockProb[0])), vector <int>(paperProb, paperProb + (sizeof paperProb / sizeof paperProb[0])), vector <int>(scissorsProb, scissorsProb + (sizeof scissorsProb / sizeof scissorsProb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int rockProb[]            = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0};
			int paperProb[]           = {150,300,300,300,300,300,300,300,300,300,300,300,300,300 ,300,300,300,300,300,300,300,300,300,300,300,300,300,300 ,300,300,300,300,300,300,300,300,300,300,300,300,300,300 ,300,300,300,300,300,300,300,300};
			int scissorsProb[]        = {150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0,0};
			double expected__         = 149.00000000000003;

			clock_t start__           = clock();
			double received__         = RockPaperScissors().bestScore(vector <int>(rockProb, rockProb + (sizeof rockProb / sizeof rockProb[0])), vector <int>(paperProb, paperProb + (sizeof paperProb / sizeof paperProb[0])), vector <int>(scissorsProb, scissorsProb + (sizeof scissorsProb / sizeof scissorsProb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int rockProb[]            = ;
			int paperProb[]           = ;
			int scissorsProb[]        = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RockPaperScissors().bestScore(vector <int>(rockProb, rockProb + (sizeof rockProb / sizeof rockProb[0])), vector <int>(paperProb, paperProb + (sizeof paperProb / sizeof paperProb[0])), vector <int>(scissorsProb, scissorsProb + (sizeof scissorsProb / sizeof scissorsProb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int rockProb[]            = ;
			int paperProb[]           = ;
			int scissorsProb[]        = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RockPaperScissors().bestScore(vector <int>(rockProb, rockProb + (sizeof rockProb / sizeof rockProb[0])), vector <int>(paperProb, paperProb + (sizeof paperProb / sizeof paperProb[0])), vector <int>(scissorsProb, scissorsProb + (sizeof scissorsProb / sizeof scissorsProb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int rockProb[]            = ;
			int paperProb[]           = ;
			int scissorsProb[]        = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RockPaperScissors().bestScore(vector <int>(rockProb, rockProb + (sizeof rockProb / sizeof rockProb[0])), vector <int>(paperProb, paperProb + (sizeof paperProb / sizeof paperProb[0])), vector <int>(scissorsProb, scissorsProb + (sizeof scissorsProb / sizeof scissorsProb[0])));
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
