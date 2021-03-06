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

#define rep(i,st,ed) for(int i=st;i<ed;i++)
#define pb push_back
#define mp make_pair
#define sz(X) ((int)(X.size()))
#define tr(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define all(x) x.begin(),x.end()
#define clr(x,c) memset(x,c,sizeof(x))
#define two(X) (1<<(X))
#define twoL(X) (((int64)(1))<<(X))
#define test(S,X) (((S)&two(X))!=0)
#define testL(S,X) (((S)&twoL(X))!=0)

typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
typedef long long LL;
typedef unsigned long long ULL;

template<class T> inline void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> inline void checkmax(T &a,T b){if(b>a) a=b;}
template<class T> inline T sqr(T x){return x*x;}
template<class T> inline T lowbit(T n){return (n^(n-1))&n;}
template<class T> string toString(T n){ostringstream ost;ost<<n;ost.flush();return ost.str();}

#define ASSERT(X) {if (!(X)) {printf("\n assertion failed at line %d\n",__LINE__);exit(0);}}




class WolfPack {
public:
	int calc(vector <int> x, vector <int> y, int m);
};





typedef long long LL;
int gcd(int a,int b){ return b?gcd(b,a%b):a; }
int lcm(int a,int b){ return a/gcd(a,b)*b;   }

//扩展欧几里得
LL ext_gcd(LL a,LL b,LL &x,LL &y){
	if(b==0){  x=1,y=0;  return a;  }
	LL d=ext_gcd(b,a%b,x,y) , temp=x;
	x=y,y=temp-a/b*y;  return d;
}

//算逆元
int get_ni(int a,int p){ //返回x,ax=1 (mod p) ap互质
	int x,y;
	ext_gcd(a,p,x,y);
	return x;
}



int C(int n, int m, int P) {
	long long t = 1;
	for(int i=0;i<m;i++) t = t*(n-i)%P;
	long long s = 1;
	for(int i=1;i<=m;i++) s = s*i%P;
	return t * get_ni(s)%P;
}


int WolfPack::calc(vector <int> x, vector <int> y, int m) {
	int n = sz(x);
	for(int i=1;i<n;i++) {

	}
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
			int x[]                   = {3,5};
			int y[]                   = {0,0};
			int m                     = 1;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int x[]                   = {0,0};
			int y[]                   = {0,1};
			int m                     = 1;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int x[]                   = {0,2,4};
			int y[]                   = {0,0,0};
			int m                     = 2;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int x[]                   = {7,8};
			int y[]                   = {8,7};
			int m                     = 1;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int x[]                   = {-2,-2,-2,0,0,0,2,2,2};
			int y[]                   = {-2,0,2,-2,0,2,-2,0,2};
			int m                     = 1000;
			int expected__            = 387540818;

			clock_t start__           = clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int x[]                   = ;
			int y[]                   = ;
			int m                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int x[]                   = ;
			int y[]                   = ;
			int m                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int x[]                   = ;
			int y[]                   = ;
			int m                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
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
