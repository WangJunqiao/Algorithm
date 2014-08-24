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


class FoxAndVacation {
public:
	int maxCities(int total, vector <int> d);
};


int FoxAndVacation::maxCities(int total, vector <int> d) {
	int dp[55][55]={false};
	clr(dp, 0x88);
	dp[0][0]=0;
	
	int ret = 0;
	repv(i, d){
		for(int j=0;j<=total;j++){
			dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
			if( d[i]+j<=total ){
				dp[i+1][j+d[i]]=max(dp[i+1][j+d[i]], dp[i][j]+1);
				ret = max(ret, dp[i+1][j+d[i]]);
			}
		}
	}
	cout<<dp[2][1]<<endl;
	return ret;
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
			int total                 = 5;
			int d[]                   = {2,2,2};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = FoxAndVacation().maxCities(total, vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int total                 = 5;
			int d[]                   = {5,6,1};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = FoxAndVacation().maxCities(total, vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int total                 = 5;
			int d[]                   = {6,6,6};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = FoxAndVacation().maxCities(total, vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int total                 = 6;
			int d[]                   = {1,1,1,1,1};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = FoxAndVacation().maxCities(total, vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int total                 = 10;
			int d[]                   = {7,1,5,6,1,3,4};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = FoxAndVacation().maxCities(total, vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int total                 = 50;
			int d[]                   = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = FoxAndVacation().maxCities(total, vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int total                 = 21;
			int d[]                   = {14,2,16,9,9,5,5,23,25,20,8,25,6,12,3,2,4,5,10,14,19,12,25,15,14};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = FoxAndVacation().maxCities(total, vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			int total                 = ;
			int d[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndVacation().maxCities(total, vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int total                 = ;
			int d[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndVacation().maxCities(total, vector <int>(d, d + (sizeof d / sizeof d[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int total                 = ;
			int d[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndVacation().maxCities(total, vector <int>(d, d + (sizeof d / sizeof d[0])));
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
