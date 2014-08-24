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


class BinPacking {
public:
	int minBins(vector <int> item);
};


int BinPacking::minBins(vector <int> item) {
	int ret = 0;
	vector<int> v = item;
	sort(all(v));
	bool vst[55] = {false};
	for(int i=sz(v)-1;i>=0;i--) if(vst[i]==false){
		if(v[i]==100) break;
		vst[i] = true;
		for(int j=i-1;j>=0;j--) if(vst[j]==false){
			if(v[i]+v[j]<=300) {
				vst[j] = true;
				break;
			}
		}
		ret ++;
	}
	int s = 0;
	rep(i, 0, sz(v)) if(vst[i]==false) s++;
	ret += s/3;
	if(s%3) ret ++;
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
			int item[]                = {150, 150, 150, 150, 150};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = BinPacking().minBins(vector <int>(item, item + (sizeof item / sizeof item[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int item[]                = {130, 140, 150, 160};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = BinPacking().minBins(vector <int>(item, item + (sizeof item / sizeof item[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int item[]                = {100, 100, 100, 100, 100, 100, 100, 100, 100};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = BinPacking().minBins(vector <int>(item, item + (sizeof item / sizeof item[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int item[]                = {100, 200, 100, 100, 100, 100, 200, 100, 200};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = BinPacking().minBins(vector <int>(item, item + (sizeof item / sizeof item[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int item[]                = {157, 142, 167, 133, 135, 157, 143, 160, 141, 123, 162, 159, 165, 137, 138, 152};
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = BinPacking().minBins(vector <int>(item, item + (sizeof item / sizeof item[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int item[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BinPacking().minBins(vector <int>(item, item + (sizeof item / sizeof item[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int item[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BinPacking().minBins(vector <int>(item, item + (sizeof item / sizeof item[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int item[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BinPacking().minBins(vector <int>(item, item + (sizeof item / sizeof item[0])));
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
