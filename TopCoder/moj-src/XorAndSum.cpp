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


class XorAndSum {
public:
	long long maxSum(vector<long long> number);
};


LL highbit(LL x){
	for(int i=62;i>=0;i--){
		if( x&(1LL<<i) ) return 1LL<<i;
	}
	return 0;
}

LL lowbit(LL x){
	for(int i=0;i<=62;i++){
		if( x&(1LL<<i) ) return 1LL<<i;
	}
	return 0;
}

long long XorAndSum::maxSum(vector<long long> num) {
	for(int i=0;i<sz(num);i++){
		if( num[i]==0 ) continue;
		LL h = highbit(num[i]);
		for(int j=i+1;j<sz(num);j++){
			if( num[j]&h ) num[j]^=num[i];
		}
		for(int j=0;j<i;j++){
			if( num[j]&h ) num[j]^=num[i];
		}
	}
	LL ma = 0;
	repv(i, num) ma^=num[i];
	LL ret = 0, add=0;
	repv(i, num){
		ret += ma^num[i];
		add=max(add, ma-ma^num[i]);
	}
	return ret+add;
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
			long long number[]        = {1, 0};
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long number[]        = {1, 2, 3};
			long long expected__      = 8;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long number[]        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long number[]        = {2, 3, 5, 7, 11, 13, 17, 19};
			long long expected__      = 233;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long number[]        = {123456789012345LL, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			long long expected__      = 1234567890123450LL;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			long long number[]        = {627, 674, 281, 272, 289, 877, 62, 122, 603, 189, 615};
			long long expected__      = 10742;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			long long number[]        = {557};
			long long expected__      = 557;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			long long number[]        = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			long long number[]        = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			long long number[]        = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum(vector<long long>(number, number + (sizeof number / sizeof number[0])));
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
