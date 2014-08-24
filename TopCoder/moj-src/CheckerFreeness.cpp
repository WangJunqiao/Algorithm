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


class CheckerFreeness {
public:
	string isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY);
};


struct Point{
	LL x,y;
	Point(LL _x=0, LL _y=0){
		x=_x;
		y=_y;
	}
	Point operator-(const Point p)const{
		return Point(x-p.x, y-p.y);
	}
};

LL xmult(Point p0, Point p1){
	return p0.x*p1.y - p0.y*p1.x;
}
/*
//º∆À„cross product (P1-P0)x(P2-P0)
int xmult(Point p1,Point p2,Point p0){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}*/

vector<int> get(VS v){
	string s="";
	repv(i, v) s+=v[i];
	istringstream sin(s);
	VI ret;
	int t;
	while( sin>>t ){
		ret.PB(t);
	}
	return ret;
}

Point w[555], b[555], b1[555], b2[555];

Point pivot;

bool cmp(const Point p1, const Point p2){
	return xmult(p1-pivot, p2-pivot)<0;
}


string CheckerFreeness::isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY) {
	VI wX = get(whiteX);
	VI wY = get(whiteY);
	VI bX = get(blackX);
	VI bY = get(blackY);
	
	int n = sz(wX), m = sz(bX);
	rep(i, 0, n){
		w[i]=Point(wX[i], wY[i]);
	}
	rep(i, 0, m){
		b[i]=Point(bX[i], bY[i]);
	}
	
	for(int i=0;i<n;i++) {
		for(int j=i+1;j<n;j++){
			int t1=0, t2=0;
			for(int k=0;k<m;k++){	
				if( xmult(w[j]-w[i], b[k]-w[i]) > 0) b1[t1++] = b[k];
				else b2[t2++]=b[k];
			}
			if( t1==0 || t2==0 ) continue;
			
			vector<Point> v1, v2;
			
			pivot = w[i];
			sort(b1, b1+t1, cmp);
			v1.PB(b1[0]); 
			v1.PB(b1[t1-1]);
			
			pivot = w[j];
			sort(b1, b1+t1, cmp);
			v1.PB(b1[0]); 
			v1.PB(b1[t1-1]);
			
			
			//
			pivot = w[i];
			sort(b2, b2+t2, cmp);
			v2.PB(b2[0]); 
			v2.PB(b2[t2-1]);
			
			pivot = w[j];
			sort(b2, b2+t2, cmp);
			v2.PB(b2[0]); 
			v2.PB(b2[t2-1]);
			
			for(int x=0;x<sz(v1);x++){
				for(int y=0;y<sz(v2);y++) {
					Point p0 = v1[x], p1 = v2[y];
					int s1, s2;
					if( xmult(p1-p0, w[i]-p0) < 0 ) s1 = -1;
					else s1 = 1;
					
					if( xmult(p1-p0, w[j]-p0) < 0 ) s2 = -1;
					else s2 = 1;
					
					if( s1*s2 < 0 ) {
						//printf("%lld %lld\n", w[i].x, w[i].y);
						//printf("%lld %lld\n", w[j].x, w[j].y);
						//printf("%lld %lld\n", p0.x, p0.y);
						//printf("%lld %lld\n", p1.x, p1.y);
						return "NO";
					}
				}
			}
		}
	}
	return "YES";
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
			string whiteX[]           = {"1 2"};
			string whiteY[]           = {"2 1"};
			string blackX[]           = {"1 2"};
			string blackY[]           = {"1 2"};
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = CheckerFreeness().isFree(vector <string>(whiteX, whiteX + (sizeof whiteX / sizeof whiteX[0])), vector <string>(whiteY, whiteY + (sizeof whiteY / sizeof whiteY[0])), vector <string>(blackX, blackX + (sizeof blackX / sizeof blackX[0])), vector <string>(blackY, blackY + (sizeof blackY / sizeof blackY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string whiteX[]           = {"2", "5", "3", " ", "1", "7", "3"};
			string whiteY[]           = {"180 254"};
			string blackX[]           = {"32", "5 1", "42"};
			string blackY[]           = {"462 423"};
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = CheckerFreeness().isFree(vector <string>(whiteX, whiteX + (sizeof whiteX / sizeof whiteX[0])), vector <string>(whiteY, whiteY + (sizeof whiteY / sizeof whiteY[0])), vector <string>(blackX, blackX + (sizeof blackX / sizeof blackX[0])), vector <string>(blackY, blackY + (sizeof blackY / sizeof blackY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string whiteX[]           = {"1 10000000 9999999"};
			string whiteY[]           = {"1 9999999 1"};
			string blackX[]           = {"2 5000000 9999998"};
			string blackY[]           = {"2 5000001 9999999"};
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = CheckerFreeness().isFree(vector <string>(whiteX, whiteX + (sizeof whiteX / sizeof whiteX[0])), vector <string>(whiteY, whiteY + (sizeof whiteY / sizeof whiteY[0])), vector <string>(blackX, blackX + (sizeof blackX / sizeof blackX[0])), vector <string>(blackY, blackY + (sizeof blackY / sizeof blackY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string whiteX[]           = {"1"};
			string whiteY[]           = {"2"};
			string blackX[]           = {"3"};
			string blackY[]           = {"4"};
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = CheckerFreeness().isFree(vector <string>(whiteX, whiteX + (sizeof whiteX / sizeof whiteX[0])), vector <string>(whiteY, whiteY + (sizeof whiteY / sizeof whiteY[0])), vector <string>(blackX, blackX + (sizeof blackX / sizeof blackX[0])), vector <string>(blackY, blackY + (sizeof blackY / sizeof blackY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string whiteX[]           = {"6115 9723 3794 2275 2268 2702 3657 915 7953 2743 7"
,"716 9645 2547 9490 9365 326 6601 5215 6771 7153 72"
,"93 5922 714 2258 4369 9524 302 8417 6620 1143"};
			string whiteY[]           = {"621 1611 7140 503 5345 7202 681 4908 2510 5908 279"
,"6 6286 6873 6682 9197 6710 8517 1913 7784 8533 665"
,"4 446 3561 7241 6168 2025 4739 9501 5340 6446"};
			string blackX[]           = {"6833 131 4151 1776 1959 7210 1903 6107 598 6220 94"
,"24 5374 6718 2919 6068 6644 5070 710 7121 1630 370"
,"3 1051 5739 9294 8798 3371 8107 2130 6608 534"};
			string blackY[]           = {"7496 2412 2801 3473 5810 2714 7853 9714 5470 3558 "
,"8143 2391 8234 7292 9311 1636 8978 1107 2262 9175 "
,"7259 8842 5294 7209 2317 3825 3413 820 3774 5393"};
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = CheckerFreeness().isFree(vector <string>(whiteX, whiteX + (sizeof whiteX / sizeof whiteX[0])), vector <string>(whiteY, whiteY + (sizeof whiteY / sizeof whiteY[0])), vector <string>(blackX, blackX + (sizeof blackX / sizeof blackX[0])), vector <string>(blackY, blackY + (sizeof blackY / sizeof blackY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string whiteX[]           = {"219211 1996214 1706774 3634920 909831 1774128 8503"
,"52 2233050 2099138 3380396 1128982 3682525 1483700"
," 763080 487867 8203 1791027 463556 1103323 1406861"
," 6374234 760949 4340236 727393 2073832 1289052 103"
,"8147 4448130 151066 412440 1068735 377239 2677933 "
,"1299598 339843 289973 3707319 555280 230418 431719"};
			string whiteY[]           = {"1638083 5698739 3105504 9726902 9745795 5049444 15"
,"80592 3952120 6606668 7460527 7239299 8726128 4913"
,"547 6264100 5701660 8865937 4969114 8014845 327236"
,"1 6389154 9739755 2561669 9412417 5452337 3150506 "
,"5832197 1571976 8779325 3306446 948271 5133709 949"
,"394 6919798 7525636 3568024 6833196 9237472 733313"
,"1 9939064 9720014"};
			string blackX[]           = {"5860334 8007503 7455523 4864927 9573526 2718360 81"
,"12104 6684287 9921506 4840886 5415948 3451454 5320"
,"996 9268757 9261724 8254668 2292750 8035828 233352"
,"1 7676906 5234406 8533320 6562751 4884098 4971897 "
,"5569360 8519168 3100295 9351613 7733878 7579030 32"
,"46775 7297460 8370542 7099759 5782969 2978083 3390"
,"488 7482758 1332401 6094629 9717305 5503121 572842"
,"1 4903563 6331656 2867455 3410007 7751527 7228221 "
,"4111694 5171296 6847697 4601273 7599828 5515929 94"
,"60593 9332762 5389080 4512091 8668538 5711743 5838"
,"534 4825079 8145628 3810005 2964724 5594550 785748"
,"3 6283769"};
			string blackY[]           = {"5911694 8009943 212555 5838688 9896256 607434 5857"
,"663 4616750 1477573 7168026 3090917 4379806 326465"
,"7 4189076 2104028 3279691 94211 8503556 78457 4394"
,"360 3344176 3223317 2624498 4883494 1532240 732937"
,"1 1518674 1353567 892134 5536454 8527392 2603965 6"
,"623264 8830827 2030444 3002706 83058 4475866 20876"
,"25 1790695 4034441 5409379 3571098 4600050 736561 "
,"250475 3733256 3011439 2144994 4523046 3119883 607"
,"582 8361403 6525451 7518329 926803 4884524 8424659"
," 7088689 5762049 9532481 4914186 7314621 4339084 3"
,"741685 3837953 3177252 612550 9688871 5872931"};
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = CheckerFreeness().isFree(vector <string>(whiteX, whiteX + (sizeof whiteX / sizeof whiteX[0])), vector <string>(whiteY, whiteY + (sizeof whiteY / sizeof whiteY[0])), vector <string>(blackX, blackX + (sizeof blackX / sizeof blackX[0])), vector <string>(blackY, blackY + (sizeof blackY / sizeof blackY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string whiteX[]           = ;
			string whiteY[]           = ;
			string blackX[]           = ;
			string blackY[]           = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CheckerFreeness().isFree(vector <string>(whiteX, whiteX + (sizeof whiteX / sizeof whiteX[0])), vector <string>(whiteY, whiteY + (sizeof whiteY / sizeof whiteY[0])), vector <string>(blackX, blackX + (sizeof blackX / sizeof blackX[0])), vector <string>(blackY, blackY + (sizeof blackY / sizeof blackY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string whiteX[]           = ;
			string whiteY[]           = ;
			string blackX[]           = ;
			string blackY[]           = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CheckerFreeness().isFree(vector <string>(whiteX, whiteX + (sizeof whiteX / sizeof whiteX[0])), vector <string>(whiteY, whiteY + (sizeof whiteY / sizeof whiteY[0])), vector <string>(blackX, blackX + (sizeof blackX / sizeof blackX[0])), vector <string>(blackY, blackY + (sizeof blackY / sizeof blackY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string whiteX[]           = ;
			string whiteY[]           = ;
			string blackX[]           = ;
			string blackY[]           = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = CheckerFreeness().isFree(vector <string>(whiteX, whiteX + (sizeof whiteX / sizeof whiteX[0])), vector <string>(whiteY, whiteY + (sizeof whiteY / sizeof whiteY[0])), vector <string>(blackX, blackX + (sizeof blackX / sizeof blackX[0])), vector <string>(blackY, blackY + (sizeof blackY / sizeof blackY[0])));
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
