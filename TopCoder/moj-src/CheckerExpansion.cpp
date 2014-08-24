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


class CheckerExpansion {
public:
	vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h);
};

const int off=100;
char ch[2*off][2*off+2];
void calc(){	
	clr(ch, '.');
	ch[off][off]='A';
	for(int i=2;i<=50;i++){
		char nn;
		if( i%2==0 ) nn='B';
		else nn='A';
		for(int x=off;x<2*off;x++) {
			for(int y=off;y<2*off;y++) if( ch[x][y]=='.'){
				if( (int)ch[x-1][y-1]+ch[x-2][y]==(int)'.'+'A'+'B'-nn ) {
					ch[x][y]=nn;
				}
			}
		}
	}
}
char get(LL x, LL y, LL t){
	if( y>x ) return '.';
	if( x+y>2*t ) return '.';
	if( x<=20 && y<=20 ) return ch[x-1][y-1];
	LL k=1;
	
}


vector <string> CheckerExpansion::resultAfter(long long t, long long x0, long long y0, int w, int h) {
	VS ret;
	for(int i=0;i<h;i++) {
		string s="";
		for(int j=0;j<w;j++){
			LL x=x0+j;
			LL y=y0+h-i-1;
			s+=get(x+1, y+1, t);
		}
		ret.PB(s);
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
			long long t               = 1;
			long long x0              = 0;
			long long y0              = 0;
			int w                     = 4;
			int h                     = 4;
			string expected__[]       = {"....", "....", "....", "A..." };

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			long long t               = 5;
			long long x0              = 4;
			long long y0              = 1;
			int w                     = 3;
			int h                     = 4;
			string expected__[]       = {"A..", "...", "B..", ".B." };

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			long long t               = 1024;
			long long x0              = 1525;
			long long y0              = 512;
			int w                     = 20;
			int h                     = 2;
			string expected__[]       = {"B...B...B...........", ".B.A.B.A.B.........." };

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			long long t               = 53;
			long long x0              = 85;
			long long y0              = 6;
			int w                     = 5;
			int h                     = 14;
			string expected__[]       = {".....", ".....", "B....", ".B.A.", ".....", ".....", ".....", ".....", ".....", ".....", "B....", ".B...", "..B..", ".A.B." };

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			long long t               = ;
			long long x0              = ;
			long long y0              = ;
			int w                     = ;
			int h                     = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 5: {
			long long t               = ;
			long long x0              = ;
			long long y0              = ;
			int w                     = ;
			int h                     = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			long long t               = ;
			long long x0              = ;
			long long y0              = ;
			int w                     = ;
			int h                     = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = CheckerExpansion().resultAfter(t, x0, y0, w, h);
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
