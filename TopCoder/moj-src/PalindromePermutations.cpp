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


class PalindromePermutations {
public:
	double palindromeProbability(string word);
};

double dp[55][55];

double get(vector<int> v) {
	double ret = 1.0;
	rep(x, 0, sz(v)) {
		int n = 0;
		rep(i, x, sz(v)) n += v[i];
		n /= 2;
		dp[0][v[x]] = 1.0;
		rep(i, 0, n) rep(j, 0, 55) if(dp[i][j]!=0){
			int nn = (n-i) * 2;

			dp[i+1][j] += dp[i][j] * (nn-j)*(nn-j-1)/(double)(nn*(nn-1));
			if(j) dp[i+1][j-2] += dp[i][j] * j*(j-1)/(double)(nn*(nn-1));
		}

		ret *= dp[n][0];
	}
	return ret;
}

double PalindromePermutations::palindromeProbability(string word) {
	map<int, int> mp;
	rep(i, 0, sz(word)) mp[word[i]] ++;
	vector<int> v;
	rep(i, 0, 200) if(mp.find(i)!=mp.end()) v.push_back(mp[i]);

	int n = sz(word);
	int sid = -1, num = 0;
	rep(i, 0, sz(v)) if(v[i]%2==1) {
		num ++;
		sid = i;
	}
	if(num > 1) return 0.0;
	double mul = 1.0;
	if(num==1) {
		mul = v[sid]/(double)n;
		v[sid]--;
		if(v[sid]==0) v.erase(v.begin()+sid);
	}
	return mul * get(v);
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
			string word               = "haha";
			double expected__         = 0.3333333333333333;

			clock_t start__           = clock();
			double received__         = PalindromePermutations().palindromeProbability(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string word               = "xxxxy";
			double expected__         = 0.2;

			clock_t start__           = clock();
			double received__         = PalindromePermutations().palindromeProbability(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string word               = "xxxx";
			double expected__         = 1.0;

			clock_t start__           = clock();
			double received__         = PalindromePermutations().palindromeProbability(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string word               = "abcde";
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = PalindromePermutations().palindromeProbability(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string word               = "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhff";
			double expected__         = 0.025641025641025637;

			clock_t start__           = clock();
			double received__         = PalindromePermutations().palindromeProbability(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string word               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = PalindromePermutations().palindromeProbability(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string word               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = PalindromePermutations().palindromeProbability(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string word               = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = PalindromePermutations().palindromeProbability(word);
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
