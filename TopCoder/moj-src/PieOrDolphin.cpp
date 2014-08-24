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
#include <cassert>
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


class PieOrDolphin {
public:
	vector <int> Distribute(vector <int> choice1, vector <int> choice2);
};


//通过了 pku2135 pku3422 hdu3667 hdu 3376
//最小费用最大流 dd实现
#define maxn 10005
#define maxm 300005
#define inf 0x3fffffff
struct Edge{ int u,v,cap,cost,x; }E[maxm];
int e,l[maxn];
inline void init(){ e=0; memset(l,-1,sizeof(l)); }

int debug;
inline void insert(int u,int v,int cap,int cost){ //单向边
	if(debug) cout<<u<<' '<<v<<' '<<cap<<' '<<cost<<endl;
	E[e].u=u; E[e].v=v; E[e].cap=cap; E[e].cost= cost; E[e].x=l[u]; l[u]=e++;
	E[e].u=v; E[e].v=u; E[e].cap=0  ; E[e].cost=-cost; E[e].x=l[v]; l[v]=e++;
}
int q[20*maxn],s,t, inq[maxn], dis[maxn],eid[maxn];
void min_cost_max_flow(int src,int sink,int &cap,int &cost){//0~n-1
	cost=cap=0;
	while( true ){ //不断增广
		//begin spfa
		for(int i=0;i<maxn;i++) dis[i]=inf; //-inf  最大费
		s=t=0; q[t++]=src; inq[src]=1; dis[src]=0;
		while(s<t){
			int u=q[s++]; inq[u]=0;
			for(int p=l[u];p>=0;p=E[p].x){
				if( E[p].cap<=0 ) continue;
				int v=E[p].v;
				if( dis[v]>dis[u]+E[p].cost ){  //<
					dis[v]=dis[u]+E[p].cost; eid[v]=p;
					if( inq[v]==0 ){
						inq[v]=1; q[t++]=v;
					}
				}
			}
		} //end spfa
		if( dis[sink]>=inf ) return;  //<=-inf
		int c=inf;
		for(int i=sink;i!=src;i=E[eid[i]].u) c=min(c,E[eid[i]].cap);
		cost+=dis[sink]*c;  cap+=c;
		for(int i=sink;i!=src;i=E[eid[i]].u) {
			int p=eid[i];  E[p].cap-=c; E[p^1].cap+=c;
		}
	}
}//*****************模板结束*******************
// int main(){
// 	int n,m,u,v,cap,cost;
// 	while(scanf("%d%d",&n,&m)!=EOF ){
// 		init(); //初始化
// 		for(int i=1;i<=m;i++){
// 			scanf("%d %d %d %d",&u,&v,&cap,&cost);
// 			insert(u,v,cap,cost);
// 		}
// 		min_cost_max_flow(0,n-1,cap,cost);
// 		printf("capicity: %d cost: %d\n",cap,cost);
// 	}
// }


