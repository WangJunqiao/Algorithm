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


class ElevenMultiples {
public:
	int countMultiples(vector <string> pieces);
};


int ElevenMultiples::countMultiples(vector <string> pieces) {
	
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
			string pieces[]           = {"58", "2012", "123"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string pieces[]           = {"1", "1111", "1", "11"};
			int expected__            = 24;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string pieces[]           = {"43925486943738659795389387498953274"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string pieces[]           = {"983", "4654", "98", "3269", "861", "30981"};
			int expected__            = 96;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string pieces[]           = {"193", "8819", "40676", "97625892", "5719", "45515667", "32598836", "70559374", "38756", "724",
"93391", "942068", "506", "901150", "874", "895567", "7560480", "7427691", "799450", "85127"};
			int expected__            = 537147821;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string pieces[]           = {"687045939630", "997856158148599044", "2014910234712225061", "9658113323175370226", "1584118137",
"67925153345598920", "6960366756", "863413844386808834", "799302243562410012", "44481835751",
"8004606814733183", "19623906615609", "23859998326058162", "461385591582", "9261878982390119",
"1569373294276", "318106951168934", "65389049931", "12791173342", "507877942026",
"3947173045690", "472425746178910", "524552931853595", "40771812249667850232", "563988469071932",
"28147819070", "797007158858587", "5716177008624223", "387565700495309324", "4716621063133318"}
;
			int expected__            = 814880650;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string pieces[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string pieces[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string pieces[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
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
