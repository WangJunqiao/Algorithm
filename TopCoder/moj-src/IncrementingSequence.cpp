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


class IncrementingSequence {
public:
	string canItBeDone(int k, vector <int> A);
};


//************二分图最大匹配,邻接矩阵********
#define maxn 555
int nL,nR; //nL->nR   base1
int match[maxn]; //1~m
bool vst[maxn];
bool mat[maxn][maxn];

void init(){
	memset(match,-1,sizeof(match));
	memset(mat,false,sizeof(mat));
}
bool dfs(int u){ //匈牙利递归
	for(int v=1;v<=nR;v++){
		if(mat[u][v] && !vst[v]) {//vst保证只搜一次
			vst[v]=true;
			int tmp=match[v];
			match[v]=u;
			if(tmp==-1 || dfs(tmp))
				return true;
			match[v]=tmp;
		}
	}
	return false;
}
int mymax_match(){
	int ret=0;
	memset(match,-1,sizeof(match));
	for(int i=1;i<=nL;i++){
		memset(vst,false,sizeof(vst));
		if( dfs(i) ) ret++;
	}
	return ret;
}//***********以上模板**********


string IncrementingSequence::canItBeDone(int k, vector <int> A) {
	nL = nR = sz(A);
	clr(mat, false);
	for(int i=1;i<=nL;i++) {
		for(int j=1;j<=nR;j++) {
			if((j-A[i-1])>=0 && (j-A[i-1])%k==0) {
				mat[i][j] = true;
			}
		}
	}
	return mymax_match() == nL ? "POSSIBLE" : "IMPOSSIBLE";
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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int k                     = 3;
			int A[]                   = {1,2,4,3};
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = IncrementingSequence().canItBeDone(k, vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int k                     = 5;
			int A[]                   = {2,2};
			string expected__         = "IMPOSSIBLE";

			clock_t start__           = clock();
			string received__         = IncrementingSequence().canItBeDone(k, vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int k                     = 1;
			int A[]                   = {1,1,1,1,1,1,1,1};
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = IncrementingSequence().canItBeDone(k, vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int k                     = 2;
			int A[]                   = {5,3,3,2,1};
			string expected__         = "IMPOSSIBLE";

			clock_t start__           = clock();
			string received__         = IncrementingSequence().canItBeDone(k, vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int k                     = 9;
			int A[]                   = {1,2,3,1,4,5,6,7,9,8};
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = IncrementingSequence().canItBeDone(k, vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int k                     = 2;
			int A[]                   = {1,1,1,1,1,1,2,2,2,2,2,2};
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = IncrementingSequence().canItBeDone(k, vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int k                     = 1;
			int A[]                   = {1};
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = IncrementingSequence().canItBeDone(k, vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			int k                     = ;
			int A[]                   = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = IncrementingSequence().canItBeDone(k, vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int k                     = ;
			int A[]                   = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = IncrementingSequence().canItBeDone(k, vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int k                     = ;
			int A[]                   = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = IncrementingSequence().canItBeDone(k, vector <int>(A, A + (sizeof A / sizeof A[0])));
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
