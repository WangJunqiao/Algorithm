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


class KleofasTail {
public:
	long long countGoodSequences(long long K, long long A, long long B);
};

int is(LL k, LL x){
	if( x==k ) return 1;
	if( x<k ) return 0;
	if( x%2==0 ) return is(k, x/2);
	else return is(k, x-1);
}
LL dfs(LL k, LL a, LL b){
	a=max(a, k);
	if( a>b ) return 0;
	if( a==k ) return 1+dfs(k, a+1, b);
	if( a%2==1 ) return is(k, a)+dfs(k, a+1, b);
	if( b%2==1 ) return is(k, b)+dfs(k, a, b-1);
	//return dfs(k, a/2, b/2)+dfs(k, a/2, b/2-1);
	return 2*dfs(k, a/2, b/2-1)+is(k, b/2);
}

long long KleofasTail::countGoodSequences(long long K, long long A, long long B) {
	return dfs(K, A, B);
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
			long long K               = 3;
			long long A               = 4;
			long long B               = 8;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long K               = 1;
			long long A               = 23457;
			long long B               = 123456;
			long long expected__      = 100000;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long K               = 1234567890123456LL;
			long long A               = 10;
			long long B               = 1000000;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long K               = 0;
			long long A               = 0;
			long long B               = 2;
			long long expected__      = 3;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long K               = 2;
			long long A               = 3;
			long long B               = 3;
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			long long K               = 13;
			long long A               = 12345;
			long long B               = 67890123;
			long long expected__      = 8387584;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			long long K               = ;
			long long A               = ;
			long long B               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long K               = ;
			long long A               = ;
			long long B               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			long long K               = ;
			long long A               = ;
			long long B               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = KleofasTail().countGoodSequences(K, A, B);
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
