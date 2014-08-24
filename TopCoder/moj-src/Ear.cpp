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


class Ear {
public:
	long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY);
};
VI x, bx, by;

int cnt[11000];


struct point{
	int x,y;
	point(int _x=0, int _y=0){
		x=_x;
		y=_y;
	}
};

//º∆À„cross product (P1-P0)x(P2-P0)
double xmult(point p1,point p2,point p0){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

int id[330][330];

long long Ear::getCount(vector <string> redX, vector <string> blueX, vector <string> blueY) {
	string tmp;
	int val; 
	x.clear();
	bx.clear();
	by.clear();
	
	tmp=""; repv(i, redX) tmp+=redX[i]; istringstream sin(tmp); while( sin>>val ) x.PB(val);
	tmp=""; repv(i, blueX) tmp+=blueX[i]; istringstream bin(tmp); while( bin>>val ) bx.PB(val);
	tmp=""; repv(i, blueY) tmp+=blueY[i]; istringstream tin(tmp); while( tin>>val ) by.PB(val);
	
	sort(all(x));
	
	for(int P=0;P<sz(bx);P++){
		for(int Q=0;Q<sz(bx);Q++){
			id[P][Q]=sz(x);
			if( by[P]<=by[Q] ) continue;
			
			for(int D=0;D<sz(x);D++){
				if( x[D]<=bx[Q] || x[D]<=bx[P] ) continue;
				if( xmult(point(bx[Q], by[Q]), point(x[D], 0), point(bx[P], by[P]) ) > 0 ){
					id[P][Q]=D;
					break;
				}
			}
		}
	}
	LL ret = 0;
	for(int A=0;A<sz(x);A++){
		clr(cnt, 0);
		rep(i, A+1, sz(x)) cnt[x[i]]++;
		rep(i, x[A]+1, 10010) cnt[i]+=cnt[i-1];
		for(int P=0;P<sz(bx);P++){
			for(int Q=0;Q<sz(bx);Q++){
				if( xmult(point(bx[Q], by[Q]), point(bx[P], by[P]), point(x[A], 0) )<=0 ) continue;
				if( by[P]<=by[Q] ) continue;
				if( x[A]>=bx[P] ) continue;
				if( x[A]>=bx[Q] ) continue;
				
				int bN = cnt[bx[Q]-1];
				int cN = sz(x)-(A+1)-cnt[bx[Q]];
				int dN = sz(x)-id[P][Q];
				
			//	printf("bN = %d cN=%d dN=%d\n", bN, cN, dN);
				
				LL cd=0;
				if( dN<=0 || cN <=1 ) continue;
				if( cN == dN ){
					cd = cN * (cN-1)/2;
				}else{
					cd = (cN-dN)*dN + dN*(dN-1)/2;
				}
			//	printf("cd=%lld\n", cd);
				
				ret += cd * (LL)bN;
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
			string redX[]             = {"3 2 8 7"};
			string blueX[]            = {"5 4"};
			string blueY[]            = {"2 4"};
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string redX[]             = {"3 2 8 7"};
			string blueX[]            = {"2 8"};
			string blueY[]            = {"3 4"};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string redX[]             = {"1 2 6 9"};
			string blueX[]            = {"3 6 8 5"};
			string blueY[]            = {"1 5 4 3"};
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string redX[]             = {"10000"};
			string blueX[]            = {"10000 9999"};
			string blueY[]            = {"10000 9999"};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string redX[]             = {"100 2", "00", " 39", "9", " 800 900 9", "99"};
			string blueX[]            = {"15", "0 250 ", "349"};
			string blueY[]            = {"2 3 1"};
			long long expected__      = 12;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string redX[]             = {"1", " ", "2", " ", "3", " ", "4 5 6", " 7 8 9"};
			string blueX[]            = {"4", " ", "5", " ", "6", " 7 ", "8"};
			string blueY[]            = {"1", " 2 ", "3 4", " 5"};
			long long expected__      = 204;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string redX[]             = ;
			string blueX[]            = ;
			string blueY[]            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string redX[]             = ;
			string blueX[]            = ;
			string blueY[]            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string redX[]             = ;
			string blueX[]            = ;
			string blueY[]            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
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
