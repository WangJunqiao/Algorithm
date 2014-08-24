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


class StringsNightmareAgain {
public:
	long long UniqueSubstrings(int a, int b, int c, int d, int n);
};

#define maxn 210000

//用法: 1,赋值data(base1). 2,赋值n(串长). 3,make_SA(). 4,make_H().
char data[maxn];
//SA是后缀数组,SA[i]表示排第i位的后缀是谁
//rnk是排名数组,rnk[i]表示后缀i排第几
//H是高度数组,H[i]为SA[i]和SA[i-1]的LCP,故从2开始
int SA[maxn],rnk[maxn],H[maxn],n;  //n字符串长度
#define getR(a)((a)>n?0:rnk[a])
inline bool cmp(int a,int b){ return data[a] < data[b]; }
int c[maxn],a[maxn],_SA[maxn],_rnk[maxn],_h[maxn],L;
void Double(){
	memset(c,0,sizeof(int) * (n + 1));int i;
	for (i=1;i<=n;i++) c[getR(i + L)]++;
	a[0] = 1;for (i=1;i<=n;i++) a[i] = a[i - 1] + c[i - 1];
	for (i=1;i<=n;i++) _SA[a[getR(i + L)]++] = i;
	memset(c,0,sizeof(int) * (n + 1));
	for (i=1;i<=n;i++) c[getR(i)]++;
	a[0] = 1;for (i=1;i<=n;i++) a[i] = a[i - 1] + c[i - 1];
	for (i=1;i<=n;i++) SA[a[getR(_SA[i])]++] = _SA[i];
	_rnk[SA[1]] = 1;
	for (i=2;i<=n;i++) 
		if (getR(SA[i]) == getR(SA[i - 1]) && getR(SA[i] + L) == getR(SA[i - 1] + L)) 
			_rnk[SA[i]] = _rnk[SA[i - 1]];
		else
			_rnk[SA[i]] = _rnk[SA[i - 1]] + 1;
	memcpy(rnk,_rnk,sizeof(int) * (n + 1));
	L <<= 1;
}
void make_SA(){ //跟字符串值大小无关的!!
	int i;
	for (i=1;i<=n;i++) SA[i] = i;
	sort(SA + 1,SA + n + 1,cmp);rnk[SA[1]] = 1;
	for (i=2;i<=n;i++) 
		if (data[SA[i]] == data[SA[i - 1]]) rnk[SA[i]] = rnk[SA[i - 1]]; 
		else rnk[SA[i]] = rnk[SA[i - 1]] + 1;
		L = 1; while (L < n) Double();
}
void make_H(){
	int i;
	memset(_h,0,sizeof(int) * (n + 1));
	for (i=1;i<=n;i++) if (rnk[i] == 1) _h[i] = 0;
	else if (i == 1 || _h[i - 1] <= 1) 
		while (data[i + _h[i]] == data[SA[rnk[i] - 1] + _h[i]]) _h[i]++;
	else{
		_h[i] = _h[i - 1] - 1;
		while (data[i + _h[i]] == data[SA[rnk[i] - 1] + _h[i]]) _h[i]++;
	}
	for (i=1;i<=n;i++) H[rnk[i]] = _h[i];
}//*************模板结束***************


int ans[maxn];

long long StringsNightmareAgain::UniqueSubstrings(int a, int b, int c, int d, int n) {
	for(int i=1;i<=n;i++) data[i] = 'a';
	for (int i = 0; i < a; ++i){
		b = (b*(LL)c+d)%n;
		data[b+1] = 'b';
	}
	::n = n;
	make_SA();
	make_H();

	LL ret = 0;
	clr(ans, 0);
	set<int> st;
	stack<int> ss;
	ss.push(SA[1]);
	st.insert(SA[1]);

	for(int i=2;i<=n;i++) {
		
	}
	cout<<endl;
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
			int a                     = 0;
			int b                     = 0;
			int c                     = 0;
			int d                     = 0;
			int n                     = 4;
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = StringsNightmareAgain().UniqueSubstrings(a, b, c, d, n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a                     = 2;
			int b                     = 3;
			int c                     = 1;
			int d                     = 1;
			int n                     = 6;
			long long expected__      = 3;

			clock_t start__           = clock();
			long long received__      = StringsNightmareAgain().UniqueSubstrings(a, b, c, d, n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a                     = 4;
			int b                     = 3;
			int c                     = 1;
			int d                     = 1;
			int n                     = 6;
			long long expected__      = 3;

			clock_t start__           = clock();
			long long received__      = StringsNightmareAgain().UniqueSubstrings(a, b, c, d, n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a                     = 4;
			int b                     = 3;
			int c                     = 3;
			int d                     = 3;
			int n                     = 10;
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = StringsNightmareAgain().UniqueSubstrings(a, b, c, d, n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a                     = 5;
			int b                     = 3;
			int c                     = 2;
			int d                     = 3;
			int n                     = 11;
			long long expected__      = 9;

			clock_t start__           = clock();
			long long received__      = StringsNightmareAgain().UniqueSubstrings(a, b, c, d, n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int a                     = 10;
			int b                     = 1000000;
			int c                     = 1000000;
			int d                     = 1;
			int n                     = 51;
			long long expected__      = 63;

			clock_t start__           = clock();
			long long received__      = StringsNightmareAgain().UniqueSubstrings(a, b, c, d, n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int a                     = ;
			int b                     = ;
			int c                     = ;
			int d                     = ;
			int n                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = StringsNightmareAgain().UniqueSubstrings(a, b, c, d, n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a                     = ;
			int b                     = ;
			int c                     = ;
			int d                     = ;
			int n                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = StringsNightmareAgain().UniqueSubstrings(a, b, c, d, n);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int a                     = ;
			int b                     = ;
			int c                     = ;
			int d                     = ;
			int n                     = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = StringsNightmareAgain().UniqueSubstrings(a, b, c, d, n);
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
