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


class FoxAndCity {
public:
	int minimalCost(vector <string> linked, vector <int> want);
};


int FoxAndCity::minimalCost(vector <string> linked, vector <int> want) {
	
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
			string linked[]           = {"NYN",
 "YNY",
 "NYN"};
			int want[]                = {0, 1, 1};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])), vector <int>(want, want + (sizeof want / sizeof want[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string linked[]           = {"NYNN",
 "YNYN",
 "NYNY",
 "NNYN"};
			int want[]                = {0, 3, 3, 3};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])), vector <int>(want, want + (sizeof want / sizeof want[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string linked[]           = {"NYNNNY",
 "YNYNNN",
 "NYNYNN",
 "NNYNYN",
 "NNNYNY",
 "YNNNYN"};
			int want[]                = {0, 2, 2, 2, 2, 2};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])), vector <int>(want, want + (sizeof want / sizeof want[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string linked[]           = {"NYY","YNN","YNN"};
			int want[]                = {0,0,0};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])), vector <int>(want, want + (sizeof want / sizeof want[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string linked[]           = {"NYNNNN",
 "YNYNNN",
 "NYNYYY",
 "NNYNYY",
 "NNYYNY",
 "NNYYYN"}
;
			int want[]                = {0, 1, 2, 3, 0, 3};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])), vector <int>(want, want + (sizeof want / sizeof want[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string linked[]           = {"NYNNNN",
 "YNYNNN",
 "NYNYYY",
 "NNYNYY",
 "NNYYNY",
 "NNYYYN"};
			int want[]                = {0, 1, 2, 4, 0, 4};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])), vector <int>(want, want + (sizeof want / sizeof want[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string linked[]           = {"NYNYYYYYYYY","YNYNNYYNYYY","NYNNNYYNYYN","YNNNYYYYYYY","YNNYNYYYNYY","YYYYYNNYYNY","YYYYYNNNYYY","YNNYYYNNNYY","YYYYNYYNNNY","YYYYYNYYNNY","YYNYYYYYYYN"};
			int want[]                = {0,1,2,0,0,5,1,3,0,2,3};
			int expected__            = 28;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])), vector <int>(want, want + (sizeof want / sizeof want[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string linked[]           = ;
			int want[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])), vector <int>(want, want + (sizeof want / sizeof want[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string linked[]           = ;
			int want[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])), vector <int>(want, want + (sizeof want / sizeof want[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string linked[]           = ;
			int want[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])), vector <int>(want, want + (sizeof want / sizeof want[0])));
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
