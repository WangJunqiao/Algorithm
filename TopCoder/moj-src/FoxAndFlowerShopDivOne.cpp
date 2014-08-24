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


class FoxAndFlowerShopDivOne {
public:
	int theMaxFlowers(vector <string> flowers, int maxDiff);
};

int n, m;
int sumL[33][33], sumP[33][33];
const int offset=910;

int xd[33][offset*2];
int xu[33][offset*2];
int yd[33][offset*2];
int yu[33][offset*2];

int get(int sum[][33], int r1, int r2, int c1, int c2){
	return sum[r2][c2]+sum[r1-1][c1-1]-sum[r1-1][c2]-sum[r2][c1-1];
}

void check(int &a, int b){
	a=max(a, b);
}


int Log[5000];
template<typename T>
struct RMQ{ //类型T必须重载operator<
	T mi[2000][15]; 
	void rmq(T* d, int N){ //预处理，传入一个数组，0~N-1
		int M=get(N);
		for(int i=0;i<N;i++) mi[i][0]=d[i];
		for(int g=1;g<=M;g++){
			int L=N-(1<<g);
			for(int i=0;i<=L;i++)
				mi[i][g]= max(mi[i][g-1], mi[i+(1<<(g-1))][g-1]);
		}
	}
	
	int get(int L){ //如果查询太多可以打个表，这个很费时间的
		//return int (log(L*1.0)/log(2.0));
		return Log[L];
	}
	T query(int &a,int &b){//询问[a,b]之间的最小值
		if( a>b ) swap(a,b);
		int g=get(b-a+1);
		return max( mi[a][g], mi[b-(1<<(g))+1][g]); 
	}
};//***************模板结束***************************

RMQ<int> rxd[33], rxu[33], ryd[33], ryu[33];



int FoxAndFlowerShopDivOne::theMaxFlowers(vector <string> f, int maxDiff) {
	rep(i, 1, 5000) Log[i] = int (log(i*1.0)/log(2.0));
	clr(sumL, 0);
	clr(sumP, 0);
	n=sz(f), m=sz(f[0]);
	
	rep(i, 1, n+1) rep(j, 1, m+1){
		if( f[i-1][j-1]=='L' ) sumL[i][j]=1;
		if( f[i-1][j-1]=='P' ) sumP[i][j]=1;
		sumL[i][j]+=sumL[i-1][j]+sumL[i][j-1]-sumL[i-1][j-1];
		sumP[i][j]+=sumP[i-1][j]+sumP[i][j-1]-sumP[i-1][j-1];
	}
	clr(xd, -1);
	clr(xu, -1);
	clr(yd, -1);
	clr(yu, -1);
	rep(i, 1, n+1) rep(j, 1, m+1){
		rep(i2, i, n+1) rep(j2, j, m+1){
			//L-P
			int L=get(sumL, i, i2, j, j2);
			int P=get(sumP, i, i2, j, j2);
			int val = L - P + offset;
			rep(k, i2, n+1) check(xd[k][val],L+P);
			rep(k, 1, i+1) check(xu[k][val], L+P);
			rep(k, j2, m+1) check(yd[k][val],L+P);
			rep(k, 1, j+1) check(yu[k][val], L+P);
		}
	}
	rep(i, 1, n+1) rep(j, 1, m+1){
		rep(i2, i, n+1) rep(j2, j, m+1){
			//L-P
			int L=get(sumL, i, i2, j, j2);
			int P=get(sumP, i, i2, j, j2);
			int val = L - P + offset;
		}
	}
	rep(i, 1, n+1){
		rxd[i].rmq(xd[i], offset*2);
		rxu[i].rmq(xu[i], offset*2);
	}
	rep(j, 1, m+1){
		ryd[j].rmq(yd[j], offset*2);
		ryu[j].rmq(yu[j], offset*2);
	}
	
	int ret = -1;
	rep(i, 1, n+1) rep(j, 1, m+1){
		rep(i2, i, n+1) rep(j2, j, m+1){
			//L-P
			int L=get(sumL, i, i2, j, j2);
			int P=get(sumP, i, i2, j, j2);
			int val = L - P ;
			int left=-val-maxDiff, right=-val+maxDiff;
			left=max(0, left+offset);
			right=min(right+offset, offset*2-1);
			if( left>right ) continue;
			if( i-1>=1 ){
				int t=rxd[i-1].query(left, right);
				if( t!=-1 ) ret=max(ret, L+P+t);
			}
			if( j-1>=1 ){
				int t=ryd[j-1].query(left, right);
				if( t!=-1 ) ret=max(ret, L+P+t);
			}
			if( i2+1<=n ){
				int t=rxu[i2+1].query(left, right);
				if( t!=-1 ) ret=max(ret, L+P+t);
			}
			if( j2+1<=m ){
				int t=ryu[j2+1].query(left, right);
				if( t!=-1 ) ret=max(ret, L+P+t);
			}
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
			string flowers[]          = {"LLL",
 "PPP",
 "LLL"};
			int maxDiff               = 1;
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string flowers[]          = {"LLL",
 "PPP",
 "LLL"};
			int maxDiff               = 0;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string flowers[]          = {"...",
 "...",
 "..."};
			int maxDiff               = 3;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string flowers[]          = {"LLPL.LPP",
 "PLPPPPLL",
 "L.P.PLLL",
 "LPL.PP.L",
 ".LLL.P.L",
 "PPLP..PL"};
			int maxDiff               = 2;
			int expected__            = 38;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string flowers[]          = {"LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL"};
			int maxDiff               = 0;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string flowers[]          = {"LLLP..LLP.PLL.LL..LP",
 "L.PL.L.LLLL.LPLLPLP.",
 "PLL.LL.LLL..PL...L..",
 ".LPPP.PPPLLLLPLP..PP",
 "LP.P.PPL.L...P.L.LLL",
 "L..LPLPP.PP...PPPL..",
 "PP.PLLL.LL...LP..LP.",
 "PL...P.PPPL..PLP.L..",
 "P.PPPLPLP.LL.L.LLLPL",
 "PLLPLLP.LLL.P..P.LPL",
 "..LLLPLPPPLP.P.LP.LL",
 "..LP..L..LLPPP.LL.LP",
 "LPLL.PLLPPLP...LL..P",
 "LL.....PLL.PLL.P....",
 "LLL...LPPPPL.PL...PP",
 ".PLPLLLLP.LPP...L...",
 "LL...L.LL.LLLPLPPPP.",
 "PLPLLLL..LP.LLPLLLL.",
 "PP.PLL..L..LLLPPL..P",
 ".LLPL.P.PP.P.L.PLPLL"};
			int maxDiff               = 9;
			int expected__            = 208;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string flowers[]          = ;
			int maxDiff               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string flowers[]          = ;
			int maxDiff               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string flowers[]          = ;
			int maxDiff               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndFlowerShopDivOne().theMaxFlowers(vector <string>(flowers, flowers + (sizeof flowers / sizeof flowers[0])), maxDiff);
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
