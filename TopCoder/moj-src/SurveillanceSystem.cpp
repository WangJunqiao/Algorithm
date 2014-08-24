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


class SurveillanceSystem {
public:
	string getContainerInfo(string containers, vector <int> reports, int L);
};

VI pos[55];

void print(LL a) {
	rep(i, 0, 10) if(a&(1LL<<i)) putchar('1'); else putchar('0');
	puts("");
}


string SurveillanceSystem::getContainerInfo(string containers, vector <int> reports, int L) {
	rep(i, 0, L+1) pos[i].clear();
	int n = sz(containers);
	rep(i, 0, n) {
		if(i+L>n) break;
		int cnt = 0;
		rep(j, 0, L) if(containers[i+j] == 'X') cnt ++;
		pos[cnt].push_back(i);
		//printf("cnt = %d, i = %d\n", cnt, i);
	}
	LL yyy = 0, ppp = 0;

	

	rep(val, 0, L+1) {
		int num = 0;
		rep(i, 0, sz(reports)) if(reports[i] == val) num ++;
		if(num == 0) continue;

		//LL yy = ~(0LL);
		LL pp = 0;

		int ccc[55] = {0};
		rep(i, 0, sz(pos[val])) {
			rep(k, 0, L) {
				ccc[pos[val][i]+k] ++;
				pp |= (1LL << (pos[val][i]+k));
			}
			
		}
		rep(i, 0, n) if(ccc[i] > sz(pos[val]) - num) {
			yyy |= (1LL << i);
		}
		//yyy |= yy;
		ppp |= pp;

	}
	
	string ret = "";
	rep(i, 0, n) {
		if(yyy & (1LL << i)) ret += "+";
		else if(ppp & (1LL << i)) ret += "?";
		else ret += "-";
	}
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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string containers         = "-X--XX";
			int reports[]             = {1, 2};
			int L                     = 3;
			string expected__         = "??++++";

			clock_t start__           = clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string containers         = "-XXXXX-";
			int reports[]             = {2};
			int L                     = 3;
			string expected__         = "???-???";

			clock_t start__           = clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string containers         = "------X-XX-";
			int reports[]             = {3, 0, 2, 0};
			int L                     = 5;
			string expected__         = "++++++++++?";

			clock_t start__           = clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string containers         = "-XXXXX---X--";
			int reports[]             = {2, 1, 0, 1};
			int L                     = 3;
			string expected__         = "???-??++++??";

			clock_t start__           = clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string containers         = "-XX--X-XX-X-X--X---XX-X---XXXX-----X";
			int reports[]             = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
			int L                     = 7;
			string expected__         = "???++++?++++++++++++++++++++??????--";

			clock_t start__           = clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string containers         = ;
			int reports[]             = ;
			int L                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string containers         = ;
			int reports[]             = ;
			int L                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string containers         = ;
			int reports[]             = ;
			int L                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
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
