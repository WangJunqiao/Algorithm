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

//----------------------zjut_DD for Topcoder-------------------------------
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
#define PB push_back
#define MP make_pair
#define ff first
#define ss second
#define two(w) (1<<(w))
#define test(x,w) (x&two(w))
#define sz(v) (int)v.size()
#define all(c) c.begin(),c.end() 
#define clr(buf,val) memset(buf,val,sizeof(buf))
#define rep(i,l,r) for(int i=(l);i<(r);i++)
#define repv(i,v)  for(int i=0;i<(int)v.size();i++)
#define repi(it,c) for(typeof(c.begin()) it=c.begin();it!=c.end();++it)
//------------------------------------------------------------------------


class SistersErasingLetters {
public:
	string whoWins(string word);
};


string s;
int dfsB(int, int);
int a[55][55], b[55][55];

int dfsA(int L, int K){
	if( K==0 ) return 0;
	if( a[L][K]>=0 ) return a[L][K];
	string tmp=s.substr(sz(s)-K);
	int j=L;
	for(int i=0;i<sz(tmp);i++){
		if( tmp[i]>s[j] && i!=sz(tmp)-1 ) return a[L][K]=1;
		if( dfsB(j, K-1-i)==0 ) return a[L][K]=1;
		if( tmp[i]<s[j] ) break;
		j++;
	}
	return a[L][K]=0;
}

int dfsB(int L, int K){
	if( K==0 ) return 1;
	if( b[L][K]>=0 ) return b[L][K];
	string tmp=s.substr(sz(s)-K);
	int j=L;
	for(int i=0;i<sz(tmp);i++){
		if( tmp[i]<s[j] && i!=sz(tmp)-1 ) return b[L][K]=1;
		if( dfsA(j, K-1-i)==0 ) return b[L][K]=1;
		if( tmp[i]>s[j] ) break;
		j++;
	}
	return b[L][K]=0;
}

string SistersErasingLetters::whoWins(string word) {
	s=word;
	clr(a, -1);
	clr(b, -1);
	
	if( dfsA(0, sz(word)) == 1 ) return "Camomile";
	return "Romashka";
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
			string word               = "topcoder";
			string expected__         = "Camomile";

			clock_t start__           = clock();
			string received__         = SistersErasingLetters().whoWins(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string word               = "program";
			string expected__         = "Romashka";

			clock_t start__           = clock();
			string received__         = SistersErasingLetters().whoWins(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string word               = "abcd";
			string expected__         = "Camomile";

			clock_t start__           = clock();
			string received__         = SistersErasingLetters().whoWins(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string word               = "abc";
			string expected__         = "Romashka";

			clock_t start__           = clock();
			string received__         = SistersErasingLetters().whoWins(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string word               = "easyproblemroundfivetopcoderopentwothousandeleven";
			string expected__         = "Camomile";

			clock_t start__           = clock();
			string received__         = SistersErasingLetters().whoWins(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string word               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = SistersErasingLetters().whoWins(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string word               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = SistersErasingLetters().whoWins(word);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string word               = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = SistersErasingLetters().whoWins(word);
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
