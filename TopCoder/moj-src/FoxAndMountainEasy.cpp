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


class FoxAndMountainEasy {
public:
	string possible(int n, int h0, int hn, string history);
};


string FoxAndMountainEasy::possible(int n, int h0, int hn, string his) {
	
	for(int i=0;i<=220000;i++){
		int j=i;
		bool fail=false;
		repv(k, his){
			if( his[k]=='U' ) j++;
			else j--;
			if( j<0 ) fail=true;
		}
		if( fail ) continue;
		int need1 = abs(h0-i);
		int need2 = abs(hn-j);
		int t = n-sz(his)-need1-need2;
		if( t>=0 && t%2==0 ){
			return "YES";
		}
	}
	return "NO";
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
			int n                     = 4;
			int h0                    = 0;
			int hn                    = 4;
			string history            = "UU";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 4;
			int h0                    = 0;
			int hn                    = 4;
			string history            = "D";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 4;
			int h0                    = 100000;
			int hn                    = 100000;
			string history            = "DDU";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 4;
			int h0                    = 0;
			int hn                    = 0;
			string history            = "DDU";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 20;
			int h0                    = 20;
			int hn                    = 20;
			string history            = "UDUDUDUDUD";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int n                     = 20;
			int h0                    = 0;
			int hn                    = 0;
			string history            = "UUUUUUUUUU";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int n                     = 20;
			int h0                    = 0;
			int hn                    = 0;
			string history            = "UUUUUUUUUUU";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			int n                     = ;
			int h0                    = ;
			int hn                    = ;
			string history            = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int n                     = ;
			int h0                    = ;
			int hn                    = ;
			string history            = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int n                     = ;
			int h0                    = ;
			int hn                    = ;
			string history            = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible(n, h0, hn, history);
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
