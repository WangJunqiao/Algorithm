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


class LongLongTripDiv1 {
public:
	string isAble(int N, vector <int> A, vector <int> B, vector <int> D, long long T);
};


string LongLongTripDiv1::isAble(int N, vector <int> A, vector <int> B, vector <int> D, long long T) {
	
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
			int N                     = 3;
			int A[]                   = {0,0,1};
			int B[]                   = {2,1,2};
			int D[]                   = {7,6,5};
			long long T               = 11;
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = LongLongTripDiv1().isAble(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(D, D + (sizeof D / sizeof D[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 3;
			int A[]                   = {0,0,1};
			int B[]                   = {2,1,2};
			int D[]                   = {7,6,5};
			long long T               = 25;
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = LongLongTripDiv1().isAble(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(D, D + (sizeof D / sizeof D[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 2;
			int A[]                   = {0};
			int B[]                   = {1};
			int D[]                   = {1};
			long long T               = 9;
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = LongLongTripDiv1().isAble(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(D, D + (sizeof D / sizeof D[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 2;
			int A[]                   = {1};
			int B[]                   = {0};
			int D[]                   = {1};
			long long T               = 1000000000000000000LL;
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = LongLongTripDiv1().isAble(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(D, D + (sizeof D / sizeof D[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 4;
			int A[]                   = {0,0,1};
			int B[]                   = {2,1,2};
			int D[]                   = {10,10,10};
			long long T               = 1000;
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = LongLongTripDiv1().isAble(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(D, D + (sizeof D / sizeof D[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int N                     = 9;
			int A[]                   = {4,8,5,8,3,6,2,6,7,6,6};
			int B[]                   = {2,7,1,5,1,3,1,1,5,4,2};
			int D[]                   = {6580,8822,1968,673,1394,9337,5486,1746,5229,4092,195};
			long long T               = 937186357646035002LL;
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = LongLongTripDiv1().isAble(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(D, D + (sizeof D / sizeof D[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int N                     = ;
			int A[]                   = ;
			int B[]                   = ;
			int D[]                   = ;
			long long T               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LongLongTripDiv1().isAble(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(D, D + (sizeof D / sizeof D[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int A[]                   = ;
			int B[]                   = ;
			int D[]                   = ;
			long long T               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LongLongTripDiv1().isAble(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(D, D + (sizeof D / sizeof D[0])), T);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int N                     = ;
			int A[]                   = ;
			int B[]                   = ;
			int D[]                   = ;
			long long T               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LongLongTripDiv1().isAble(N, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(D, D + (sizeof D / sizeof D[0])), T);
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
