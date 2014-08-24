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


class AntlerSwapping {
public:
	int getmin(vector <int> antler1, vector <int> antler2, int capacity);
};


int AntlerSwapping::getmin(vector <int> antler1, vector <int> antler2, int capacity) {
	int n = sz(antler1);
	int ret = 1000000000;
	rep(s, 0, (1<<n)) {
		vector<int> v;
		bool fail = false;
		rep(i, 0, n) {
			if(s&(1<<i)) {
				if(abs(antler1[i] - antler2[i]) > capacity) fail = true; 
			} else {
				v.push_back(antler1[i]);
				v.push_back(antler2[i]);
			}
		}
		if(fail) continue;
		sort(all(v));
		rep(i, 0, sz(v)) {
			if(abs(v[i]-v[i+1]) > capacity) fail = true;
			i++;
		}
		if(fail) continue;
		ret = min(ret, sz(v)/2 - 1);
	}
	if(ret > 1000000) return -1;
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
			int antler1[]             = {3, 2, 2};
			int antler2[]             = {3, 5, 5};
			int capacity              = 0;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = AntlerSwapping().getmin(vector <int>(antler1, antler1 + (sizeof antler1 / sizeof antler1[0])), vector <int>(antler2, antler2 + (sizeof antler2 / sizeof antler2[0])), capacity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int antler1[]             = {4, 2, 6, 4, 8, 5, 2, 3};
			int antler2[]             = {3, 4, 5, 2, 8, 5, 7, 6};
			int capacity              = 1;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = AntlerSwapping().getmin(vector <int>(antler1, antler1 + (sizeof antler1 / sizeof antler1[0])), vector <int>(antler2, antler2 + (sizeof antler2 / sizeof antler2[0])), capacity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int antler1[]             = {12, 34, 56, 78};
			int antler2[]             = {1234, 2345, 3456, 4567};
			int capacity              = 100;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = AntlerSwapping().getmin(vector <int>(antler1, antler1 + (sizeof antler1 / sizeof antler1[0])), vector <int>(antler2, antler2 + (sizeof antler2 / sizeof antler2[0])), capacity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int antler1[]             = {47, 58, 2013};
			int antler2[]             = {49, 55, 2013};
			int capacity              = 3;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = AntlerSwapping().getmin(vector <int>(antler1, antler1 + (sizeof antler1 / sizeof antler1[0])), vector <int>(antler2, antler2 + (sizeof antler2 / sizeof antler2[0])), capacity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int antler1[]             = {4, 1, 7, 5, 7, 8, 2, 1, 3, 1, 7, 5, 9, 4, 9, 1};
			int antler2[]             = {10, 6, 5, 3, 1, 8, 4, 4, 4, 7, 1, 4, 6, 5, 10, 10};
			int capacity              = 1;
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = AntlerSwapping().getmin(vector <int>(antler1, antler1 + (sizeof antler1 / sizeof antler1[0])), vector <int>(antler2, antler2 + (sizeof antler2 / sizeof antler2[0])), capacity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int antler1[]             = ;
			int antler2[]             = ;
			int capacity              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AntlerSwapping().getmin(vector <int>(antler1, antler1 + (sizeof antler1 / sizeof antler1[0])), vector <int>(antler2, antler2 + (sizeof antler2 / sizeof antler2[0])), capacity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int antler1[]             = ;
			int antler2[]             = ;
			int capacity              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AntlerSwapping().getmin(vector <int>(antler1, antler1 + (sizeof antler1 / sizeof antler1[0])), vector <int>(antler2, antler2 + (sizeof antler2 / sizeof antler2[0])), capacity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int antler1[]             = ;
			int antler2[]             = ;
			int capacity              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AntlerSwapping().getmin(vector <int>(antler1, antler1 + (sizeof antler1 / sizeof antler1[0])), vector <int>(antler2, antler2 + (sizeof antler2 / sizeof antler2[0])), capacity);
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