vector <int> PieOrDolphin::Distribute(vector <int> choice1, vector <int> choice2) {
	debug = choice1.size() <=6;
	init();
	int src = 50, sink = 51;
	int cnt[55] = {0};

	for(int i=0;i<choice1.size();i++){
		cnt[choice1[i]] ++;
		cnt[choice2[i]] ++;
	}
	for(int j=0;j<50;j++) {
		vector<int> tmp;
		for(int i=1;i<=cnt[j];i++){
			tmp.push_back(-2);
		}
		if(tmp.size()%2==1) tmp[tmp.size()/2] = 0;
		for(int i=(tmp.size()+1)/2;i<tmp.size();i++) tmp[i] *= -1;
		for(int i=0;i<tmp.size();i++) {
			insert(j, sink, 1, tmp[i]);
		}
	}
	int nid = 52;
	vector<int> eid;
	for(int i=0;i<choice1.size();i++) {
		insert(src, nid, 1, 0);
		insert(nid, choice1[i], 1, 0);
		eid.push_back(e-2);
		insert(nid, choice2[i], 1, 0);
		nid++;
	}
	int cap, cost;
	min_cost_max_flow(src, sink, cap, cost);
	cout<<"cap = "<<cap<<' '<<cost<<endl;
	assert(cap == choice1.size());
	vector<int> ret;
	for(int i=0;i<eid.size();i++) {
		if(E[eid[i]].cap == 0) ret.push_back(1);
		else ret.push_back(2);
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
	
	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, clock_t elapsed) { 
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
			int choice1[]             = {10, 20, 10};
			int choice2[]             = {20, 30, 20};
			int expected__[]          = {2, 2, 1 };

			clock_t start__           = clock();
			vector <int> received__   = PieOrDolphin().Distribute(vector <int>(choice1, choice1 + (sizeof choice1 / sizeof choice1[0])), vector <int>(choice2, choice2 + (sizeof choice2 / sizeof choice2[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int choice1[]             = {0, 0};
			int choice2[]             = {1, 1};
			int expected__[]          = {2, 1 };

			clock_t start__           = clock();
			vector <int> received__   = PieOrDolphin().Distribute(vector <int>(choice1, choice1 + (sizeof choice1 / sizeof choice1[0])), vector <int>(choice2, choice2 + (sizeof choice2 / sizeof choice2[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int choice1[]             = {0, 1, 2, 3, 5, 6, 7, 8};
			int choice2[]             = {8, 7, 6, 5, 3, 2, 1, 0};
			int expected__[]          = {2, 2, 2, 2, 2, 2, 2, 2 };

			clock_t start__           = clock();
			vector <int> received__   = PieOrDolphin().Distribute(vector <int>(choice1, choice1 + (sizeof choice1 / sizeof choice1[0])), vector <int>(choice2, choice2 + (sizeof choice2 / sizeof choice2[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int choice1[]             = {49, 0, 48, 1};
			int choice2[]             = {3, 4, 5, 6};
			int expected__[]          = {2, 2, 2, 2 };

			clock_t start__           = clock();
			vector <int> received__   = PieOrDolphin().Distribute(vector <int>(choice1, choice1 + (sizeof choice1 / sizeof choice1[0])), vector <int>(choice2, choice2 + (sizeof choice2 / sizeof choice2[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int choice1[]             = {21,4,14,0,31,46,1,34,2,3,27,19,47,46,17,11,41,12,31,0,34,18,8,14,23,40,0,18,48,35,42,24,25,32,25,44,17,6,44,34,12,39,43,39,26, 34,10,6,13,2,40,15,16,32,32,29,1,23,8,10,49,22,10,15,40,20,0,30,1,43,33,42,28,39,28,4,38,11,5,1,47,12,0,22,20,33,33,34,18,8,23,6};
			int choice2[]             = {25,5,39,20,44,47,11,49,42,17,25,15,23,11,32,17,24,4,11,47,27,41,40,0,49,27,5,28,6,11,18,0,17,1,0,32,45,28,17,5,13,40,40,25,33, 7,8,32,12,0,39,30,8,39,23,9,8,34,34,37,5,1,24,23,0,29,11,42,29,40,24,18,37,1,21,0,31,47,23,33,45,48,31,11,40,45,24,22,19,26,37,39};
			int expected__[]          = {2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 1, 2, 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1 };

			clock_t start__           = clock();
			vector <int> received__   = PieOrDolphin().Distribute(vector <int>(choice1, choice1 + (sizeof choice1 / sizeof choice1[0])), vector <int>(choice2, choice2 + (sizeof choice2 / sizeof choice2[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int choice1[]             = ;
			int choice2[]             = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = PieOrDolphin().Distribute(vector <int>(choice1, choice1 + (sizeof choice1 / sizeof choice1[0])), vector <int>(choice2, choice2 + (sizeof choice2 / sizeof choice2[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			int choice1[]             = ;
			int choice2[]             = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = PieOrDolphin().Distribute(vector <int>(choice1, choice1 + (sizeof choice1 / sizeof choice1[0])), vector <int>(choice2, choice2 + (sizeof choice2 / sizeof choice2[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			int choice1[]             = ;
			int choice2[]             = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = PieOrDolphin().Distribute(vector <int>(choice1, choice1 + (sizeof choice1 / sizeof choice1[0])), vector <int>(choice2, choice2 + (sizeof choice2 / sizeof choice2[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
