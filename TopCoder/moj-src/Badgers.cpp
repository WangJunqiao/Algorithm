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

#define sz(X) ((int)(X.size()))
#define all(x) x.begin(),x.end()
#define clr(x,c) memset(x,c,sizeof(x))
#define rep(i,st,ed) for(int i=st;i<ed;i++)

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;
//--------------------------------------------


class Badgers {
public:
	int feedMost(vector <int> hunger, vector <int> greed, int totalFood);
};


int Badgers::feedMost(vector <int> hunger, vector <int> greed, int totalFood) {
	int ret = 0;
	for(int i=1;i<=sz(hunger);i++) {
		vector<int> v;
		rep(j, 0, sz(hunger)) v.push_back(hunger[j]+(i-1)*greed[j]);
		sort(all(v));
		int sum = 0;
		rep(j, 0, i) sum += v[j];
		if(sum <= totalFood) ret = i;
	}
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
			int hunger[]              = {1,2,3};
			int greed[]               = {2,2,1};
			int totalFood             = 7;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = Badgers().feedMost(vector <int>(hunger, hunger + (sizeof hunger / sizeof hunger[0])), vector <int>(greed, greed + (sizeof greed / sizeof greed[0])), totalFood);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int hunger[]              = {5,2,1,5};
			int greed[]               = {0,2,4,1};
			int totalFood             = 19;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = Badgers().feedMost(vector <int>(hunger, hunger + (sizeof hunger / sizeof hunger[0])), vector <int>(greed, greed + (sizeof greed / sizeof greed[0])), totalFood);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int hunger[]              = {1,1,1,1,1};
			int greed[]               = {1000,1000,1000,1000,1000};
			int totalFood             = 10;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = Badgers().feedMost(vector <int>(hunger, hunger + (sizeof hunger / sizeof hunger[0])), vector <int>(greed, greed + (sizeof greed / sizeof greed[0])), totalFood);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int hunger[]              = {1,2,3,4,5,6,7,8,9,10};
			int greed[]               = {10,9,8,7,6,5,4,3,2,1};
			int totalFood             = 100;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = Badgers().feedMost(vector <int>(hunger, hunger + (sizeof hunger / sizeof hunger[0])), vector <int>(greed, greed + (sizeof greed / sizeof greed[0])), totalFood);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int hunger[]              = ;
			int greed[]               = ;
			int totalFood             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Badgers().feedMost(vector <int>(hunger, hunger + (sizeof hunger / sizeof hunger[0])), vector <int>(greed, greed + (sizeof greed / sizeof greed[0])), totalFood);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int hunger[]              = ;
			int greed[]               = ;
			int totalFood             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Badgers().feedMost(vector <int>(hunger, hunger + (sizeof hunger / sizeof hunger[0])), vector <int>(greed, greed + (sizeof greed / sizeof greed[0])), totalFood);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int hunger[]              = ;
			int greed[]               = ;
			int totalFood             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Badgers().feedMost(vector <int>(hunger, hunger + (sizeof hunger / sizeof hunger[0])), vector <int>(greed, greed + (sizeof greed / sizeof greed[0])), totalFood);
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
