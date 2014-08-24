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


class RadioRange {
public:
	double RadiusProbability(vector <int> X, vector <int> Y, vector <int> R, int Z);
};


double RadioRange::RadiusProbability(vector <int> X, vector <int> Y, vector <int> R, int Z) {
	set<double> st;
	st.insert(0);
	st.insert(Z);
	//cout<<fabs(4.054354)<<endl;
	for(int i=0;i<sz(X);i++) {
		double d = sqrt(X[i]*(double)X[i] + Y[i]*(double)Y[i]);
		cout<<d<<endl;
		if(fabs(R[i]-d) < Z) st.insert(fabs(R[i]-d));
		if(R[i]+d < Z) st.insert(R[i]+d);
	}
	
	vector<double> seg(all(st));
	rep(i, 0, sz(seg)) cout<<seg[i]<<' '; cout<<endl;
	
	double ret = 0.0;
	for(int i=0;i<sz(seg)-1;i++) {
		double r = (seg[i]+seg[i+1]) / 2.0;
		bool can = true;
		for(int j=0;j<sz(X);j++) {
			double d = sqrt(X[j]*(double)X[j] + Y[j]*(double)Y[j]);
			if(d>=r+R[j] || d<=r-R[j]);
			else can = false;
		}
		if(can) {
			ret += (seg[i+1]-seg[i]) / (double)Z;
		}
	}
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
			int X[]                   = {0};
			int Y[]                   = {0};
			int R[]                   = {5};
			int Z                     = 10;
			double expected__         = 0.5;

			clock_t start__           = clock();
			double received__         = RadioRange().RadiusProbability(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), Z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int X[]                   = {0};
			int Y[]                   = {0};
			int R[]                   = {10};
			int Z                     = 10;
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = RadioRange().RadiusProbability(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), Z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int X[]                   = {10};
			int Y[]                   = {10};
			int R[]                   = {10};
			int Z                     = 10;
			double expected__         = 0.4142135623730951;

			clock_t start__           = clock();
			double received__         = RadioRange().RadiusProbability(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), Z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int X[]                   = {11, -11, 0, 0};
			int Y[]                   = {0, 0, 11, -11};
			int R[]                   = {10, 10, 10, 10};
			int Z                     = 31;
			double expected__         = 0.3548387096774194;

			clock_t start__           = clock();
			double received__         = RadioRange().RadiusProbability(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), Z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int X[]                   = {100};
			int Y[]                   = {100};
			int R[]                   = {1};
			int Z                     = 10;
			double expected__         = 1.0;

			clock_t start__           = clock();
			double received__         = RadioRange().RadiusProbability(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), Z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int X[]                   = {1000000000};
			int Y[]                   = {1000000000};
			int R[]                   = {1000000000};
			int Z                     = 1000000000;
			double expected__         = 0.41421356237309503;

			clock_t start__           = clock();
			double received__         = RadioRange().RadiusProbability(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), Z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int X[]                   = {20, -20, 0, 0};
			int Y[]                   = {0, 0, 20, -20};
			int R[]                   = {50, 50, 50, 50};
			int Z                     = 100;
			double expected__         = 0.3;

			clock_t start__           = clock();
			double received__         = RadioRange().RadiusProbability(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), Z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			int X[]                   = {0, -60, -62, -60, 63, -97};
			int Y[]                   = {-72, 67, 61, -8, -32, 89};
			int R[]                   = {6, 7, 8, 7, 5, 6};
			int Z                     = 918;
			double expected__         = 0.9407071068962471;

			clock_t start__           = clock();
			double received__         = RadioRange().RadiusProbability(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), Z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 8: {
			int X[]                   = ;
			int Y[]                   = ;
			int R[]                   = ;
			int Z                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RadioRange().RadiusProbability(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), Z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int X[]                   = ;
			int Y[]                   = ;
			int R[]                   = ;
			int Z                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RadioRange().RadiusProbability(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), Z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			int X[]                   = ;
			int Y[]                   = ;
			int R[]                   = ;
			int Z                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RadioRange().RadiusProbability(vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), Z);
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
