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


class InverseRMQ {
public:
	string possible(int n, vector <int> A, vector <int> B, vector <int> ans);
};

struct DD{
	int A, B, ans;
	DD(int _a=0, int _b=0, int _ans=0) {
		A = _a;
		B = _b;
		ans = _ans;
	}
	bool operator<(const DD &b) const {
		return ans < b.ans;
	}
};

const string IMP = "Impossible";
const string PPP = "Possible";


vector<PII> pool;
void put(int A, int B) {
	pool.push_back(PII(A, B));
	while(true) {
		sort(all(pool));
		bool find = false;
		rep(i, 0, sz(pool)) rep(j, i+1, sz(pool)) {
			if(pool[i].second +1 >= pool[j].first) {
				int L = min(pool[i].first, pool[j].first);
				int R = max(pool[i].second, pool[j].second);
				pool.erase(pool.begin()+i);
				pool.erase(pool.begin()+i);
				pool.push_back(PII(L, R));
				find = true;
				goto end;
			}
		}
		end:;
		if(!find) break;
	}
}


string InverseRMQ::possible(int n, vector <int> A, vector <int> B, vector <int> ans) {
	vector<DD> v;
	rep(i, 0, sz(A)) {
		v.push_back(DD(A[i], B[i], ans[i]));
	}
	sort(all(v));
	pool.clear();
	//int last = 0;
	for(int x=0;x<sz(v);) {
		int y = x;
		while(y<sz(v) && v[y].ans == v[x].ans) y++;
		//[x, y)
		int L = v[x].A, R = v[x].B;
		//cout<<x<<' '<<y<<endl;
		rep(i, x, y) {
			L = max(L, v[i].A);
			R = min(R, v[i].B);
		}
		if(L>R) return IMP;

		rep(i, 0, sz(pool)) if(pool[i].first <= L && pool[i].second>=R) return IMP;
		int minL = v[x].A, maxR = v[x].B;
		rep(i, x, y) {
			minL = min(minL, v[i].A);
			maxR = max(maxR, v[i].B);
		}
		put(minL, maxR);
		int sum = 0;
		rep(i, 0, sz(pool)) sum += pool[i].second - pool[i].first + 1;
		if(sum > v[x].ans) return IMP;

		x = y;
	}
	return PPP;
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
			int n                     = 10;
			int A[]                   = {4,5,6};
			int B[]                   = {5,6,7};
			int ans[]                 = {6,7,5};
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = InverseRMQ().possible(n, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(ans, ans + (sizeof ans / sizeof ans[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 3;
			int A[]                   = {1,2,3};
			int B[]                   = {1,2,3};
			int ans[]                 = {3,3,3};
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = InverseRMQ().possible(n, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(ans, ans + (sizeof ans / sizeof ans[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 600;
			int A[]                   = {1,101,201,301,401,501};
			int B[]                   = {100,200,300,400,500,600};
			int ans[]                 = {100,200,300,400,500,600};
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = InverseRMQ().possible(n, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(ans, ans + (sizeof ans / sizeof ans[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 1000000000;
			int A[]                   = {1234,1234};
			int B[]                   = {5678,5678};
			int ans[]                 = {10000,20000};
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = InverseRMQ().possible(n, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(ans, ans + (sizeof ans / sizeof ans[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 8;
			int A[]                   = {1,2,3,4,5,6,7,8};
			int B[]                   = {1,2,3,4,5,6,7,8};
			int ans[]                 = {4,8,2,5,6,3,7,1};
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = InverseRMQ().possible(n, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(ans, ans + (sizeof ans / sizeof ans[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int n                     = 1000000000;
			int A[]                   = {1};
			int B[]                   = {1000000000};
			int ans[]                 = {19911120};
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = InverseRMQ().possible(n, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(ans, ans + (sizeof ans / sizeof ans[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int n                     = ;
			int A[]                   = ;
			int B[]                   = ;
			int ans[]                 = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = InverseRMQ().possible(n, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(ans, ans + (sizeof ans / sizeof ans[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int n                     = ;
			int A[]                   = ;
			int B[]                   = ;
			int ans[]                 = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = InverseRMQ().possible(n, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(ans, ans + (sizeof ans / sizeof ans[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int n                     = ;
			int A[]                   = ;
			int B[]                   = ;
			int ans[]                 = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = InverseRMQ().possible(n, vector <int>(A, A + (sizeof A / sizeof A[0])), vector <int>(B, B + (sizeof B / sizeof B[0])), vector <int>(ans, ans + (sizeof ans / sizeof ans[0])));
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
