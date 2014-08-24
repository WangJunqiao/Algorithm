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


class AliceBobShuffle {
public:
	int countWays(vector <int> AliceStart, vector <int> BobStart, vector <int> AliceEnd, vector <int> BobEnd);
};


int AliceBobShuffle::countWays(vector <int> AliceStart, vector <int> BobStart, vector <int> AliceEnd, vector <int> BobEnd) {
	
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
			int AliceStart[]          = {1, 3};
			int BobStart[]            = {2, 4};
			int AliceEnd[]            = {2, 3};
			int BobEnd[]              = {1, 4};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = AliceBobShuffle().countWays(vector <int>(AliceStart, AliceStart + (sizeof AliceStart / sizeof AliceStart[0])), vector <int>(BobStart, BobStart + (sizeof BobStart / sizeof BobStart[0])), vector <int>(AliceEnd, AliceEnd + (sizeof AliceEnd / sizeof AliceEnd[0])), vector <int>(BobEnd, BobEnd + (sizeof BobEnd / sizeof BobEnd[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int AliceStart[]          = {1, 2, 1};
			int BobStart[]            = {1, 2};
			int AliceEnd[]            = {1, 2, 1};
			int BobEnd[]              = {2, 1};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = AliceBobShuffle().countWays(vector <int>(AliceStart, AliceStart + (sizeof AliceStart / sizeof AliceStart[0])), vector <int>(BobStart, BobStart + (sizeof BobStart / sizeof BobStart[0])), vector <int>(AliceEnd, AliceEnd + (sizeof AliceEnd / sizeof AliceEnd[0])), vector <int>(BobEnd, BobEnd + (sizeof BobEnd / sizeof BobEnd[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int AliceStart[]          = {1};
			int BobStart[]            = {2};
			int AliceEnd[]            = {3};
			int BobEnd[]              = {4};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = AliceBobShuffle().countWays(vector <int>(AliceStart, AliceStart + (sizeof AliceStart / sizeof AliceStart[0])), vector <int>(BobStart, BobStart + (sizeof BobStart / sizeof BobStart[0])), vector <int>(AliceEnd, AliceEnd + (sizeof AliceEnd / sizeof AliceEnd[0])), vector <int>(BobEnd, BobEnd + (sizeof BobEnd / sizeof BobEnd[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int AliceStart[]          = {1, 2};
			int BobStart[]            = {3};
			int AliceEnd[]            = {3};
			int BobEnd[]              = {2, 1};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = AliceBobShuffle().countWays(vector <int>(AliceStart, AliceStart + (sizeof AliceStart / sizeof AliceStart[0])), vector <int>(BobStart, BobStart + (sizeof BobStart / sizeof BobStart[0])), vector <int>(AliceEnd, AliceEnd + (sizeof AliceEnd / sizeof AliceEnd[0])), vector <int>(BobEnd, BobEnd + (sizeof BobEnd / sizeof BobEnd[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int AliceStart[]          = {3, 3, 2, 4, 1, 3, 1, 2, 1, 1, 5, 5, 1, 2, 3, 1, 2, 1, 2, 1, 1, 1, 2};
			int BobStart[]            = {4, 1, 4, 3, 4, 4, 4, 3, 2, 1, 6, 2, 2, 3, 2, 2, 1, 3, 2, 3};
			int AliceEnd[]            = {4, 1, 4, 3, 4, 4, 4, 1, 3, 1, 2, 2, 2, 3, 2, 1, 2, 1, 2, 2, 2};
			int BobEnd[]              = {3, 3, 2, 3, 4, 2, 1, 2, 1, 1, 5, 6, 5, 1, 3, 1, 2, 3, 1, 1, 1, 3};
			int expected__            = 314159265;

			clock_t start__           = clock();
			int received__            = AliceBobShuffle().countWays(vector <int>(AliceStart, AliceStart + (sizeof AliceStart / sizeof AliceStart[0])), vector <int>(BobStart, BobStart + (sizeof BobStart / sizeof BobStart[0])), vector <int>(AliceEnd, AliceEnd + (sizeof AliceEnd / sizeof AliceEnd[0])), vector <int>(BobEnd, BobEnd + (sizeof BobEnd / sizeof BobEnd[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int AliceStart[]          = ;
			int BobStart[]            = ;
			int AliceEnd[]            = ;
			int BobEnd[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AliceBobShuffle().countWays(vector <int>(AliceStart, AliceStart + (sizeof AliceStart / sizeof AliceStart[0])), vector <int>(BobStart, BobStart + (sizeof BobStart / sizeof BobStart[0])), vector <int>(AliceEnd, AliceEnd + (sizeof AliceEnd / sizeof AliceEnd[0])), vector <int>(BobEnd, BobEnd + (sizeof BobEnd / sizeof BobEnd[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int AliceStart[]          = ;
			int BobStart[]            = ;
			int AliceEnd[]            = ;
			int BobEnd[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AliceBobShuffle().countWays(vector <int>(AliceStart, AliceStart + (sizeof AliceStart / sizeof AliceStart[0])), vector <int>(BobStart, BobStart + (sizeof BobStart / sizeof BobStart[0])), vector <int>(AliceEnd, AliceEnd + (sizeof AliceEnd / sizeof AliceEnd[0])), vector <int>(BobEnd, BobEnd + (sizeof BobEnd / sizeof BobEnd[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int AliceStart[]          = ;
			int BobStart[]            = ;
			int AliceEnd[]            = ;
			int BobEnd[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AliceBobShuffle().countWays(vector <int>(AliceStart, AliceStart + (sizeof AliceStart / sizeof AliceStart[0])), vector <int>(BobStart, BobStart + (sizeof BobStart / sizeof BobStart[0])), vector <int>(AliceEnd, AliceEnd + (sizeof AliceEnd / sizeof AliceEnd[0])), vector <int>(BobEnd, BobEnd + (sizeof BobEnd / sizeof BobEnd[0])));
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
