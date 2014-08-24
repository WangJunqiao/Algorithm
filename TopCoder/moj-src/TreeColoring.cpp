#pragma comment(linker, "/STACK:16777216")

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
#include <cassert>
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


//linked list, 邻接表用STL的vector超时的时候使用
template <typename T> struct Vector{
	struct Node {
		T val;
		Node *prev;
	};
	Node *tail;
	int tot;
	Vector() {
		tail = NULL;
		tot = 0;
	}
	void push_back(const T &val) {
		Node *p = new Node();
		p->val = val;
		p->prev = tail;
		tail = p;
		tot ++;
	}
	int size() {
		return tot;
	}

	void clear() {
		_release();
		tot = 0;
	}
	Node *last;
	int last_i;
	T& operator[](int i) {
		assert(i < tot);
		if(i==0) {
			last = tail;
		} else if(i == last_i) {

		} else if(i==last_i + 1) {
			last = last->prev;
		} else {
			puts("invalid access mode!!!");
			assert(false);
		}
		last_i = i;
		return last->val;
	}
	~Vector() {
		_release();
	}
private:
	Vector(const Vector &b) {}
	Vector& operator=(const Vector &b) {}

	void _release() {
		while(NULL != tail) {
			Node *tmp = tail->prev;
			delete tail;
			tail = tmp;
		}
	}
};

class TreeColoring {
public:
	long long color(int N, int Q, int startSeed, int threshold, int maxDist);
};
#define maxn 110000
#define SQRT 500

int N, Q, maxDist, threshold;
int curValue;
int parent[maxn], dist[maxn], queryType[maxn], queryNode[maxn];
int genNextRandom() {
	curValue = (curValue * 1999 + 17) % 1000003;
	return curValue;
}

void generateInput() {
	for (int i = 0; i < N-1; i++) {
		dist[i] = genNextRandom() % maxDist;
		parent[i] = genNextRandom();
		if (parent[i] < threshold) {
			parent[i] = i;
		} else {
			parent[i] = parent[i] % (i + 1);
		}
	}

	for (int i = 0; i < Q; i++) {
		queryType[i] = genNextRandom() % 2 + 1;
		queryNode[i] = genNextRandom() % N;
	}
}

#define KKK 220000

int log222[KKK];

struct LCA_RMQ{
	Vector<int> *adj;
	//***********以上需要外部赋值********
	void LCA(int N, int root=0){//0~N-1,进行lca预处理
		fill(dep, dep+N, -1); //未访问
		sid=0; _dfs(root); 
		_rmq(N*2-1);
	}
	void _dfs(int root){ //模拟递归， 生成_dfs序列
		dep[root]=0;
		ver.push(root);
		ind.push(0);
		while(!ver.empty()){
			int u=ver.top(), &p=ind.top(); 
			pos[u]=sid;
			seq[sid++]=u;
repeat:;
			if( p<adj[u].size() ){
				int v=adj[u][p++];
				if( dep[v]>=0 ) goto repeat;
				dep[v]=dep[u]+1;
				ver.push( v );
				ind.push( 0 );
			}else{
				ver.pop();
				ind.pop();
			}
		}
	}
	void _rmq(int len){
		int M=_get(len);
		for(int i=0;i<len;i++) mi[i][0]=seq[i];
		for(int g=1;g<=M;g++){
			int L=len-(1<<g);
			for(int i=0;i<=L;i++){
				mi[i][g]= dep[ mi[i][g-1] ]<dep[ mi[i+(1<<(g-1))][g-1] ] ?
					mi[i][g-1]:mi[i+(1<<(g-1))][g-1];//888888888
			}
		}
	}
	int _get(int L){//查询太多， 需要预处理
		return log222[L];
	}
	int query(int a,int b){//询问a和b的lca,返回编号
		if( pos[a]>pos[b] ) swap(a, b);
		int wa=pos[a], wb=pos[b];
		int g=_get(wb-wa+1);
		return dep[ mi[wa][g] ]<dep[ mi[wb-(1<<(g))+1][g] ] ? 
			mi[wa][g]:mi[wb-(1<<(g))+1][g];//****和上面不一样的
	}
	int dep[maxn]; //每个节点的_dfs深度
	int seq[2*maxn], sid;//seq存节点，长度为2*N-1
	int mi[maxn*2][20];//比较的是dep[ seq[i] ]
	int pos[maxn];//节点i在seq里的最后一个位置
	stack<int> ver, ind;
}lca_rmq;

Vector<int> adj[maxn];
Vector<int> vvv[maxn];
LL dep_dis[maxn];

void dfs_1(int u, LL value, int fa) {
	dep_dis[u] = value;
	rep(i, 0, sz(adj[u])) {
		int v = adj[u][i];
		if(v==fa) continue;
		dfs_1(v, value + vvv[u][i], u);
	}
}
bool isblue[maxn];
vector<int> blue_buf;
LL sum[maxn], tmp_sum[maxn];
bool cb[maxn];
int num[maxn];
void dfs_num(int u, int fa) {
	num[u] = 0;
	if(cb[u]) num[u] ++;
	rep(i, 0, sz(adj[u])) {
		int v = adj[u][i];
		if(v==fa) continue;
		dfs_num(v, u);
		num[u] += num[v];
	}
}

