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


class SubstringReversal {
public:
	vector <int> solve(string S);
};


vector <int> SubstringReversal::solve(string S) {

	int id = 0, L = 0, R = 0;
	string tmp = S;
	while(id<sz(S)) {
		bool have = false;
		rep(i, id+1, sz(S)) if(S[i] < S[id]) have = true;
		if(have) break;
		id++;
	}
	if(id<sz(S)) {
		rep(j, id, sz(S)) {
			string tt = S.substr(id, j-id+1);
			reverse(all(tt));
			string ss = S.substr(0, id) + tt + S.substr(j+1);
			if(ss < tmp) {
				L = id; R = j;
				tmp = ss;
			}
		}
	}
	vector<int> ret;
	ret.push_back(L);
	ret.push_back(R);
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

	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, clock_t elapsed) { 
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
			string S                  = "abdc";
			int expected__[]          = {2, 3 };

			clock_t start__           = clock();
			vector <int> received__   = SubstringReversal().solve(S);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
				}
		case 1: {
			string S                  = "aabbcc";
			int expected__[]          = {0, 0 };

			clock_t start__           = clock();
			vector <int> received__   = SubstringReversal().solve(S);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
				}
		case 2: {
			string S                  = "misof";
			int expected__[]          = {0, 4 };

			clock_t start__           = clock();
			vector <int> received__   = SubstringReversal().solve(S);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
				}
		case 3: {
			string S                  = "ivan";
			int expected__[]          = {0, 2 };

			clock_t start__           = clock();
			vector <int> received__   = SubstringReversal().solve(S);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
				}
		case 4: {
			string S                  = "thisseemstobeaneasyproblem";
			int expected__[]          = {0, 13 };

			clock_t start__           = clock();
			vector <int> received__   = SubstringReversal().solve(S);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
				}

				// custom cases

				/*      case 5: {
				string S                  = ;
				int expected__[]          = ;

				clock_t start__           = clock();
				vector <int> received__   = SubstringReversal().solve(S);
				return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
				}*/
				/*      case 6: {
				string S                  = ;
				int expected__[]          = ;

				clock_t start__           = clock();
				vector <int> received__   = SubstringReversal().solve(S);
				return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
				}*/
				/*      case 7: {
				string S                  = ;
				int expected__[]          = ;

				clock_t start__           = clock();
				vector <int> received__   = SubstringReversal().solve(S);
				return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
