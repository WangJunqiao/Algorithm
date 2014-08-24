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


class FavouriteDigits {
public:
	long long findNext(long long N, int digit1, int count1, int digit2, int count2);
};


long long FavouriteDigits::findNext(long long N, int digit1, int count1, int digit2, int count2) {
	int d[20]={0};
	for(int i=16;i>=0;i--){
		for(int x=0;x<10;x++){
			d[i]=x;
			LL tmp=0;
			int c1=count1, c2=count2, first=true;
			for(int j=16;j>=i;j--){
				if( d[j]!=0 ){
					first=false;
					tmp=10*tmp+d[j];
					if( d[j]==digit1 ) c1--;
					if( d[j]==digit2 ) c2--;
				}else if( first==false ){
					tmp=10*tmp+d[j];
					if( d[j]==digit1 ) c1--;
					if( d[j]==digit2 ) c2--;
				}
			}
			c1=max(0, c1);
			c2=max(0, c2);
			if( c1+c2>i ) continue;
			VI v;
			rep(k, 0, c1) v.PB(digit1);
			rep(k, 0, c2) v.PB(digit2);
			rep(k, c1+c2, i) v.PB(9);
			sort(all(v));
			reverse(all(v));
			repv(k, v) tmp=10*tmp+v[k];
			if( tmp>=N ) break;
			else continue;
		}
	}
	LL ret=0;
	for(int i=16;i>=0;i--) ret=10*ret+d[i];
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
			long long N               = 47;
			int digit1                = 1;
			int count1                = 0;
			int digit2                = 2;
			int count2                = 0;
			long long expected__      = 47;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long N               = 47;
			int digit1                = 5;
			int count1                = 0;
			int digit2                = 9;
			int count2                = 1;
			long long expected__      = 49;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long N               = 47;
			int digit1                = 5;
			int count1                = 0;
			int digit2                = 3;
			int count2                = 1;
			long long expected__      = 53;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long N               = 47;
			int digit1                = 2;
			int count1                = 1;
			int digit2                = 0;
			int count2                = 2;
			long long expected__      = 200;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long N               = 123456789012345LL;
			int digit1                = 1;
			int count1                = 2;
			int digit2                = 2;
			int count2                = 4;
			long long expected__      = 123456789012422LL;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			long long N               = 92;
			int digit1                = 1;
			int count1                = 1;
			int digit2                = 0;
			int count2                = 0;
			long long expected__      = 100;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			long long N               = ;
			int digit1                = ;
			int count1                = ;
			int digit2                = ;
			int count2                = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long N               = ;
			int digit1                = ;
			int count1                = ;
			int digit2                = ;
			int count2                = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			long long N               = ;
			int digit1                = ;
			int count1                = ;
			int digit2                = ;
			int count2                = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
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
