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


class AntOnGraph {
public:
	string maximumBonus(vector <string> p0, vector <string> p1, vector <string> p2, int stepsPerSecond, int timeLimit);
};



#define maxn 55
#define Type LL
const LL inf=1LL<<61;
struct Matrix{
	Type d[maxn][maxn]; int R,C;
	Matrix(int r=0,int c=0):R(r),C(c){ 
		rep(i, 0, r) rep(j, 0, c) {
			d[i][j]=-inf;
		}
		//rep(i, 0, r) d[i][i]=0;
	}
	Type* operator[](int i){ return d[i]; }
};


Matrix operator*(const Matrix &a,const Matrix &b){
	assert( a.C == b.R ); //
	Matrix r; r.R=a.R; r.C=b.C;
	for(int i=0;i<r.R;i++){
		for(int j=0;j<r.C;j++){
			Type tmp=-inf;
			for(int k=0;k<a.C;k++){
				tmp=max(tmp, a.d[i][k] + b.d[k][j]);
			}
			r.d[i][j]=tmp;
		}
	}
	return r;
}
Matrix operator^(Matrix &a,long long m){

//printf("m=%lld\n", m);
	assert(a.R==a.C);
	Matrix ret=a, A=a;
	m--;
	//for(int i=0;i<a.R;i++) ret[i][i]=0; //单位阵
	for(;m;m/=2) {
		if( m&1 ) ret=ret*A;
		A=A*A;
	}
	return ret;
}//-------------------模板结束-----------------------------------


void print(Matrix a){
	rep(i, 0, a.R){
		rep(j, 0, a.C) cout<<a[i][j]<<' ';
		cout<<endl;
	}
}

string AntOnGraph::maximumBonus(vector <string> p0, vector <string> p1, vector <string> p2, int steps, int timeLimit) {
	int n=sz(p0);
	Matrix mat(n, n);
	rep(i, 0, n) rep(j, 0, n){
		LL val=(p0[i][j]-'0')*100+(p1[i][j]-'0')*10+p2[i][j]-'0';
		val-=500;
		if( val==-500 ) val=-inf;
		mat[i][j]=max(mat[i][j], (LL)val);
	}
	
	LL ans=-inf;
	
	for(int i=1;i<=110 && i<=timeLimit;i++){
		Matrix tmp=mat^(i*steps);
		ans=max(ans, tmp[0][1]);
		//print(tmp);
	}
	for(int i=timeLimit-5;i<=timeLimit;i++){
		if( i<=0 ) continue;
		Matrix tmp=mat^(i*(LL)steps);
		ans=max(ans, tmp[0][1]);
		//print(tmp);
	}
	if( ans<=-inf/10 ) return "IMPOSSIBLE";
	char ch[555];
	sprintf(ch, "%lld", ans);
	return ch;
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
			string p0[]               = {"05","50"};
			string p1[]               = {"00","00"};
			string p2[]               = {"01","10"};
			int stepsPerSecond        = 3;
			int timeLimit             = 2;
			string expected__         = "3";

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus(vector <string>(p0, p0 + (sizeof p0 / sizeof p0[0])), vector <string>(p1, p1 + (sizeof p1 / sizeof p1[0])), vector <string>(p2, p2 + (sizeof p2 / sizeof p2[0])), stepsPerSecond, timeLimit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string p0[]               = {"05","50"};
			string p1[]               = {"00","00"};
			string p2[]               = {"01","10"};
			int stepsPerSecond        = 2;
			int timeLimit             = 3;
			string expected__         = "IMPOSSIBLE";

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus(vector <string>(p0, p0 + (sizeof p0 / sizeof p0[0])), vector <string>(p1, p1 + (sizeof p1 / sizeof p1[0])), vector <string>(p2, p2 + (sizeof p2 / sizeof p2[0])), stepsPerSecond, timeLimit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string p0[]               = {"0550","0000","0005","5000"};
			string p1[]               = {"0000","0000","0000","0000"};
			string p2[]               = {"0110","0000","0001","1000"};
			int stepsPerSecond        = 7;
			int timeLimit             = 9;
			string expected__         = "49";

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus(vector <string>(p0, p0 + (sizeof p0 / sizeof p0[0])), vector <string>(p1, p1 + (sizeof p1 / sizeof p1[0])), vector <string>(p2, p2 + (sizeof p2 / sizeof p2[0])), stepsPerSecond, timeLimit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string p0[]               = {"0540","0000","0004","4000"};
			string p1[]               = {"0090","0000","0009","9000"};
			string p2[]               = {"0190","0000","0009","9000"};
			int stepsPerSecond        = 7;
			int timeLimit             = 9;
			string expected__         = "-5";

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus(vector <string>(p0, p0 + (sizeof p0 / sizeof p0[0])), vector <string>(p1, p1 + (sizeof p1 / sizeof p1[0])), vector <string>(p2, p2 + (sizeof p2 / sizeof p2[0])), stepsPerSecond, timeLimit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string p0[]               = {"079269665406","506042219642","720809987956",
 "315099331918","952306192584","406390344278",
 "999241035142","370785209189","728363760165",
 "019367419000","279718007804","610188263490"};
			string p1[]               = {"038604914953","804585763146","350629473403",
 "028096403898","575205051686","427800322647",
 "655168017864","582553303278","980402170192",
 "620737714031","686142310509","092421645460"};
			string p2[]               = {"063231394554","109852259379","740182746422",
 "853015982521","476805512496","898530717993",
 "430534005863","440162807186","132879980431",
 "685312177072","780267345400","959947501200"};
			int stepsPerSecond        = 37;
			int timeLimit             = 1221;
			string expected__         = "20992235";

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus(vector <string>(p0, p0 + (sizeof p0 / sizeof p0[0])), vector <string>(p1, p1 + (sizeof p1 / sizeof p1[0])), vector <string>(p2, p2 + (sizeof p2 / sizeof p2[0])), stepsPerSecond, timeLimit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string p0[]               = ;
			string p1[]               = ;
			string p2[]               = ;
			int stepsPerSecond        = ;
			int timeLimit             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus(vector <string>(p0, p0 + (sizeof p0 / sizeof p0[0])), vector <string>(p1, p1 + (sizeof p1 / sizeof p1[0])), vector <string>(p2, p2 + (sizeof p2 / sizeof p2[0])), stepsPerSecond, timeLimit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string p0[]               = ;
			string p1[]               = ;
			string p2[]               = ;
			int stepsPerSecond        = ;
			int timeLimit             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus(vector <string>(p0, p0 + (sizeof p0 / sizeof p0[0])), vector <string>(p1, p1 + (sizeof p1 / sizeof p1[0])), vector <string>(p2, p2 + (sizeof p2 / sizeof p2[0])), stepsPerSecond, timeLimit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string p0[]               = ;
			string p1[]               = ;
			string p2[]               = ;
			int stepsPerSecond        = ;
			int timeLimit             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = AntOnGraph().maximumBonus(vector <string>(p0, p0 + (sizeof p0 / sizeof p0[0])), vector <string>(p1, p1 + (sizeof p1 / sizeof p1[0])), vector <string>(p2, p2 + (sizeof p2 / sizeof p2[0])), stepsPerSecond, timeLimit);
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
