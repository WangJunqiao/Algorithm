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


class KeyDungeonDiv1 {
public:
	int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys);
};

#define RRR 140
int dp[1<<12][RRR];

void check(int &a, int b){
	a = max(a, b);
}

int KeyDungeonDiv1::maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys) {
	clr(dp, -1);
	int R = keys[0], G = keys[1], W = keys[2];
	dp[0][0] = W;
	int n = sz(doorR);
	int ret = 0;
	rep(s, 0, 1<<n) rep(toR, 0, RRR) if(dp[s][toR]>=0) {
		int sumR = R, sumG = G, sumW = W;
		rep(i, 0, n) if(s&(1<<i)) {
			sumR += roomR[i];
			sumG += roomG[i];
			sumW += roomW[i];
			
			sumR -= doorR[i];
			sumG -= doorG[i];
		}
		sumR += toR;
		sumG += (sumW - toR - dp[s][toR]);
		sumW = dp[s][toR];

		ret = max(ret, sumR + sumG + sumW);
		rep(i, 0, n) if(!(s&(1<<i))) {
			int need_toR = max(0, doorR[i]-sumR);
			int need_toG = max(0, doorG[i]-sumG);
			if(need_toG + need_toR <= sumW) {
				check(dp[s+(1<<i)][toR + need_toR], sumW-need_toR-need_toG+roomW[i]);
			}
		}
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
			int doorR[]               = {1, 2, 3};
			int doorG[]               = {0, 4, 9};
			int roomR[]               = {0, 0, 10};
			int roomG[]               = {0, 8, 9};
			int roomW[]               = {1, 0, 8};
			int keys[]                = {3, 1, 2};
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int doorR[]               = {1, 1, 1, 2};
			int doorG[]               = {0, 2, 3, 1};
			int roomR[]               = {2, 1, 0, 4};
			int roomG[]               = {1, 3, 3, 1};
			int roomW[]               = {1, 0, 2, 1};
			int keys[]                = {0, 4, 0};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int doorR[]               = {2, 0, 4};
			int doorG[]               = {3, 0, 4};
			int roomR[]               = {0, 0, 9};
			int roomG[]               = {0, 0, 9};
			int roomW[]               = {8, 5, 9};
			int keys[]                = {0, 0, 0};
			int expected__            = 27;

			clock_t start__           = clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int doorR[]               = {5, 3, 0, 0};
			int doorG[]               = {0, 1, 2, 1};
			int roomR[]               = {0, 9, 2, 4};
			int roomG[]               = {2, 9, 2, 0};
			int roomW[]               = {0, 9, 1, 1};
			int keys[]                = {1, 1, 0};
			int expected__            = 32;

			clock_t start__           = clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int doorR[]               = {9,5,10,8,4,3,0,8,4,1,3,9};
			int doorG[]               = {9,10,0,8,9,4,3,8,1,8,10,4};
			int roomR[]               = {1,2,0,2,3,3,5,3,1,3,0,5};
			int roomG[]               = {5,2,5,0,5,2,3,4,0,0,5,2};
			int roomW[]               = {1,5,1,2,0,4,4,0,3,3,1,3};
			int keys[]                = {5,0,1};
			int expected__            = 16;

			clock_t start__           = clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int doorR[]               = ;
			int doorG[]               = ;
			int roomR[]               = ;
			int roomG[]               = ;
			int roomW[]               = ;
			int keys[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int doorR[]               = ;
			int doorG[]               = ;
			int roomR[]               = ;
			int roomG[]               = ;
			int roomW[]               = ;
			int keys[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int doorR[]               = ;
			int doorG[]               = ;
			int roomR[]               = ;
			int roomG[]               = ;
			int roomW[]               = ;
			int keys[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
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
