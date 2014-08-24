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
#include <cassert>
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


class FarStrings {
public:
	vector <string> find(string t);
};


int dis[30][30];

int edit_dis(string s1, string s2) {
	int len1 = s1.length(), len2 = s2.length();
	for(int j=0;j<=s2.length();j++) dis[0][j] = j;
	for(int i=1;i<=len1;i++) {
		dis[i][0] = i;
		for(int j=1;j<=len2;j++) {
			int tmp = 1000000;
			tmp = min(tmp, 1 + dis[i][j-1]);
			tmp = min(tmp, 1 + dis[i-1][j]);
			tmp = min(tmp, 1 + dis[i-1][j-1]);
			if(s1[i-1] == s2[j-1]) tmp = min(tmp, dis[i-1][j-1]);
			dis[i][j] = tmp;
		}
	}
	return dis[len1][len2];
}

bool get(string t, int step, string &s) {
		for(char ch='a';ch<='z';ch++) {
			s.push_back(ch);
			int ed = edit_dis(s, t.substr(0, s.length()));
			if(ed > step) {
				s.pop_back();
				continue;
			}
			if(ed == step) {
				s += t.substr(s.length());
				return true;
			}
			if(ed + t.length()-(s.length()) >= step) {
				if(get(t, step, s)) return true;
				s.pop_back();
				continue;
			} else {
				s.pop_back();
				continue;
			}
		}
		//assert(s.length() == i+1);
	return false;
}

vector <string> FarStrings::find(string t) {
	vector<string> ret;
	for(int i=1;i<=t.length();i++) {
		string s="";
		get(t, i, s);
		ret.push_back(s);
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
	
	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }
	template<> ostream& operator<<(ostream &os, const vector<string> &v) { os << "{"; for (vector<string>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " \"" << *vi << "\""; } os << " }"; return os; }

	int verify_case(int casenum, const vector <string> &expected, const vector <string> &received, clock_t elapsed) { 
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
			string t                  = "tyudatanfdadasfsafafdfsaf";
			string expected__[]       = {"aaan", "aaaa", "aaba", "babb" };

			clock_t start__           = clock();
			vector <string> received__ = FarStrings().find(t);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string t                  = "ir";
			string expected__[]       = {"ar", "aa" };

			clock_t start__           = clock();
			vector <string> received__ = FarStrings().find(t);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string t                  = "aaa";
			string expected__[]       = {"aab", "abb", "bbb" };

			clock_t start__           = clock();
			vector <string> received__ = FarStrings().find(t);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string t                  = "bazinga";
			string expected__[]       = {"aazinga", "aaainga", "aaaanga", "aaaaaga", "aaaaaaa", "aaaaaab", "abbaabb" };

			clock_t start__           = clock();
			vector <string> received__ = FarStrings().find(t);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			string t                  = "bcdab";
			string expected__[]       = {"acdab", "aadab", "aaaab", "aaaaa", "aaaca" };

			clock_t start__           = clock();
			vector <string> received__ = FarStrings().find(t);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string t                  = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = FarStrings().find(t);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			string t                  = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = FarStrings().find(t);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			string t                  = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = FarStrings().find(t);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
