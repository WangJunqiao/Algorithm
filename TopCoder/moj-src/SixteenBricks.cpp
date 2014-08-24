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


class SixteenBricks {
public:
	int maximumSurface(vector <int> height);
};


int SixteenBricks::maximumSurface(vector <int> height) {
	sort(all(height));
	int ans = 16, ret = 0;
	rep(i, 8, 16) ans += 4 * height[i];

	vector<int> per;
	rep(i, 0, 8) per.push_back(i);
	do{
		int tmp = ans;
		tmp -= 4*height[per[0]];
		tmp -= 4*height[per[1]];
		for(int i=2;i<6;i++) {
			tmp = tmp - 2*height[per[i]];
		}
		ret = max(ret, tmp);
	}while(next_permutation(all(per)));

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
			int height[]              = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
			int expected__            = 32;

			clock_t start__           = clock();
			int received__            = SixteenBricks().maximumSurface(vector <int>(height, height + (sizeof height / sizeof height[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int height[]              = {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2};
			int expected__            = 64;

			clock_t start__           = clock();
			int received__            = SixteenBricks().maximumSurface(vector <int>(height, height + (sizeof height / sizeof height[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int height[]              = {77, 78, 58, 34, 30, 20, 8, 71, 37, 74, 21, 45, 39, 16, 4, 59} ;
			int expected__            = 1798;

			clock_t start__           = clock();
			int received__            = SixteenBricks().maximumSurface(vector <int>(height, height + (sizeof height / sizeof height[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 3: {
			int height[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SixteenBricks().maximumSurface(vector <int>(height, height + (sizeof height / sizeof height[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 4: {
			int height[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SixteenBricks().maximumSurface(vector <int>(height, height + (sizeof height / sizeof height[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int height[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SixteenBricks().maximumSurface(vector <int>(height, height + (sizeof height / sizeof height[0])));
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
