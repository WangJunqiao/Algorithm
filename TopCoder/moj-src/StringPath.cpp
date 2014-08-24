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


class StringPath {
public:
	int countBoards(int n, int m, string A, string B);
};

int dp[2][1<<9][1<<9];

bool test(int x, int w) {
	return x&(1<<w);
}

const int mod = 1000000009;
void add(int &a, int b) {
	a = (a+b)%mod;
}

int sss(int x, int w, int t) {
	if(t) {
		return x|(1<<w);
	} else {
		return x&((1<<20)-1 - (1<<w));
	}
}
// 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 
int StringPath::countBoards(int n, int m, string A, string B) {
	if(sz(A) != n+m-1) return 0;
	if(sz(B) != n+m-1) return 0;
	int L = n + m - 1;
	if(A[0]!=B[0] || A[L-1]!=B[L-1])
		return 0;
	clr(dp, 0);
	bool now = false;
	dp[now][1][1] = 1;

	rep(i, 1, n+1) {

		rep(j, 0, m) {
			clr(dp[!now], 0);
			rep(x, 0, (1<<(m+1))) rep(y, 0, (1<<(1+m))) if(dp[now][x][y]) {
				//printf("j = %d, x = %d, y = %d\n", j, x, y);

				for(char ch='A';ch<='Z';ch++) {
					int nx = x;
					if((test(x, j)||test(x, j+1)) && ch==A[i+j-1]) 
						nx = sss(nx, j+1, 1);
					else
						nx = sss(nx, j+1, 0);
					int ny = y;
					if((test(y, j)||test(y, j+1)) && ch==B[i+j-1])
						ny = sss(ny, j+1, 1);
					else
						ny = sss(ny, j+1, 0);
					//printf("i = %d, j+1 = %d, nx = %d, ny = %d\n", i, j+1, nx, ny);
					add(dp[!now][nx][ny], dp[now][x][y]);
				}
			}
			now = !now;
		}

		clr(dp[!now], 0);
		rep(x, 0, (1<<(m+1))) rep(y, 0, (1<<(1+m))) if(dp[now][x][y]){
			//printf("i = %d, j = %d, x = %d, y = %d\n", i, m, x, y);
			add(dp[!now][sss(x, 0, 0)][sss(y, 0, 0)], dp[now][x][y]);
		}
		now = !now;
	}
	int ret = 0;
	rep(x, 0, (1<<(m+1))) rep(y, 0, (1<<(1+m))) if(test(x, m) && test(y, m)) {
		add(ret, dp[!now][x][y]);
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
			int n                     = 2;
			int m                     = 2;
			string A                  = "ABC";
			string B                  = "ADC";
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = StringPath().countBoards(n, m, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 1: {
			int n                     = 2;
			int m                     = 2;
			string A                  = "ABC";
			string B                  = "ABD";
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = StringPath().countBoards(n, m, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 2: {
			int n                     = 3;
			int m                     = 4;
			string A                  = "ABCDDE";
			string B                  = "ACCBDE";
			int expected__            = 1899302;

			clock_t start__           = clock();
			int received__            = StringPath().countBoards(n, m, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 3: {
			int n                     = 8;
			int m                     = 8;
			string A                  = "ZZZZZZZZZZZZZZZ";
			string B                  = "ZABCDEFGHIJKLMZ";
			int expected__            = 120390576;

			clock_t start__           = clock();
			int received__            = StringPath().countBoards(n, m, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}

				// custom cases

				/*      case 4: {
				int n                     = ;
				int m                     = ;
				string A                  = ;
				string B                  = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = StringPath().countBoards(n, m, A, B);
				return verify_case(casenum__, expected__, received__, clock()-start__);
				}*/
				/*      case 5: {
				int n                     = ;
				int m                     = ;
				string A                  = ;
				string B                  = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = StringPath().countBoards(n, m, A, B);
				return verify_case(casenum__, expected__, received__, clock()-start__);
				}*/
				/*      case 6: {
				int n                     = ;
				int m                     = ;
				string A                  = ;
				string B                  = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = StringPath().countBoards(n, m, A, B);
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
