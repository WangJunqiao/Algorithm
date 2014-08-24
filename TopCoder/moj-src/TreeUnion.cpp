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


class TreeUnion {
public:
	double expectedCycles(vector <string> tree1, vector <string> tree2, int K);
};

#define maxn 310

int n;
int dis1[maxn][maxn], dis2[maxn][maxn];

void aaa(int dis[][maxn], vector<string> vs) {
	string s = "";
	rep(i, 0, sz(vs)) s += vs[i];
	VI v;
	istringstream sin(s);
	int x; 
	while(sin>>x) {
		v.push_back(x);
	}
	n = sz(v)+ 1;
	rep(i, 0, n) {
		rep(j, 0, n) dis[i][j] = 1000000;
		dis[i][i] = 0;
	}
	rep(i, 0, sz(v)) {
		dis[i+1][v[i]] = dis[v[i]][i+1] = 1;
	}
	rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
}

int num[maxn][maxn];

double TreeUnion::expectedCycles(vector <string> tree1, vector <string> tree2, int K) {
	aaa(dis1, tree1);
	aaa(dis2, tree2);
	clr(num, 0);
	rep(i, 0, n) {
		rep(j, 0, n) if(i!=j ) num[i][dis2[i][j]] ++;
	}
	double ret = 0.0;
	rep(x, 0, n) {
		rep(y, 0, n) if(x!=y) {
			if(dis1[x][y] >= K) continue;
			rep(z, 0, n) {
				int t = K-(dis1[x][y] + 2);
				if(t>0) ret += num[z][t] / (double)(n-1) / (double)n; 
			}
		}
	}
	return ret/2.0;
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
	
	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ(double expected, double result) { if (isnan(expected)) { return isnan(result); } else if (isinf(expected)) { if (expected > 0) { return result > 0 && isinf(result); } else { return result < 0 && isinf(result); } } else if (isnan(result) || isinf(result)) { return false; } else if (fabs(result - expected) < MAX_DOUBLE_ERROR) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }
	
	int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received); 
			if (rerr > 0) {
				sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			string tree1[]            = {"0"};
			string tree2[]            = {"0"};
			int K                     = 4;
			double expected__         = 1.0;

			clock_t start__           = clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string tree1[]            = {"0 1"};
			string tree2[]            = {"0 1"};
			int K                     = 4;
			double expected__         = 1.3333333333333333;

			clock_t start__           = clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string tree1[]            = {"0 1"};
			string tree2[]            = {"0 1"};
			int K                     = 6;
			double expected__         = 0.3333333333333333;

			clock_t start__           = clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string tree1[]            = {"0 ", "1 1 1"};
			string tree2[]            = {"0 1 0 ", "1"};
			int K                     = 5;
			double expected__         = 4.0;

			clock_t start__           = clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string tree1[]            = {"0 1 2 0 1 2 0 1 2 5 6 1", "0 11", " 4"};
			string tree2[]            = {"0 1 1 0 2 3 4 3 4 6 6", " 10 12 12"};
			int K                     = 7;
			double expected__         = 13.314285714285713;

			clock_t start__           = clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string tree1[]            = ;
			string tree2[]            = ;
			int K                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string tree1[]            = ;
			string tree2[]            = ;
			int K                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string tree1[]            = ;
			string tree2[]            = ;
			int K                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
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
