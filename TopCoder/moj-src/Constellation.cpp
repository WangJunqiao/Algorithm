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


class Constellation {
public:
	double expectation(vector <int> x, vector <int> y, vector <int> prob);
};


struct Tri{
	int x, y;
	double pro;
	Tri(int _x=0, int _y=0, double _p=0) {
		x = _x;
		y = _y;
		pro = _p;
	}
	bool operator<(const Tri &b) const{
		if(x != b.x) return x < b.x;
		return y < b.y;
	}
};

double pro[55][55][55];
double are[55][55][55];

const double PI = acos(-1.0);

bool cmp(const pair<double, int> &a, const pair<double, int> &b) {
	double t1 = a.first;
	double t2 = b.first;
	if(t1 >= 3*PI/2) t1 -= 2*PI;
	if(t2 >= 3*PI/2) t2 -= 2*PI;
	return t1 < t2;
}

double xmult(double x1,double y1,double x2,double y2,double x0,double y0){
	return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0);
}

double Constellation::expectation(vector <int> x, vector <int> y, vector <int> prob) {
	vector<Tri> ps;
	int n = sz(x);
	rep(i, 0, n) ps.push_back(Tri(x[i], y[i], prob[i]/1000.0));
	sort(all(ps));
	clr(pro, 0);
	clr(are, 0);
	double p = 1.0;
	for(int i=0;i<n;i++) {
		pro[i][i][i] = p * ps[i].pro;
		are[i][i][i] = 0.0;
		p *= (1.0 - ps[i].pro);
	}
	double ret = 0.0;
	rep(i, 0, n) rep(sj, 0, n) rep(j, sj, n)  if(pro[i][sj][j]>0) {
		vector<pair<double, int> > v;
		rep(k, j+1, n) {
			double x = ps[k].x - ps[j].x;
			double y = ps[k].y - ps[j].y;
			v.push_back(make_pair(atan2(x, y), k));
		}
		sort(all(v), cmp);

		double p = 1.0;
		for(int k=0;k<sz(v);k++) {
			int id = v[k].second;
			double x0 = ps[j].x;
			double y0 = ps[j].y;
			double x1 = x0 + x0 - ps[sj].x;
			double y1 = y0 + y0 - ps[sj].y;
			double x2 = ps[id].x;
			double y2 = ps[id].y;
			if(xmult(x1, y1, x2, y2, x0, y0) >= 0) {
				printf("sj = %d, j = %d, id = %d\n", sj, j, id);
				pro[i][j][id] = pro[i][sj][j] * ps[id].pro * p;
				are[i][j][id] = are[i][sj][j] + xmult(x0, y0, x2, y2, 0, 0) / 2.0;

				p *= (1.0 - ps[id].pro);
			}
		}
		double ppp = pro[i][sj][j] * p;
		double aaa = are[i][sj][j] + xmult(ps[j].x, ps[j].y, ps[i].x, ps[i].y, 0, 0)/2.0;
		ret += abs(aaa) * ppp;
		//cout<<ppp<<endl;
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
	
	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ(double expected, double result) { if (isnan(expected)) { return isnan(result); } else if (isinf(expected)) { if (expected > 0) { return result > 0 && isinf(result); } else { return result < 0 && isinf(result); } } else if (isnan(result) || isinf(result)) { return false; } else if (fabs(result - expected) < MAX_DOUBLE_ERROR) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }
	
	int verify_case(int casenum, const double &expected, const double &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received); 
			if (rerr > 0) {
				sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int x[]                   = {0,0,1};
			int y[]                   = {0,1,0};
			int prob[]                = {500,500,500};
			double expected__         = 0.0625;

			clock_t start__           = clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int x[]                   = {0,1,0,1};
			int y[]                   = {0,0,1,1};
			int prob[]                = {1000,1000,400,800};
			double expected__         = 0.6000000000000001;

			clock_t start__           = clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int x[]                   = {-1,-1,-1,0,0,0,1,1,1};
			int y[]                   = {-1,0,1,-1,0,1,-1,0,1};
			int prob[]                = {500,500,500,500,500,500,500,500,500};
			double expected__         = 1.9375;

			clock_t start__           = clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int x[]                   = {0,0,1,2,2};
			int y[]                   = {0,1,2,1,0};
			int prob[]                = {1000,500,200,500,1000};
			double expected__         = 1.3;

			clock_t start__           = clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int x[]                   = {1,5,5,8,2,6,9};
			int y[]                   = {3,6,4,2,5,7,9};
			int prob[]                = {100,400,200,1000,400,900,600};
			double expected__         = 12.888936;

			clock_t start__           = clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int x[]                   = {-100,100,-100,100,-42,57,-34,76,35,-75,-54,10,43};
			int y[]                   = {-100,-100,100,100,52,-57,-84,63,-43,50,63,10,-44};
			int prob[]                = {1000,1000,1000,1000,342,747,897,325,678,34,53,6,253};
			double expected__         = 40000.0;

			clock_t start__           = clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int x[]                   = ;
			int y[]                   = ;
			int prob[]                = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int x[]                   = ;
			int y[]                   = ;
			int prob[]                = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int x[]                   = ;
			int y[]                   = ;
			int prob[]                = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
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
