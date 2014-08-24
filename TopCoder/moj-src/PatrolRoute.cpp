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


class PatrolRoute {
public:
	int countRoutes(int X, int Y, int minT, int maxT);
};

const int mod=1000000007;
#define maxn 21000
void calc(int X, int *dp){
	rep(i, 0, maxn){
		dp[i]=0;
	}
	for(int d1=1;d1<=X;d1++){
		for(int d2=1;d2<=X;d2++){
			if( d1+d2+1>X ) break;
			if( d1+d2+d1+d2>=maxn ) continue;
			dp[2*(d1+d2)]=(dp[2*(d1+d2)]+(X-(d1+d2)))%mod;
		}
	}
}

int dp1[maxn], dp2[maxn];
int sum1[maxn];

int PatrolRoute::countRoutes(int X, int Y, int minT, int maxT) {
	calc(X, dp1);
	calc(Y, dp2);
	sum1[0]=dp1[0];
	rep(i, 1, maxn) sum1[i]=(sum1[i-1]+dp1[i])%mod;
	int ans=0;
	for(int i=0;i<=maxT;i++){
		int l=minT-i, r=maxT-i;
		l=max(0, l);
		r=max(0, r);
		if( l==0 ) ans=(ans+dp2[i]*(LL)sum1[r])%mod;
		else ans=(ans+dp2[i]*(LL)((sum1[r]-sum1[l-1])%mod))%mod;
	}
	ans=(ans%mod+mod)%mod;
	return (ans*(LL)6)%mod;
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
			int X                     = 3;
			int Y                     = 3;
			int minT                  = 1;
			int maxT                  = 20000;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int X                     = 3;
			int Y                     = 3;
			int minT                  = 4;
			int maxT                  = 7;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int X                     = 4;
			int Y                     = 6;
			int minT                  = 9;
			int maxT                  = 12;
			int expected__            = 264;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int X                     = 7;
			int Y                     = 5;
			int minT                  = 13;
			int maxT                  = 18;
			int expected__            = 1212;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int X                     = 4000;
			int Y                     = 4000;
			int minT                  = 4000;
			int maxT                  = 14000;
			int expected__            = 859690013;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int X                     = ;
			int Y                     = ;
			int minT                  = ;
			int maxT                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int X                     = ;
			int Y                     = ;
			int minT                  = ;
			int maxT                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int X                     = ;
			int Y                     = ;
			int minT                  = ;
			int maxT                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PatrolRoute().countRoutes(X, Y, minT, maxT);
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
