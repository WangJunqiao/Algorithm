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


class ArcadeManao {
public:
	int shortestLadder(vector <string> level, int coinRow, int coinColumn);
};


int R, C;
int N, M;
VS le;

bool can[55][55];
int dir[4][2] = {0,1, 0,-1, 1,0, -1,0};

bool ill(int tx, int ty) {
	return tx>=0 && tx<N && ty>=0 && ty<M;

}

void dfs(int x, int y, int L) {
	can[x][y] = true;
	for(int in=0;in<4;in++) {
		if(in<2) {
			for(int j=-1;j<=1;j++) {
				int tx = x+dir[in][0] * j;
				int ty = y+dir[in][1] * j;
				if(!ill(tx, ty)) continue;
				if(can[tx][ty]) continue;
				if(le[tx][ty]!='X') continue;
				dfs(tx, ty, L);
			}
		} else {
			for(int j=-L;j<=L;j++) {
				int tx = x+dir[in][0] * j;
				int ty = y+dir[in][1] * j;
				if(!ill(tx, ty)) continue;
				if(can[tx][ty]) continue;
				if(le[tx][ty]!='X') continue;
				dfs(tx, ty, L);
			}

		}
	}
}

bool check(int L) {
	memset(can, false, sizeof(can));
	dfs(N-1, 0, L);
	return can[R][C];
}


int ArcadeManao::shortestLadder(vector <string> level, int coinRow, int coinColumn) {
	R = coinRow-1;
	C = coinColumn-1;
	le = level;
	N = sz(le), M = sz(le[0]);

	if(check(0)) return 0;
	int lo = 0, hi = 100;
	while(lo+1 < hi) {
		int mid = (lo + hi)/2;
		if(check(mid)) hi = mid;
		else lo = mid;
	}
	return hi;
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
			string level[]            = {"XXXX....",
				"...X.XXX",
				"XXX..X..",
				"......X.",
				"XXXXXXXX"};
			int coinRow               = 2;
			int coinColumn            = 4;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 1: {
			string level[]            = {"XXXX",
				"...X",
				"XXXX"};
			int coinRow               = 1;
			int coinColumn            = 1;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 2: {
			string level[]            = {"..X..",
				".X.X.",
				"X...X",
				".X.X.",
				"..X..",
				"XXXXX"};
			int coinRow               = 1;
			int coinColumn            = 3;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 3: {
			string level[]            = {"X"};
			int coinRow               = 1;
			int coinColumn            = 1;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 4: {
			string level[]            = {"XXXXXXXXXX",
				"...X......",
				"XXX.......",
				"X.....XXXX",
				"..XXXXX..X",
				".........X",
				".........X",
				"XXXXXXXXXX"};
			int coinRow               = 1;
			int coinColumn            = 1;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}

				// custom cases

				/*      case 5: {
				string level[]            = ;
				int coinRow               = ;
				int coinColumn            = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
				return verify_case(casenum__, expected__, received__, clock()-start__);
				}*/
				/*      case 6: {
				string level[]            = ;
				int coinRow               = ;
				int coinColumn            = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
				return verify_case(casenum__, expected__, received__, clock()-start__);
				}*/
				/*      case 7: {
				string level[]            = ;
				int coinRow               = ;
				int coinColumn            = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
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
