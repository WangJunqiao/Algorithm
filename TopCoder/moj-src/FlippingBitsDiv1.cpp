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


class FlippingBitsDiv1 {
public:
	int getmin(vector <string> S, int M);
};


void flip(string &s) {
	rep(i, 0, sz(s)) s[i] = (int)'0'+'1' - s[i];
}

void check(int &a, int b) {
	a = min(a, b);
}

int f1(string s, int SEG, int M, int N) {
	int ret = 0;
	rep(i, 0, M) {
		int t[2] = {0};
		for(int j=i;j<N;j+=M) t[s[j]-'0'] ++;
		ret += min(t[0], t[1]);
	}
	int ans = 1;
	rep(i, 0, SEG*M-M) {
		s[i] = '0'+(int)'1'-s[i];
	}
	rep(i, 0, M) {
		int t[2] = {0};
		for(int j=i;j<N;j+=M) t[s[j]-'0'] ++;
		ans += min(t[0], t[1]);
	}
	return min(ans, ret);
}

int get(string &s1, string &s2) {
	int ret = 0;
	rep(i, 0, sz(s1)) if(s1[i] != s2[i]) ret ++;
	return ret;
}

int dp[333][2];

int calc(string s, string ts, int N, int M, int SEG) {
	clr(dp, 0x3f);
	string tmp = s.substr((SEG-1)*M, M);
	dp[SEG-1][0] = get(tmp, ts);
	flip(tmp);
	dp[SEG-1][1] = get(tmp, ts) + 1;
	int ret = 1000000;
	for(int seg=SEG-1;seg>0;seg--) rep(one, 0, 2) if(dp[seg][one] < 1000000000) {
		//bu fan
		tmp = s.substr((seg-1)*M, M);
		if(one) flip(tmp);
		check(dp[seg-1][one], dp[seg][one] + get(tmp, ts));
		//fan 
		tmp = s.substr((seg-1)*M, M);
		if(!one) flip(tmp);
		check(dp[seg-1][!one], dp[seg][one] + get(tmp, ts) + 1);
	}
	rep(one, 0, 2) check(ret, dp[0][one]);
	return ret;
}
int FlippingBitsDiv1::getmin(vector <string> S, int M) {
	string s = "";
	rep(i, 0, sz(S)) s += S[i];
	int N = sz(s);
	if(M==0 || M==N) return 0;
	int SEG = N/M;
	if(N%M) SEG ++;
	int ret = f1(s, SEG, M, N);
	
	for(int x=0;x<SEG;x++) {
		string ts = s.substr(x*M, M);
		if(sz(ts) < M) continue;
		check(ret, calc(s, ts, N, M, SEG));
		flip(ts);
		check(ret, calc(s, ts, N, M, SEG));
	}

	return ret;
} //101 100 001 101

















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
			string S[]                = {"00111000"};
			int M                     = 1;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S[]                = {"101100001101"};
			int M                     = 3;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S[]                = {"11111111"};
			int M                     = 4;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S[]                = {"1101001000"};
			int M                     = 8;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string S[]                = {"1","10","11","100","101","110"};
			int M                     = 5;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string S[]                = {"1001011000101010001111111110111011011100110001001"};
			int M                     = 2;
			int expected__            = 16;

			clock_t start__           = clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string S[]                = ;
			int M                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string S[]                = ;
			int M                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string S[]                = ;
			int M                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
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
