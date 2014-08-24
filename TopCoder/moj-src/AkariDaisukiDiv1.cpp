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


class AkariDaisukiDiv1 {
public:
	int countF(string Waai, string Akari, string Daisuki, string S, string F, int k);
};

string W, A, D, S;
const int mod=1000000007;
const LL inf=1LL<<40;
int a0, a1, a2;

LL len[55];

// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
char get1(int k, int pos){
	if( k==0 ) return S[pos-1];
	//cout<<k<<' '<<pos<<endl;
	if( pos<=sz(W) ) return W[ pos-1 ];
	pos-=sz(W);
	if( pos<=len[k-1] ) return get1(k-1, pos);
	pos-=len[k-1];
	if( pos<=sz(A) ) return A[pos-1];
	pos-=sz(A);
	if( pos<=len[k-1] ) return get1(k-1, pos);
	pos-=len[k-1];
	return D[pos-1];
}

char get2(int k, int pos){
	//cout<<k<<' '<<pos<<" 55"<<endl;
	if( k==0 ) return S[pos-1];
	if( pos<=sz(D) ) return D[ sz(D)-pos ];
	pos-=sz(D);
	if( pos<=len[k-1] ) return get2(k-1, pos);
	pos-=len[k-1];
	if( pos<=sz(A) ) return A[ sz(A)-pos ];
	pos-=sz(A);
	if( pos<=len[k-1] ) return get2(k-1, pos);
	pos-=len[k-1];
	return W[sz(W)-pos];
}

int dfs(string S, string F, int k){
	//cout<<k<<endl;
	if( len[k]<=1000 ){
		rep(i, 0, k) S=W+S+A+S+D;
		int ret=0;
		rep(i, 0, sz(S)-sz(F)+1 ) if( S.substr(i, sz(F))==F ) ret++;
		return ret;
	}
	string s;
	
	int ret=0;
	
	s=W;
	rep(i, 0, 55) s+=get1(k-1, i+1);
	rep(i, 0, sz(W) ) if( s.substr(i, sz(F))==F) ret++;

	s="";
	rep(i, 0, 55) s=get2(k-1, i+1)+s;
	s+=A;
	rep(i, 0, 55) s=s+get1(k-1, i+1);
	rep(i, 55-sz(F)+1, 55+sz(A) ) if( s.substr(i, sz(F))==F) ret++;
	
	s="";
	rep(i, 0, 55) s+=get2(k-1, i+1);
	s+=D;
	rep(i, 55-sz(F)+1, sz(s)-sz(F)+1 ) if( s.substr(i, sz(F))==F) ret++;

	return (ret+2*dfs(S, F, k-1) )%mod;
}

int AkariDaisukiDiv1::countF(string Wi, string Ai, string Di, string S, string F, int k) {
	W=Wi; A=Ai; D=Di;
	::S=S;
	
	string s;
	
	a0=0, a1=0, a2=0;
	s=""; rep(i, 0, 55) s+=W;
	repv(i, W) if( s.substr(i, sz(F)) == F) a0++;
	
	s=""; rep(i, 0, 55) s+=D;
	s+=A; rep(i, 0, 55) s+=W;
	int id=55*sz(D);
	rep(i, id-sz(F)+1, id+sz(A) ) if( s.substr(i, sz(F))==F) a1++;
	
	
	s=""; rep(i, 0, 55) s+=D;
	id=sz(s)-sz(D);
	rep(i, id-sz(F)+1, sz(s)-sz(F)+1) if( s.substr(i, sz(F))==F) a2++;
	
	len[0]=sz(S);
	rep(i, 1, 55){
		len[i]=sz(W)+sz(A)+sz(D)+2*len[i-1];
		if( len[i]>=inf ) len[i]=inf;
	}
	
	int ret=0, mul=1;
	for(int i=k;;i--){
		if( i<=50 ) {
			ret=(ret+mul*(LL)dfs(S, F, i)%mod )%mod;
			break;
		}else{
			ret=(ret+(a0+a1+a2)*(LL)mul%mod)%mod;
			mul=(mul*2)%mod;
		}
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
			string Waai               = "a";
			string Akari              = "b";
			string Daisuki            = "c";
			string S                  = "x";
			string F                  = "axb";
			int k                     = 2;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string Waai               = "a";
			string Akari              = "b";
			string Daisuki            = "c";
			string S                  = "x";
			string F                  = "abcdefghij";
			int k                     = 1;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string Waai               = "a";
			string Akari              = "a";
			string Daisuki            = "a";
			string S                  = "b";
			string F                  = "aba";
			int k                     = 2;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string Waai               = "a";
			string Akari              = "b";
			string Daisuki            = "c";
			string S                  = "d";
			string F                  = "baadbdcbadbdccccbaaaadbdcbadbdccbaadbdcba";
			int k                     = 58;
			int expected__            = 191690599;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string Waai               = "a";
			string Akari              = "x";
			string Daisuki            = "y";
			string S                  = "b";
			string F                  = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
			int k                     = 49;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string Waai               = "waai";
			string Akari              = "akari";
			string Daisuki            = "daisuki";
			string S                  = "usushio";
			string F                  = "id";
			int k                     = 10000000;
			int expected__            = 127859200;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string Waai               = "vfsebgjfyfgerkqlr";
			string Akari              = "ezbiwls";
			string Daisuki            = "kjerx";
			string S                  = "jbmjvaawoxycfndukrjfg";
			string F                  = "bgjfyfgerkqlrvfsebgjfyfgerkqlrvfsebgjfyfgerkqlrvfs";
			int k                     = 1575724;
			int expected__            = 483599313;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string Waai               = ;
			string Akari              = ;
			string Daisuki            = ;
			string S                  = ;
			string F                  = ;
			int k                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string Waai               = ;
			string Akari              = ;
			string Daisuki            = ;
			string S                  = ;
			string F                  = ;
			int k                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string Waai               = ;
			string Akari              = ;
			string Daisuki            = ;
			string S                  = ;
			string F                  = ;
			int k                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
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
