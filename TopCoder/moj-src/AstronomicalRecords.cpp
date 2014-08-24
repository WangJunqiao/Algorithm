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


class AstronomicalRecords {
public:
	int minimalPlanets(vector <int> A, vector <int> B);
};

int ai, bj;
bool match(int xi, int yj) {
	return ai * (LL) yj == bj * (LL) xi;
}

int dp[55][55];

void check(int &a, int b){
	a = max(a, b);
}

int AstronomicalRecords::minimalPlanets(vector <int> A, vector <int> B) {
	int ma = 0;
	rep(i, 0, sz(A)) rep(j, 0, sz(B)) {
		ai = A[i];
		bj = B[j];
		clr(dp, 0);
		rep(y, 0, sz(B)) {
			if(match(A[0], B[y])) dp[0][y] = 1;
			if(y>0) check(dp[0][y], dp[0][y-1]);
		}
		rep(x, 0, sz(A)) {
			if(match(A[x], B[0])) dp[x][0] = 1;
			if(x>0) check(dp[x][0], dp[x-1][0]);
		}
		rep(x, 1, sz(A)) rep(y, 1, sz(B)) {
			check(dp[x][y], dp[x-1][y]);
			check(dp[x][y], dp[x][y-1]);
			if(match(A[x], B[y])) 
				check(dp[x][y], dp[x-1][y-1] + 1);
		}
		rep(x, 0, sz(A)) rep(y, 0, sz(B))
			check(ma, dp[x][y]);
	}
	cout<<ma<<endl;
	return sz(A) + sz(B) - ma;
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
			int A[]                   = {1,2,1,2,1};
			int B[]                   = {2,1,2,1,2};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = AstronomicalRecords().minimalPlanets(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int A[]                   = {1,2,3,4};
			int B[]                   = {2,4,6,8};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = AstronomicalRecords().minimalPlanets(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int A[]                   = {2,3,2,3,2,3,2};
			int B[]                   = {600,700,600,700,600,700,600};
			int expected__            = 10;

			clock_t start__           = clock();
			int received__            = AstronomicalRecords().minimalPlanets(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int A[]                   = {1,2,3,4,5,6,7,8,9};
			int B[]                   = {6,7,8,9,10,11,12};
			int expected__            = 12;

			clock_t start__           = clock();
			int received__            = AstronomicalRecords().minimalPlanets(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int A[]                   = {100000000,200000000};
			int B[]                   = {200000000,100000000};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = AstronomicalRecords().minimalPlanets(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int A[]                   = ;
			int B[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AstronomicalRecords().minimalPlanets(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int A[]                   = ;
			int B[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AstronomicalRecords().minimalPlanets(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int A[]                   = ;
			int B[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AstronomicalRecords().minimalPlanets(vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])));
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
