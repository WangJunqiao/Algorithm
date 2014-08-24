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


class MagicalHats {
public:
	int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses);
};

int n, m, H, G, mul[15];
bool vst[2000000];
int dp[2000000];
PII p[15];


int dfs(int s){
	if( dp[s]>=-10000000 ) return dp[s];
	int ts=s, data[13], num=0;
	rep(i, 0, H){
		data[i]=ts%3; 
		ts/=3;
		if( data[i] ) num++;
	}
	if( num==G ){
		if( vst[s] ) return 0;
		return -1000000;
	}
	int ret=-1000000;
	rep(i, 0, H) if( data[i]==0 ){
		
		int tmp=-1000000;
		for(int j=1;j<=2;j++){
			int ttt=(j==2)+dfs(s+j*mul[i]);
			if( ttt<0 ) continue;
			if( tmp<0 ) tmp=ttt;
			tmp=min(tmp, ttt);
		}
		
		ret=max(ret, tmp);
	}
	return dp[s]=ret;
}


int MagicalHats::findMaximumReward(vector <string> board, vector <int> coins, int g) {
	n=sz(board), m=sz(board[0]), H=0;
	G=g;
	rep(i, 0, n) rep(j, 0, m) if( board[i][j]=='H' ) {
		p[H].ff=i;
		p[H].ss=j;
		H++;
	}
	//printf("H=%d\n", H);
	mul[0]=1;
	rep(i, 1, 14) mul[i]=mul[i-1]*3;
	clr(vst, false);
	rep(s, 0, mul[H]){ //ƒƒ¿Ô”–coin
		int two=0, zero=0, ts=s;
		int row[13]={0}, col[13]={0};
		rep(i, 0, H) {
			if( ts%3==0 )zero++;
			if( ts%3==2 )two++;
			if( ts%3==1 ){
				row[ p[i].ff ]++;
				col[ p[i].ss ]++;
			}
			ts/=3;
		}
		//if( s==2 ) printf("zero=%d two=%d\n", zero, two);
		
		if( zero || two!=sz(coins) ) continue;
		bool can=true;
		rep(i, 0, n) if( row[i]&1 ) can=false;
		rep(i, 0, m) if( col[i]&1 ) can=false;
		if( can==false ) continue;
		vst[s]=true;
	}
	//cout<<vst[2]<<endl;
	for(int i=mul[H]-1;i>=0;i--) if( vst[i] ) {
		int ts=i;
		rep(j, 0, H) {
			if( ts%3 ){
				vst[ i-mul[j]*(ts%3) ]=true;
			}
			ts/=3;
		}
	}
	
	clr(dp, 0x88);
	int ma=dfs(0);
	if( ma<0 ) return -1;
	//cout<<ma<<endl;
	int ret=0;
	sort(all(coins));
	for(int i=0;i<ma && i<sz(coins);i++) ret+=coins[i];
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
			string board[]            = {"H"};
			int coins[]               = {1};
			int numGuesses            = 1;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"HHH",
 "H.H",
 "HH."};
			int coins[]               = {9};
			int numGuesses            = 1;
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"HH",
 "HH"};
			int coins[]               = {1,2,3,4};
			int numGuesses            = 3;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"HHH",
 "HHH",
 "H.H"};
			int coins[]               = {13,13,13,13};
			int numGuesses            = 2;
			int expected__            = 13;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"HHH",
 "HHH",
 "H.H"};
			int coins[]               = {13,13,13,13};
			int numGuesses            = 3;
			int expected__            = 26;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {"H.H.",
 ".H.H",
 "H.H."};
			int coins[]               = {17};
			int numGuesses            = 6;
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string board[]            = {"HHH",
 "H.H",
 "HHH",
 "H.H",
 "HHH"};
			int coins[]               = {33,337,1007,2403,5601,6003,9999};
			int numGuesses            = 5;
			int expected__            = 1377;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			string board[]            = {".............",
 ".............",
 ".............",
 ".............",
 ".............",
 ".............",
 ".....H.H.....",
 "......H......",
 ".....H.H.....",
 ".............",
 ".............",
 ".............",
 "............."};
			int coins[]               = {22};
			int numGuesses            = 3;
			int expected__            = 22;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 8: {
			string board[]            = ;
			int coins[]               = ;
			int numGuesses            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string board[]            = ;
			int coins[]               = ;
			int numGuesses            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			string board[]            = ;
			int coins[]               = ;
			int numGuesses            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MagicalHats().findMaximumReward(vector <string>(board, board + (sizeof board / sizeof board[0])), vector <int>(coins, coins + (sizeof coins / sizeof coins[0])), numGuesses);
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
