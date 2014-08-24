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


class FoxAndFencing {
public:
	string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d);
};


const string Yes = "Ciel";
const string Draw = "Draw";
const string No = "Liss";

string FoxAndFencing::WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d) {
	if(mov1 + rng1 >= d) return Yes;
	if(mov1 > mov2) {
		if(mov1+rng1 <= rng2) return Draw;

	}
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
			int mov1                  = 1;
			int mov2                  = 58;
			int rng1                  = 1;
			int rng2                  = 58;
			int d                     = 2;
			string expected__         = "Ciel";

			clock_t start__           = clock();
			string received__         = FoxAndFencing().WhoCanWin(mov1, mov2, rng1, rng2, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int mov1                  = 2;
			int mov2                  = 1;
			int rng1                  = 1;
			int rng2                  = 100;
			int d                     = 50;
			string expected__         = "Liss";

			clock_t start__           = clock();
			string received__         = FoxAndFencing().WhoCanWin(mov1, mov2, rng1, rng2, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int mov1                  = 2;
			int mov2                  = 1;
			int rng1                  = 1;
			int rng2                  = 100;
			int d                     = 150;
			string expected__         = "Draw";

			clock_t start__           = clock();
			string received__         = FoxAndFencing().WhoCanWin(mov1, mov2, rng1, rng2, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int mov1                  = 100;
			int mov2                  = 100;
			int rng1                  = 100;
			int rng2                  = 100;
			int d                     = 100000000;
			string expected__         = "Draw";

			clock_t start__           = clock();
			string received__         = FoxAndFencing().WhoCanWin(mov1, mov2, rng1, rng2, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int mov1                  = 100;
			int mov2                  = 1;
			int rng1                  = 100;
			int rng2                  = 1;
			int d                     = 100000000;
			string expected__         = "Ciel";

			clock_t start__           = clock();
			string received__         = FoxAndFencing().WhoCanWin(mov1, mov2, rng1, rng2, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int mov1                  = 100;
			int mov2                  = 1;
			int rng1                  = 100;
			int rng2                  = 250;
			int d                     = 100000000;
			string expected__         = "Draw";

			clock_t start__           = clock();
			string received__         = FoxAndFencing().WhoCanWin(mov1, mov2, rng1, rng2, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int mov1                  = 100;
			int mov2                  = 1;
			int rng1                  = 100;
			int rng2                  = 150;
			int d                     = 100000000;
			string expected__         = "Ciel";

			clock_t start__           = clock();
			string received__         = FoxAndFencing().WhoCanWin(mov1, mov2, rng1, rng2, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			int mov1                  = 100;
			int mov2                  = 50;
			int rng1                  = 100;
			int rng2                  = 1;
			int d                     = 100000000;
			string expected__         = "Ciel";

			clock_t start__           = clock();
			string received__         = FoxAndFencing().WhoCanWin(mov1, mov2, rng1, rng2, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 8: {
			int mov1                  = 100;
			int mov2                  = 150;
			int rng1                  = 100;
			int rng2                  = 1;
			int d                     = 100000000;
			string expected__         = "Draw";

			clock_t start__           = clock();
			string received__         = FoxAndFencing().WhoCanWin(mov1, mov2, rng1, rng2, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 9: {
			int mov1                  = ;
			int mov2                  = ;
			int rng1                  = ;
			int rng2                  = ;
			int d                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndFencing().WhoCanWin(mov1, mov2, rng1, rng2, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			int mov1                  = ;
			int mov2                  = ;
			int rng1                  = ;
			int rng2                  = ;
			int d                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndFencing().WhoCanWin(mov1, mov2, rng1, rng2, d);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 11: {
			int mov1                  = ;
			int mov2                  = ;
			int rng1                  = ;
			int rng2                  = ;
			int d                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndFencing().WhoCanWin(mov1, mov2, rng1, rng2, d);
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
