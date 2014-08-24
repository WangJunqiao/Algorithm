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
#include <unordered_map>

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<string> VS;

typedef unsigned int UI;

#define sz(X) ((int)(X.size()))
#define all(x) x.begin(),x.end()
#define clr(x,c) memset(x,c,sizeof(x))
#define rep(i,s,e) for(int i=s;i<e;i++)


class EllysPairing {
public:
	int getMax(int M, vector <int> count, vector <int> first, vector <int> mult, vector <int> add);
};


int ccc[1000000];

int EllysPairing::getMax(int M, vector <int> count, vector <int> first, vector <int> mult, vector <int> add) {
	
	int w = 0, hmask = (1<<30)-1 - ((1<<15)-1);
	while((1<<w) < M) w++;
	
	clr(ccc, 0);
	
	rep(i, 0, sz(count)) {
		int t = first[i];
		ccc[(t&hmask)>>15] ++;
		for(int j=2;j<=count[i];j++) {
			t = ((UI)t * (UI)mult[i] + (UI)add[i]) & (M-1);
			ccc[(t & hmask)>>15] ++;
		}
	}
	int hval = 0, ma = 0;
	rep(i, 0, 1000000) if(ccc[i]>ma) {
		ma = ccc[i];
		hval = i<<15;
	}
	
	
	
	int num = 0, lmask = (1<<15)-1;
	clr(ccc, 0);
	rep(i, 0, sz(count)) {
		num += count[i];
		int t = first[i];
		if((t&hmask) == hval) ccc[t&lmask] ++;
		for(int j=2;j<=count[i];j++) {
			t = ((UI)t * (UI)mult[i] + (UI)add[i]) & (M-1);
			if((t&hmask) == hval) ccc[t&lmask] ++;
		}
	}
	
	ma = 0;
	rep(i, 0, 1000000) ma = max(ma, ccc[i]);
	
	if(2*ma > num) return num - ma;
	return num / 2;
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
			int M                     = 16;
			int count[]               = {4, 7};
			int first[]               = {5, 3};
			int mult[]                = {2, 3};
			int add[]                 = {1, 0};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = EllysPairing().getMax(M, vector <int>(count, count + (sizeof count / sizeof count[0])), vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(mult, mult + (sizeof mult / sizeof mult[0])), vector <int>(add, add + (sizeof add / sizeof add[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int M                     = 8;
			int count[]               = {6, 4, 3};
			int first[]               = {0, 3, 2};
			int mult[]                = {3, 7, 5};
			int add[]                 = {0, 3, 2};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = EllysPairing().getMax(M, vector <int>(count, count + (sizeof count / sizeof count[0])), vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(mult, mult + (sizeof mult / sizeof mult[0])), vector <int>(add, add + (sizeof add / sizeof add[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int M                     = 128;
			int count[]               = {42, 13, 666, 17, 1337, 42, 1};
			int first[]               = {18, 76, 3, 122, 0, 11, 11};
			int mult[]                = {33, 17, 54, 90, 41, 122, 20};
			int add[]                 = {66, 15, 10, 121, 122, 1, 30};
			int expected__            = 1059;

			clock_t start__           = clock();
			int received__            = EllysPairing().getMax(M, vector <int>(count, count + (sizeof count / sizeof count[0])), vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(mult, mult + (sizeof mult / sizeof mult[0])), vector <int>(add, add + (sizeof add / sizeof add[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int M                     = 1048576;
			int count[]               = {4242, 42, 9872, 13, 666, 21983, 17, 1337, 42, 1};
			int first[]               = {19, 18, 76, 42, 3, 112, 0, 11, 11, 12};
			int mult[]                = {27, 33, 10, 8, 17, 9362, 90, 41, 122, 20};
			int add[]                 = {98, 101, 66, 15, 10, 144, 3, 1, 5, 1};
			int expected__            = 16232;

			clock_t start__           = clock();
			int received__            = EllysPairing().getMax(M, vector <int>(count, count + (sizeof count / sizeof count[0])), vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(mult, mult + (sizeof mult / sizeof mult[0])), vector <int>(add, add + (sizeof add / sizeof add[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int M                     = 1073741824;
			int count[]               = {894602, 946569, 887230, 856152, 962583, 949356, 904847, 829100, 842183, 958440, 811081, 864078, 809209, 938727, 949135, 892809, 816528, 961237, 979142, 890922};
			int first[]               = {844085078, 898937259, 243490172, 887804102, 187696417, 156820442, 237600210, 618812924, 153000239, 912364033, 254936966, 650298774, 982988140, 649258331, 566444626, 201481721, 492943390, 1061953081, 492672963, 960519711};
			int mult[]                = {1036482037, 583219072, 819168094, 253755052, 548208982, 401830167, 638626082, 43642932, 123607749, 485521178, 860368129, 30334704, 219771462, 733375600, 130839219, 415503960, 294132484, 1044831462, 256910484, 198852170};
			int add[]                 = {889169006, 604831366, 967292994, 980686280, 844875791, 1027687492, 357734882, 295879743, 48284748, 421729100, 1049536313, 327207332, 948053446, 271229570, 664579359, 795815285, 842856528, 876662975, 675611938, 634229925};
			int expected__            = 8971965;

			clock_t start__           = clock();
			int received__            = EllysPairing().getMax(M, vector <int>(count, count + (sizeof count / sizeof count[0])), vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(mult, mult + (sizeof mult / sizeof mult[0])), vector <int>(add, add + (sizeof add / sizeof add[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int M                     = ;
			int count[]               = ;
			int first[]               = ;
			int mult[]                = ;
			int add[]                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EllysPairing().getMax(M, vector <int>(count, count + (sizeof count / sizeof count[0])), vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(mult, mult + (sizeof mult / sizeof mult[0])), vector <int>(add, add + (sizeof add / sizeof add[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int M                     = ;
			int count[]               = ;
			int first[]               = ;
			int mult[]                = ;
			int add[]                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EllysPairing().getMax(M, vector <int>(count, count + (sizeof count / sizeof count[0])), vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(mult, mult + (sizeof mult / sizeof mult[0])), vector <int>(add, add + (sizeof add / sizeof add[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int M                     = ;
			int count[]               = ;
			int first[]               = ;
			int mult[]                = ;
			int add[]                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EllysPairing().getMax(M, vector <int>(count, count + (sizeof count / sizeof count[0])), vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(mult, mult + (sizeof mult / sizeof mult[0])), vector <int>(add, add + (sizeof add / sizeof add[0])));
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
