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


class NarrowPassage {
public:
	int minDist(int L, vector <int> a, vector <int> b);
};


int NarrowPassage::minDist(int L, vector <int> a, vector <int> b) {
	int ret = 1e9;
	vector<PII> v;
	rep(i, 0, sz(a)) {
		v.push_back(PII(a[i], b[i]));
	}
	sort(all(v));
	for(int i=0;i<v.size();i++) {
		bool can = true;
		rep(ni, 0, i) if(v[ni].second > v[i].second) can = false;
		rep(ni, i+1, v.size()) if(v[ni].second < v[i].second) can = false;
		if(can==false) continue;

		int tmp = abs(v[i].first - v[i].second);
		int ti;
		for(ti=i-1;ti>=0;ti--) {
			bool is = true;
			rep(x, 0, ti) if(v[x].second > v[ti].second) is = false;
			if(!is) break;
			tmp += abs(v[ti].first - v[ti].second);
		}
		while(ti>=0) {
			tmp += v[ti].first + v[ti].second;
			ti--;
		}

		for(ti=i+1;ti<sz(v);ti++) {
			bool is = true;
			rep(x, ti+1, sz(v)) if(v[x].second < v[ti].second) is = false;
			if(!is) break;
			tmp += abs(v[ti].first - v[ti].second);
		}
		while(ti<sz(v)) {
			tmp += abs(L-v[ti].first) + abs(L-v[ti].second);
			ti++;
		}

		ret = min(ret, tmp);
	}

	for(int x=0;x<sz(v);x++) { //first one
		for(int y=-1;y<sz(v);y++)  { //<=y to left
			int tmp = 0;
			if(x<=y) tmp = v[x].first + v[x].second;
			else tmp = 2*L - v[x].first - v[x].second;

			for(int i=0;i<sz(v);i++) if(i!=x) {
				if(v[i].second < v[x].second) {
					if(i<=y) tmp += v[i].first + v[i].second;
					else tmp += L - v[i].first + L + v[i].second;
				} else {
					if(i>y) tmp += 2*L - v[i].first - v[i].second;
					else tmp += v[i].first + L + L - v[i].second;
				}
			}
			ret = min(ret, tmp);
		}
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
			int L                     = 5;
			int a[]                   = {1, 2};
			int b[]                   = {3, 4};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = NarrowPassage().minDist(L, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 1: {
			int L                     = 10;
			int a[]                   = {3, 9};
			int b[]                   = {8, 6};
			int expected__            = 14;

			clock_t start__           = clock();
			int received__            = NarrowPassage().minDist(L, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 2: {
			int L                     = 265467;
			int a[]                   = {133548, 103861, 29821, 199848, 92684, 219824, 215859, 62821, 172409, 109235, 38563, 148854, 24742, 174068, 205005, 75922, 87316, 5542, 57484, 40792, 25229, 152216, 21547, 22203, 84712, 231522, 235703, 184895, 100787, 174440, 156904, 84898, 185568, 108732, 260098, 89488, 221604, 104555, 165775, 90444, 81952, 149671, 209674, 22185, 45420, 41928, 16098, 65324, 90870, 35243};
			int b[]                   = {150289, 135139, 69841, 227226, 177427, 230314, 199175, 81572, 220468, 151049, 40009, 145963, 115246, 252932, 263651, 38434, 120096, 69576, 29789, 115046, 33310, 260771, 5723, 80733, 107864, 142447, 235490, 242149, 124564, 134602, 245962, 7078, 215816, 219864, 190499, 210237, 212894, 142760, 126472, 201935, 119308, 120211, 235235, 19446, 87314, 17286, 61990, 102050, 261812, 257};
			int expected__            = 7148670;

			clock_t start__           = clock();
			int received__            = NarrowPassage().minDist(L, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 3: {
			int L                     = 1000000;
			int a[]                   = {706292, 756214, 490048, 228791, 567805, 353900, 640393, 562496, 217533, 934149, 938644, 127480, 777134, 999144, 41485, 544051, 417987, 767415, 971662, 959022, 670563, 34065, 518183, 750574, 546576, 207758, 159932, 429345, 670513, 271901, 476062, 392721, 774733, 502586, 915436, 120280, 951729, 699859, 581770, 268966, 79392, 888601, 378829, 350198, 939459, 644983, 605862, 721305, 269232, 137587};
			int b[]                   = {322468, 673534, 83223, 551733, 341310, 485064, 885415, 927526, 159402, 28144, 441619, 305530, 883149, 413745, 932694, 214862, 677401, 104356, 836580, 300580, 409942, 748444, 744205, 119051, 999286, 462508, 984346, 887773, 856655, 245559, 418763, 840266, 999775, 962927, 779570, 488394, 760591, 326325, 206948, 13999, 285467, 401562, 786209, 169847, 171326, 2901, 296531, 572035, 364920, 939046};
			int expected__            = 45670501;

			clock_t start__           = clock();
			int received__            = NarrowPassage().minDist(L, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}

				// custom cases

				/*      case 4: {
				int L                     = ;
				int a[]                   = ;
				int b[]                   = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = NarrowPassage().minDist(L, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
				}*/
				/*      case 5: {
				int L                     = ;
				int a[]                   = ;
				int b[]                   = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = NarrowPassage().minDist(L, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
				}*/
				/*      case 6: {
				int L                     = ;
				int a[]                   = ;
				int b[]                   = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = NarrowPassage().minDist(L, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
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
