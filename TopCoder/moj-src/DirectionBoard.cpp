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




class DirectionBoard {
public:
	int getMinimum(vector <string> board);
};


//二分图最大权值匹配,KM算法  O(m^3)  (在n<m的时候比zju模板慢)
//modified by zjut_DD
typedef int type;
const int MAX = 330;
const type inf = 1<<30;

int n,m,match[MAX];      // n<=m   match:Y->X
type w[MAX][MAX];        // 权值
type lx[MAX],ly[MAX];    // 标号
bool sx[MAX],sy[MAX];    // 是否被搜索过
bool dfs(int u){
	sx [u] = true;
	for(int v=0;v<m;v++){
		if(!sy[v] && lx[u]+ly[v]==w[u][v]){
			sy[v]=true;
			if(match[v]==-1 || dfs(match[v])){
				match[v]=u;
				return true;
			}
		}
	}
	return false;
}
type bestmatch() {//二分图最大权匹配,权值改成负的最小权匹配
	if( n<m ){ //左边点数少于右边,补成m*m的
		for(int i=n;i<m;i++) for(int j=0;j<m;j++) w[i][j]=0;
	}
	for(int i=0;i<m;i++){
		lx[i]=-inf; ly[i]=0;
		for(int j=0;j<m;j++){ //任意时刻,两定标和>=边权
			if (lx[i]<w[i][j]) lx[i]=w[i][j];
		}
	}
	memset(match,-1,sizeof(match));
	for(int u=0;u<m;u++){
		while (1) {
			memset(sx,0,sizeof(sx));
			memset(sy,0,sizeof(sy));
			if (dfs (u) ) break; //能增广了
			type dx = inf; // 修改标号
			for(int i=0;i<m;i++){
				if (!sx[i]) continue;
				for(int j=0;j<m;j++){
					if(sy[j]) continue;
					dx=min(lx[i]+ly[j]-w[i][j],dx);
				}
			}
			for(int i=0;i<m;i++) if(sx[i]) lx[i]-=dx;
			for(int j=0;j<m;j++) if(sy[j]) ly[j]+=dx;
		}
	}
	type sum = 0;
	for(int j=0;j<m;j++) sum+=w[ match[j] ][j];
	return sum;
}//*用法,初始化n,m,w[][], 调用bestmatch


int DirectionBoard::getMinimum(vector <string> board) {
	int N = sz(board), M = sz(board[0]);
	n = N*M, m = N*M;
	clr(w, 0x88);
	rep(i, 0, N) rep(j, 0, M) {
		int dir[4][2] = {0,-1, 0,1, -1,0, 1,0};
		char ch[4] = {'L', 'R', 'U', 'D'};
		rep(d, 0, 4) {
			int tx = (i+dir[d][0]+N)%N;
			int ty = (j+dir[d][1]+M)%M;
			if(board[i][j]==ch[d]) {
				checkmax(w[tx*M+ty][i*M+j], 0);
			} else {
				checkmax(w[tx*M+ty][i*M+j], -1);
			}
		}
	}
	return -bestmatch();
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
			string board[]            = {"RRRD",
 "URDD",
 "UULD",
 "ULLL"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"RRRD",
 "URLL",
 "LRRR"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"RRD",
 "URD",
 "ULL"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"ULRLRD",
 "UDDLRR"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"UDLRLDLD",
 "DLDLLDLR",
 "LLLLLDLD",
 "UUURRRDD"};
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {"UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUUDDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "RRRDLDURDURUDDR"}
;
			int expected__            = 73;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DirectionBoard().getMinimum(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
