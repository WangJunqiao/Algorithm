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


class RectangularSum {
public:
	long long minimalArea(int height, int width, long long S);
};


long long RectangularSum::minimalArea(int height, int width, long long S) {
	if( S<height*(LL)width ) return 1;
	LL ret=1e15;
	if( width<=1000 ){
		//LL sum=0;
		for(int i=0;i<width;i++){
			LL sum=0;
			for(int j=i;j<width;j++){
				sum+=j;
				if( sum>S ) break;
				LL ss=S-sum, add=(j-i+1)*(LL)width;
				if( ss%add ) break;
				ss/=add;
				
			}
		}
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
			int height                = 2;
			int width                 = 3;
			long long S               = 8;
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int height                = 3;
			int width                 = 3;
			long long S               = 10;
			long long expected__      = -1;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int height                = 3;
			int width                 = 3;
			long long S               = 36;
			long long expected__      = 9;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int height                = 25;
			int width                 = 25;
			long long S               = 16000;
			long long expected__      = 32;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int height                = 1000000;
			int width                 = 1000000;
			long long S               = 1000000000000LL;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int height                = ;
			int width                 = ;
			long long S               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int height                = ;
			int width                 = ;
			long long S               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int height                = ;
			int width                 = ;
			long long S               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = RectangularSum().minimalArea(height, width, S);
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
