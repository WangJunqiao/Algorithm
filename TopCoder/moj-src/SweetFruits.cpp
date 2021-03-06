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


class SweetFruits {
public:
	int countTrees(vector <int> sweetness, int maxSweetness);
};


int SweetFruits::countTrees(vector <int> sweetness, int maxSweetness) {
	
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
			int sweetness[]           = {1, 2, -1, 3};
			int maxSweetness          = 3;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int sweetness[]           = {1, 2, -1, 3};
			int maxSweetness          = 5;
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int sweetness[]           = {-1, -1, 2, 5, 5};
			int maxSweetness          = 6;
			int expected__            = 20;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int sweetness[]           = {2, 6, 8, 4, 1, 10, -1, -1, -1, -1};
			int maxSweetness          = 15;
			int expected__            = 17024000;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int sweetness[]           = {1078451, -1, 21580110, 8284711, -1, 4202301, 3427559, 8261270, -1, 16176713, 22915672, 24495540, 19236, 5477666, 12280316, 3305896, 17917887, 564911, 22190488, 21843923, 23389728, 14641920, 9590140, 12909561, 20405638, 100184, 23336457, 12780498, 18859535, 23180993, 10278898, 5753075, 21250919, 17563422, 10934412, 22557980, 24895749, 7593671, 10834579, 5606562};
			int maxSweetness          = 245243285;
			int expected__            = 47225123;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int sweetness[]           = ;
			int maxSweetness          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int sweetness[]           = ;
			int maxSweetness          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int sweetness[]           = ;
			int maxSweetness          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
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
