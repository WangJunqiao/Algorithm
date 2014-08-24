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


class GearsDiv1 {
public:
	int getmin(string color, vector <string> graph);
};

//author: momodi@whuacm
//ural 1099
//一般图匹配,带花树算法
//初始化需要 n的大小(base0),adj矩阵

#include<iostream>
using namespace std;
#define maxn 100
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
// 
// int main(){
// 	int N,a,b;
// 	scanf("%d",&N);
// 	n=N;
// 	memset(adj,false,sizeof(adj));
// 	while(scanf("%d%d",&a,&b)!=EOF){
// 		adj[a-1][b-1]=adj[b-1][a-1]=true;
// 	}
// 	int ret=max_match();
// 	printf("%d\n",ret*2);
// 	for(int i=0;i<N;i++){
// 		if( match[i]!=-1){
// 			printf("%d %d\n",i+1,match[i]+1);
// 			match[ match[i] ]=-1;
// 		}
// 	}
// }








int solve(string color, VS graph, map<char, int> mp) {
	n = sz(color);
	memset(adj, false, sizeof(adj));
	rep(i, 0, n) rep(j, 0, n) if(mp[color[i]] == mp[color[j]] && graph[i][j]=='Y') {
		adj[i][j] = adj[j][i] = true;
	} 
	return max_match();
}





int GearsDiv1::getmin(string color, vector <string> graph) {
	map<char, int> mp;
	int ret = 10000;
	mp['R'] = 0; mp['G'] = 0; mp['B'] = 1;
	ret = min(ret, solve(color, graph, mp));
	mp['R'] = 0; mp['G'] = 1; mp['B'] = 0;
	ret = min(ret, solve(color, graph, mp));
	mp['R'] = 1; mp['G'] = 0; mp['B'] = 0;
	ret = min(ret, solve(color, graph, mp));
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
			string color              = "RGB";
			string graph[]            = {"NYY","YNY","YYN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string color              = "RGBR";
			string graph[]            = {"NNNN","NNNN","NNNN","NNNN"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string color              = "RGBR";
			string graph[]            = {"NYNN","YNYN","NYNY","NNYN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string color              = "RRRRRGRRBGRRGBBGGGBRRRGBRGRRGG";
			string graph[]            = {"NNNNNYNNNYNNYNNNYNNNNNNNNYNNYY",
 "NNNNNNNNYNNNYNYNNYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNNNNYNNNNNNYNNNY",
 "NNNNNNNNNYNNYNNYYYNNNNYNNYNNNN",
 "NNNNNNNNNYNNYNNYYYNNNNYNNNNNNN",
 "YNYNNNYYYNNYNYYNNNNNYYNYNNYYNN",
 "NNNNNYNNNNNNNNNYYYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNYNNNNNNNNNNNNYN",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "YNNYYNNNYNNNNYYNNNYNYYNYNNNNNN",
 "NNNNNNNNNNNNYNNYNYNNNNYNNNNNNY",
 "NNNNNYNNNNNNYNNYYYNNNNNNNNNNYN",
 "YYNYYNNNYNYYNYYNNNYNYNNYNNNNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNYNYYY",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "NNNYYNYYYNYYNYYNNNYNYNNYYNYYNN",
 "YNNYYNYNYNNYNYYNNNYNNNNYYNNYNN",
 "NYNYYNYNYNYYNYYNNNNYYNNYYNYNNN",
 "NNYNNNNNNYNNYNNYYNNNNNYNNYNNNY",
 "NNNNNNNNNNNNNNNNNYNNNNYNNYNNNY",
 "NNNNNYNNNYNNYNNYNYNNNNYNNNNNYY",
 "NNNNNYNNNYNNNNNNNNNNNNYNNNNNNN",
 "NYNYYNYNYNYNNYYNNNYYYYNYYNYNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNNNNNY",
 "NNNNNNNNNNNNNNNYYYNNNNYNNYNNYY",
 "YYYYNNYNYNNNNYYNNNYYNNNNYNYYNN",
 "NNNNNYNNNNNNNNNYNYNNNNYNNYNNYN",
 "NNNNNYNNNNNNNYNYYNNNNNNNNYNNYY",
 "YYNNNNYYYNNYNYYNNNNNYNNNYNYYNN",
 "YYYNNNYNYNYNNYYNNNYYYNNYYNNYNN"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
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
