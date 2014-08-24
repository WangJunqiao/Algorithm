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
#define sz(X) ((int)(X.size()))
#define tr(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define all(x) x.begin(),x.end()
#define clr(x,c) memset(x,c,sizeof(x))
#define two(X) (1<<(X))
#define twoL(X) (((long long)(1))<<(X))
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




class SkiResorts {
public:
	long long minCost(vector <string> road, vector <int> altitude);
};

vector<int> H;
map<int, int> mp;

long long dis[55][55];
queue<int> q;
bool inq[55][55];


void update(int v, int h, long long d) {
	if(dis[v][h] > d) {
		dis[v][h] = d;
		if(!inq[v][h]) {
			q.push(v);
			q.push(h);
			//inq[v][h]=true;
		}
	}
}


long long SkiResorts::minCost(vector <string> road, vector <int> altitude) {
	set<int> st;
	rep(i, 0, sz(altitude)) st.insert(altitude[i]);
	for(set<int>::iterator it=st.begin();it!=st.end();++it) H.push_back(*it);
	sort(all(H));
	rep(i, 0, sz(H)) mp[H[i]] = i;

	int N = sz(road), M = sz(H);
	for(int i=0;i<N;i++) for(int j=0;j<M;j++) dis[i][j] = twoL(55);
	clr(inq, false);
	for(int i=mp[altitude[0]];i<M;i++) update(0, i, H[i]-altitude[0]);

	while(!q.empty()) {
		int v = q.front(); q.pop();
		int h= q.front(); q.pop();
		//inq[v][h]=false;
		for(int i=0;i<N;i++) if(road[v][i]=='Y'){
			for(int j=0;j<=h;j++) {
				update(i, j, dis[v][h]+abs(H[j]-altitude[i]));
			}
		}
	}
	long long mi = twoL(50);
	for(int i=0;i<M;i++) mi = min(mi, dis[N-1][i]);
	if(mi >= twoL(50))
		return -1;
	return mi;

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
			string road[]             = {"NYN",
 "YNY",
 "NYN"};
			int altitude[]            = {30, 20, 10};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string road[]             = {"NY",
 "YN"};
			int altitude[]            = {10, 20};
			long long expected__      = 10;

			clock_t start__           = clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string road[]             = {"NYN",
 "YNN",
 "NNN"};
			int altitude[]            = {573, 573, 573};
			long long expected__      = -1;

			clock_t start__           = clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string road[]             = {"NNYNNYYYNN",
 "NNNNYNYNNN",
 "YNNNNYYNNN",
 "NNNNNNYNYY",
 "NYNNNNNNYY",
 "YNYNNNNYNN",
 "YYYYNNNYNN",
 "YNNNNYYNNN",
 "NNNYYNNNNN",
 "NNNYYNNNNN"};
			int altitude[]            = {7, 4, 13, 2, 8, 1, 8, 15, 5, 15};
			long long expected__      = 12;

			clock_t start__           = clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string road[]             = ;
			int altitude[]            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string road[]             = ;
			int altitude[]            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string road[]             = ;
			int altitude[]            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
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
