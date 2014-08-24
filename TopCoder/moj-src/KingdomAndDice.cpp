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


class KingdomAndDice {
public:
	double newFairness(vector <int> firstDie, vector <int> secondDie, int X);
};

bool dp[51][2505];


double KingdomAndDice::newFairness(vector <int> fir, vector <int> sec, int X) {
	set<int> st;
	repv(i, fir) st.insert(fir[i]);
	sort(all(sec));
	sec.PB(X+1);
	clr(dp, false);
	dp[0][0]=true;
	int cnt=0, zero=0;
	repv(i, fir) {
		if( fir[i]==0 ) zero++;
		repv(j, sec) if( fir[i]>sec[j]) cnt++;
	}
	int N=sz(fir), sum=N*N;
	//printf("cnt=%d\n", cnt);
	repv(i, sec){
		if( i==sz(sec)-1 ) break;
		int num=0;
		int add=i+1;
		for(int val=sec[i]+1;val<sec[i+1];val++){
			if( num==zero ) break;
			if( st.find(val)==st.end() ) num++;
		}
	//	printf("num=%d add=%d\n", num, add);
		for(int j=zero;j>=0;j--){
			for(int k=0;k<sum;k++) if( dp[j][k] ){
				int tmp=k;
				for(int sel=1;sel<=num && sel+j<=zero;sel++){
					tmp+=add;
					if( tmp>sum ) break;
					dp[j+sel][tmp]=true;
				}
			}
		}
	}
	int ret=cnt;
	rep(i, 0, zero+1) rep(j, 0, sum+1){
		if( dp[i][j] ){
			int tmp=cnt+j;
	//		printf("j=%d\n", j);
			int a=tmp*2, b=ret*2, c=sum*2;
			if( abs(a-sum) < abs(b-sum) ) ret=tmp;
			else if( (abs(a-sum)==abs(b-sum)) && (a<b) ) ret=tmp;
		}
	}
	return ret/(double)sum;
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
	
	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ(double expected, double result) { if (isnan(expected)) { return isnan(result); } else if (isinf(expected)) { if (expected > 0) { return result > 0 && isinf(result); } else { return result < 0 && isinf(result); } } else if (isnan(result) || isinf(result)) { return false; } else if (fabs(result - expected) < MAX_DOUBLE_ERROR) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }
	
	int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received); 
			if (rerr > 0) {
				sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int firstDie[]            = {0, 2, 7, 0};
			int secondDie[]           = {6, 3, 8, 10};
			int X                     = 12;
			double expected__         = 0.4375;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int firstDie[]            = {0, 2, 7, 0};
			int secondDie[]           = {6, 3, 8, 10};
			int X                     = 10;
			double expected__         = 0.375;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int firstDie[]            = {0, 0};
			int secondDie[]           = {5, 8};
			int X                     = 47;
			double expected__         = 0.5;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int firstDie[]            = {19, 50, 4};
			int secondDie[]           = {26, 100, 37};
			int X                     = 1000;
			double expected__         = 0.2222222222222222;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int firstDie[]            = {6371, 0, 6256, 1852, 0, 0, 6317, 3004, 5218, 9012};
			int secondDie[]           = {1557, 6318, 1560, 4519, 2012, 6316, 6315, 1559, 8215, 1561};
			int X                     = 10000;
			double expected__         = 0.49;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int firstDie[]            = ;
			int secondDie[]           = ;
			int X                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int firstDie[]            = ;
			int secondDie[]           = ;
			int X                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int firstDie[]            = ;
			int secondDie[]           = ;
			int X                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = KingdomAndDice().newFairness(vector <int>(firstDie, firstDie + (sizeof firstDie / sizeof firstDie[0])), vector <int>(secondDie, secondDie + (sizeof secondDie / sizeof secondDie[0])), X);
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
