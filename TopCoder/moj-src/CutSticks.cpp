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

//----------------------zjut_DD for Topcoder-------------------------------
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
#define PB push_back
#define MP make_pair
#define ff first
#define ss second
#define two(w) (1<<(w))
#define test(x,w) (x&two(w))
#define sz(v) (int)v.size()
#define all(c) c.begin(),c.end() 
#define clr(buf,val) memset(buf,val,sizeof(buf))
#define rep(i,l,r) for(int i=(l);i<(r);i++)
#define repv(i,v)  for(int i=0;i<(int)v.size();i++)
#define repi(it,c) for(typeof(c.begin()) it=c.begin();it!=c.end();++it)
//------------------------------------------------------------------------


class CutSticks {
public:
	double maxKth(vector <int> sticks, int C, int K);
};


double CutSticks::maxKth(vector <int> sticks, int C, int K) {
	
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
			int sticks[]              = {5, 8};
			int C                     = 1;
			int K                     = 1;
			double expected__         = 8.0;

			clock_t start__           = clock();
			double received__         = CutSticks().maxKth(vector <int>(sticks, sticks + (sizeof sticks / sizeof sticks[0])), C, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int sticks[]              = {5, 8};
			int C                     = 1;
			int K                     = 2;
			double expected__         = 5.0;

			clock_t start__           = clock();
			double received__         = CutSticks().maxKth(vector <int>(sticks, sticks + (sizeof sticks / sizeof sticks[0])), C, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int sticks[]              = {5, 8};
			int C                     = 1;
			int K                     = 3;
			double expected__         = 4.0;

			clock_t start__           = clock();
			double received__         = CutSticks().maxKth(vector <int>(sticks, sticks + (sizeof sticks / sizeof sticks[0])), C, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int sticks[]              = {1000000000, 1000000000, 1};
			int C                     = 2;
			int K                     = 5;
			double expected__         = 1.0;

			clock_t start__           = clock();
			double received__         = CutSticks().maxKth(vector <int>(sticks, sticks + (sizeof sticks / sizeof sticks[0])), C, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int sticks[]              = {76, 594, 17, 6984, 26, 57, 9, 876, 5816, 73, 969, 527, 49};
			int C                     = 789;
			int K                     = 456;
			double expected__         = 34.92;

			clock_t start__           = clock();
			double received__         = CutSticks().maxKth(vector <int>(sticks, sticks + (sizeof sticks / sizeof sticks[0])), C, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int sticks[]              = ;
			int C                     = ;
			int K                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = CutSticks().maxKth(vector <int>(sticks, sticks + (sizeof sticks / sizeof sticks[0])), C, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int sticks[]              = ;
			int C                     = ;
			int K                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = CutSticks().maxKth(vector <int>(sticks, sticks + (sizeof sticks / sizeof sticks[0])), C, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int sticks[]              = ;
			int C                     = ;
			int K                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = CutSticks().maxKth(vector <int>(sticks, sticks + (sizeof sticks / sizeof sticks[0])), C, K);
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
