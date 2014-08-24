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


class TwoConvexShapes {
public:
	int countWays(vector <string> grid);
};

const int mod=1000000007;
LL dp[55][55][3]; //0=   1ºı…Ÿ  2‘ˆº”
int n, m;
void add(LL &a, LL b){
	a=(a+b)%mod;
}

VS g;
char get(int i, int j){
	return g[i-1][j-1];
}

bool canbe(int row, int l, int r, char ch){
	for(int i=l;i<=r;i++){
		if( get(row, i)==ch || get(row,i)=='?' ) continue;
		return false;
	}
	return true;
}

int TwoConvexShapes::countWays(vector <string> grid) {
	LL ret=0;
	g=grid;
	n=sz(grid), m=sz(grid[0]);
	
	for(int w=0;w<2;w++){
		//cout<<w<<endl;
		char ch1, ch2;
		if( w==0 ) ch1='B', ch2='W';
		else ch1='W', ch2='B';
		clr(dp, 0);
		for(int i=0;i<=m;i++) {
			if( canbe(1, 1, i, ch1) && canbe(1, i+1, m, ch2) ) {
				dp[1][i][0]=1;
				//printf("i=%d\n", i);
			}
		}
		for(int i=1;i<n;i++) for(int j=0;j<=m;j++) for(int k=0;k<3;k++) if( dp[i][j][k] ) {
			for(int nj=0;nj<=m;nj++) {
				if( k==1 && nj>j ) continue;
				if( k==2 && nj<j ) continue;
				int nk;
				if( nj==j ) nk=k;
				else if( nj>j ) nk=2;
				else nk=1;
				if( canbe(i+1, 1, nj, ch1) && canbe(i+1, nj+1, m, ch2) ){
					add(dp[i+1][nj][nk], dp[i][j][k]);
				}
			}
		}
		for(int j=0;j<=m;j++) for(int k=0;k<3;k++) add(ret, dp[n][j][k]);
	}
	
	for(int i=1;i<=n;i++){
		bool allB1=true, allW1=true, allB2=true, allW2=true;
		for(int j=1;j<=n;j++) {
			if( j<=i ) {
				if( !canbe(j, 1, m, 'B') ) allB1=false;
				if( !canbe(j, 1, m, 'W') ) allW1=false;
			}else{
				if( !canbe(j, 1, m, 'B') ) allB2=false;
				if( !canbe(j, 1, m, 'W') ) allW2=false;
			}
		}
		if( i==n ){
			if( allB1 ) ret=(ret+mod-1)%mod;
			if( allW1 ) ret=(ret+mod-1)%mod;
		}else{
			if( allB1 && allW2 ) ret=(ret+mod-1)%mod;
			if( allW1 && allB2 ) ret=(ret+mod-1)%mod;
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
				string grid[]             = {"??",
					"??"};
				int expected__            = 14;

				clock_t start__           = clock();
				int received__            = TwoConvexShapes().countWays(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}
		case 1: {
				string grid[]             = {"B?",
					"??"};
				int expected__            = 7;

				clock_t start__           = clock();
				int received__            = TwoConvexShapes().countWays(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}
		case 2: {
				string grid[]             = {"WWB",
					"WWW",
					"WWW",
					"WWW"};
				int expected__            = 1;

				clock_t start__           = clock();
				int received__            = TwoConvexShapes().countWays(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}
		case 3: {
				string grid[]             = {"BBBBBB",
					"WWBBBB",
					"WBBBBB"};
				int expected__            = 0;

				clock_t start__           = clock();
				int received__            = TwoConvexShapes().countWays(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}
		case 4: {
				string grid[]             = {"?BB?",
					"BBBB",
					"?BB?"};
				int expected__            = 5;

				clock_t start__           = clock();
				int received__            = TwoConvexShapes().countWays(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}
		case 5: {
				string grid[]             = {"?WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
					"B?WWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
					"BB?WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
					"BBB?WWWWWWWWWWWWWWWWWWWWWWWWWWW",
					"BBBB?WWWWWWWWWWWWWWWWWWWWWWWWWW",
					"BBBBB?WWWWWWWWWWWWWWWWWWWWWWWWW",
					"BBBBBB?WWWWWWWWWWWWWWWWWWWWWWWW",
					"BBBBBBB?WWWWWWWWWWWWWWWWWWWWWWW",
					"BBBBBBBB?WWWWWWWWWWWWWWWWWWWWWW",
					"BBBBBBBBB?WWWWWWWWWWWWWWWWWWWWW",
					"BBBBBBBBBB?WWWWWWWWWWWWWWWWWWWW",
					"BBBBBBBBBBB?WWWWWWWWWWWWWWWWWWW",
					"BBBBBBBBBBBB?WWWWWWWWWWWWWWWWWW",
					"BBBBBBBBBBBBB?WWWWWWWWWWWWWWWWW",
					"BBBBBBBBBBBBBB?WWWWWWWWWWWWWWWW",
					"BBBBBBBBBBBBBBB?WWWWWWWWWWWWWWW",
					"BBBBBBBBBBBBBBBB?WWWWWWWWWWWWWW",
					"BBBBBBBBBBBBBBBBB?WWWWWWWWWWWWW",
					"BBBBBBBBBBBBBBBBBB?WWWWWWWWWWWW",
					"BBBBBBBBBBBBBBBBBBB?WWWWWWWWWWW",
					"BBBBBBBBBBBBBBBBBBBB?WWWWWWWWWW",
					"BBBBBBBBBBBBBBBBBBBBB?WWWWWWWWW",
					"BBBBBBBBBBBBBBBBBBBBBB?WWWWWWWW",
					"BBBBBBBBBBBBBBBBBBBBBBB?WWWWWWW",
					"BBBBBBBBBBBBBBBBBBBBBBBB?WWWWWW",
					"BBBBBBBBBBBBBBBBBBBBBBBBB?WWWWW",
					"BBBBBBBBBBBBBBBBBBBBBBBBBB?WWWW",
					"BBBBBBBBBBBBBBBBBBBBBBBBBBB?WWW",
					"BBBBBBBBBBBBBBBBBBBBBBBBBBBB?WW",
					"BBBBBBBBBBBBBBBBBBBBBBBBBBBBB?W"};
				int expected__            = 73741817;

				clock_t start__           = clock();
				int received__            = TwoConvexShapes().countWays(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}

			// custom cases

			/*      case 6: {
			string grid[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TwoConvexShapes().countWays(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
			/*      case 7: {
			string grid[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TwoConvexShapes().countWays(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
			/*      case 8: {
			string grid[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TwoConvexShapes().countWays(vector <string>(grid, grid + (sizeof grid / sizeof grid[0])));
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
