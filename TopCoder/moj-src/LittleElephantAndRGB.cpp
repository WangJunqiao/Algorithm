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


class LittleElephantAndRGB {
public:
	long long getNumber(vector <string> list, int minGreen);
};


int valid(int len) {
	if(len==0) return 0;
	return len + len * (len-1) / 2;
}

int cnt[2510][2510];
int ccc[2510];
int ddd[2510];

long long LittleElephantAndRGB::getNumber(vector <string> list, int minGreen) {
	
	string s = "";
	rep(i, 0, sz(list)) s += list[i];
	int n = sz(s);
	if(minGreen > sz(s)) return 0;
	LL sum = 0;
	rep(i, 0, n) {
		sum += (i+1) * (LL) valid(n-1-i);
	}

	clr(cnt, 0);
	for(int i=n-1;i>=0;i--) {
		int left = 0, ma = 0, tmp = 0;
		for(int j=i;j<n;j++) {
			if(j-i == left && s[j]=='G') {
				left ++;
			}
			if(s[j]=='G') {
				tmp ++;
			} else {
				tmp = 0;
			}
			ma = max(ma, tmp);

			if(ma >= minGreen) 
				continue;
			cnt[i][left] ++;
		}
	}
	for(int i=n-2;i>=0;i--) {
		for(int j=0;j<n;j++) cnt[i][j] += cnt[i+1][j];
	}

	for(int i=0;i<n;i++) {
		clr(ccc, 0);
		int left = 0, ma = 0, tmp = 0;
		for(int j=i;j>=0;j--) {
			if(i-j == left && s[j]=='G') {
				left ++;
			}
			if(s[j]=='G') {
				tmp ++;
			} else {
				tmp = 0;
			}
			ma = max(ma, tmp);

			if(ma >= minGreen) 
				continue;
			ccc[left] ++;
		}

		clr(ddd, 0);
		for(int j=0;j<n;j++) {
			ddd[j] = cnt[i+1][j];
			if(j) ddd[j] += ddd[j-1];
		}

		for(int j=0;j<minGreen;j++) {
			sum -= ccc[j] * (LL) ddd[minGreen-1-j];
		}
	}
	return sum;
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) { 
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
			string list[]             = {"GRG"};
			int minGreen              = 2;
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = LittleElephantAndRGB().getNumber(vector <string>(list, list + (sizeof list / sizeof list[0])), minGreen);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string list[]             = {"GG", "GG"};
			int minGreen              = 3;
			long long expected__      = 9;

			clock_t start__           = clock();
			long long received__      = LittleElephantAndRGB().getNumber(vector <string>(list, list + (sizeof list / sizeof list[0])), minGreen);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string list[]             = {"GRBGRBBRG"};
			int minGreen              = 2;
			long long expected__      = 11;

			clock_t start__           = clock();
			long long received__      = LittleElephantAndRGB().getNumber(vector <string>(list, list + (sizeof list / sizeof list[0])), minGreen);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string list[]             = {"RRBRBBRRR", "R", "B"};
			int minGreen              = 1;
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = LittleElephantAndRGB().getNumber(vector <string>(list, list + (sizeof list / sizeof list[0])), minGreen);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string list[]             = {"GRGGGRBRGG", "GGGGGGGG", "BRGRBRB"};
			int minGreen              = 4;
			long long expected__      = 12430;

			clock_t start__           = clock();
			long long received__      = LittleElephantAndRGB().getNumber(vector <string>(list, list + (sizeof list / sizeof list[0])), minGreen);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string list[]             = ;
			int minGreen              = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = LittleElephantAndRGB().getNumber(vector <string>(list, list + (sizeof list / sizeof list[0])), minGreen);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string list[]             = ;
			int minGreen              = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = LittleElephantAndRGB().getNumber(vector <string>(list, list + (sizeof list / sizeof list[0])), minGreen);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string list[]             = ;
			int minGreen              = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = LittleElephantAndRGB().getNumber(vector <string>(list, list + (sizeof list / sizeof list[0])), minGreen);
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
