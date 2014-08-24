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


class XorCards {
public:
	long long numberOfWays(vector<long long> number, long long limit);
};

#define  maxm 55
int c[55][55], b[55];

//模2情况下, c[][] * x[] = b[]
//高斯法求秩,判断方程组是否有解,-1表示无解
int gauss(int n,int m,int c[][maxm],int *b){ //会改变c和b数组
	int zhi=0,k,i,j;
	for(i=1,j=1;i<=n && j<=m;){
		int cur=0;
		for(k=i;cur==0 && k<=n;k++) {
			if(c[k][j]) { cur=1; break; }
		}
		if( cur==0 ){ j++; continue; } //
		for(int jj=j;jj<=m;jj++) swap(c[i][jj], c[k][jj]);
		swap(b[i],b[k]);
		for(k=i+1;k<=n;k++){
			if(c[k][j]){
				for(int jj=j;jj<=m;jj++)
					c[k][jj]^=c[i][jj];
				b[k]^=b[i];
			}
		}
		zhi++,i++,j++;
	}
	while(i<=n) if(b[i++]) return -1;
	return zhi;
}
const LL one = 1;
long long get(vector<long long> number, long long eq, int high_N) {
	int N = sz(number);
	for(int i=1;i<=high_N;i++) {
		for(int j=0;j<N;j++) {
			c[i][j+1] = number[j]&(one<<(51-i)) ? 1 : 0;
		}
		b[i] = eq & (one<<(51-i)) ? 1 : 0;
	}
	int zhi = gauss(high_N, N, c, b);
	if(zhi<0 ) return 0;
	return one<<(N - zhi);
}

long long XorCards::numberOfWays(vector<long long> number, long long limit) {
	LL ret = 0;
	for(int i=50;i>=0;i--) {
		if(limit & (one<<i)) {
			long long t = get(number, limit-(one<<i), 50-i+1);
			//printf("eq = %lld, high_N = %d, t = %lld\n", limit-(one<<i), 50-i+1, t);
			ret += t;
		}
	}
	ret += get(number, limit, 51);
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
			long long number[]        = {1, 2};
			long long limit           = 2;
			long long expected__      = 3;

			clock_t start__           = clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long number[]        = {5, 5};
			long long limit           = 3;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long number[]        = {1, 2, 3, 4, 5, 6, 7};
			long long limit           = 5;
			long long expected__      = 96;

			clock_t start__           = clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long number[]        = {123, 456, 789, 147, 258, 369, 159, 357};
			long long limit           = 500;
			long long expected__      = 125;

			clock_t start__           = clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long number[]        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			long long limit           = 1000000000000000LL;
			long long expected__      = 4294967296LL;

			clock_t start__           = clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			long long number[]        = {1000000000000000LL, 999999999999999LL};
			long long limit           = 65535;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			long long number[]        = ;
			long long limit           = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long number[]        = ;
			long long limit           = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			long long number[]        = ;
			long long limit           = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
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
