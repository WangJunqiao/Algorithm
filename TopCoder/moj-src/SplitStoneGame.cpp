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


class SplitStoneGame {
public:
	string winOrLose(vector <int> number);
};

int memo[55][55];

bool dfs(int one, int two) {
	if(two==0) return false;
	if(one+two < 3) return false;

	if(memo[one][two] >=0) return memo[one][two];

	int &ret = memo[one][two];
	if(one>=2 && dfs(one-2, two+1)==false) return ret = 1;
	if(one>=1 && two>=2 && dfs(one-1, two) ==false) return ret = 1;
	if(two>=3 && dfs(one, two-1)==false) return ret = 1;
	return ret = 0;
}

string SplitStoneGame::winOrLose(vector <int> number) {
	clr(memo, -1);
	int one = 0, two = 0;
	rep(i, 0, sz(number)) if(number[i]==1) one ++; else two ++;
	if(dfs(one, two)) return "WIN";
	else return "LOSE";
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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int number[]              = {1, 1, 1};
			string expected__         = "LOSE";

			clock_t start__           = clock();
			string received__         = SplitStoneGame().winOrLose(vector <int>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int number[]              = {2, 2};
			string expected__         = "LOSE";

			clock_t start__           = clock();
			string received__         = SplitStoneGame().winOrLose(vector <int>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int number[]              = {1, 1, 2};
			string expected__         = "WIN";

			clock_t start__           = clock();
			string received__         = SplitStoneGame().winOrLose(vector <int>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int number[]              = {1, 2, 3, 4, 3, 2, 2, 4, 3, 1, 4, 4, 1, 2, 4, 4, 1, 4, 3, 1, 4, 2, 1};
			string expected__         = "WIN";

			clock_t start__           = clock();
			string received__         = SplitStoneGame().winOrLose(vector <int>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int number[]              = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 3, 1, 9, 1, 3, 1, 1, 1, 1, 1};
			string expected__         = "LOSE";

			clock_t start__           = clock();
			string received__         = SplitStoneGame().winOrLose(vector <int>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int number[]              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = SplitStoneGame().winOrLose(vector <int>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int number[]              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = SplitStoneGame().winOrLose(vector <int>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int number[]              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = SplitStoneGame().winOrLose(vector <int>(number, number + (sizeof number / sizeof number[0])));
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
