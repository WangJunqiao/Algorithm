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


class TheTree {
public:
	int maximumDiameter(vector <int> cnt);
};


int dis[110][110];

int TheTree::maximumDiameter(vector <int> cnt) {
	int N = sz(cnt);
	rep(i, 0, N) cnt[i] = min(cnt[i], 2);
	int n = 1;
	vector<int> v;
	v.push_back(0);
	clr(dis, 0x3f);
	rep(i, 0, N) {
		if(cnt[i]==1) {
			dis[v[0]][n] = 1;
			dis[n][v[0]] = 1;
			v.clear();
			v.push_back(n++);
		} else if(sz(v)==1) {
			dis[v[0]][n] = 1;
			dis[n][v[0]] = 1;
			n ++;
			dis[v[0]][n] = 1;
			dis[n][v[0]] = 1;
			n ++;
			v.clear();
			v.push_back(n-2);
			v.push_back(n-1);
		} else {
			dis[v[0]][n] = 1;
			dis[n][v[0]] = 1;
			n ++;
			dis[v[1]][n] = 1;
			dis[n][v[1]] = 1;
			n ++;
			v.clear();
			v.push_back(n-2);
			v.push_back(n-1);
		}
	}
	rep(i, 0, n) dis[i][i] = 0;
	rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
	int ma = 0;
	rep(i, 0, n) rep(j, 0, n) ma = max(ma, dis[i][j]);
	return ma;
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
			int cnt[]                 = {3};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TheTree().maximumDiameter(vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int cnt[]                 = {2, 2};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = TheTree().maximumDiameter(vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int cnt[]                 = {4, 1, 2, 4};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = TheTree().maximumDiameter(vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int cnt[]                 = {4, 2, 1, 3, 2, 5, 7, 2, 4, 5, 2, 3, 1, 13, 6};
			int expected__            = 21;

			clock_t start__           = clock();
			int received__            = TheTree().maximumDiameter(vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int cnt[]                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheTree().maximumDiameter(vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int cnt[]                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheTree().maximumDiameter(vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int cnt[]                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheTree().maximumDiameter(vector <int>(cnt, cnt + (sizeof cnt / sizeof cnt[0])));
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
