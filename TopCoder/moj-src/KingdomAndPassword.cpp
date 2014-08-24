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


class KingdomAndPassword {
public:
	long long newPassword(long long oldPassword, vector <int> restrictedDigits);
};


map<VI, LL> mp;
LL old;
VI res;

bool better(LL x1, LL x2, LL old){
	//if( x2==-1 ) return true;
	if( abs(x1-old) != abs(x2-old) ) 
		return abs(x1-old) < abs(x2-old);
	return x1 < x2;
}

LL dfs(VI v){
	if( mp.find(v)!=mp.end() ) return mp[v];
	
	int num=0;
	rep(i, 1, 10){
		num+=v[i];
	}
	if( num==0 ) return 0;
	LL mul=1;
	rep(i, 1, num) mul*=10;
	int w=old/mul%10;
	//v[0]=0 等于
	//v[0]=1 小于
	//v[0]=2 大于
	LL ret=-1;
	rep(i, 1, 10)if( v[i] && res[sz(res)-num]!=i ) {
		//if( sz(res)<4 ) printf("num=%d i=%d\n", num, i);
		VI tmp=v;
		tmp[i]--;
		if( v[0]==0 ){
			if( i<w ) tmp[0]=1;
			if( i>w ) tmp[0]=2;
		}
		LL ans=dfs(tmp);
		if( ans!=-1 ) {
			ans+=mul*i;
			if( ret==-1 ) ret=ans;
			else if( v[0]==0 && better(ans, ret, old%(mul*10)) ) ret=ans;
			else if( v[0]==1 && ans>ret ) ret=ans;
			else if( v[0]==2 && ans<ret ) ret=ans;
		}
	}
	return mp[v]=ret;
}

long long KingdomAndPassword::newPassword(long long old, vector <int> res) {
	mp.clear();
	::old=old;
	::res=res;
	VI v(10, 0);
	while( old ){
		v[old%10]++;
		old/=10;
	}
	return dfs(v);
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
			long long oldPassword     = 548;
			int restrictedDigits[]    = {5, 1, 8};
			long long expected__      = 485;

			clock_t start__           = clock();
			long long received__      = KingdomAndPassword().newPassword(oldPassword, vector <int>(restrictedDigits, restrictedDigits + (sizeof restrictedDigits / sizeof restrictedDigits[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long oldPassword     = 7777;
			int restrictedDigits[]    = {4, 7, 4, 7};
			long long expected__      = -1;

			clock_t start__           = clock();
			long long received__      = KingdomAndPassword().newPassword(oldPassword, vector <int>(restrictedDigits, restrictedDigits + (sizeof restrictedDigits / sizeof restrictedDigits[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long oldPassword     = 58;
			int restrictedDigits[]    = {4, 7};
			long long expected__      = 58;

			clock_t start__           = clock();
			long long received__      = KingdomAndPassword().newPassword(oldPassword, vector <int>(restrictedDigits, restrictedDigits + (sizeof restrictedDigits / sizeof restrictedDigits[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long oldPassword     = 172;
			int restrictedDigits[]    = {4, 7, 4};
			long long expected__      = 127;

			clock_t start__           = clock();
			long long received__      = KingdomAndPassword().newPassword(oldPassword, vector <int>(restrictedDigits, restrictedDigits + (sizeof restrictedDigits / sizeof restrictedDigits[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long oldPassword     = 241529363573463LL;
			int restrictedDigits[]    = {1, 4, 5, 7, 3, 9, 8, 1, 7, 6, 3, 2, 6, 4, 5};
			long long expected__      = 239676554423331LL;

			clock_t start__           = clock();
			long long received__      = KingdomAndPassword().newPassword(oldPassword, vector <int>(restrictedDigits, restrictedDigits + (sizeof restrictedDigits / sizeof restrictedDigits[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			long long oldPassword     = ;
			int restrictedDigits[]    = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = KingdomAndPassword().newPassword(oldPassword, vector <int>(restrictedDigits, restrictedDigits + (sizeof restrictedDigits / sizeof restrictedDigits[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			long long oldPassword     = ;
			int restrictedDigits[]    = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = KingdomAndPassword().newPassword(oldPassword, vector <int>(restrictedDigits, restrictedDigits + (sizeof restrictedDigits / sizeof restrictedDigits[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long oldPassword     = ;
			int restrictedDigits[]    = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = KingdomAndPassword().newPassword(oldPassword, vector <int>(restrictedDigits, restrictedDigits + (sizeof restrictedDigits / sizeof restrictedDigits[0])));
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
