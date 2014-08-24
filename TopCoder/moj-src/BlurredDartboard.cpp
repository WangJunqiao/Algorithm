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


class BlurredDartboard {
public:
	int minThrows(vector <int> points, int P);
};


int dp[555];

int BlurredDartboard::minThrows(vector <int> points, int P) {
	int ma=0, n=sz(points);
	bool vst[55]={false};
	repv(i, points){
		if( points[i]==0 ) continue;
		ma=max(ma, points[i]);
		vst[ points[i] ]=true;
	}
	
	
	//2+4+6+7+8+9
	int num=0, sum=0;
	rep(i, 1, n+1) if( vst[i]==false ){
		num++;
		sum+=i;
	}
	printf("num=%d sum=%d\n", num, sum);
	if( num==0 ){
		if( P%ma==0 ) return P/ma;
		return P/ma+1;
	}
	if( ma*num >= sum ){
		if( P%ma==0 ) return P/ma;
		return P/ma+1;
	}
	printf("dp[34]=%d\n",dp[34]);
	int ret=P/sum*num;
	P%=sum;
	if( P==0 ) return ret;
	int sss=1000000000;
	if( ma && P%ma==0 ) sss=P/ma;
	else if( ma ) sss=P/ma+1;
	
	int ttt;
	for(int i=1, j=0, k=0;i<=n;i++){
		if( vst[i] ) continue;
		j+=i;
		k++;
		if( j>=P ) return ret+min(sss, k);
	}
	return -1;
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
			int points[]              = {0, 3, 4, 0, 0};
			int P                     = 8;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int points[]              = {0, 0, 0, 0, 0};
			int P                     = 15;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int points[]              = {4, 7, 8, 1, 3, 2, 6, 5};
			int P                     = 2012;
			int expected__            = 252;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int points[]              = {0, 0, 5, 0, 0, 0, 1, 3, 0, 0};
			int P                     = 2012;
			int expected__            = 307;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int points[]              = {0, 2, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 6, 0, 0, 0, 4, 0, 0, 0};
			int P                     = 1000000000;
			int expected__            = 84656087;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int points[]              = ;
			int P                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int points[]              = ;
			int P                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int points[]              = ;
			int P                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BlurredDartboard().minThrows(vector <int>(points, points + (sizeof points / sizeof points[0])), P);
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
