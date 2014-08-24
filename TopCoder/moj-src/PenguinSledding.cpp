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


class PenguinSledding {
public:
	long long countDesigns(int numCheckpoints, vector <int> checkpoint1, vector <int> checkpoint2);
};


long long PenguinSledding::countDesigns(int numCheckpoints, vector <int> checkpoint1, vector <int> checkpoint2) {
	
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) { 
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
			int numCheckpoints        = 2;
			int checkpoint1[]         = {1};
			int checkpoint2[]         = {2};
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = PenguinSledding().countDesigns(numCheckpoints, vector <int>(checkpoint1, checkpoint1 + (sizeof checkpoint1 / sizeof checkpoint1[0])), vector <int>(checkpoint2, checkpoint2 + (sizeof checkpoint2 / sizeof checkpoint2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int numCheckpoints        = 4;
			int checkpoint1[]         = {1,2,3};
			int checkpoint2[]         = {2,3,4};
			long long expected__      = 6;

			clock_t start__           = clock();
			long long received__      = PenguinSledding().countDesigns(numCheckpoints, vector <int>(checkpoint1, checkpoint1 + (sizeof checkpoint1 / sizeof checkpoint1[0])), vector <int>(checkpoint2, checkpoint2 + (sizeof checkpoint2 / sizeof checkpoint2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int numCheckpoints        = 6;
			int checkpoint1[]         = {1,3,6};
			int checkpoint2[]         = {2,4,4};
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = PenguinSledding().countDesigns(numCheckpoints, vector <int>(checkpoint1, checkpoint1 + (sizeof checkpoint1 / sizeof checkpoint1[0])), vector <int>(checkpoint2, checkpoint2 + (sizeof checkpoint2 / sizeof checkpoint2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int numCheckpoints        = 50;
			int checkpoint1[]         = {40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 50, 40, 40, 40, 23, 4, 24, 40, 22, 40, 8, 40, 40, 40, 34, 21, 40, 40, 38, 40, 40, 40, 40, 40, 28, 40, 40, 40, 40, 46, 13, 40, 40, 40, 47, 40, 40};
			int checkpoint2[]         = {45, 42, 20, 48, 12, 32, 25, 10, 26, 39, 16, 2, 19, 43, 37, 17, 19, 19, 19, 18, 19, 27, 19, 29, 11, 36, 19, 19, 1, 41, 19, 35, 14, 33, 49, 3, 19, 7, 5, 19, 31, 19, 19, 6, 9, 15, 19, 44, 30};
			long long expected__      = 68719493118LL;

			clock_t start__           = clock();
			long long received__      = PenguinSledding().countDesigns(numCheckpoints, vector <int>(checkpoint1, checkpoint1 + (sizeof checkpoint1 / sizeof checkpoint1[0])), vector <int>(checkpoint2, checkpoint2 + (sizeof checkpoint2 / sizeof checkpoint2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int numCheckpoints        = 36;
			int checkpoint1[]         = {13, 24, 24, 20, 31, 16, 10, 36, 34, 32, 28, 5, 20, 29, 23, 2, 14, 4, 9, 5, 19, 21, 8, 1, 26, 27, 25, 15, 22, 30, 30, 6, 11, 7, 2, 35, 13, 29, 4, 12, 33, 18, 13, 14, 17, 35, 3};
			int checkpoint2[]         = {10, 15, 27, 1, 29, 11, 5, 18, 33, 1, 9, 2, 31, 6, 19, 10, 33, 18, 6, 27, 3, 22, 4, 12, 31, 30, 34, 16, 7, 24, 3, 28, 15, 21, 22, 8, 26, 20, 14, 32, 25, 17, 35, 8, 36, 26, 23};
			long long expected__      = 162;

			clock_t start__           = clock();
			long long received__      = PenguinSledding().countDesigns(numCheckpoints, vector <int>(checkpoint1, checkpoint1 + (sizeof checkpoint1 / sizeof checkpoint1[0])), vector <int>(checkpoint2, checkpoint2 + (sizeof checkpoint2 / sizeof checkpoint2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int numCheckpoints        = ;
			int checkpoint1[]         = ;
			int checkpoint2[]         = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = PenguinSledding().countDesigns(numCheckpoints, vector <int>(checkpoint1, checkpoint1 + (sizeof checkpoint1 / sizeof checkpoint1[0])), vector <int>(checkpoint2, checkpoint2 + (sizeof checkpoint2 / sizeof checkpoint2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int numCheckpoints        = ;
			int checkpoint1[]         = ;
			int checkpoint2[]         = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = PenguinSledding().countDesigns(numCheckpoints, vector <int>(checkpoint1, checkpoint1 + (sizeof checkpoint1 / sizeof checkpoint1[0])), vector <int>(checkpoint2, checkpoint2 + (sizeof checkpoint2 / sizeof checkpoint2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int numCheckpoints        = ;
			int checkpoint1[]         = ;
			int checkpoint2[]         = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = PenguinSledding().countDesigns(numCheckpoints, vector <int>(checkpoint1, checkpoint1 + (sizeof checkpoint1 / sizeof checkpoint1[0])), vector <int>(checkpoint2, checkpoint2 + (sizeof checkpoint2 / sizeof checkpoint2[0])));
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
