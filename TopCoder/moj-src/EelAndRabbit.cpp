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

#define sz(X) ((int)(X.size()))
#define all(x) x.begin(),x.end()
#define clr(x,c) memset(x,c,sizeof(x))
#define rep(i,st,ed) for(int i=st;i<ed;i++)

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;
//--------------------------------------------


class EelAndRabbit {
public:
	int getmax(vector <int> l, vector <int> t);
};


int get(vector<int> l, vector<int> t, int xx) {
	if(xx==0) return 0;
	vector<int> tt = t;
	rep(i, 0, sz(l)) tt.push_back(t[i]+l[i]);
	int ret = 0;
	rep(i, 0, sz(tt)) {
		vector<int> nl, nt;
		int tmp = 0;
		rep(j, 0, sz(l)) {
			if(tt[i]-t[j] >=0 && tt[i]-t[j]-l[j]<=0) {
				tmp ++;
			} else {
				nl.push_back(l[j]);
				nt.push_back(t[j]);
			}
		}
		ret = max(ret, tmp+get(nl, nt, xx-1));
	}
	return ret;
}

int EelAndRabbit::getmax(vector <int> l, vector <int> t) {
	return get(l, t, 2);
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
			int l[]                   = {2, 4, 3, 2, 2, 1, 10};
			int t[]                   = {2, 6, 3, 7, 0, 2, 0};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int l[]                   = {1, 1, 1};
			int t[]                   = {2, 0, 4};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int l[]                   = {1};
			int t[]                   = {1};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int l[]                   = {8, 2, 1, 10, 8, 6, 3, 1, 2, 5};
			int t[]                   = {17, 27, 26, 11, 1, 27, 23, 12, 11, 13};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int l[]                   = ;
			int t[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int l[]                   = ;
			int t[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int l[]                   = ;
			int t[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EelAndRabbit().getmax(vector <int>(l, l + (sizeof l / sizeof l[0])), vector <int>(t, t + (sizeof t / sizeof t[0])));
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
