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


class EllysFigurines {
public:
	int getMoves(vector <string> board, int R, int C);
};


//最大流 dinic  pku 3469
#define MAXN 20005
#define MAXE 600000
#define inf  0x3f3f3f3f
struct Edge{  int v,c,x; }E[MAXE]; //指向的节点, 剩余可增广的流量
int l[MAXN],e;                     //必须保证e的初始值是偶数
void init(){ e=0; memset(l,-1,sizeof(l));  }
inline void insert(int u,int v,int f,int invf){ //u->v=f   v->u=invf
	E[e].v=v; E[e].c=f;   E[e].x=l[u]; l[u]=e++;
	E[e].v=u; E[e].c=invf;E[e].x=l[v]; l[v]=e++;
}
struct Netflow{
	int src,sink; //需要初始化
	//以上
	int L[MAXN],Q[MAXN]; //L=level  Q=queue
	int _bfs(){ //广搜,并标记level(只取流量大于0的边)
		int s=0,t=0,u;
		memset(L,0xff,sizeof(L));
		L[src]=0; Q[t++]=src;
		while (s<t){
			u=Q[s++];
			for (int p=l[u];p>=0;p=E[p].x)
				if (E[p].c && L[E[p].v]==-1)
					L[(Q[t++]=E[p].v)]=L[u]+1;
		}
		return L[sink]!=-1;
	}
	int _find(int u,int in){ //in:能流入u节点的最大流量. 返回u节点能流出的最大流量
		if (u==sink) return in;
		int t,w=0; //w表示已经从u流出的总流量
		for (int p=l[u];p>=0 && w<in;p=E[p].x){
			if (E[p].c>0 && L[E[p].v]==L[u]+1){
				if (t=_find(E[p].v,min(E[p].c,in-w))){
					E[  p].c-=t;
					E[p^1].c+=t; //这里表示必须
					w+=t;     //多路增广优势巨大
				}
			}
		}
		if( w<in )L[u]=-1;//关键的一句话
		return w;
	}
	int dinic(){
		int t,res=0;
		while (_bfs())while (t=_find(src,inf))res+=t;
		return res;
	}
}flow; //********模板结束***********
//init(); insert(...); flow.src=.. ; flow.dinic();

int EllysFigurines::getMoves(vector <string> board, int R, int C) {
	int row[55], col[55];
	int n = sz(board), m = sz(board);
	for(int i=0;i<n;i++) row[i] = i+1;
	for(int j=0;j<m;j++) col[j] = n+1+j;
	int cnt = n+m+1;
	int src = 0, sink = 3000;
	init();
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(board[i][j]=='X') {
		insert(src, cnt, 1, 0);
		for(int k=0;k<R;k++) if(i-k>=0) {
			insert(cnt, row[i-k], 1, 0);
		}
		for(int k=0;k<C;k++) if(j-k>=0) {
			insert(cnt, col[j-k], 1, 0);
		}
		cnt++;
	}
	for(int i=1;i<=n+m;i++) insert(i, sink, 1, 0);
	flow.sink = sink;
	flow.src = src;
	return flow.dinic();
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
			string board[]            = {".X.X.",
 "XX..X",
 ".XXX.",
 "...X.",
 ".X.XX"};
			int R                     = 1;
			int C                     = 2;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = EllysFigurines().getMoves(vector <string>(board, board + (sizeof board / sizeof board[0])), R, C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {".X.X.",
 "XX..X",
 ".X.X.",
 "...X.",
 ".X.XX"};
			int R                     = 2;
			int C                     = 2;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = EllysFigurines().getMoves(vector <string>(board, board + (sizeof board / sizeof board[0])), R, C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"XXXXXXX"};
			int R                     = 2;
			int C                     = 3;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = EllysFigurines().getMoves(vector <string>(board, board + (sizeof board / sizeof board[0])), R, C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"XXXXX",
 "X....",
 "XXX..",
 "X....",
 "XXXXX"};
			int R                     = 1;
			int C                     = 1;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = EllysFigurines().getMoves(vector <string>(board, board + (sizeof board / sizeof board[0])), R, C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"XXX..XXX..XXX.",
 ".X..X....X...X",
 ".X..X....X...X",
 ".X..X....X...X",
 ".X...XXX..XXX.",
 "..............",
 "...XX...XXX...",
 "....X......X..",
 "....X....XXX..",
 "....X......X..",
 "...XXX..XXX..."};
			int R                     = 1;
			int C                     = 2;
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = EllysFigurines().getMoves(vector <string>(board, board + (sizeof board / sizeof board[0])), R, C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string board[]            = ;
			int R                     = ;
			int C                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EllysFigurines().getMoves(vector <string>(board, board + (sizeof board / sizeof board[0])), R, C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string board[]            = ;
			int R                     = ;
			int C                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EllysFigurines().getMoves(vector <string>(board, board + (sizeof board / sizeof board[0])), R, C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string board[]            = ;
			int R                     = ;
			int C                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EllysFigurines().getMoves(vector <string>(board, board + (sizeof board / sizeof board[0])), R, C);
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
