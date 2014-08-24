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


class FoxPaintingBalls {
public:
	long long theMax(long long R, long long G, long long B, int N);
};


long long FoxPaintingBalls::theMax(long long R, long long G, long long B, int N) {
	if( N==1 ) return R+G+B;
	if( N%3==1 ){
		LL sum = N*(LL)(N+1)/2;
		LL single = sum/3;
		LL ret = 0;
		LL mm=min(min(R, G), B);
		LL yu = R+G+B-mm*3;
		if( yu>mm/single ){
			return mm/single;
		}
		ret = yu;
		LL all = mm-yu*single;
		ret +=all/(single*3+1)*3;
		all%=(single*3+1);
		
		vector<LL> v;
		v.PB(all); 
		v.PB(all);
		v.PB(all);
		while( true ){
			sort(all(v));
			if( v[0]<single ) break;
			if( v[2]<single+1 ) break;
			v[0]-=single;
			v[1]-=single;
			v[2]-=(single+1);
			ret++;
		}
		return ret;
	}else{
		LL sum = N*(LL)(N+1)/2;
		LL single = sum/3;
		return min( min(R/single, G/single), B/single);
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
			long long R               = 100000;
			long long G               = 50000;
			long long B               = 25000;
			int N                     = 4;
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = FoxPaintingBalls().theMax(R, G, B, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long R               = 1;
			long long G               = 2;
			long long B               = 3;
			int N                     = 3;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = FoxPaintingBalls().theMax(R, G, B, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long R               = 8;
			long long G               = 6;
			long long B               = 6;
			int N                     = 4;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = FoxPaintingBalls().theMax(R, G, B, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long R               = 7;
			long long G               = 6;
			long long B               = 7;
			int N                     = 4;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = FoxPaintingBalls().theMax(R, G, B, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long R               = 100;
			long long G               = 100;
			long long B               = 100;
			int N                     = 4;
			long long expected__      = 30;

			clock_t start__           = clock();
			long long received__      = FoxPaintingBalls().theMax(R, G, B, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			long long R               = 19330428391852493LL;
			long long G               = 48815737582834113LL;
			long long B               = 11451481019198930LL;
			int N                     = 3456;
			long long expected__      = 5750952686LL;

			clock_t start__           = clock();
			long long received__      = FoxPaintingBalls().theMax(R, G, B, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			long long R               = 1;
			long long G               = 1;
			long long B               = 1;
			int N                     = 1;
			long long expected__      = 3;

			clock_t start__           = clock();
			long long received__      = FoxPaintingBalls().theMax(R, G, B, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			long long R               = ;
			long long G               = ;
			long long B               = ;
			int N                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FoxPaintingBalls().theMax(R, G, B, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			long long R               = ;
			long long G               = ;
			long long B               = ;
			int N                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FoxPaintingBalls().theMax(R, G, B, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			long long R               = ;
			long long G               = ;
			long long B               = ;
			int N                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FoxPaintingBalls().theMax(R, G, B, N);
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
