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

#define sz(X) ((int)(X.size()))
#define all(x) x.begin(),x.end()
#define clr(x,c) memset(x,c,sizeof(x))
#define rep(i,st,ed) for(int i=st;i<ed;i++)

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;
//--------------------------------------------


class TheTilesDivOne {
public:
	int find(vector <string> board);
};


//author: momodi@whuacm
//ural 1099
//一般图匹配,带花树算法
//初始化需要 n的大小(base0),adj矩阵

#include<iostream>
using namespace std;
#define maxn 3000
int n;//节点个数,用的是0~n-1,
int match[maxn];//每个点匹配情况
bool adj[maxn][maxn];//邻接阵,连通为true
void clear() {
	memset(adj, 0, sizeof(adj));
	n = 0;
}
void insert(const int &u, const int &v) {
	adj[u][v] = adj[v][u] = 1;
}
int Q[maxn], pre[maxn], base[maxn];
bool _h[maxn];
bool in_blossom[maxn];
void argument(int u) {
	while (u != -1) {
		int v = pre[u];
		int k = match[v];
		match[u] = v;
		match[v] = u;
		u = k;
	}
}
void change_blossom(int b, int u) {
	while (base[u] != b) {
		int v = match[u];
		in_blossom[base[v]] = in_blossom[base[u]] = true;
		u = pre[v];
		if (base[u] != b) {
			pre[u] = v;
		}
	}
}
int find_base(int u, int v) {
	bool in_path[maxn] = {};
	while (true) {
		in_path[u] = true;
		if (match[u] == -1) {
			break;
		}
		u = base[pre[match[u]]];
	}
	while (!in_path[v]) {
		v = base[pre[match[v]]];
	}
	return v;
}
int contract(int u, int v) {
	memset(in_blossom, 0, sizeof(in_blossom));
	int b = find_base(base[u], base[v]);
	change_blossom(b, u);
	change_blossom(b, v);
	if (base[u] != b) {
		pre[u] = v;
	}
	if (base[v] != b) {
		pre[v] = u;
	}
	return b;
}
int bfs(int p) {
	memset(pre, -1, sizeof(pre));
	memset(_h, 0, sizeof(_h));
	for (int i = 0; i < n; ++i) {
		base[i] = i;
	}
	Q[0] = p;  _h[p] = 1;
	for (int s = 0, t = 1; s < t; ++s) {
		int u = Q[s];
		for (int v = 0; v < n; ++v) {
			if (adj[u][v] && base[u] != base[v] && v != match[u]){
				if (v == p || (match[v] != -1 && pre[match[v]] != -1)){
					int b = contract(u, v);
					for (int i = 0; i < n; ++i) {
						if (in_blossom[base[i]]) {
							base[i] = b;
							if (_h[i] == 0){
								_h[i] = 1;
								Q[t++] = i;
							}
						}
					}
				} else if (pre[v] == -1) {
					pre[v] = u;
					if (match[v] == -1) {
						argument(v);
						return 1;
					} 
					else{
						Q[t++] = match[v];
						_h[match[v]] = 1;
					}
				}
			}
		}
	}
	return 0;
}
int max_match(){ //节点编号从0~n-1
	memset(match, -1, sizeof(match));//没匹配的就是-1
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		if (match[i] == -1) {
			ans += bfs(i);
		}
	}
	return ans;
}//**************模板结束**************







int dir[4][2] = {0,1, 1,0, 0,-1, -1,0};



int id[55][55];
int N, M;

bool ill(int i, int j) {
	return i>=0 && i<N && j>=0 && j<M;
}



int TheTilesDivOne::find(vector <string> board) {
	int cnt = 0;
	N = sz(board), M = sz(board[0]);
	rep(i, 0, N) rep(j, 0, M) {
		id[i][j] = cnt++;
	}
	n = cnt;
	memset(adj, false, sizeof(adj));
	rep(i, 0, N) rep(j, 0, M) {
		if((i+j)%2==0 && board[i][j]=='.') {
			cout<<i<<' '<<j<<endl;
			for(int in=0;in<4;in++) {
				int tx1 = i+dir[in][0];
				int ty1 = j+dir[in][1];

				int tx2 = i+dir[(in+1)%4][0];
				int ty2 = j+dir[(in+1)%4][1];



				if(!ill(tx1, ty1)) continue;
				if(!ill(tx2, ty2)) continue;
				if(board[tx1][ty1] == 'X' || board[tx2][ty2]=='X') continue;

				int id1 = id[tx1][ty1];
				int id2 = id[tx2][ty2];

				//printf("id1 = %d, id2 = %d\n", id1, id2);

				adj[id1] [id2] = true;
				adj[id2] [id1] = true;
			}
		}
	}
	return max_match();
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
			string board[]            = {"X.X",
 "...",
 "X.X"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"...",
 "...",
 "..."};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"......X.X.XXX.X.XX."};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"X.....XXX.XX..XXXXXXXXX...X.XX.XX....X",
 ".XXXX..X..XXXXXXXX....XX.X.X.X.....XXX",
 "....XX....X.XX..X.X...XX.X..XXXXXXX..X",
 "XX.XXXXX.X.X..X..XX.XXX..XX...XXX.X..."};
			int expected__            = 13;

			clock_t start__           = clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
