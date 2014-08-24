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


class PastingPaintingDivOne {
public:
	vector<long long> countColors(vector <string> clipboard, int T);
};

LL R, G, B;

char ch[5555];
void fuck(string s, int T){
	//cout<<s<<' '<<T<<endl;
	while( sz(s) >0 && s[0]=='.' ) s=s.substr(1);
	while( sz(s) >0 && s[sz(s)-1]=='.' ) s=s.substr(0, sz(s)-1);
	if( sz(s)==0 ) return;
	if( s[0]=='R' ) R+=T-1;
	if( s[0]=='G' ) G+=T-1;
	if( s[0]=='B' ) B+=T-1;
	
	
	int tt = min(T, 60);
	//printf("tt=%d\n", tt);
	int start = 0;
	clr(ch, '.');
	for(int k=0;k<tt;k++){
		
		for(int i=0;i<sz(s);i++){
			if( s[i]=='.' ) continue;
			ch[start+i]=s[i];
		}
		start++;
	}

	start--;
	for(int i=0;i<sz(s);i++){
		if( ch[start+i]=='R' ) R++;
		if( ch[start+i]=='G' ) G++;
		if( ch[start+i]=='B' ) B++;
	}
}

vector<long long> PastingPaintingDivOne::countColors(vector <string> clip, int T) {
	int n=sz(clip), m=sz(clip[0]);
	R=G=B=0;
	for(int i=0;i<n;i++){
		//printf("i=%d\n", i);
		string s = "";
		int x=i, y=0;
		while( x<n && y<m ){
			s+=clip[x][y];
			x++;y++;
			//cout<<s<<endl;
		}
		fuck(s, T);
	}
	for(int j=1;j<m;j++){
		string s = "";
		int x=0, y=j;
		while( x<n && y<m ){
			s+=clip[x][y];
			x++;y++;
		}
		fuck(s, T);
	}
	vector<LL> ret;
	ret.PB(R);
	ret.PB(G);
	ret.PB(B);
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

	int verify_case(int casenum, const vector<long long> &expected, const vector<long long> &received, clock_t elapsed) { 
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
			string clipboard[]        = {
"..G",
"R..",
"BG."
};
			int T                     = 3;
			long long expected__[]    = {3, 4, 3};

			clock_t start__           = clock();
			vector<long long> received__ = PastingPaintingDivOne().countColors(vector <string>(clipboard, clipboard + (sizeof clipboard / sizeof clipboard[0])), T);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string clipboard[]        = {
"R...",
"....",
"....",
"...R"
};
			int T                     = 2;
			long long expected__[]    = {4, 0, 0};

			clock_t start__           = clock();
			vector<long long> received__ = PastingPaintingDivOne().countColors(vector <string>(clipboard, clipboard + (sizeof clipboard / sizeof clipboard[0])), T);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string clipboard[]        = {"RGB"};
			int T                     = 100000;
			long long expected__[]    = {100000, 100000, 100000};

			clock_t start__           = clock();
			vector<long long> received__ = PastingPaintingDivOne().countColors(vector <string>(clipboard, clipboard + (sizeof clipboard / sizeof clipboard[0])), T);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string clipboard[]        = {"."};
			int T                     = 1000000000;
			long long expected__[]    = {0, 0, 0};

			clock_t start__           = clock();
			vector<long long> received__ = PastingPaintingDivOne().countColors(vector <string>(clipboard, clipboard + (sizeof clipboard / sizeof clipboard[0])), T);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			string clipboard[]        = {
"RB.",
".G."
}
;
			int T                     = 100;
			long long expected__[]    = {100, 1, 100};

			clock_t start__           = clock();
			vector<long long> received__ = PastingPaintingDivOne().countColors(vector <string>(clipboard, clipboard + (sizeof clipboard / sizeof clipboard[0])), T);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			string clipboard[]        = {
"..........G..........",
".........G.G.........",
"........G...G........",
".......G.....G.......",
"......G..B.B..G......",
".....G...B.B...G.....",
"....G...........G....",
"...G...R.....R...G...",
"..G.....RRRRRR....G..",
".G..........RR.....G.",
"GGGGGGGGGGGGGGGGGGGGG"
};
			int T                     = 1000000000;
			long long expected__[]    = {2000000018, 17000000048LL, 2000000005};

			clock_t start__           = clock();
			vector<long long> received__ = PastingPaintingDivOne().countColors(vector <string>(clipboard, clipboard + (sizeof clipboard / sizeof clipboard[0])), T);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string clipboard[]        = ;
			int T                     = ;
			long long expected__[]    = ;

			clock_t start__           = clock();
			vector<long long> received__ = PastingPaintingDivOne().countColors(vector <string>(clipboard, clipboard + (sizeof clipboard / sizeof clipboard[0])), T);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			string clipboard[]        = ;
			int T                     = ;
			long long expected__[]    = ;

			clock_t start__           = clock();
			vector<long long> received__ = PastingPaintingDivOne().countColors(vector <string>(clipboard, clipboard + (sizeof clipboard / sizeof clipboard[0])), T);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 8: {
			string clipboard[]        = ;
			int T                     = ;
			long long expected__[]    = ;

			clock_t start__           = clock();
			vector<long long> received__ = PastingPaintingDivOne().countColors(vector <string>(clipboard, clipboard + (sizeof clipboard / sizeof clipboard[0])), T);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
