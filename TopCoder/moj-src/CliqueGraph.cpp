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


class CliqueGraph {
public:
	long long calcSum(int N, vector <int> V, vector <int> sizes);
};


#define MAXN 10000
//dijkstra 
#define inf 0x3fffffff //最大值
typedef int ValueT;
typedef pair<int, ValueT> Edge;
vector<Edge> adj[MAXN];
ValueT dis[MAXN];

struct DD{
	int v;
	ValueT dis;
	DD(int _v=0, ValueT _dis=0):v(_v),dis(_dis){};
	bool operator<(const DD &b)const{
		return dis > b.dis;
	}
};
void dijkstra(int source){//源点为source
	for(int i=0;i<MAXN;i++) dis[i] = inf;
	priority_queue<DD> pq;
	dis[source]=0;
	pq.push(DD(source, 0));
	while(!pq.empty()){
		DD temp = pq.top();
		pq.pop();
		int u = temp.v;
		if(temp.dis > dis[u]) continue; //之前扩展过
		for(int p = 0;p < (int)adj[u].size();p++){
			int v = adj[u][p].first;
			if(dis[v] > dis[u] + adj[u][p].second){
				dis[v] = dis[u] + adj[u][p].second;
				pq.push(DD(v, dis[v]));
			}
		}
	}
}

void init(int n) {
	for(int i=0;i<=n;i++) {
		adj[i].clear();
	}
}

void addEdge(int u, int v, ValueT val) { //插入单向边
	adj[u].push_back(Edge(v, val));
}

long long CliqueGraph::calcSum(int N, vector <int> V, vector <int> sizes) {
	init(9000);
	int ID = N, sum = 0;
	rep(x, 0, sz(sizes)) {
		int nsum = sum + sizes[x];
		rep(i, sum, nsum) {
			addEdge(V[i], ID, 0);
			addEdge(ID, V[i], 1);
			//addEdge(V[i], ID, 1);
			//addEdge(ID, V[i], 1);
		}
		ID++;
		sum = nsum;
	}

	LL ret = 0;
	rep(s, 0, N) {
		dijkstra(s);
		rep(j, s+1, N) ret += dis[j];
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
			int V[]                   = {0,1,2,0,3};
			int sizes[]               = {3,2};
			long long expected__      = 8;

			clock_t start__           = clock();
			long long received__      = CliqueGraph().calcSum(N, vector <int>(V, V + (sizeof V / sizeof V[0])), vector <int>(sizes, sizes + (sizeof sizes / sizeof sizes[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 5;
			int V[]                   = {0,1,2,3,1,2,4};
			int sizes[]               = {4,3};
			long long expected__      = 12;

			clock_t start__           = clock();
			long long received__      = CliqueGraph().calcSum(N, vector <int>(V, V + (sizeof V / sizeof V[0])), vector <int>(sizes, sizes + (sizeof sizes / sizeof sizes[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 15;
			int V[]                   = {1,3,5,7,9,11,13,0 ,2,3,6,7,10,11,14,0 ,4,5,6,7,12,13,14,0 ,8,9,10,11,12,13,14,0};
			int sizes[]               = {8,8,8,8};
			long long expected__      = 130;

			clock_t start__           = clock();
			long long received__      = CliqueGraph().calcSum(N, vector <int>(V, V + (sizeof V / sizeof V[0])), vector <int>(sizes, sizes + (sizeof sizes / sizeof sizes[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 3: {
			int N                     = ;
			int V[]                   = ;
			int sizes[]               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = CliqueGraph().calcSum(N, vector <int>(V, V + (sizeof V / sizeof V[0])), vector <int>(sizes, sizes + (sizeof sizes / sizeof sizes[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 4: {
			int N                     = ;
			int V[]                   = ;
			int sizes[]               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = CliqueGraph().calcSum(N, vector <int>(V, V + (sizeof V / sizeof V[0])), vector <int>(sizes, sizes + (sizeof sizes / sizeof sizes[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int N                     = ;
			int V[]                   = ;
			int sizes[]               = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = CliqueGraph().calcSum(N, vector <int>(V, V + (sizeof V / sizeof V[0])), vector <int>(sizes, sizes + (sizeof sizes / sizeof sizes[0])));
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
