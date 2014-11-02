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


class GreaterGame {
public:
	double calc(vector <int> hand, vector <int> sothe);
};


double GreaterGame::calc(vector <int> a, vector <int> b) {
	int n = a.size();
	bool vst[110] = {false};
	for (int i = 0; i < a.size(); i ++) {
        vst[a[i]] = true;
	}
	for (int i = 0; i < b.size(); i ++) {
        vst[b[i]] = true;
	}
	sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int cannt = 0, fu = 0;
    double ans = 0.0;
    for (int i = 0; i < b.size(); i ++) {
        if (b[i] < 0) {
            fu ++;
            continue;
        }
        int j = -1;
        for (int k = 0; k < a.size(); k ++) {
            if (a[k] > b[i]) {
                j = k;
                break;
            }
        }
        if (j >= 0) {
            a.erase(a.begin() + j);
            ans += 1.0;
        } else {
            cannt ++;
        }
    }
    for (int i = 0; i < cannt; i ++) {
        a.erase(a.begin());
    }
    for (int i = 0; i < a.size(); i ++) {
        int num = 0;
        for (int j = 1; j <= 2 * n; j ++) {
            if (vst[j] == false && a[i] > j) {
                num ++;
            }
        }
        ans += num / (double)fu;
    }
    return ans;
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
			int hand[]                = {4,2};
			int sothe[]               = {-1,-1};
			double expected__         = 1.5;

			clock_t start__           = clock();
			double received__         = GreaterGame().calc(vector <int>(hand, hand + (sizeof hand / sizeof hand[0])), vector <int>(sothe, sothe + (sizeof sothe / sizeof sothe[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int hand[]                = {4,2};
			int sothe[]               = {1,3};
			double expected__         = 2.0;

			clock_t start__           = clock();
			double received__         = GreaterGame().calc(vector <int>(hand, hand + (sizeof hand / sizeof hand[0])), vector <int>(sothe, sothe + (sizeof sothe / sizeof sothe[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int hand[]                = {2};
			int sothe[]               = {-1};
			double expected__         = 1.0;

			clock_t start__           = clock();
			double received__         = GreaterGame().calc(vector <int>(hand, hand + (sizeof hand / sizeof hand[0])), vector <int>(sothe, sothe + (sizeof sothe / sizeof sothe[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int hand[]                = {1,3,5,7};
			int sothe[]               = {8,-1,4,-1};
			double expected__         = 2.5;

			clock_t start__           = clock();
			double received__         = GreaterGame().calc(vector <int>(hand, hand + (sizeof hand / sizeof hand[0])), vector <int>(sothe, sothe + (sizeof sothe / sizeof sothe[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int hand[]                = {6,12,17,14,20,8,16,7,2,15};
			int sothe[]               = {-1,-1,4,-1,11,3,13,-1,-1,18};
			double expected__         = 8.0;

			clock_t start__           = clock();
			double received__         = GreaterGame().calc(vector <int>(hand, hand + (sizeof hand / sizeof hand[0])), vector <int>(sothe, sothe + (sizeof sothe / sizeof sothe[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int hand[]                = ;
			int sothe[]               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = GreaterGame().calc(vector <int>(hand, hand + (sizeof hand / sizeof hand[0])), vector <int>(sothe, sothe + (sizeof sothe / sizeof sothe[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int hand[]                = ;
			int sothe[]               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = GreaterGame().calc(vector <int>(hand, hand + (sizeof hand / sizeof hand[0])), vector <int>(sothe, sothe + (sizeof sothe / sizeof sothe[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int hand[]                = ;
			int sothe[]               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = GreaterGame().calc(vector <int>(hand, hand + (sizeof hand / sizeof hand[0])), vector <int>(sothe, sothe + (sizeof sothe / sizeof sothe[0])));
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
