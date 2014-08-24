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


class ShoutterDiv1 {
public:
	int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1);
};

string get(VS vs){
	string s = "";
	rep(i, 0, sz(vs)) s+=vs[i];
	return s;
}

vector<int> parse(VS v1000, VS v100, VS v10, VS v1) {
	string s1000 = get(v1000);
	string s100 = get(v100);
	string s10 = get(v10);
	string s1 = get(v1);
	vector<int> ret;
	rep(i, 0, sz(s1)) {
		ret.push_back(1000*(s1000[i]-'0') + 100*(s100[i]-'0') + 10*(s10[i]-'0') + 1*(s1[i]-'0'));
	}
	return ret;
}

int maSe[11000];

void check(int &a, int b){
	a = max(a, b);
}

int dp[11000];



vector<PII> reasons[11000];
bool vst[11000], can[11000];

int ShoutterDiv1::count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1) {
	vector<int> s = parse(s1000, s100, s10, s1);
	vector<int> t = parse(t1000, t100, t10, t1);
	
	vector<PII> v;
	rep(i, 0, sz(s)) v.push_back(PII(s[i], t[i]));
	sort(all(v));

	int maT = v[0].second;
	rep(i, 1, sz(v)) {
		if(v[i].first > maT) return -1;
		maT = max(maT, v[i].second);
	}

	//rep(i, 0, sz(v)) printf("[%d, %d]\n", v[i].first, v[i].second);

	clr(maSe, 0);
	rep(i, 0, sz(v)) {
		check(maSe[v[i].first], v[i].second);
	}
	rep(i, 1, 10000) check(maSe[i], maSe[i-1]);

	clr(dp, 0x3f);
	int miT = 10000000;
	rep(i, 0, 10000) reasons[i].clear();

	rep(i, 0, sz(v)) {
		if(v[i].first > miT) break;
		dp[v[i].second] = 1;
		reasons[v[i].second].push_back(PII(-1, i));
		miT = min(miT, v[i].second);
	}
	int ans = 1000000;

	

	rep(i, 0, 10000) {
		if(i>=v.back().first) {
			ans = min(ans, dp[i]);
		}
		rep(j, 0, sz(v)) {
			if(v[j].first <=i && v[j].second>i) {
				if(dp[i]+1 < dp[v[j].second]) {
					dp[v[j].second] = dp[i]+1;
					reasons[v[j].second].clear();
					reasons[v[j].second].push_back(PII(i, j));
				}else if(dp[i]+1 == dp[v[j].second]) {
					reasons[v[j].second].push_back(PII(i, j));
				}
			}
		}
	}

	clr(vst, false);
	clr(can, false);

	rep(i, 0, 10000) {
		if(dp[i] == ans && i>=v.back().first) can[i] = true;
	}


	for(int i=9999;i>=0;i--) {
		if(can[i]){
			rep(j, 0, sz(reasons[i])) {
				if(reasons[i][j].first>=0) can[reasons[i][j].first] = true;
				vst[reasons[i][j].second] = true;
			}
		}
	}
	int mis = 0;
	rep(i, 0, sz(v)) if(vst[i]) mis ++;

	//printf("ans = %d, n = %d\n", ans, sz(v));
	return ans * sz(v) - mis;
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
			string s1000[]            = {"22", "2"};
			string s100[]             = {"00", "0"};
			string s10[]              = {"11", "1"};
			string s1[]               = {"21", "4"};
			string t1000[]            = {"22", "2"};
			string t100[]             = {"00", "0"};
			string t10[]              = {"11", "1"};
			string t1[]               = {"43", "6"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s1000[]            = {"00"};
			string s100[]             = {"00"};
			string s10[]              = {"00"};
			string s1[]               = {"13"};
			string t1000[]            = {"00"};
			string t100[]             = {"00"};
			string t10[]              = {"00"};
			string t1[]               = {"24"};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s1000[]            = {"0000"};
			string s100[]             = {"0000"};
			string s10[]              = {"0000"};
			string s1[]               = {"1234"};
			string t1000[]            = {"0000"};
			string t100[]             = {"0000"};
			string t10[]              = {"0000"};
			string t1[]               = {"2345"};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s1000[]            = {"0000000000"};
			string s100[]             = {"0000000000"};
			string s10[]              = {"0000000000"};
			string s1[]               = {"7626463146"};
			string t1000[]            = {"0000000000"};
			string t100[]             = {"0000000000"};
			string t10[]              = {"0000000000"};
			string t1[]               = {"9927686479"};
			int expected__            = 18;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s1000[]            = {"00000000000000000000000000000000000000000000000000"};
			string s100[]             = {"00000000000000000000000000000000000000000000000000"};
			string s10[]              = {"50353624751857130208544645495168271486083954769538"};
			string s1[]               = {"85748487990028258641117783760944852941545064635928"};
			string t1000[]            = {"00000000000000000000000000000000000000000000000000"};
			string t100[]             = {"00000000000000000000000000000000000000000000000000"};
			string t10[]              = {"61465744851859252308555855596388482696094965779649"};
			string t1[]               = {"37620749792666153778227385275518278477865684777411"};
			int expected__            = 333;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string s1000[]            = ;
			string s100[]             = ;
			string s10[]              = ;
			string s1[]               = ;
			string t1000[]            = ;
			string t100[]             = ;
			string t10[]              = ;
			string t1[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string s1000[]            = ;
			string s100[]             = ;
			string s10[]              = ;
			string s1[]               = ;
			string t1000[]            = ;
			string t100[]             = ;
			string t10[]              = ;
			string t1[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string s1000[]            = ;
			string s100[]             = ;
			string s10[]              = ;
			string s1[]               = ;
			string t1000[]            = ;
			string t100[]             = ;
			string t10[]              = ;
			string t1[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
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
