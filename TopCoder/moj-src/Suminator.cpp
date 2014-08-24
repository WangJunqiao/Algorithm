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


class Suminator {
public:
	int findMissing(vector <int> program, int wantedResult);
};

typedef pair<LL, LL> DD;

DD get(stack<DD> &st){
	if( st.empty() ) return DD(0, 0);
	DD ret = st.top();
	st.pop();
	return ret;
}

DD simu(VI pro){
	stack<DD> st;
	repv(i, pro){
		if( pro[i]==-1 ){
			st.push(DD(1, 0));
		} else if( pro[i]==0 ){
			DD d1=get(st);
			DD d2=get(st);
			d1.first += d2.first;
			d1.second+= d2.second;
			st.push(d1);
		} else {
			st.push(DD(0, pro[i]));
		}
	}
	return get(st);
}

int Suminator::findMissing(vector <int> program, int wanted) {
	DD d1 = simu(program);
	LL ans=-1;
	if( d1.first==0 && d1.second==wanted ) {
		ans=1;
	}
	if( d1.first!=0 ){
		LL t=wanted-d1.second;
		if( t>0 && t%d1.first==0 ){
			ans=t/d1.first;
		}
	}
	repv(i, program) if( program[i]==-1 ) program[i]=0;
	DD d2=simu(program);
	if( d2.second == wanted ) return 0;
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
			int program[]             = {7,-1,0};
			int wantedResult          = 10;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int program[]             = {100, 200, 300, 0, 100, -1};
			int wantedResult          = 600;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int program[]             = {-1, 7, 3, 0, 1, 2, 0, 0};
			int wantedResult          = 13;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int program[]             = {-1, 8, 4, 0, 1, 2, 0, 0};
			int wantedResult          = 16;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int program[]             = {1000000000, 1000000000, 1000000000, 1000000000, -1, 0, 0, 0, 0};
			int wantedResult          = 1000000000;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int program[]             = {7, -1, 3, 0};
			int wantedResult          = 3;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int program[]             = ;
			int wantedResult          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int program[]             = ;
			int wantedResult          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int program[]             = ;
			int wantedResult          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Suminator().findMissing(vector <int>(program, program + (sizeof program / sizeof program[0])), wantedResult);
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
