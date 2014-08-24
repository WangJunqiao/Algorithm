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


class NonXorLife {
public:
	int countAliveCells(vector <string> field, int K);
};

bool alive[4000][4000];
int offset=2000;
int dir[4][2]={0,1, 1,0, 0,-1, -1,0};
int NonXorLife::countAliveCells(vector <string> field, int K) {
	queue<int> q;
	clr(alive, false);
	repv(i, field) repv(j, field[i]) if( field[i][j]=='o' ){
		alive[i+offset][j+offset]=true;
		q.push(i+offset); q.push(j+offset); q.push(0);
	}
	while( !q.empty() ){
		int x=q.front(); q.pop();
		int y=q.front(); q.pop();
		int z=q.front(); q.pop();
		//cout<<x<<' '<<y<<endl;
		if( z==K ) continue;
		rep(in, 0, 4){
			int tx=x+dir[in][0];
			int ty=y+dir[in][1];
			if( alive[tx][ty]==false ){
				alive[tx][ty]=true;
				q.push(tx);
				q.push(ty);
				q.push(z+1);
			}
		}
	}
	int ret=0;
	rep(i, 0, 4000) rep(j, 0, 4000) if( alive[i][j] ) ret++;
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
			string field[]            = {"oo"
,"o."};
			int K                     = 3;
			int expected__            = 36;

			clock_t start__           = clock();
			int received__            = NonXorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string field[]            = {".."
,".."};
			int K                     = 23;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = NonXorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string field[]            = {"o"};
			int K                     = 1000;
			int expected__            = 2002001;

			clock_t start__           = clock();
			int received__            = NonXorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string field[]            = {"o.oo.ooo"
,"o.o.o.oo"
,"ooo.oooo"
,"o.o..o.o"
,"o.o..o.o"
,"o..oooo."
,"..o.o.oo"
,"oo.ooo.o"};
			int K                     = 1234;
			int expected__            = 3082590;

			clock_t start__           = clock();
			int received__            = NonXorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string field[]            = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = NonXorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string field[]            = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = NonXorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string field[]            = ;
			int K                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = NonXorLife().countAliveCells(vector <string>(field, field + (sizeof field / sizeof field[0])), K);
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
