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


class HexagonalBoard {
public:
	int minColors(vector <string> board);
};


//-----------------------二分图判定-------
#define maxn 2600
int adj[maxn][maxn]; //adj[i][j] = 1表示连通
int col[maxn]; //col=1白色，col=2黑色
bool dfs_bipartite(int n, int u, int c){
	col[u] = c;
	for(int i=0;i<n;i++) if(adj[u][i]==1) { //连接的
		if(col[i] == 0) {
			if(!dfs_bipartite(n, i, 3-c))
				return false;
		} else if(col[i] == c) {
			return false;
		}
	}
	return true;
}
bool check_bipartite(int n) {
	memset(col, 0, sizeof(col));
	for(int i=0;i<n;i++) {
		if(col[i]==0) {
			if(dfs_bipartite(n, i, 1) == false) 
				return false;
		}
	}
	return true;
}//------------------------------

int n, m, id[55][55];
bool have;
VS board;
void check(int i, int j, int x, int y) {
	if(x<0 || x>=n || y<0 || y>=m) 
		return;
	if(board[x][y]=='-')
		return;
	have = true;
	adj[id[i][j]][id[x][y]] = 1;
	adj[id[x][y]][id[i][j]] = 1;
}

int HexagonalBoard::minColors(vector <string> board) {
	int cnt = 0;
	::board = board;
	n = sz(board[0]), m = sz(board[0]);
	rep(i, 0, n) rep(j, 0, m) id[i][j] = cnt ++;

	clr(adj, 0);
	have = false;
	bool X = false;
	rep(i, 0, n) rep(j, 0, m) if(board[i][j]=='X'){
		X = true;
		check(i, j, i, j-1);
		check(i, j, i, j+1);
		check(i, j, i-1, j);
		check(i, j, i-1, j+1);
		check(i, j, i+1, j-1);
		check(i, j, i+1, j);
	}
	if(!X) return 0;
	if(!have) return 1;
	if(check_bipartite(cnt))
		return 2;
	return 3;
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
			string board[]            = {"---",
 "---",
 "---"}
 ;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = HexagonalBoard().minColors(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"-X--",
 "---X",
 "----",
 "-X--"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = HexagonalBoard().minColors(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"XXXX",
 "---X",
 "---X",
 "---X"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = HexagonalBoard().minColors(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"XX-XX--"
,"-XX-XXX"
,"X-XX--X"
,"X--X-X-"
,"XX-X-XX"
,"-X-XX-X"
,"-XX-XX-"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = HexagonalBoard().minColors(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = HexagonalBoard().minColors(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = HexagonalBoard().minColors(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = HexagonalBoard().minColors(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
