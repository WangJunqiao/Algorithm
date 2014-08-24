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


class FibonacciXor {
public:
	int find(long long A, long long B);
};
vector<LL> f;
const int mod = 1000000007;

int CC[88];

const int MAXN = 100000;

bitset<80> v[MAXN], ans;




int FibonacciXor::find(long long A, long long B) {
	f.clear();
	LL a = 0, b = 1;
	while(a<1e15) {
		LL c = a + b;
		f.push_back(c);
		a = b;
		b = c;
		//cout<<c<<' ';
	} //cout<<endl;

	CC[0] = 1;
	rep(i, 1, 78) CC[i] = CC[i-1] * 2 %mod;

	vector<int> vv;
	rep(i, 0, MAXN) vv.push_back(i);
	rep(i, 0, MAXN) v[i].reset();
	
	for(int i=f.size()-1;i>=0;i--) {
		rep(j, 0, MAXN) {
			if(vv[j]>=f[i]) {
				v[j].set(i, 1);
				vv[j] -= f[i];
			} else {

			}
		}
	}
	rep(i, 1, MAXN) v[i] ^= v[i-1];

	cout<<f[f.size()-1]<<endl;


	printf("size = %d\n", sz(f));


	vector<pair<LL, LL> > pairs;
	pairs.push_back(make_pair(A, B));
	ans.reset();
	while(true) {
		vector<pair<LL, LL> > tmp;
		rep(i, 0, sz(pairs) ) {
			if(pairs[i].second < MAXN) {
				ans ^= v[pairs[i].second];
				if(pairs[i].first) ans ^= v[pairs[i].first-1];
			} else {
				tmp.push_back(pairs[i]);
			}
		}
		pairs = tmp;
		if(pairs.size() == 0) break;

// 		bool tui = true;
// 		rep(i, 0, sz(pairs)) if(pairs[i].second) tui = false;
// 		if(tui) break;

		LL num = 0, x;
		tmp.clear();
		for(x=f.size()-1;x>=0;x--) {
			bool can = false;
			rep(i, 0, sz(pairs)) if(pairs[i].second >= f[x]) can = true;
			if(can) break;
		}
		cout<<x<<endl;

		rep(i, 0, sz(pairs)) {
			if(pairs[i].second >= f[x]) {
				if(pairs[i].first >= f[x]) {
					num += pairs[i].second - pairs[i].first + 1;
					tmp.push_back(make_pair(pairs[i].first-f[x], pairs[i].second-f[x]));
				} else {
					num += pairs[i].second - f[x] + 1;
					tmp.push_back(make_pair(0, pairs[i].second-f[x]));
					tmp.push_back(make_pair(pairs[i].first, f[x]-1));
				}
			} else {
				tmp.push_back(pairs[i]);
			}
		}
		if(num%2==1) {
			if(ans.test(x)) ans.set(x, 0);
			else ans.set(x, 1);
		}
// 		cout<<pairs.size()<<endl;
// 		pairs.clear();
// 		sort(all(tmp));
// 		for(int i=0;i<sz(tmp);) {
// 			int j = i;
// 			while(j<sz(tmp) && tmp[j]==tmp[i]) j++;
// 			if((j-i)%2==1) pairs.push_back(tmp[i]);
// 			i = j;
// 		}
// 		continue;

		vector<pair<LL, int> > ss;
		rep(i, 0, sz(tmp)) {
			ss.push_back(make_pair(tmp[i].first, 1));
			ss.push_back(make_pair(tmp[i].second+1, -1));
		}
		sort(all(ss));
		pairs.clear();
		

		LL cnt = 0;
		for(int i=0;i<ss.size();) {
			int j = i;
			while(j<ss.size() && ss[j].first == ss[i].first) {
				cnt += ss[j].second;
				j++;
			}
			if(cnt%2==1) {
				pairs.push_back(make_pair(ss[i].first, ss[j].first-1));
			}
			i = j;
		}
		cout<<pairs.size()<<endl;
		cout<<pairs[0].first << ' '<<pairs[0].second<<endl;
	}

	int ret = 0;
	rep(i, 0, 80) if(ans.test(i)) ret = (ret + CC[i]) % mod;
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
			long long A               = 1;
			long long B               = 2;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = FibonacciXor().find(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long A               = 3;
			long long B               = 10;
			int expected__            = 25;

			clock_t start__           = clock();
			int received__            = FibonacciXor().find(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long A               = 1LL;
			long long B               = 1000000000000000LL;
			int expected__            = 780431495;

			clock_t start__           = clock();
			int received__            = FibonacciXor().find(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 3: {
			long long A               = ;
			long long B               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FibonacciXor().find(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 4: {
			long long A               = ;
			long long B               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FibonacciXor().find(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			long long A               = ;
			long long B               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FibonacciXor().find(A, B);
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
