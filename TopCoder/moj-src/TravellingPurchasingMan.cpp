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


class TravellingPurchasingMan {
public:
	int maxStores(int N, vector <string> interestingStores, vector <string> roads);
};

int dis[55][55];
int __dp[1<<16][16];

void check(int &a, int b){
	a = min(a, b);
}

int TravellingPurchasingMan::maxStores(int N, vector <string> intes, vector <string> roads) {
	clr(dis, 0x3f);
	rep(i, 0, N) dis[i][i] = 0;
	rep(i, 0, sz(roads)) {
		istringstream sin(roads[i]);
		int a, b, len;
		sin>>a>>b>>len;
		dis[a][b] = dis[b][a] = min(dis[a][b], len);
	}
	rep(k, 0, N) rep(i, 0, N) rep(j, 0, N) dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);

	vector<int> S, T, D;
	rep(i, 0, sz(intes)) {
		istringstream sin(intes[i]);
		int s, t, d;
		sin>>s>>t>>d;
		S.push_back(s);
		T.push_back(t);
		D.push_back(d);
	}
	int M = sz(intes);

	clr(__dp, 0x3f);
	rep(i, 0, M) if(dis[N-1][i]<=T[i]){
		int ddd = max(S[i] + D[i], dis[N-1][i] + D[i]);
		__dp[1<<i][i] = ddd;
	}
	const int inf = 100000000;
	rep(i, 0, (1<<M)) {
		rep(j, 0, M) if(__dp[i][j] < inf) {
			rep(k, 0, M) if(!(i & (1<<k) )) {
				int tt = dis[j][k] + __dp[i][j];
				if(tt<=T[k]) {
					int ddd = max(tt+D[k], S[k]+D[k]);
					check(__dp[i+(1<<k)][k], ddd);
				}
				//dis[i|(1<<k)][k] = min(dis[i|(1<<k)][k], dis[i][j]+)
			}
		}
	}
	int ret = 0;
	rep(i, 0, (1<<M)) rep(j, 0, M) if(__dp[i][j] < inf) {
		int num = 0;
		rep(k, 0, M) if(i&(1<<k)) num ++;
		ret = max(ret, num);
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
			int N                     = 3;
			string interestingStores[] = {"1 10 10" , "1 55 31", "10 50 100" };
			string roads[]            = {"1 2 10"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = TravellingPurchasingMan().maxStores(N, vector <string>(interestingStores, interestingStores + (sizeof interestingStores / sizeof interestingStores[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 3;
			string interestingStores[] = {"1 10 10" , "1 55 30", "10 50 100" };
			string roads[]            = {"1 2 10"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TravellingPurchasingMan().maxStores(N, vector <string>(interestingStores, interestingStores + (sizeof interestingStores / sizeof interestingStores[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 5;
			string interestingStores[] = {"0 1000 17"};
			string roads[]            = {"2 3 400", "4 1 500", "4 3 300", "1 0 700", "0 2 400"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = TravellingPurchasingMan().maxStores(N, vector <string>(interestingStores, interestingStores + (sizeof interestingStores / sizeof interestingStores[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 3: {
			int N                     = ;
			string interestingStores[] = ;
			string roads[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TravellingPurchasingMan().maxStores(N, vector <string>(interestingStores, interestingStores + (sizeof interestingStores / sizeof interestingStores[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 4: {
			int N                     = ;
			string interestingStores[] = ;
			string roads[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TravellingPurchasingMan().maxStores(N, vector <string>(interestingStores, interestingStores + (sizeof interestingStores / sizeof interestingStores[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int N                     = ;
			string interestingStores[] = ;
			string roads[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TravellingPurchasingMan().maxStores(N, vector <string>(interestingStores, interestingStores + (sizeof interestingStores / sizeof interestingStores[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
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
