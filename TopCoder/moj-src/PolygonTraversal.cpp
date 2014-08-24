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




class PolygonTraversal {
public:
	long long count(int N, vector <int> points);
};

LL dp[1<<18][18];

long long PolygonTraversal::count(int N, vector <int> points) {
	if(sz(points)<=2) return 0;
	clr(dp, 0);
	int s = 0;
	for(int i=0;i<points.size();i++) {
		s |= two(points[i]-1);
	}
	dp[s][points[points.size()-1]-1] = 1;
	bool zz[44];
	for(int i=0;i<two(N);i++) {
		for(int j=0;j<N;j++) if(dp[i][j]) {
			for(int k=0;k<N;k++) if(test(i, k)) zz[k] = zz[k+N] = true;
			else zz[k] = zz[k+N] = false;
			int x = j+1;
			while(zz[x]==false) x++;
			int y = j-1;
			while(zz[(y+N)%N]==false) y--;
			if(y<x) y+=N;
			for(int k=x+1;k<y;k++) if(zz[k]==false) {
				dp[i|two(k%N)][k%N] += dp[i][j];
			}
		}
	}
	LL ret = 0;
	for(int i=0;i<N;i++) {
		int j = points[0]-1;
		int a=abs(i-j);
		if(a==1 || a==N-1) continue;
		ret += dp[two(N)-1][i];
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

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int N                     = 5;
			int points[]              = {1, 3, 5};
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 6;
			int points[]              = {1, 4, 2};
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 7;
			int points[]              = {2, 4, 7};
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 7;
			int points[]              = {1, 2, 3, 4, 6, 5};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 18;
			int points[]              = {1, 7, 18};
			long long expected__      = 4374612736LL;

			clock_t start__           = clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int N                     = ;
			int points[]              = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			int points[]              = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int points[]              = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
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
