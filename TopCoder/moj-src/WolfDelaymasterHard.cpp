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


class WolfDelaymasterHard {
public:
	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd);
};

const int mod = 1000000007;

#define  maxn 21000000

char s[2200000];
int dp[2200000];
int sum[2200000];

int lastw[2200000];
int lasto[maxn];

int WolfDelaymasterHard::countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd) {
	rep(i, 0, N) s[i] = '?';				// Concatenation of N '?'s

	LL x = w0;
	for(int i=0;i<wlen;i++){
		s[x] = 'w';				// Rewrite the x-th (0-based) character of s
		x = (x * wmul + wadd) % N;
	}

	x = o0;
	for(int i=0;i<olen;i++){
		s[x] = 'o';				// Rewrite the x-th (0-based) character of s
		x = (x * omul + oadd) % N;
	}

	dp[0] = sum[0] = 0;
	int lw = -1, lo = -1;
	rep(i, 0, N) {
		if(s[i]=='w') lw = i;
		if(s[i]=='o') lo = i;
		lastw[i] = lw;
		lasto[i] = lo;
	}
	rep(i, 0, N) {
		int len = min(i+1, i - lastw[i]);
		len = min(len, )
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
			int N                     = 8;
			int wlen                  = 5;
			int w0                    = 2;
			int wmul                  = 3;
			int wadd                  = 2;
			int olen                  = 0;
			int o0                    = 6;
			int omul                  = 7;
			int oadd                  = 1;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = WolfDelaymasterHard().countWords(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 20;
			int wlen                  = 19;
			int w0                    = 12;
			int wmul                  = 9;
			int wadd                  = 15;
			int olen                  = 1;
			int o0                    = 8;
			int omul                  = 11;
			int oadd                  = 1;
			int expected__            = 26;

			clock_t start__           = clock();
			int received__            = WolfDelaymasterHard().countWords(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 40;
			int wlen                  = 24;
			int w0                    = 34;
			int wmul                  = 5;
			int wadd                  = 11;
			int olen                  = 33;
			int o0                    = 35;
			int omul                  = 23;
			int oadd                  = 27;
			int expected__            = 296;

			clock_t start__           = clock();
			int received__            = WolfDelaymasterHard().countWords(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 60;
			int wlen                  = 35;
			int w0                    = 8;
			int wmul                  = 55;
			int wadd                  = 3;
			int olen                  = 11;
			int o0                    = 20;
			int omul                  = 9;
			int oadd                  = 29;
			int expected__            = 10058904;

			clock_t start__           = clock();
			int received__            = WolfDelaymasterHard().countWords(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 2000;
			int wlen                  = 183;
			int w0                    = 994;
			int wmul                  = 862;
			int wadd                  = 468;
			int olen                  = 148;
			int o0                    = 433;
			int omul                  = 1247;
			int oadd                  = 1989;
			int expected__            = 532199331;

			clock_t start__           = clock();
			int received__            = WolfDelaymasterHard().countWords(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int N                     = 2000000;
			int wlen                  = 419443;
			int w0                    = 1305303;
			int wmul                  = 1761823;
			int wadd                  = 1007025;
			int olen                  = 874640;
			int o0                    = 1516339;
			int omul                  = 229519;
			int oadd                  = 1473199;
			int expected__            = 861766906;

			clock_t start__           = clock();
			int received__            = WolfDelaymasterHard().countWords(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int N                     = 8;
			int wlen                  = 6;
			int w0                    = 0;
			int wmul                  = 1;
			int wadd                  = 1;
			int olen                  = 3;
			int o0                    = 3;
			int omul                  = 6;
			int oadd                  = 1;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = WolfDelaymasterHard().countWords(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			int N                     = ;
			int wlen                  = ;
			int w0                    = ;
			int wmul                  = ;
			int wadd                  = ;
			int olen                  = ;
			int o0                    = ;
			int omul                  = ;
			int oadd                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = WolfDelaymasterHard().countWords(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int N                     = ;
			int wlen                  = ;
			int w0                    = ;
			int wmul                  = ;
			int wadd                  = ;
			int olen                  = ;
			int o0                    = ;
			int omul                  = ;
			int oadd                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = WolfDelaymasterHard().countWords(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int N                     = ;
			int wlen                  = ;
			int w0                    = ;
			int wmul                  = ;
			int wadd                  = ;
			int olen                  = ;
			int o0                    = ;
			int omul                  = ;
			int oadd                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = WolfDelaymasterHard().countWords(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
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