void dfs_cal(int u, int fa, LL S) {
	tmp_sum[u] = S;
	rep(i, 0, sz(adj[u])) {
		int v = adj[u][i];
		if(v==fa) continue;
		dfs_cal(v, u, S-vvv[u][i]*(LL)num[v]+vvv[u][i]*(LL)(blue_buf.size()-num[v]));
	}
}

long long TreeColoring::color(int N, int Q, int startSeed, int threshold, int maxDist) {
	::N = N;
	::Q = Q;
	::maxDist = maxDist;
	::threshold = threshold;
	curValue = startSeed;

	rep(i, 1, KKK) log222[i] = (int)(log(i*1.0)/log(2.0));

	generateInput();

	rep(i, 0, N) {
		adj[i].clear();
		vvv[i].clear();
	}
	rep(i, 0, N-1) {
		adj[i+1].push_back(parent[i]);
		vvv[i+1].push_back(dist[i]);
		adj[parent[i]].push_back(i+1);
		vvv[parent[i]].push_back(dist[i]);
	}

	lca_rmq.adj = adj;
	lca_rmq.LCA(N, 0);

	dfs_1(0, 0, -1);

	LL ans = 0;
	clr(isblue, false);
	clr(sum, 0);
	blue_buf.clear();
	rep(q, 0, Q) {
		if(queryType[q]==1) {
			if(isblue[queryNode[q]]==false) {
				blue_buf.push_back(queryNode[q]);
				isblue[queryNode[q]] = true;
			}
		} else {
			int u = queryNode[q];
			LL tmp = sum[u];
			rep(i, 0, sz(blue_buf)) {
				int v = blue_buf[i];
				int lca = lca_rmq.query(u, v);
				if(lca == 0) {
					tmp += dep_dis[u] + dep_dis[v];
				} else {
					tmp += dep_dis[u] + dep_dis[v] - 2 * dep_dis[lca];
				}
			}
			ans ^= tmp;
			//if(N<20) cout<<tmp<<endl;
		}
		if(blue_buf.size() >= SQRT) {
			clr(cb, false);
			clr(num, 0);
			rep(i, 0, sz(blue_buf)) cb[blue_buf[i]] = true;
			LL S = 0;
			dfs_num(0, -1);
			rep(i, 0, N) if(cb[i]) S += dep_dis[i];
			dfs_cal(0, -1, S);
			rep(i, 0, N) sum[i] += tmp_sum[i];
			blue_buf.clear();
		}
	}
	return ans;
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
			int N                     = 4;
			int Q                     = 6;
			int startSeed             = 15;
			int threshold             = 2;
			int maxDist               = 5;
			long long expected__      = 7;

			clock_t start__           = clock();
			long long received__      = TreeColoring().color(N, Q, startSeed, threshold, maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 4;
			int Q                     = 5;
			int startSeed             = 2;
			int threshold             = 9;
			int maxDist               = 10;
			long long expected__      = 30;

			clock_t start__           = clock();
			long long received__      = TreeColoring().color(N, Q, startSeed, threshold, maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 8;
			int Q                     = 8;
			int startSeed             = 3;
			int threshold             = 5;
			int maxDist               = 7;
			long long expected__      = 6;

			clock_t start__           = clock();
			long long received__      = TreeColoring().color(N, Q, startSeed, threshold, maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 14750;
			int Q                     = 50;
			int startSeed             = 29750;
			int threshold             = 1157;
			int maxDist               = 21610;
			long long expected__      = 2537640;

			clock_t start__           = clock();
			long long received__      = TreeColoring().color(N, Q, startSeed, threshold, maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 99999;
			int Q                     = 99999;
			int startSeed             = 948616;
			int threshold             = 1;
			int maxDist               = 7;
			long long expected__      = 1111722LL;

			clock_t start__           = clock();
			long long received__      = TreeColoring().color(N, Q, startSeed, threshold, maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int N                     = 100000;
			int Q                     = 100000;
			int startSeed             = 654321;
			int threshold             = 1000003;
			int maxDist               = 1000003;
			long long expected__      = 562600687570528LL;

			clock_t start__           = clock();
			long long received__      = TreeColoring().color(N, Q, startSeed, threshold, maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int N                     = ;
			int Q                     = ;
			int startSeed             = ;
			int threshold             = ;
			int maxDist               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = TreeColoring().color(N, Q, startSeed, threshold, maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int Q                     = ;
			int startSeed             = ;
			int threshold             = ;
			int maxDist               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = TreeColoring().color(N, Q, startSeed, threshold, maxDist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int N                     = ;
			int Q                     = ;
			int startSeed             = ;
			int threshold             = ;
			int maxDist               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = TreeColoring().color(N, Q, startSeed, threshold, maxDist);
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
