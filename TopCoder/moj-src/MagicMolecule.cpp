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

//----------------------zjut_DD for Topcoder-------------------------------
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
#define PB push_back
#define MP make_pair
#define ff first
#define ss second
#define two(w) (1<<(w))
#define test(x,w) (x&two(w))
#define sz(v) (int)v.size()
#define all(c) c.begin(),c.end() 
#define clr(buf,val) memset(buf,val,sizeof(buf))
#define rep(i,l,r) for(int i=(l);i<(r);i++)
#define repv(i,v)  for(int i=0;i<(int)v.size();i++)
#define repi(it,c) for(typeof(c.begin()) it=c.begin();it!=c.end();++it)
//------------------------------------------------------------------------


class MagicMolecule {
public:
	int maxMagicPower( vector <int> magicPower, vector <string> magicBond );
	int maxMagicPower2( vector <int> magicPower, vector <string> magicBond );
};


VI mp;
VS mb;
int min_size;
int ret;
int sel[55];

void dfs(int cur_ans, int cur_num) {
	VI v;
	bool ss[55];
	clr(ss, true);
	rep(i, 0, sz(mp)) {
		if( sel[i]==1 ) {
			v.PB(i);
		}
	}
	repv(i, v) {
		for(int j=0;j<sz(mp);j++) if(v[i]!=j && mb[v[i]][j]=='N') {
			ss[j]=false;
		}
	}
	int max_num = 0;
	rep(i, 0, sz(mp)) if(ss[i]) max_num++;

	int maV = -1, id = -1;
	int max_ans = cur_ans;
	
	rep(i, 0, sz(mp))  if(sel[i]==-1) {
		bool can = true;
		for(int j=0;can && j<sz(v);j++) {
			if(mb[i][v[j]]=='N') can = false;
		}
		if( can && mp[i]>maV) {
			maV = mp[i];
			id = i;
		}
		if( can ) {
			max_ans += mp[i];
		}
	}
	//printf("id = %d\n", id);
	if(max_ans < ret) return;
	if(max_num < min_size ) return;
	if(id == -1) return;
	if(cur_num+1 >= min_size) {
		ret = max(ret, cur_ans+mp[id]);
	}
	sel[id]=1;
	dfs(cur_ans+mp[id], cur_num+1);
	sel[id]=0;
	dfs(cur_ans, cur_num);
	sel[id] = -1;
}

int MagicMolecule::maxMagicPower( vector <int> magicPower, vector <string> magicBond ) {
	mp = magicPower;
	mb = magicBond;
	for(min_size = 0;3*min_size<2*sz(mp);min_size++);
	printf("min_size = %d\n", min_size);
	clr(sel, -1);
	ret = -1;
	dfs(0, 0);
	return ret;

}



bool bad[55];
//VI mp;
//VS mb;
int ans;
void dfs_bad(int bad_num) {
	int n = sz(mp);
	if(3*(n-bad_num)<2*n) return;
	int u, v;
	for(u=0;u<n;u++) if(bad[u]==0) {
		for(v=u+1;v<n;v++) if(bad[v]==0) {
			if(mb[u][v]=='N') {
				bad[u]=1;
				dfs_bad(bad_num+1);
				bad[u]=0;
				bad[v]=1;
				dfs_bad(bad_num+1);
				bad[v]=0;
				return;
			}
		}
	}
	int tmp = 0;
	for(int i=0;i<n;i++) if(bad[i]==false) {
		tmp += mp[i];
	}
	ans = max(ans, tmp);
}
int MagicMolecule::maxMagicPower2( vector <int> magicPower, vector <string> magicBond ) {
	ans = -1;
	mp = magicPower;
	mb = magicBond;
	for(int i=0;i<(int)magicPower.size();i++)  bad[i] = 0;
	dfs_bad(0);
	return ans;
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
			int magicPower[]          = {1,2,3};
			string magicBond[]        = {"NYY","YNN","YNN"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 1: {
			int magicPower[]          = {1,1,1,1};
			string magicBond[]        = {"NNYY","NNYY","YYNN","YYNN"};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 2: {
			int magicPower[]          = {86,15,100,93,53,50};
			string magicBond[]        = {"NYYYYN","YNNNNY","YNNYYN","YNYNYN","YNYYNY","NYNNYN"};
			int expected__            = 332;

			clock_t start__           = clock();
			int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}
		case 3: {
			int magicPower[]          = {3969,9430,7242,8549,8190,8368,3704,9740,1691};
			string magicBond[]        = {"NYYYYYYYY","YNYYYYYYY","YYNYYYYYY","YYYNYYYYY","YYYYNYYYY","YYYYYNYYY","YYYYYYNNY","YYYYYYNNY","YYYYYYYYN"};
			int expected__            = 57179;

			clock_t start__           = clock();
			int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
				}

				// custom cases

				/*      case 4: {
				int magicPower[]          = ;
				string magicBond[]        = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
				}*/
				/*      case 5: {
				int magicPower[]          = ;
				string magicBond[]        = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
				}*/
				/*      case 6: {
				int magicPower[]          = ;
				string magicBond[]        = ;
				int expected__            = ;

				clock_t start__           = clock();
				int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
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
