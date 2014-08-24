#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<string> VS;

#define sz(X) ((int)(X.size()))
#define all(x) x.begin(),x.end()
#define clr(x,c) memset(x,c,sizeof(x))
#define rep(i,s,e) for(int i=s;i<e;i++)


class FoxAndGo3 {
public:
	int maxEmptyCells(vector <string> board);
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

int dir[4][2] = {0,1, 1,0, 0,-1, -1,0};

int id2[55][55];
int id[55][55];
bool vst[55][55];

int FoxAndGo3::maxEmptyCells(vector <string> board) {
	init();
	int n = sz(board);
	int cnt = 1;
	rep(i, 0, n) rep(j, 0, n) id[i][j] = cnt++;	
	rep(i, 0, n) rep(j, 0, n) id2[i][j] = cnt++;	

	clr(vst, false);

	int src = 0, sink = cnt ++;

	int sum = 0;
	rep(i, 0, n) rep(j, 0, n) if(board[i][j]!='x') {
		sum ++;
		if(board[i][j]=='.') {
			insert(id[i][j], id2[i][j], 1, 0);
			insert(id2[i][j], sink, 1, 0);
		}
		if(board[i][j]=='o') {
			insert(src, id[i][j], 1, 0);
			rep(in, 0, 4) {
				int ti = i+dir[in][0];
				int tj = j+dir[in][1];
				if(ti<0 || ti>=n || tj<0 || tj>=n) continue;
				if(board[ti][tj] == '.') {
					insert(id[i][j], id[ti][tj], 1, 0);
				}
			}
		}
	}
	//printf("sum = %d\n", sum);
	flow.src = src;
	flow.sink = sink;
	return sum - flow.dinic();
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
			string board[]            = {"o.o",
 ".o.",
 "o.o"};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = FoxAndGo3().maxEmptyCells(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"...",
 ".o.",
 "..."}
;
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = FoxAndGo3().maxEmptyCells(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"xxxxx",
 "xxoxx",
 "xo.ox",
 "xxoxx",
 "xxxxx"}
;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = FoxAndGo3().maxEmptyCells(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {".xox.",
 ".o.ox",
 "x.o.o",
 "ox.ox",
 ".ox.."}
 ;
			int expected__            = 12;

			clock_t start__           = clock();
			int received__            = FoxAndGo3().maxEmptyCells(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"o.o.o",
 ".ox..",
 "oxxxo",
 "..x..",
 "o.o.o"}
;
			int expected__            = 12;

			clock_t start__           = clock();
			int received__            = FoxAndGo3().maxEmptyCells(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {"...",
 "...",
 "..."};
			int expected__            = 9;

			clock_t start__           = clock();
			int received__            = FoxAndGo3().maxEmptyCells(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndGo3().maxEmptyCells(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndGo3().maxEmptyCells(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndGo3().maxEmptyCells(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
