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


class ColorTheCells {
public:
	int minimalTime(vector <int> dryingTime);
};

void checkmax(int &a, int b){
	a = max(a, b);
}

int ColorTheCells::minimalTime(vector <int> dryingTime) {
	int n = sz(dryingTime);
	vector<int> v;
	rep(i, 0, n) v.push_back(i);
	int ret = 1 << 30;
	do{
		
		rep(s, 0, (1<<n)) {
			int cur = 0;
			int time = 0;
			int paint[10];
			clr(paint, 0x8f);
			bool fail = false;
			rep(step, 0, n) {
				int nxt = v[step];
				if(s&(1<<step)) nxt ++;
				else nxt --;
				if(nxt < 0 || nxt>=n) {
					fail = true;
					break;
				}
				if(nxt > cur) {
					while(cur != nxt) {
						checkmax(time, paint[cur+1]+dryingTime[cur+1]);
						time ++;
						cur ++;
					}
				}
				if(nxt < cur) {
					while(cur != nxt) {
						checkmax(time, paint[cur-1]+dryingTime[cur-1]);
						time ++;
						cur --;
					}
				}
				time ++;
				paint[v[step]] = time;
			}
			if(fail) continue;
			ret = min(ret, time);
		}
		
	}while(next_permutation(all(v)));
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
			int dryingTime[]          = {2, 2, 3};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = ColorTheCells().minimalTime(vector <int>(dryingTime, dryingTime + (sizeof dryingTime / sizeof dryingTime[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int dryingTime[]          = {1, 2, 100, 1};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = ColorTheCells().minimalTime(vector <int>(dryingTime, dryingTime + (sizeof dryingTime / sizeof dryingTime[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int dryingTime[]          = {33, 58, 21, 44};
			int expected__            = 26;

			clock_t start__           = clock();
			int received__            = ColorTheCells().minimalTime(vector <int>(dryingTime, dryingTime + (sizeof dryingTime / sizeof dryingTime[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int dryingTime[]          = {35198, 26281, 72533, 91031, 44326, 43178, 85530};
			int expected__            = 26287;

			clock_t start__           = clock();
			int received__            = ColorTheCells().minimalTime(vector <int>(dryingTime, dryingTime + (sizeof dryingTime / sizeof dryingTime[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int dryingTime[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorTheCells().minimalTime(vector <int>(dryingTime, dryingTime + (sizeof dryingTime / sizeof dryingTime[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int dryingTime[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorTheCells().minimalTime(vector <int>(dryingTime, dryingTime + (sizeof dryingTime / sizeof dryingTime[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int dryingTime[]          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ColorTheCells().minimalTime(vector <int>(dryingTime, dryingTime + (sizeof dryingTime / sizeof dryingTime[0])));
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
