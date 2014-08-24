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


class CrossingTheRiver {
public:
	string isItEvenPossible(int waterWidth, int landWidth, vector <int> blockHeight, int depth);
};

short dp[52][52][102][102];



string CrossingTheRiver::isItEvenPossible(int waterWidth, int landWidth, vector <int> blocks, int depth) {
	int num=0;
	//cout<<"555"<<endl;
	repv(i, blocks) if( blocks[i]==depth ) num++;
	if( num>=waterWidth ) return "POSSIBLE";
	
	set<int> st;
	repv(i, blocks) st.insert(blocks[i]);
	//cout<<"hhel"<<endl;
	sort(all(blocks));
	for(int mid=1;mid+depth<=100;mid++){
		if( st.find(mid+depth) == st.end() ) continue;
		int num0=0, num1=0;
		repv(i, blocks) {
			if( blocks[i]>=mid ) num1++;
			if( blocks[i]<=mid+depth ) num0++;
		}
		if( num0<waterWidth ) continue;
		if( num1<landWidth ) continue;
		clr(dp, -1);
		dp[0][0][0][mid]=0;
		repv(i, blocks){
			//cout<<i<<endl;
			int H=blocks[i];
			for(int j=0;j<=50;j++) {
				
				for(int k=0;k<=100-depth;k++){
					for(int x=0;x<=100;x++){
						dp[i+1][j][k][x]=max(dp[i+1][j][k][x], dp[i][j][k][x]);
						if( x>=0 && (H==x||H==x+1) && dp[i][j][k][x]>=0 ){
							dp[i+1][j][k][H]=max((int)dp[i+1][j][k][H], dp[i][j][k][x]+1);
						}
						if( j+1<=50 && (H-depth==k||H-depth==k+1) && H-depth>=0 && k>=0 && dp[i][j][k][x]>=0 ){
							dp[i+1][j+1][H-depth][x]=max(dp[i+1][j+1][H-depth][x], dp[i][j][k][x]);
						}
					}
				}
			}
			
		}
		int n=sz(blocks);
		for(int j=waterWidth;j<=50;j++) for(int x=0;x<=100;x++){
			if( dp[n][j][mid][x]>=landWidth ) {
				printf("mid=%d j=%d x=%d\n", mid, j, x);
				return "POSSIBLE";
			}
		}
	}
	return "IMPOSSIBLE";
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
			int waterWidth            = 3;
			int landWidth             = 3;
			int blockHeight[]         = {3,4,4,5,5, 6};
			int depth                 = 2;
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int waterWidth            = 3;
			int landWidth             = 3;
			int blockHeight[]         = {3,4,4,5,6, 6};
			int depth                 = 2;
			string expected__         = "IMPOSSIBLE";

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int waterWidth            = 5;
			int landWidth             = 2;
			int blockHeight[]         = {4,4,4,4,4};
			int depth                 = 4;
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int waterWidth            = 5;
			int landWidth             = 5;
			int blockHeight[]         = {5,5,5,5,5,5, 2,3,4,4,6, 7, 3, 2};
			int depth                 = 2;
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int waterWidth            = 5;
			int landWidth             = 7;
			int blockHeight[]         = {6,6,6,6,6,6,6, 6,6,6,6,6,7,8,9,10};
			int depth                 = 5;
			string expected__         = "POSSIBLE";

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int waterWidth            = 1;
			int landWidth             = 1;
			int blockHeight[]         = {5,3,4};
			int depth                 = 2;
			string expected__         = "IMPOSSIBLE";

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int waterWidth            = ;
			int landWidth             = ;
			int blockHeight[]         = ;
			int depth                 = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int waterWidth            = ;
			int landWidth             = ;
			int blockHeight[]         = ;
			int depth                 = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int waterWidth            = ;
			int landWidth             = ;
			int blockHeight[]         = ;
			int depth                 = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CrossingTheRiver().isItEvenPossible(waterWidth, landWidth, vector <int>(blockHeight, blockHeight + (sizeof blockHeight / sizeof blockHeight[0])), depth);
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
