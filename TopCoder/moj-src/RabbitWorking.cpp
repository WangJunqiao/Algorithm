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


class RabbitWorking {
public:
	double getMaximum(vector <string> profit);
};


double RabbitWorking::getMaximum(vector <string> profit) {
	int n=sz(profit);
	rep(i, 0, n) rep(j, 0, n) profit[i][j]-='0';
	double ans=0;
	while( n>1 ){
		double p=0;
		rep(i, 0, n) rep(j, i+1, n) p+=profit[i][j];
		double c=n*(200-n);
		if( p/c > ans ) ans=p/c;
		
		int mi=(int)(1e9);
		int worst=-1;
		rep(i, 0, n){
			int tmp=0;
			rep(j, 0, n) tmp+=profit[i][j];
			if( tmp<mi ){
				mi=tmp;
				worst=i;
			}
		}
		rep(i, 0, n) profit[i].erase(profit[i].begin()+worst);
		profit.erase(profit.begin()+worst);
		n--;
	}
	return ans;
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
			string profit[]           = { "071", 
  "702", 
  "120" }
;
			double expected__         = 0.017676767676767676;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string profit[]           = { "061", 
  "602", 
  "120" }
;
			double expected__         = 0.015228426395939087;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string profit[]           = { "0" }
;
			double expected__         = 0.0;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string profit[]           = { "013040", 
  "100010", 
  "300060", 
  "000008", 
  "416000", 
  "000800" }
;
			double expected__         = 0.021996615905245348;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string profit[]           = { "06390061", 
  "60960062", 
  "39090270", 
  "96900262", 
  "00000212", 
  "00222026", 
  "66761201", 
  "12022610" }
;
			double expected__         = 0.06871794871794872;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string profit[]           = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string profit[]           = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string profit[]           = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = RabbitWorking().getMaximum(vector <string>(profit, profit + (sizeof profit / sizeof profit[0])));
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
