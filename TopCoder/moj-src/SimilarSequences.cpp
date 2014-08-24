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


class SimilarSequences {
public:
	int count(vector <int> seq, int bound);
};

const int mod = 1000000009;
void add(int &a, int b) {
	a = (a+b) % mod;
}

int SimilarSequences::count(vector <int> seq, int bound) {
	set<vector<int> > st;
	rep(i, 0, sz(seq)) {
		vector<int> v;
		rep(j, 0, sz(seq)) {
			if(i!=j) v.push_back(seq[j]);
		}
		st.insert(v);
	}
	set<int> nn;
	rep(i, 0, sz(seq)) nn.insert(seq[i]);
	int T = sz(nn);
	VI x(all(nn));
	set<VI> ss;
	int ans = 0;
	for(set<VI>::iterator it=st.begin();it!=st.end();++it) {
		VI tmpv = *it;
		rep(i, 0, sz(tmpv)+1) {
			if(bound > T) add(ans, bound-T);
			rep(j, 0, sz(x)) {
				vector<int> tmp;
				rep(y, 0, i) tmp.push_back(tmpv[y]);
				tmp.push_back(x[j]);
				rep(y, i, sz(tmpv)) tmp.push_back(tmpv[y]);
				ss.insert(tmp);
			}
		}
	}
	printf("ans = %d\n", ans);
	add(ans, sz(ss));
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
			int seq[]                 = {1, 1};
			int bound                 = 3;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = SimilarSequences().count(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])), bound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int seq[]                 = {1, 2};
			int bound                 = 2;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = SimilarSequences().count(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])), bound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int seq[]                 = {999999999};
			int bound                 = 1000000000;
			int expected__            = 1000000000;

			clock_t start__           = clock();
			int received__            = SimilarSequences().count(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])), bound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int seq[]                 = {1, 2, 3, 4, 5};
			int bound                 = 5;
			int expected__            = 97;

			clock_t start__           = clock();
			int received__            = SimilarSequences().count(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])), bound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int seq[]                 = {5, 8, 11, 12, 4, 1, 7, 9};
			int bound                 = 1000000000;
			int expected__            = 999999363;

			clock_t start__           = clock();
			int received__            = SimilarSequences().count(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])), bound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int seq[]                 = ;
			int bound                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SimilarSequences().count(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])), bound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int seq[]                 = ;
			int bound                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SimilarSequences().count(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])), bound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int seq[]                 = ;
			int bound                 = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SimilarSequences().count(vector <int>(seq, seq + (sizeof seq / sizeof seq[0])), bound);
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
