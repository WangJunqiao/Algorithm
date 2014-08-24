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




class TheMagicMatrix {
public:
	int find(int n, vector <int> rows, vector <int> columns, vector <int> values);
};


int TheMagicMatrix::find(int n, vector <int> rows, vector <int> columns, vector <int> values) {
	
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
			int rows[]                = {0, 1};
			int columns[]             = {1, 0};
			int values[]              = {4, 4};
			int expected__            = 10;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 2;
			int rows[]                = {0, 1};
			int columns[]             = {1, 0};
			int values[]              = {4, 7};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 4;
			int rows[]                = {0, 0, 0, 1, 2, 2, 2, 3, 3, 3};
			int columns[]             = {0, 1, 2, 3, 0, 1, 2, 0, 1, 2};
			int values[]              = {3, 5, 1, 9, 5, 1, 8, 6, 7, 1};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 474;
			int rows[]                = {44, 77};
			int columns[]             = {47, 74};
			int values[]              = {4, 7};
			int expected__            = 83494518;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int n                     = ;
			int rows[]                = ;
			int columns[]             = ;
			int values[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int n                     = ;
			int rows[]                = ;
			int columns[]             = ;
			int values[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int n                     = ;
			int rows[]                = ;
			int columns[]             = ;
			int values[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheMagicMatrix().find(n, vector <int>(rows, rows + (sizeof rows / sizeof rows[0])), vector <int>(columns, columns + (sizeof columns / sizeof columns[0])), vector <int>(values, values + (sizeof values / sizeof values[0])));
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
