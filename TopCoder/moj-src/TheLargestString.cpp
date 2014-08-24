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

#define rep(i,st,ed) for(int i=st;i<ed;i++)
#define pb push_back
#define mp make_pair
#define sz(X) ((int)(X.size()))
#define tr(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define all(x) x.begin(),x.end()
#define clr(x,c) memset(x,c,sizeof(x))
#define two(X) (1<<(X))
#define twoL(X) (((int64)(1))<<(X))
#define test(S,X) (((S)&two(X))!=0)
#define testL(S,X) (((S)&twoL(X))!=0)

typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
typedef long long LL;
typedef unsigned long long ULL;

template<class T> inline void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> inline void checkmax(T &a,T b){if(b>a) a=b;}
template<class T> inline T sqr(T x){return x*x;}
template<class T> inline T lowbit(T n){return (n^(n-1))&n;}
template<class T> string toString(T n){ostringstream ost;ost<<n;ost.flush();return ost.str();}

#define ASSERT(X) {if (!(X)) {printf("\n assertion failed at line %d\n",__LINE__);exit(0);}}




class TheLargestString {
public:
	string find(string s, string t);
};

bool dp[55][155];

bool can(string s, string t, string ans) {
	for(int len=1;len<=sz(ans);len++) {
		if(len < sz(ans)-len) continue;
		string a1 = ans.substr(0, len);
		string a2 = ans.substr(len);

		clr(dp, false);
		rep(i, 0, sz(s)) {
			if(s[i] == a1[0]) {
				if(0>=sz(a2) || t[i] == a2[0]) {
					dp[i][0] = true;
				}
			}
		}
		rep(i, 0, sz(s)-1) {
			rep(j, 0, sz(a1)-1) if(dp[i][j]) {
				dp[i+1][j] = true;
				if(s[i+1] == a1[j+1]) {
					if(j+1>=sz(a2) || t[i+1] == a2[j+1]) {
						dp[i+1][j+1] = true;
					}
				}
			}
		}
		rep(i, 0, sz(s)) if(dp[i][sz(a1)-1]) return true;
	}
	return false;
}


string TheLargestString::find(string s, string t) {

	string ret = "";
	while(true) {
		bool suc = false;
		for(char ch = 'z';ch>='a';ch--) {
			if(can(s, t, ret+ch)) {
				ret = ret + ch;
				suc = true;
				break;
			}
		}
		if(!suc) return ret;
	}


// 	vector<int> v;
// 	int start = 0;
// 	while(start < sz(s)){
// 		char ch = 'a'-1;
// 		rep(i, start, sz(s)) {
// 			ch = max(ch, s[i]);
// 		}
// 		rep(i, start, sz(s)) {
// 			if(s[i] == ch) {
// 				v.push_back(i);
// 				start = i+1;
// 			}
// 		}
// 	}
// 	
// 	string ss, tt;
// 	rep(i, 0, sz(v)) {
// 		ss += s[v[i]];
// 		tt += t[v[i]];
// 	}
// 
// 	string ret = "";
// 	rep(len, 1, sz(ss)+1) {
// 		string tmp = ss.substr(0, len) + tt.substr(0, len);
// 		if(tmp > ret) ret = tmp;
// 	}
// 
// 
// 	string S, T;
// 	rep(i, 0, sz(v)) {
// 		if(s[v[i]] == s[0]) {
// 			S += s[v[i]];
// 			T += t[v[i]];
// 		}
// 
// 
// 	}
// 
// 
// 	return ret;



// 
// 	int diff_id = 0;
// 	while(diff_id < sz(tt) && tt[diff_id] == ss[ss.length()-1]) diff_id ++;
// 	if(diff_id == sz(tt)) return ss + tt;
// 	if(tt[diff_id] < ss[ss.length()-1]) return ss + tt;
// 	int 
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
			string s                  = "ab";
			string t                  = "zy";
			string expected__         = "by";

			clock_t start__           = clock();
			string received__         = TheLargestString().find(s, t);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s                  = "abacaba";
			string t                  = "zzzaaaa";
			string expected__         = "cbaaaa";

			clock_t start__           = clock();
			string received__         = TheLargestString().find(s, t);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s                  = "x";
			string t                  = "x";
			string expected__         = "xx";

			clock_t start__           = clock();
			string received__         = TheLargestString().find(s, t);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s                  = "abbabbabbababaaaabbababab";
			string t                  = "bababbaabbbababbbbababaab";
			string expected__         = "bbbbbbbbbbbbbbbbbbaaab";

			clock_t start__           = clock();
			string received__         = TheLargestString().find(s, t);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string s                  = ;
			string t                  = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = TheLargestString().find(s, t);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string s                  = ;
			string t                  = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = TheLargestString().find(s, t);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string s                  = ;
			string t                  = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = TheLargestString().find(s, t);
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
