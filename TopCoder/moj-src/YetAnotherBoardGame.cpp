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


class YetAnotherBoardGame {
public:
	int minimumMoves(vector <string> board);
};

VS B;
int row[15], col[15];

int dfs(){
	bool suc = true;
	rep(i, 0, sz(B)) rep(j, 0, sz(B[0])) {

	}
}

int YetAnotherBoardGame::minimumMoves(vector <string> board) {
	B = board;
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
			string board[]            = {"BBBBBBBBB",
 "BBWBBBBBB",
 "BWWWBBBBB",
 "BBWBBBWBB",
 "BBBBBWBWB",
 "BBBBBBWBB"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"BBW",
 "WWW",
 "BWW"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"WBW",
 "BBW",
 "WBW"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"BBBB",
 "WBWB",
 "BBBB",
 "BBBB"};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"WWWWWBW",
 "WBWBWBW",
 "BBWBBWW"};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {"WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW"}
;
			int expected__            = 30;

			clock_t start__           = clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
