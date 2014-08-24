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


class TravelOnMars {
public:
	int minTimes(vector <int> range, int startCity, int endCity);
};


bool inq[55];
queue<int> q;
int dis[55];
void update(int u, int d) {
	if(dis[u] <= d) return;
	dis[u] = d;
	if(inq[u] == false) {
		q.push(u);
		inq[u] = true;
	}
}

int TravelOnMars::minTimes(vector <int> range, int startCity, int endCity) {
	int n = sz(range);
	clr(inq, false);
	rep(i, 0, n) dis[i] = 1000000000;
	update(startCity, 0);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(int i=-range[u];i<=range[u];i++) {
			int v = u+i;
			if(v>=n) v-=n;
			if(v<0) v+=n;
			update(v, dis[u]+1);
		}
	}
	return dis[endCity];
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
			int range[]               = {2,1,1,1,1,1};
			int startCity             = 1;
			int endCity               = 4;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int range[]               = {2,1,1,1,1,1};
			int startCity             = 4;
			int endCity               = 1;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int range[]               = {2,1,1,2,1,2,1,1};
			int startCity             = 2;
			int endCity               = 6;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int range[]               = {3,2,1,1,3,1,2,2,1,1,2,2,2,2,3};
			int startCity             = 6;
			int endCity               = 13;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int range[]               = ;
			int startCity             = ;
			int endCity               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int range[]               = ;
			int startCity             = ;
			int endCity               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int range[]               = ;
			int startCity             = ;
			int endCity               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
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
