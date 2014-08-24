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


class PerfectSquare {
public:
	int ways(vector <int> x);
};

#define maxm 500

int c[500*20][maxm];
int b[500*20];

//模2情况下, c[][] * x[] = b[]
//高斯法求秩,判断方程组是否有解,-1表示无解
int gauss(int n, int m, int c[][maxm], int *b){ //会改变c和b数组
	int zhi=0, k, i, j;
	for(i = 0, j = 0;i < n && j < m;){
		int cur=0;
		for(k = i;cur == 0 && k < n;k++) {
			if(c[k][j]) { cur=1; break; }
		}
		if( cur==0 ){ j++; continue; } //
		for(int jj = j;jj < m;jj++) swap(c[i][jj], c[k][jj]);
		swap(b[i], b[k]);
		for(k=i+1;k<n;k++){
			if(c[k][j]){
				for(int jj = j;jj < m;jj++)
					c[k][jj] ^= c[i][jj];
				b[k] ^= b[i];
			}
		}
		zhi++,i++,j++;
	}
	while(i<n) if(b[i++]) return -1;
	return zhi;
}


int sqr(int xx) {
	int x = sqrt(xx*1.0);
	if(x*x==xx) return x;
	if((x+1) * (x+1) == xx) return x + 1;
}

vector<int> di;

int PerfectSquare::ways(vector <int> x) {
	di.clear();
	di.push_back(1);
	for(int i=0;i<sz(x);i++){
		for(int j=1;j*j<=x[i];j++) {
			if(x[i]%j==0) {
				di.push_back(j);
				di.push_back(x[i]/j);
			}
		}
	}


	set<int> st(all(di));
	di = vector<int>(all(st));

	int K = sqr(sz(x));//K*K
	printf("K = %d\n", K);

	int n = sz(di) + 2*K;
	for(int i=0;i<n;i++) b[i] = 1;
	for(int i=0;i<sz(di);i++) b[i] = 0;

	clr(c, 0);

	for(int j=0;j<sz(x);j++) {
		for(int i=0;i<sz(di);i++) {
			if(di[i]==1) {
				continue;
			}
			int num = 0, tmp = x[j];
			while(tmp%di[i]==0) {
				num ++;
				tmp /= di[i];
			}

			if(num%2==1) {
				c[i][j] = 1;
			}
		}
		int s = j/K, t = j%K;
		c[sz(di)+s][j] = 1;
		c[sz(di)+K+t][j] = 1;
	}

	if(n<10) {
	for(int i=0;i<n;i++) {
		for(int j=0;j<sz(x);j++) {
			cout<<c[i][j]<<' ';
		}cout<<"    "<<b[i]<<endl;
	}
	}

	int ret = gauss(n, sz(x), c, b);
	if(ret == -1) return 0;
	int ttt = 1;
	for(int i=1;i<ret;i++) {
		ttt = ttt*2%1000000007;
	}
	return ttt;
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
			int x[]                   = {1, 1, 1, 2} ;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = PerfectSquare().ways(vector <int>(x, x + (sizeof x / sizeof x[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int x[]                   = {620, 620, 620, 620} ;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = PerfectSquare().ways(vector <int>(x, x + (sizeof x / sizeof x[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int x[]                   = {1, 2, 3, 4, 5, 6, 7, 8, 9};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = PerfectSquare().ways(vector <int>(x, x + (sizeof x / sizeof x[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int x[]                   = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = PerfectSquare().ways(vector <int>(x, x + (sizeof x / sizeof x[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int x[]                   = {2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13, 14,15,16,17};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = PerfectSquare().ways(vector <int>(x, x + (sizeof x / sizeof x[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int x[]                   = {9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690, 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690, 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690, 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690, 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690, 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690, 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690, 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690, 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690, 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690};
			int expected__            = 993282280;

			clock_t start__           = clock();
			int received__            = PerfectSquare().ways(vector <int>(x, x + (sizeof x / sizeof x[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int x[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PerfectSquare().ways(vector <int>(x, x + (sizeof x / sizeof x[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int x[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PerfectSquare().ways(vector <int>(x, x + (sizeof x / sizeof x[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int x[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PerfectSquare().ways(vector <int>(x, x + (sizeof x / sizeof x[0])));
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
