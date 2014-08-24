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


class MapGuessing {
public:
	long long countPatterns(string goal, vector <string> code);
};
int mm[2000], mi=1000, ma=1000, id=1000;

bool can(string g, int start ){
	for(int i=0;i<ma-mi+1;i++){
		if( start+i>=sz(g) ) return false;
		if( mm[mi+i]==-1 ) continue;
		if( g[start+i]-'0' == mm[mi+i] ) continue;
		else return false;
	}
	return true;
}

void moni(string c){
	mi=1000, ma=1000, id=1000;
	clr(mm, -1);
	repv(i, c){
		if( c[i]=='0' ) mm[id]=0;
		else if( c[i]=='1' ) mm[id]=1;
		else if( c[i]=='<' ) {
			id--;
			mi=min(mi, id);
		} else {
			id++;
			ma=max(ma, id);
		}
	}
}

long long MapGuessing::countPatterns(string goal, vector <string> code) {
	
	string c="";
	repv(i, code) c+=code[i];
	

	LL ret = 0;
	//if( ma-mi+1 > sz(goal) ) return 0;
	
	int vst[55];
	clr(vst, 0);
	bool first=true;
	for(int i=0;i<sz(goal);i++){
		for(int len=sz(c);len>=1;len--){
			moni(c.substr(0, len));
			if( can(goal, i) ){
				int num=0;
				for(int j=0;j<ma-mi+1;j++){
					if( mm[mi+j]==-1 ) continue;
					if( vst[i+j] ) continue;
					num++;
				}
				
				ret += (1LL<<num)-!first;
				first=false;
				for(int j=0;j<ma-mi+1;j++){
					if( mm[mi+j]==-1 ) continue;
					vst[i+j]=1;
				}
				//printf("i=%d  num=%d  ret=%lld\n", i, num, ret);
			}
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
				string goal               = "000";
				string code[]             = {"0"};
				long long expected__      = 4;

				clock_t start__           = clock();
				long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}
		case 1: {
				string goal               = "001";
				string code[]             = {"0>1"};
				long long expected__      = 5;

				clock_t start__           = clock();
				long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}
		case 2: {
				string goal               = "000";
				string code[]             = {"1>1>1"};
				long long expected__      = 1;

				clock_t start__           = clock();
				long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}
		case 3: {
				string goal               = "11001";
				string code[]             = {">><<<<><<"};
				long long expected__      = 0;

				clock_t start__           = clock();
				long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}
		case 4: {
				string goal               = "1000101011";
				string code[]             = {"1<<0>>0>1"};
				long long expected__      = 22;

				clock_t start__           = clock();
				long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}
		case 5: {
				string goal               = "00000010000000000000000000000000";
				string code[]             = {"><>>0<0<>>1>0><>", "<<0>>0<>><0>0>>><><", ">>>0<>", ">0><>>>>0<<><>>0>>>0<0>>0>"};
				long long expected__      = 13601;

				clock_t start__           = clock();
				long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}
		case 6: {
				string goal               = "11100011010111111010100100110001101";
				string code[]             = {"11111111111111111111"
					,"1<><><><><><><><><>1"
					,"1<>000>000><0<><0<>1"
					,"1<0<><>0><0<00>00<>1"
					,"1<>00<>000><0<0<0<>1"
					,"1<><>0>0><0<0<><0<>1"
					,"1<000<>0><0<0<><0<>1"
					,"1<><><><><><><><><>1"
					,"1<>000><000<>000><>1"
					,"1<>0><><0<><>0><><>1"
					,"1<>000><000<>000><>1"
					,"1<><>0><><0<><>0><>1"
					,"1<>000><000<>000><>1"
					,"1<><><><><><><><><>1"
					,"11111111111111111111"};
				long long expected__      = 90;

				clock_t start__           = clock();
				long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
				return verify_case(casenum__, expected__, received__, clock()-start__);
			}

			// custom cases

			/*      case 7: {
			string goal               = ;
			string code[]             = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
			/*      case 8: {
			string goal               = ;
			string code[]             = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
			/*      case 9: {
			string goal               = ;
			string code[]             = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
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
