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
#include <math.h>
#include <float.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <cassert>

using namespace std;

#define sz(X) ((int)(X.size()))
#define all(x) x.begin(),x.end()
#define clr(x,c) memset(x,c,sizeof(x))
#define rep(i,st,ed) for(int i=st;i<ed;i++)

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;
//--------------------------------------------


class TheSwapsDivOne {
public:
	double find(vector <string> sequence, int k);
};


//----------------------------矩阵--------------------------

#define maxn 11
typedef double Type;
struct Matrix{
	Type d[maxn][maxn]; int R,C;
	Matrix(int r=0,int c=0):R(r),C(c){ memset(d,0,sizeof(d)); }
	Type* operator[](int i){ return d[i]; }
};
Matrix operator*(const Matrix &a,const Matrix &b){
	//assert( a.C == b.R ); //
	Matrix r; r.R=a.R; r.C=b.C;
	for(int i=0;i<r.R;i++){
		for(int j=0;j<r.C;j++){
			Type tmp=0;
			for(int k=0;k<a.C;k++){
				if( a.d[i][k] && b.d[k][j] ) 
					tmp=(tmp+a.d[i][k] * b.d[k][j]);
			}
			r.d[i][j]=tmp;
		}
	}
	return r;
}
Matrix operator^(const Matrix &a,long long m){
	//assert(a.R==a.C);
	Matrix ret(a.R,a.C), A=a;
	for(int i=0;i<a.R;i++) ret[i][i]=1; //单位阵
	for(;m;m/=2) {
		if( m&1 ) ret=ret*A;
		A=A*A;
	}
	return ret;
}//-------------------模板结束-----------------------------------

vector<double> xx[22];

double TheSwapsDivOne::find(vector <string> sequence, int k) {
	string s = "";
	rep(i, 0, sz(sequence)) s += sequence[i];
	int num[22] = {0};
	rep(i, 0, sz(s)) num[s[i]-'0'] ++;

	int len = sz(s);
	double tot = len*(len-1)/2;


	for(int i=0;i<10;i++) {
		
		Matrix mat1(1, 10), mat2(10, 10);
		mat1[0][i] = 1.0;
		for(int x=0;x<10;x++) { //kai shi 
			for(int y=0;y<10;y++) {//hou lai
				if(x==y) {
					mat2[x][y] = ((len-1)*(len-2)/2 + num[x]-1) / tot;
				} else {
					mat2[x][y] = num[y] / tot;
				}
			}
		}
		mat1 = mat1*(mat2^k);

		xx[i].clear();
		rep(x, 0, 10) xx[i].push_back(mat1[0][x]);
// 
//  		rep(x, 0, 10) {
//  			printf("%lf ", xx[i][x]);
//  		}
//  		puts("");
	}

	double sum = 0.0;
	rep(i, 0, sz(s)) {
		double tmp = 0.0;
		int t = s[i]-'0';
		rep(j, 0, 10) tmp += xx[t][j] * j;
		//printf("tmp = %lf\n", tmp);
		sum += tmp * (i+1) * (len-i);
	}
	return sum/(len*(len+1)/2);
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
			string sequence[]         = {"4", "77"};
			int k                     = 1;
			double expected__         = 10.0;

			clock_t start__           = clock();
			double received__         = TheSwapsDivOne().find(vector <string>(sequence, sequence + (sizeof sequence / sizeof sequence[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string sequence[]         = {"4", "77"};
			int k                     = 47;
			double expected__         = 10.0;

			clock_t start__           = clock();
			double received__         = TheSwapsDivOne().find(vector <string>(sequence, sequence + (sizeof sequence / sizeof sequence[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string sequence[]         = {"1", "1", "1", "1", "1", "1", "1"};
			int k                     = 1000000;
			double expected__         = 3.0;

			clock_t start__           = clock();
			double received__         = TheSwapsDivOne().find(vector <string>(sequence, sequence + (sizeof sequence / sizeof sequence[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string sequence[]         = {"572685085149095989026478064633266980348504469", "19720257361", "9", "69"};
			int k                     = 7;
			double expected__         = 98.3238536775161;

			clock_t start__           = clock();
			double received__         = TheSwapsDivOne().find(vector <string>(sequence, sequence + (sizeof sequence / sizeof sequence[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string sequence[]         = ;
			int k                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheSwapsDivOne().find(vector <string>(sequence, sequence + (sizeof sequence / sizeof sequence[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string sequence[]         = ;
			int k                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheSwapsDivOne().find(vector <string>(sequence, sequence + (sizeof sequence / sizeof sequence[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string sequence[]         = ;
			int k                     = ;
			double expected__         = ;

			clock_t start__           = clock();
			double received__         = TheSwapsDivOne().find(vector <string>(sequence, sequence + (sizeof sequence / sizeof sequence[0])), k);
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
