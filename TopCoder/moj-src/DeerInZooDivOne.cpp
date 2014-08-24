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


class DeerInZooDivOne {
public:
	int getmax(vector <int> a, vector <int> b);
};


typedef int type;
const int MAX = 55;
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
// int main(){
// 	while( scanf("%d %d",&n,&m)!=EOF ){
// 		for(int i=0;i<n;i++) for(int j=0;j<m;j++) scanf("%d",w[i]+j);
// 		printf("%d\n",bestmatch());
// 	}
// }


VI adj[55];
int N;
bool vst[55];
vector<int> path;
bool dfs(int u, int pa, int v) {
	if(u==v) {
		path.push_back(u);
		return true;
	}
	for(int i=0;i<(int)adj[u].size();i++) {
		int t = adj[u][i];
		if(t==pa) continue;
		if(dfs(t, u, v)) {
			path.push_back(u);
			return true;
		}
	}
	return false;
}
void find_path(int u, int v) {
	//memset(vst, false, sizeof(vst));
	path.clear();
	dfs(u, -1, v);
}

int cut1, cut2;

vector<int> dep[2][55];
int dd[55];

void dfs_deep(int f, int u, int d) {
	dep[f][d].push_back(u);
	dd[u] = d;
	vst[u] = true;
	rep(i, 0, sz(adj[u])) {
		int v = adj[u][i];
		if(u==cut1 && v==cut2) continue;
		if(u==cut2 && v==cut1) continue;
		if(vst[v]) continue;
		dfs_deep(f, v, d+1);
	}
}

int val[55][55];

int DeerInZooDivOne::getmax(vector <int> a, vector <int> b) {
	N = sz(a)+1;
	rep(i, 0, N) adj[i].clear();
	rep(i, 0, sz(a)) {
		adj[a[i]].push_back(b[i]);
		adj[b[i]].push_back(a[i]);
	}
	int ret = 0;
	rep(i, 0, N) rep(j, i+1, N) {
		find_path(i, j);
		rep(x, 0, sz(path)-1) {
			cut1 = path[x];
			cut2 = path[x+1];
		}
		memset(vst, false, sizeof(vst));
		rep(x, 0, 55) dep[0][x].clear(), dep[1][x].clear();
		dfs_deep(0, i, 0);
		dfs_deep(1, j, 0);

		memset(val, 0, sizeof(val));
		for(int d=50;d>=0;d--) {
			if(dep[0][d].size() == 0) continue;
			if(dep[1][d].size() == 0) continue;
			rep(x, 0, sz(dep[0][d])){
				rep(y, 0, sz(dep[1][d])) {
					n = 0, m = 0;
					int u = dep[0][d][x];
					//int v = dep[1][d][y];
					vector<int> v1, v2;
					rep(k, 0, sz(adj[u])) {
						int v = adj[u][k];
						if(u==cut1 && v==cut2) continue;
						if(v==cut1 && u==cut2) continue;
						if(dd[v]!=dd[u]+1) continue;
						v1.push_back(v);
						n++;
					}
					u = dep[1][d][y];
					rep(k, 0, sz(adj[u])) {
						int v = adj[u][k];
						if(u==cut1 && v==cut2) continue;
						if(v==cut1 && u==cut2) continue;
						if(dd[v]!=dd[u]+1) continue;
						v2.push_back(v);
						m++;
					}
					rep(p, 0, sz(v1)) rep(q, 0, sz(v2)) w[p][q] = val[v1[p]][v2[q]];
					val[dep[0][d][x]][dep[1][d][y]] = bestmatch()+1;
				}
			}
		}
		ret = max(ret, val[i][j]);
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
			int a[]                   = {0, 1, 2};
			int b[]                   = {1, 2, 3};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {1, 8, 1, 7, 4, 2, 5, 2};
			int b[]                   = {5, 3, 6, 8, 2, 6, 8, 0};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {0};
			int b[]                   = {1};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {0, 11, 10, 10, 19, 17, 6, 17, 19, 10, 10, 11, 9, 9, 14, 2, 13, 11, 6};
			int b[]                   = {7, 5, 2, 12, 8, 9, 16, 8, 4, 18, 8, 13, 15, 13, 17, 16, 3, 1, 7};
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {14, 13, 28, 15, 20, 4, 9, 6, 1, 23, 19, 25, 25, 8, 14, 16, 2, 8, 15, 25, 22, 22, 28, 10, 10, 14, 24, 27, 8};
			int b[]                   = {21, 5, 12, 13, 27, 1, 24, 17, 27, 17, 23, 14, 18, 26, 7, 26, 11, 0, 25, 23, 3, 29, 22, 11, 22, 29, 15, 28, 29};
			int expected__            = 11;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int a[]                   = ;
			int b[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a[]                   = ;
			int b[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a[]                   = ;
			int b[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DeerInZooDivOne().getmax(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
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
