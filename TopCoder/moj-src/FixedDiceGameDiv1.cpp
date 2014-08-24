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


class FixedDiceGameDiv1 {
public:
	double getExpectation(int a, int b, int c, int d);
};


double dp[2][2555];

void f(int a, int b, double *p) {
	clr(dp, 0);
	dp[0][0] = 1.0;
	bool now = false;
	rep(i, 0, a) {
		clr(dp[!now], 0);
		rep(j, 0, 2555) if(dp[now][j]) {
			rep(k, 1, b+1) dp[!now][j+k] += dp[now][j] * 1.0 / b;
		}
		now = !now;
	}
	rep(i, 0, 2555) p[i] = dp[now][i];
}

double p1[2555], p2[2555];

double FixedDiceGameDiv1::getExpectation(int a, int b, int c, int d) {
	//freopen("e:/out.txt", "w", stdout);
	f(a, b, p1);
	f(c, d, p2);
	double div = 0.0, ans = 0.0;
	//if( c*d< 30) {
	//	rep(i, 0, a*b+1) cout<<p1[i]<<' '; cout<<endl;
	//	rep(i, 0, c*d+1) cout<<i<<' '<<p2[i]<<endl;
	//}
	rep(i, 0, 2555) {
		//cout<<i<<' '<<p1[i]<<endl;
		double ddd = 0.0;
		rep(j, 0, i) ddd += p2[j];
		//cout<<i<<' '<<ddd<<endl;
		ans += i * p1[i] * ddd;
		div += p1[i] * ddd;
	}
	if(div == 0) return -1;
	cout<<div<<endl;
	return ans / div;
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
			int a                     = 1;
			int b                     = 2;
			int c                     = 1;
			int d                     = 5;
			double expected__         = 2.0;

			clock_t start__           = clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a                     = 3;
			int b                     = 1;
			int c                     = 1;
			int d                     = 3;
			double expected__         = 3.0;

			clock_t start__           = clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a                     = 1;
			int b                     = 5;
			int c                     = 1;
			int d                     = 1;
			double expected__         = 3.4999999999999996;

			clock_t start__           = clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a                     = 2;
			int b                     = 6;
			int c                     = 50;
			int d                     = 30;
			double expected__         = -1.0;

			clock_t start__           = clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a                     = 50;
			int b                     = 11;
			int c                     = 50;
			int d                     = 50;
			double expected__         = 369.8865999182022;

			clock_t start__           = clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int a                     = ;
			int b                     = ;
			int c                     = ;
			int d                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a                     = ;
			int b                     = ;
			int c                     = ;
			int d                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a                     = ;
			int b                     = ;
			int c                     = ;
			int d                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = FixedDiceGameDiv1().getExpectation(a, b, c, d);
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
