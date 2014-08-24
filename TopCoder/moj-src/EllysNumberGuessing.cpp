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


class EllysNumberGuessing {
public:
	int getNumber(vector <int> guesses, vector <int> answers);
};

bool check(VI g, VI a, int ss) {
	rep(i, 0, sz(g)) {
		if(g[i]-a[i] == ss || g[i]+a[i]==ss) continue;
		return false;
	}
	return true;
}

int EllysNumberGuessing::getNumber(vector <int> g, vector <int> a) {
	int ans1 = g[0] + a[0];
	int ans2 = g[0] - a[0];
	
	vector<int> v;
	if(check(g, a, ans1) && ans1>=1 && ans1<=1000000000) {
		v.push_back(ans1);
	}
	if(check(g, a, ans2) && ans2>=1 && ans2<=1000000000) {
		v.push_back(ans2);
	}
	
	if(sz(v) == 2) return -1;
	if(sz(v) == 0) return -2;
	return v[0];
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
			int guesses[]             = {600, 594};
			int answers[]             = {6, 12};
			int expected__            = 606;

			clock_t start__           = clock();
			int received__            = EllysNumberGuessing().getNumber(vector <int>(guesses, guesses + (sizeof guesses / sizeof guesses[0])), vector <int>(answers, answers + (sizeof answers / sizeof answers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int guesses[]             = {100, 50, 34, 40};
			int answers[]             = {58, 8, 8, 2};
			int expected__            = 42;

			clock_t start__           = clock();
			int received__            = EllysNumberGuessing().getNumber(vector <int>(guesses, guesses + (sizeof guesses / sizeof guesses[0])), vector <int>(answers, answers + (sizeof answers / sizeof answers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int guesses[]             = {500000, 600000, 700000};
			int answers[]             = {120013, 220013, 79987};
			int expected__            = -2;

			clock_t start__           = clock();
			int received__            = EllysNumberGuessing().getNumber(vector <int>(guesses, guesses + (sizeof guesses / sizeof guesses[0])), vector <int>(answers, answers + (sizeof answers / sizeof answers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int guesses[]             = {500000000};
			int answers[]             = {133742666};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = EllysNumberGuessing().getNumber(vector <int>(guesses, guesses + (sizeof guesses / sizeof guesses[0])), vector <int>(answers, answers + (sizeof answers / sizeof answers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int guesses[]             = {76938260, 523164588, 14196746, 296286419, 535893832, 41243148, 364561227, 270003278, 472017422, 367932361, 395758413, 301278456, 186276934, 316343129, 336557549, 52536121, 98343562, 356769915, 89249181, 335191879};
			int answers[]             = {466274085, 20047757, 529015599, 246925926, 7318513, 501969197, 178651118, 273209067, 71194923, 175279984, 147453932, 241933889, 356935411, 226869216, 206654796, 490676224, 444868783, 186442430, 453963164, 208020466};
			int expected__            = 543212345;

			clock_t start__           = clock();
			int received__            = EllysNumberGuessing().getNumber(vector <int>(guesses, guesses + (sizeof guesses / sizeof guesses[0])), vector <int>(answers, answers + (sizeof answers / sizeof answers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int guesses[]             = {42};
			int answers[]             = {42};
			int expected__            = 84;

			clock_t start__           = clock();
			int received__            = EllysNumberGuessing().getNumber(vector <int>(guesses, guesses + (sizeof guesses / sizeof guesses[0])), vector <int>(answers, answers + (sizeof answers / sizeof answers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int guesses[]             = {999900000};
			int answers[]             = {100001};
			int expected__            = 999799999;

			clock_t start__           = clock();
			int received__            = EllysNumberGuessing().getNumber(vector <int>(guesses, guesses + (sizeof guesses / sizeof guesses[0])), vector <int>(answers, answers + (sizeof answers / sizeof answers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			int guesses[]             = ;
			int answers[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EllysNumberGuessing().getNumber(vector <int>(guesses, guesses + (sizeof guesses / sizeof guesses[0])), vector <int>(answers, answers + (sizeof answers / sizeof answers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int guesses[]             = ;
			int answers[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EllysNumberGuessing().getNumber(vector <int>(guesses, guesses + (sizeof guesses / sizeof guesses[0])), vector <int>(answers, answers + (sizeof answers / sizeof answers[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int guesses[]             = ;
			int answers[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EllysNumberGuessing().getNumber(vector <int>(guesses, guesses + (sizeof guesses / sizeof guesses[0])), vector <int>(answers, answers + (sizeof answers / sizeof answers[0])));
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
