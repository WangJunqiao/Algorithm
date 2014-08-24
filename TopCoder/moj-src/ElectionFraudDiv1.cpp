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


class ElectionFraudDiv1 {
public:
	int MinimumVoters(vector <int> percentages);
};


VI per;


bool check(int sum){
	int mi=0, ma=0;
	repv(i, per){
		int x=max(0, per[i]*2-1);
		int y=per[i]*2+1;
		if( x*sum%200==0 ) mi+=x*sum/200;
		else mi+=(x*sum/200+1);
		if( y*sum%200==0 ) ma+=(y*sum/200-1);
		else ma+=y*sum/200;
	}
	if( mi<=sum && ma>=sum ) return true;
	return false;
}




int ElectionFraudDiv1::MinimumVoters(vector <int> per) {
	::per=per;
	for(int i=1;i<=100000;i++){
		if( check(i) ) return i;
	}
	return -1;
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
			int percentages[]         = {33, 33, 33};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int percentages[]         = {29, 29, 43};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int percentages[]         = {12, 12, 12, 12, 12, 12, 12, 12};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int percentages[]         = {13, 13, 13, 13, 13, 13, 13, 13};
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int percentages[]         = {0, 1, 100};
			int expected__            = 200;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int percentages[]         = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4};
			int expected__            = 97;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int percentages[]         = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int percentages[]         = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int percentages[]         = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ElectionFraudDiv1().MinimumVoters(vector <int>(percentages, percentages + (sizeof percentages / sizeof percentages[0])));
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
