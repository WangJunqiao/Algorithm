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



class Excavations {
public:
	long long count(vector <int> kind, vector <int> depth, vector <int> found, int K);
};


bool is[55];
int id[1100000];
LL dp[2][55][55][55];

void add(LL &a, LL b){
	a += b;
}


long long Excavations::count(vector <int> kind, vector <int> depth, vector <int> found, int K) {
	clr(is, false);
	rep(i, 0, sz(found)) is[found[i]] = true;
	int tmp[55], cnt = 0;
	rep(i, 0, sz(depth)) tmp[cnt++] = depth[i];
	//tmp[cnt++] = 110000;
	
	sort(tmp, tmp+cnt);
	cnt = unique(tmp, tmp+cnt) - tmp;
	rep(i, 0, cnt) id[tmp[i]] = i;

	printf("cnt = %d\n", cnt);

	vector<PII> v;
	rep(i, 0, sz(kind)) v.push_back(PII(kind[i], depth[i]));
	sort(all(v));
	int n = sz(v);

	dp[0][0][0][cnt] = 1;
	bool now = false;
	rep(i, 0, sz(v)) {
		clr(dp[!now], 0);
		rep(k, 0, K) rep(x, 0, cnt) rep(y, x+1, cnt+1) {
			if(dp[now][k][x][y] == 0) continue;
			for(int ni=i;ni<n;ni++) {
				if()
			}
		} 
		now = !now;
	}
	LL ret = 0;
	rep(x, 0, cnt) rep(y, x+1, cnt+1) {
		if(dp[now][K][x][y] == 0) continue;
		add(ret, dp[now][K][x][y]);
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) {
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
	//{, , {11, 43}, 13}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int kind[]                = {1, 1, 2, 2};
			int depth[]               = {10, 15, 10, 20};
			int found[]               = {1};
			int K                     = 2;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int kind[]                = {1, 1, 2, 2};
			int depth[]               = {10, 15, 10, 20};
			int found[]               = {1, 2};
			int K                     = 2;
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int kind[]                = {1, 2, 3, 4};
			int depth[]               = {10, 10, 10, 10};
			int found[]               = {1, 2};
			int K                     = 3;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int kind[]                = {1, 2, 2, 3, 1, 3, 2, 1, 2};
			int depth[]               = {12512, 12859, 125, 1000, 99, 114, 125, 125, 114};
			int found[]               = {1, 2, 3};
			int K                     = 7;
			long long expected__      = 35;

			clock_t start__           = clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int kind[]                = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
			int depth[]               = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3};
			int found[]               = {50};
			int K                     = 18;
			long long expected__      = 9075135300LL;

			clock_t start__           = clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int kind[]                = ;
			int depth[]               = ;
			int found[]               = ;
			int K                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int kind[]                = ;
			int depth[]               = ;
			int found[]               = ;
			int K                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int kind[]                = ;
			int depth[]               = ;
			int found[]               = ;
			int K                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
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