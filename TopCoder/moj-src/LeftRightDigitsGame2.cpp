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


class LeftRightDigitsGame2 {
public:
	string minNumber(string digits, string lowerBound);
};

string D, L;
string dp[55][55][3];

string dfs(int s, int len, int cmp){
	//printf("s=%d len=%d cmp=%d\n", s, len, cmp);
	if( len==1 ){
		//cout<<D[0]<<" do"<<endl;
		string ret = "";
		if( cmp==0 ) ret+=D[0];
		if( cmp==1 && D[0]>=L[s] ) ret+=D[0];
		if( cmp==2 && D[0]>L[s] ) ret+=D[0];
		return ret;
	}
	if( dp[s][len][cmp]!="-1" ) return dp[s][len][cmp];
	string ret1="", ret2="";
	//left
	if( D[len-1] < L[s] ){
		if( cmp==0 ) ret1 = D[len-1] + dfs(s+1, len-1, cmp);
	} else if( D[len-1] == L[s] ){
		ret1 = D[len-1] + dfs(s+1, len-1, cmp);
	} else {
		ret1 = D[len-1] + dfs(s+1, len-1, 0);
	}
	// right
	if( D[len-1] < L[s+len-1] ){
		if( cmp==0 ) ret2 = dfs(s, len-1, cmp) + D[len-1];
		else ret2 = dfs(s, len-1, 2) + D[len-1];
	}else if( D[len-1] == L[s+len-1] ){
		ret2 = dfs(s, len-1, cmp) + D[len-1];
	}else {
		if( cmp==0 ) ret2 = dfs(s, len-1, cmp) + D[len-1];
		else ret2 = dfs(s, len-1, 1) + D[len-1];
	}
	string c = L.substr(s, len), ret="";
	//cout<<"ret1="<<ret1<<"    ret2="<<ret2<<endl;
	if( sz(ret1) == sz(c) ){
		ret = ret1;
	} 
	if( sz(ret2) == sz(c) ){
		if( ret=="" ) ret= ret2;
		else if( ret2<ret ) ret=ret2;
	} 
	//cout<<ret<<endl;
	return dp[s][len][cmp] = ret;
}

string LeftRightDigitsGame2::minNumber(string d, string l) {
	int n = sz(d);
	rep(i, 0, n) rep(k, 0, n+1) rep(l, 0, 3) dp[i][k][l]="-1";
	D=d;
	L=l;
	return dfs(0, sz(d), 1);
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
			string digits             = "565";
			string lowerBound         = "556";
			string expected__         = "556";

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string digits             = "565";
			string lowerBound         = "566";
			string expected__         = "655";

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string digits             = "565";
			string lowerBound         = "656";
			string expected__         = "";

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string digits             = "9876543210";
			string lowerBound         = "5565565565";
			string expected__         = "5678943210";

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string digits             = "8016352";
			string lowerBound         = "1000000";
			string expected__         = "1086352";

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string digits             = ;
			string lowerBound         = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string digits             = ;
			string lowerBound         = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string digits             = ;
			string lowerBound         = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = LeftRightDigitsGame2().minNumber(digits, lowerBound);
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
