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


class History {
public:
	string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries);
};


int N;
vector<int> years[55];
struct Batter {
	int A, ya, B, yb;
};
vector<Batter> batters;

Batter parse(string s){
	Batter ret;
	ret.A = s[0]-'A';
	ret.ya = s[1]-'0';
	ret.B = s[3]-'A';
	ret.yb = s[4]-'0';
	return ret;
}



int dis[55][55], dis2[55][55];

bool check(int sa, int sb) {
	clr(dis, 0x3f);
	rep(i, 0, N) dis[i][i] = 0;
	rep(i, 0, sz(batters)) {
		int A = batters[i].A;
		int B = batters[i].B;
		int y1 = years[batters[i].A][batters[i].ya];
		int y2 = years[batters[i].A][batters[i].ya+1] - 1;
		int y3 = years[batters[i].B][batters[i].yb];
		int y4 = years[batters[i].B][batters[i].yb+1] - 1;

		dis[B][A] = min(dis[B][A], y4-y1);
		dis[A][B] = min(dis[A][B], y2-y3);
	}
	rep(k, 0, N) rep(i, 0, N) rep(j, 0, N) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	memcpy(dis2, dis, sizeof(dis));
	rep(k, 0, N) rep(i, 0, N) rep(j, 0, N) dis2[i][j] = min(dis2[i][j], dis2[i][k]+dis2[k][j]);
	//rep(i, 0, N) rep(j, 0, N) if(dis2[i][j] < dis[i][j]) return false;
	if(dis2[sa][sb] < dis[sa][sb]) return false;
	return true;
}

string History::verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries) {
	N = sz(dynasties);
	rep(i, 0, sz(dynasties)) {
		years[i].clear();
		istringstream sin(dynasties[i]);
		int x; 
		while(sin>>x) {
			years[i].push_back(x);
		}
	}	
	batters.clear();
	string s = "";
	rep(i, 0, sz(battles)) s += battles[i];
	string tmp;
	istringstream sin(s);
	while(sin>>tmp) {
		batters.push_back(parse(tmp));
	}

	string ans = "";
	rep(i, 0, sz(queries)) {
		batters.push_back(parse(queries[i]));
		if(check(queries[i][0]-'A', queries[i][3]-'A')) {
			ans += "Y";
		} else {
			ans += "N";
		}
		batters.pop_back();
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
			string dynasties[]        = {"1 2 4",
 "1 2 3"};
			string battles[]          = {"A1-B0"};
			string queries[]          = {"A0-B0",
 "A0-B1",
 "A1-B0",
 "A1-B1"};
			string expected__         = "NNYY";

			clock_t start__           = clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string dynasties[]        = {"1000 2000 3000 10000",
 "600 650 2000",
 "1 1001 20001"};
			string battles[]          = {"B1-C0 A0-B0 A2-C1 B1-C1"};
			string queries[]          = {"A0-B1",
 "A1-B1",
 "A2-B1",
 "C0-A0",
 "B0-A2",
 "C1-B0"};
			string expected__         = "YYYYNN";

			clock_t start__           = clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string dynasties[]        = {"1 4 5",
 "10 13 17"};
			string battles[]          = {"A0-B0 A0-B0 B0-A0"};
			string queries[]          = {"A1-B0",
 "A0-B1",
 "A1-B1"};
			string expected__         = "YYY";

			clock_t start__           = clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string dynasties[]        = {"1 5 6",
 "1 2 5"};
			string battles[]          = {"A0",
 "-B0 A",
 "1-B1"};
			string queries[]          = {"A0-B0",
 "A1-B0",
 "A0-B1",
 "A1-B1"};
			string expected__         = "YNYY";

			clock_t start__           = clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string dynasties[]        = {"2294 7344","366 384 449 965 1307 1415","307 473 648 688 1097","1145 1411 1569 2606","87 188 551 598 947 998 1917 1942"}
;
			string battles[]          = {"A0-B4 B4-E2 B3-E2 D2-E4 A0-E4 B1-C3 A0-E3 A0-E6 D0","-E2 B2-E1 B4-E3 B4-D0 D0-E3 A0-D1 B2-C3 B1-C3 B4-E","3 D0-E1 B3-D0 B3-E2"}
;
			string queries[]          = {"A0-C2","E6-C2","A0-E4","B3-C1","C0-D2","B0-C1","D1-C3","C3-D0","C1-E3","D1-A0"};
			string expected__         = "YNYNNYNNNY";

			clock_t start__           = clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string dynasties[]        = ;
			string battles[]          = ;
			string queries[]          = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string dynasties[]        = ;
			string battles[]          = ;
			string queries[]          = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string dynasties[]        = ;
			string battles[]          = ;
			string queries[]          = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
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
