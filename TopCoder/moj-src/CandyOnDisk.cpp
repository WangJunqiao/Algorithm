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


class CandyOnDisk {
public:
	string ableToAchieve( vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty );
};


string CandyOnDisk::ableToAchieve( vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty ) {
	return "";
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
			int x[]                   = {0, 4};
			int y[]                   = {0, 0};
			int r[]                   = {3, 3};
			int sx                    = -1;
			int sy                    = -2;
			int tx                    = 6;
			int ty                    = 1;
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = CandyOnDisk().ableToAchieve(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(r, r + (sizeof r / sizeof r[0])), sx, sy, tx, ty);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int x[]                   = {0, 3};
			int y[]                   = {0, 0};
			int r[]                   = {5, 3};
			int sx                    = -4;
			int sy                    = 0;
			int tx                    = -2;
			int ty                    = 0;
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = CandyOnDisk().ableToAchieve(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(r, r + (sizeof r / sizeof r[0])), sx, sy, tx, ty);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int x[]                   = {0};
			int y[]                   = {0};
			int r[]                   = {1};
			int sx                    = 0;
			int sy                    = 0;
			int tx                    = 571;
			int ty                    = 571;
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = CandyOnDisk().ableToAchieve(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(r, r + (sizeof r / sizeof r[0])), sx, sy, tx, ty);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int x[]                   = {0};
			int y[]                   = {0};
			int r[]                   = {1};
			int sx                    = 571;
			int sy                    = 571;
			int tx                    = 571;
			int ty                    = 571;
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = CandyOnDisk().ableToAchieve(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(r, r + (sizeof r / sizeof r[0])), sx, sy, tx, ty);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int x[]                   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
			int y[]                   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
			int r[]                   = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
			int sx                    = 2;
			int sy                    = 2;
			int tx                    = 19;
			int ty                    = 19;
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = CandyOnDisk().ableToAchieve(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(r, r + (sizeof r / sizeof r[0])), sx, sy, tx, ty);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int x[]                   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
			int y[]                   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
			int r[]                   = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
			int sx                    = 2;
			int sy                    = 2;
			int tx                    = 19;
			int ty                    = 19;
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = CandyOnDisk().ableToAchieve(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(r, r + (sizeof r / sizeof r[0])), sx, sy, tx, ty);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int x[]                   = ;
			int y[]                   = ;
			int r[]                   = ;
			int sx                    = ;
			int sy                    = ;
			int tx                    = ;
			int ty                    = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CandyOnDisk().ableToAchieve(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(r, r + (sizeof r / sizeof r[0])), sx, sy, tx, ty);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int x[]                   = ;
			int y[]                   = ;
			int r[]                   = ;
			int sx                    = ;
			int sy                    = ;
			int tx                    = ;
			int ty                    = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CandyOnDisk().ableToAchieve(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(r, r + (sizeof r / sizeof r[0])), sx, sy, tx, ty);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int x[]                   = ;
			int y[]                   = ;
			int r[]                   = ;
			int sx                    = ;
			int sy                    = ;
			int tx                    = ;
			int ty                    = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CandyOnDisk().ableToAchieve(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(r, r + (sizeof r / sizeof r[0])), sx, sy, tx, ty);
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
