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

//----------------------zjut_DD for Topcoder-------------------------------
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
#define PB push_back
#define MP make_pair
#define ff first
#define ss second
#define two(w) (1<<(w))
#define test(x,w) (x&two(w))
#define sz(v) (int)v.size()
#define all(c) c.begin(),c.end() 
#define clr(buf,val) memset(buf,val,sizeof(buf))
#define rep(i,l,r) for(int i=(l);i<(r);i++)
#define repv(i,v)  for(int i=0;i<(int)v.size();i++)
#define repi(it,c) for(typeof(c.begin()) it=c.begin();it!=c.end();++it)
//------------------------------------------------------------------------


class XorBoard {
public:
	int count(int H, int W, int Rcount, int Ccount, int S);
};

const int N = 1600;
const int mod=555555555;

int C[N][N], dp[N][N];

void add(int &a, int b){
	a=(a+b)%mod;
}

void calc(){
	clr(C, 0);
	clr(dp, 0);
	for(int i=0;i<N;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	dp[0][1]=1; //number wei
	for(int i=0;i<N-5;i++) for(int w=0;w<N-5;w++){
		add(dp[i][w+1], dp[i][w]);
		add(dp[i+2][w], dp[i][w]);
	}
}

int XorBoard::count(int H, int W, int Rcount, int Ccount, int S) {
	calc();
	int ret=0;
	for(int h=0;h<=Rcount;h++) {
		for(int w=0;w<=Ccount;w++){
			int sum = h*W+w*H-h*w*2;
			if( sum!=S ) continue;
			int yr=Rcount-h;
			int yc=Ccount-w;
			if( yr%2 || yc%2 ) continue;
			if( H==2 && W==2 ) {
				//printf("h=%d w=%d yr=%d yc=%d\n", h, w, yr, yc);
				//printf("%d %d %d %d\n", C[H][h], C[W][w], dp[yr][H+1], dp[yc][W+1]);
			}
			add(ret, C[H][h]*(LL)C[W][w]%mod*dp[yr][H]%mod*dp[yc][W]%mod);
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
			int H                     = 2;
			int W                     = 2;
			int Rcount                = 2;
			int Ccount                = 2;
			int S                     = 4;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int H                     = 2;
			int W                     = 2;
			int Rcount                = 0;
			int Ccount                = 0;
			int S                     = 1;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int H                     = 10;
			int W                     = 20;
			int Rcount                = 50;
			int Ccount                = 40;
			int S                     = 200;
			int expected__            = 333759825;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int H                     = 1200;
			int W                     = 1000;
			int Rcount                = 800;
			int Ccount                = 600;
			int S                     = 4000;
			int expected__            = 96859710;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int H                     = 555;
			int W                     = 555;
			int Rcount                = 555;
			int Ccount                = 555;
			int S                     = 5550;
			int expected__            = 549361755;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int H                     = ;
			int W                     = ;
			int Rcount                = ;
			int Ccount                = ;
			int S                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int H                     = ;
			int W                     = ;
			int Rcount                = ;
			int Ccount                = ;
			int S                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int H                     = ;
			int W                     = ;
			int Rcount                = ;
			int Ccount                = ;
			int S                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = XorBoard().count(H, W, Rcount, Ccount, S);
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
