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


class TheExperiment {
public:
	int countPlacements(vector <string> intensity, int M, int L, int A, int B);
};

#define maxn 310

int sum[maxn];
const int mod = 1000000009;

void add(int &a, int b) {
	a+=b;
	if(a>=mod) a-= mod;
}

int dp[2][2][maxn][maxn];
void subdp(string s, int A, int B, int L) {
	s = "0" + s;
	for(int i=1;i<sz(s);i++) sum[i] = sum[i-1] + (s[i]-'0');
	rep(N, 0, 2) rep(t, 0, 2) rep(i, 0, maxn) rep(j, 0, maxn) dp[N][t][i][j] = 0;
	dp[1][0][0][0] = 1;
	//dp[0][0][0] = 1;
	//cout<<sz(s)<<endl;


	rep(i, 0, sz(s)) {
		rep(j, 0, sz(s)){ 
			rep(t, 0, 2) {
				rep(_new, 0, 2) if(dp[_new][t][i][j]) {
					if(_new || t==1) add(dp[1][0][i+1][j], dp[_new][t][i][j]);
					rep(k, i+1, sz(s)) {

						//add(dp[0][k][j], dp[t][i][j]);
						

						if(k-i<=L) {
							if(sum[k]-sum[i] < A) continue;
							if(sum[k]-sum[i] > B) continue;
							int nt = t;
							if(k-i == L) nt = 1;
							add(dp[0][nt][k][j+1], dp[_new][t][i][j]);
							//add(dp[0][k][j], dp[t][i][j]);
						}

						//if(sz(s)==7) printf("nt = %d, k = %d, j+1 = %d\n", nt, k, j+1);
					}
				}
			}
		}
	}
}

int TheExperiment::countPlacements(vector <string> intensity, int M, int L, int A, int B) {
	string s = "";
	rep(i, 0, sz(intensity)) s+=intensity[i];

	subdp(s, A, B, L);
	int ans = 0;
	rep(N, 0, 2) rep(T, 0, 2) {
		if(N==0 && T==0) continue;
		add(ans, dp[N][T][sz(s)][M]);
	}
	return ans;
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
			string intensity[]        = {"341156"};
			int M                     = 3;
			int L                     = 3;
			int A                     = 6;
			int B                     = 10;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 1: {
			string intensity[]        = {"999112999"};
			int M                     = 2;
			int L                     = 4;
			int A                     = 21;
			int B                     = 30;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 2: {
			string intensity[]        = {"111"};
			int M                     = 2;
			int L                     = 2;
			int A                     = 2;
			int B                     = 3;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 3: {
			string intensity[]        = {"59059", "110", "1132230231"};
			int M                     = 1;
			int L                     = 5;
			int A                     = 10;
			int B                     = 20;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 4: {
			string intensity[]        = {"111111111111111111111111", "111111111111111111111111111", "11111111111111111111111"};
			int M                     = 12;
			int L                     = 8;
			int A                     = 4;
			int B                     = 2700;
			int expected__            = 418629948;

			clock_t start__           = clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}

				// custom cases

				/*      case 5: {
				string intensity[]        = ;
				int M                     = ;
				int L                     = ;
				int A                     = ;
				int B                     = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
				return verify_case(casenum__, expected__, received__, clock()-start__);
				}*/
				/*      case 6: {
				string intensity[]        = ;
				int M                     = ;
				int L                     = ;
				int A                     = ;
				int B                     = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
				return verify_case(casenum__, expected__, received__, clock()-start__);
				}*/
				/*      case 7: {
				string intensity[]        = ;
				int M                     = ;
				int L                     = ;
				int A                     = ;
				int B                     = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
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
