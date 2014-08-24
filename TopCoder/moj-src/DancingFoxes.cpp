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


class DancingFoxes {
public:
	int minimalDays(vector <string> friendship);
};

int dis[55][55];

int DancingFoxes::minimalDays(vector <string> friendship) {
	int n = sz(friendship);
	rep(i, 0, n) {
		rep(j, 0, n) if(friendship[i][j]=='Y') dis[i][j] = 1;
		else dis[i][j] = 1000000000;
	}
	rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
	if(dis[0][1] >= 100000000) return -1;
	int x = 0, p = dis[0][1];
	while(p>1) {
		if(p==1) return x;
		if(p==2) return 1+x;
		int np = 1;
		p-=2;
		while(p>=3) {
			np += 2;
			p-=3;
		}
		p += np;
		x++;
	}
	return x;
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
			string friendship[]       = {"NNY",
 "NNY",
 "YYN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = DancingFoxes().minimalDays(vector <string>(friendship, friendship + (sizeof friendship / sizeof friendship[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string friendship[]       = {"NNNNN",
 "NNYYY",
 "NYNYY",
 "NYYNY",
 "NYYYN"};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = DancingFoxes().minimalDays(vector <string>(friendship, friendship + (sizeof friendship / sizeof friendship[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string friendship[]       = {"NNYYNN",
 "NNNNYY",
 "YNNNYN",
 "YNNNNY",
 "NYYNNN",
 "NYNYNN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DancingFoxes().minimalDays(vector <string>(friendship, friendship + (sizeof friendship / sizeof friendship[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string friendship[]       = {"NNYNNNNYN",
 "NNNNYNYNN",
 "YNNYNYNNN",
 "NNYNYNYYN",
 "NYNYNNNNY",
 "NNYNNNYNN",
 "NYNYNYNNN",
 "YNNYNNNNY",
 "NNNNYNNYN"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = DancingFoxes().minimalDays(vector <string>(friendship, friendship + (sizeof friendship / sizeof friendship[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string friendship[]       = {"NY",
 "YN"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = DancingFoxes().minimalDays(vector <string>(friendship, friendship + (sizeof friendship / sizeof friendship[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string friendship[]       = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DancingFoxes().minimalDays(vector <string>(friendship, friendship + (sizeof friendship / sizeof friendship[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string friendship[]       = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DancingFoxes().minimalDays(vector <string>(friendship, friendship + (sizeof friendship / sizeof friendship[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string friendship[]       = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DancingFoxes().minimalDays(vector <string>(friendship, friendship + (sizeof friendship / sizeof friendship[0])));
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
