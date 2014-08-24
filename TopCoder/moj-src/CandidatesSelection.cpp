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


class CandidatesSelection {
public:
	string possible(vector <string> score, vector <int> result);
};

VS sc;
VI res;

bool asc(int s, int t) {
	for(int i=s+1;i<=t;i++) if(res[i]<res[i-1]) return false;
	return true;
}

bool can(int s, int t, int col, vector<int> &ge) {
	//printf("s = %d, t = %d, col = %d\n", s, t, col);

	vector<int> v[26];
	ge.clear();
	for(int i=s;i<=t;i++) {
		v[sc[res[i]][col]-'A'].push_back(i);
	}
	int last = s-1;
	for(int x=0;x<26;x++) if(sz(v[x])) {
		int ma = 0, mi = 10000;
		for(int y=0;y<v[x].size();y++) {
			ma = max(ma, v[x][y]);
			mi = min(mi, v[x][y]);
		}
		if(mi != last + 1) return false;
		ge.push_back(ma);
		last = ma;
	}
	//rep(i, 0, sz(ge)) cout<<ge[i]<<' '; cout<<endl;
	return last == t;
}

string CandidatesSelection::possible(vector <string> score, vector <int> result) {
	sc = score;
	res = result;

	vector<int> ge;
	ge.push_back(sz(result)-1);
	bool find = false;
	int cnt = 0;
	while(true) {
		//cout<<sz(ge)<<' '<<cnt++<<endl;
		bool all = true;
		for(int i=0, j=0;i<ge.size();i++) {
			if(asc(j, ge[i])); else all = false;
			j = ge[i] + 1;
		}
		if(all) {
			find = true;
			break;
		}
		bool conti = false;
		for(int j=0;j<sc[0].length();j++) {
			bool all_can = true;
			vector<int> new_ge, tmp;
			for(int x=0, y=0;x<ge.size();x++) {
				if(can(y, ge[x], j, tmp)) {
					rep(b, 0, sz(tmp)) new_ge.push_back(tmp[b]);
				} else {
					all_can = false;
				}
				y = ge[x] + 1;
			}
			if(all_can && sz(new_ge)>sz(ge)) {
				ge = new_ge;
				conti = true;
				break;
			}
		}
		if(conti) continue;
		else break;
	}


	if(find) return "Possible";
	else return "Impossible";
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
			string score[]            = {"CC", "AA", "BB"};
			int result[]              = {1,2,0};
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = CandidatesSelection().possible(vector <string>(score, score + (sizeof score / sizeof score[0])), vector <int>(result, result + (sizeof result / sizeof result[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string score[]            = {"BAB", "ABB", "AAB", "ABA"};
			int result[]              = {2,0,1,3};
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = CandidatesSelection().possible(vector <string>(score, score + (sizeof score / sizeof score[0])), vector <int>(result, result + (sizeof result / sizeof result[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string score[]            = {"BAB", "ABB", "AAB", "ABA"};
			int result[]              = {0, 1, 3, 2};
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = CandidatesSelection().possible(vector <string>(score, score + (sizeof score / sizeof score[0])), vector <int>(result, result + (sizeof result / sizeof result[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string score[]            = {"AAA", "ZZZ"};
			int result[]              = {1, 0};
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = CandidatesSelection().possible(vector <string>(score, score + (sizeof score / sizeof score[0])), vector <int>(result, result + (sizeof result / sizeof result[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string score[]            = {"ZZZ", "AAA"};
			int result[]              = {0, 1};
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = CandidatesSelection().possible(vector <string>(score, score + (sizeof score / sizeof score[0])), vector <int>(result, result + (sizeof result / sizeof result[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string score[]            = {"ZYYYYX","YXZYXY","ZZZZXX","XZXYYX","ZZZYYZ","ZZXXYZ","ZYZZXZ","XZYYZX"};
			int result[]              = {3,7,1,0,2,5,6,4};
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = CandidatesSelection().possible(vector <string>(score, score + (sizeof score / sizeof score[0])), vector <int>(result, result + (sizeof result / sizeof result[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string score[]            = ;
			int result[]              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CandidatesSelection().possible(vector <string>(score, score + (sizeof score / sizeof score[0])), vector <int>(result, result + (sizeof result / sizeof result[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string score[]            = ;
			int result[]              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CandidatesSelection().possible(vector <string>(score, score + (sizeof score / sizeof score[0])), vector <int>(result, result + (sizeof result / sizeof result[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string score[]            = ;
			int result[]              = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CandidatesSelection().possible(vector <string>(score, score + (sizeof score / sizeof score[0])), vector <int>(result, result + (sizeof result / sizeof result[0])));
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
