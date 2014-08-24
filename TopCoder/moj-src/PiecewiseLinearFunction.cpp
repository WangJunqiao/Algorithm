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


class PiecewiseLinearFunction {
public:
	int maximumSolutions(vector <int> Y);
};


int go(vector<int> Y, int x) {
	//printf("check x = %d\n", x);
	set<int> st;
	rep(i, 0, sz(Y)-1) {
		if(Y[i] == x) {
			st.insert(2*i);
		} else if(Y[i+1]==x){
			st.insert(2*i+2);
		} else if(min(Y[i], Y[i+1])<x && max(Y[i], Y[i+1])>x) {
			st.insert(2*i+1);
		}
	}
	return sz(st);
}


int PiecewiseLinearFunction::maximumSolutions(vector <int> Y) {
	rep(i, 0, sz(Y)) Y[i] *= 2;
	rep(i, 0, sz(Y)-1) if(Y[i]==Y[i+1]) return -1;
	set<int> st;
	rep(i, 0, sz(Y)) st.insert(Y[i]);
	vector<int> v(all(st));

	int ret = 0;
	rep(i, 0, sz(v)) {
		ret = max(ret, go(Y, v[i]));
		ret = max(ret, go(Y, v[i]+1));
		
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
			int Y[]                   = {-1,9, -1, 9 ,-1 ,9 ,1 ,-9 ,1 ,-9, 1 ,-9 ,1};
			int expected__            = 12;

			clock_t start__           = clock();
			int received__            = PiecewiseLinearFunction().maximumSolutions(vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int Y[]                   = {4, 4};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = PiecewiseLinearFunction().maximumSolutions(vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int Y[]                   = {1, 4, -1, 2};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = PiecewiseLinearFunction().maximumSolutions(vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int Y[]                   = {2, 1, 2, 1, 3, 2, 3, 2};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = PiecewiseLinearFunction().maximumSolutions(vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int Y[]                   = {125612666, -991004227, 0, 6, 88023, -1000000000, 1000000000, -1000000000, 1000000000};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = PiecewiseLinearFunction().maximumSolutions(vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int Y[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PiecewiseLinearFunction().maximumSolutions(vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int Y[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PiecewiseLinearFunction().maximumSolutions(vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int Y[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PiecewiseLinearFunction().maximumSolutions(vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
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
"NNNNNNYNNNYYYNNYNYNYNNNNNNNYNNNNNNNYNNYNNYNNNYYNYY"
"NNNNNNYNNNYYYNNYNYNYNNNNNNNYNNNYNNNYNNYNNYNNNYYNYY"