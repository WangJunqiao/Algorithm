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


class MysticAndCandies {
public:
	int minBoxes(int C, int X, vector <int> low, vector <int> high);
};


VI low, high;

bool cmp(const int &a, const int &b) {
	if(low[a]-(high[b]-low[b]) >= low[b]-(high[a]-low[a])) {
		return false;
	}
	return true;
}

int MysticAndCandies::minBoxes(int C, int X, vector <int> low, vector <int> high) {
	int ret = 1000;
	VI v = low;
	sort(all(v));
	reverse(all(v));
	int sum = 0;
	for(ret=0;ret<sz(v);ret++) {
		sum += v[ret];
		if(sum >= X) break;
	}
	ret ++;
	ret = min(ret, sz(low));

	::low = low;
	::high = high;
	v.clear();
	rep(i, 0, sz(low)) v.push_back(i);
	sort(all(v), cmp);

	//rep(i, 0, sz(v)) cout<<v[i]<<' '; cout<<endl;

	int sumL = 0;
	rep(i, 0, sz(low)) sumL += low[i];

	rep(i, 0, sz(v)) {
		int sumK = 0, sum = 0;
		rep(j, 0, i+1) {
			int id = v[j];
			sumK += (high[id]-low[id]);
		}
		rep(j, i+1, sz(v)) {
			int id = v[j];
			sum += low[id];
		}
	//	cout<<sumK<<' '<<sum<<endl;
		if(C-sumL < sumK) continue;
		if(C-sumL-sumK + sum>= X) ret = min(ret, sz(v)-i-1);
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
			int C                     = 15;
			int X                     = 12;
			int low[]                 = {1, 2, 3, 4, 5};
			int high[]                = {1, 2, 3, 4, 5};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = MysticAndCandies().minBoxes(C, X, vector <int>(low, low + (sizeof low / sizeof low[0])), vector <int>(high, high + (sizeof high / sizeof high[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int C                     = 60;
			int X                     = 8;
			int low[]                 = {5, 2, 3};
			int high[]                = {49, 48, 47};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = MysticAndCandies().minBoxes(C, X, vector <int>(low, low + (sizeof low / sizeof low[0])), vector <int>(high, high + (sizeof high / sizeof high[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int C                     = 58;
			int X                     = 30;
			int low[]                 = {3, 9, 12, 6, 15};
			int high[]                = {8, 12, 20, 8, 15};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = MysticAndCandies().minBoxes(C, X, vector <int>(low, low + (sizeof low / sizeof low[0])), vector <int>(high, high + (sizeof high / sizeof high[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int C                     = 207581165;
			int X                     = 172146543;
			int low[]                 = {4725448, 2753824, 6019698, 4199708, 4070001, 3589497, 5358499, 3637585, 5393667, 2837466, 2747807, 2918199, 3638042, 5199002, 3072044, 3858909, 3762101, 3657754, 3218704, 3888861, 3195689, 4768935, 3137633, 4124272, 4125056, 6087486, 3632970, 3620489, 2748765, 5917493, 3958996, 3335021, 3517186, 5543440, 2951006, 3403270, 3299481, 3093204, 4092331};
			int high[]                = {5702812, 6805664, 6823687, 5337687, 4286533, 4999849, 6567411, 4563235, 6618139, 6260135, 6249469, 3821449, 5963157, 6385012, 4255959, 5786920, 6112817, 4103918, 6371537, 4231698, 3409172, 6806782, 5623563, 4511221, 6407338, 6491490, 5209517, 6076093, 6530132, 6111464, 5833839, 6253088, 5595160, 6236805, 5772388, 5285713, 5617002, 4650978, 5234740};
			int expected__            = 31;

			clock_t start__           = clock();
			int received__            = MysticAndCandies().minBoxes(C, X, vector <int>(low, low + (sizeof low / sizeof low[0])), vector <int>(high, high + (sizeof high / sizeof high[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int C                     = 43873566;
			int X                     = 32789748;
			int low[]                 = {2053198, 2175819, 4260803, 1542497, 1418952, 5000015, 1381849, 2462882, 6466891, 1827580, 6943641, 5775477};
			int high[]                = {2827461, 3726335, 5410505, 4781355, 4925909, 5621160, 7325774, 5025476, 7876037, 8072075, 6979462, 6647628};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = MysticAndCandies().minBoxes(C, X, vector <int>(low, low + (sizeof low / sizeof low[0])), vector <int>(high, high + (sizeof high / sizeof high[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int C                     = ;
			int X                     = ;
			int low[]                 = ;
			int high[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MysticAndCandies().minBoxes(C, X, vector <int>(low, low + (sizeof low / sizeof low[0])), vector <int>(high, high + (sizeof high / sizeof high[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int C                     = ;
			int X                     = ;
			int low[]                 = ;
			int high[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MysticAndCandies().minBoxes(C, X, vector <int>(low, low + (sizeof low / sizeof low[0])), vector <int>(high, high + (sizeof high / sizeof high[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int C                     = ;
			int X                     = ;
			int low[]                 = ;
			int high[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MysticAndCandies().minBoxes(C, X, vector <int>(low, low + (sizeof low / sizeof low[0])), vector <int>(high, high + (sizeof high / sizeof high[0])));
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
