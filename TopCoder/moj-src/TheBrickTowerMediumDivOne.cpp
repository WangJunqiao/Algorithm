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


class TheBrickTowerMediumDivOne {
public:
	vector <int> find(vector <int> heights);
};

VI H;
int get(bool* used, int last){
	VI hs;
	int n=sz(H);
	rep(i, 0, n) if( used[i]==false ){
		hs.PB(H[i]);
	}
	if( sz(hs)==0 ) return 0;
	sort(all(hs));
	reverse(all(hs));
	int ret=max(hs[0], last), mi=min(hs[0], last);
	for(int i=1;i<sz(hs);i++){
		ret+=max(mi, hs[i]);
		mi=min(mi, hs[i]);
	}
	return ret;
}

vector <int> TheBrickTowerMediumDivOne::find(vector <int> h) {
	bool used[55]={false}, tmp[55];
	VI ret;
	H=h;
	int n=sz(h);
	int mi=10000000, id=-1;
	rep(j, 0, n){
		memcpy(tmp, used, sizeof(tmp));
		tmp[j]=true;
		int t=get(tmp, h[j]);
		//printf("j=%d  t=%d\n", j, t);
		if( t<mi ){
			mi=t;
			id=j;
		}
	}
	//printf("id=%d\n", id);
	ret.PB(id);
	used[id]=true;
	for(int i=1;i<n;i++){
		int mi=100000000, id=-1;
		rep(j, 0, n) if( used[j]==false ){
			memcpy(tmp, used, sizeof(tmp));
			tmp[j]=true;
			int t=get(tmp, h[j])+max(h[j], h[ret.back()]);
			//printf("t=%d\n", t);
			if( t<mi ){
				mi=t;
				id=j;
			}
		}
		//printf("id=%d\n", id);
		ret.PB(id);
		used[id]=true;
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

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, clock_t elapsed) { 
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
				int heights[]             = {4, 7, 5};
				int expected__[]          = {0, 2, 1 };

				clock_t start__           = clock();
				vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
				return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
			}
		case 1: {
				int heights[]             = {4, 4, 4, 4, 4, 4, 4};
				int expected__[]          = {0, 1, 2, 3, 4, 5, 6 };

				clock_t start__           = clock();
				vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
				return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
			}
		case 2: {
				int heights[]             = {2, 3, 3, 2};
				int expected__[]          = {0, 3, 1, 2 };

				clock_t start__           = clock();
				vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
				return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
			}
		case 3: {
				int heights[]             = {13, 32, 38, 25, 43, 47, 6};
				int expected__[]          = {0, 6, 3, 1, 2, 4, 5 };

				clock_t start__           = clock();
				vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
				return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
			}

			// custom cases

			/*      case 4: {
			int heights[]             = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
			/*      case 5: {
			int heights[]             = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
			/*      case 6: {
			int heights[]             = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = TheBrickTowerMediumDivOne().find(vector <int>(heights, heights + (sizeof heights / sizeof heights[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
