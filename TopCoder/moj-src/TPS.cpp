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


class TPS {
public:
	int minimalBeacons(vector <string> linked);
};


//dancing link
//�ظ��������� NUAA 1507
#include<iostream>
#define MAXR 55//row
#define MAXC 55*55//column
#define TOTAL (MAXR+1)*(MAXC+1)
using namespace std;

int n,m,mat[MAXR][MAXC];//��ʼ����0��1����1��1��ʼ��
int cid[TOTAL],rid[TOTAL],s[MAXC];//��ʾ�кţ��кţ�ÿ�е��ܸ���
int res[MAXR];//ÿ��ȡ������
int l[TOTAL],r[TOTAL],u[TOTAL],d[TOTAL];
int lastc[MAXC];//��i�е�������һ��Ԫ��

void remove(const int &col){//��һ����û�ˣ�������ͷ**********
	for(int i=d[col];i!=col;i=d[i]){
		r[l[i]]=r[i];
		l[r[i]]=l[i];
	}
}
void backtrack(const int &col){
	for(int i=u[col];i!=col;i=u[i]){
		r[l[i]]=i;
		l[r[i]]=i;
	}
}
inline void addlr(const int &ln,const int &rn){//���˺��ǳɻ���
	l[ r[ln] ]=rn; r[rn]=r[ln];
	r[ln]=rn;  l[rn]=ln;
}
inline void addud(const int &un,const int &dn){
	u[ d[un] ]=dn; d[dn]=d[un];
	d[un]=dn;  u[dn]=un;
}
//*********************************************************
bool visit[MAXC];
int H(){//���ۺ�������ʾҪ�ظ�����ȫ����������Ҫ����
	int res=0;
	memset(visit,false,sizeof(visit));
	for(int c=r[0];c!=0;c=r[c]){
		if(!visit[c]){
			res++;
			visit[c]=true;
			for(int i=d[c];i!=c;i=d[i])
				for(int j=r[i];j!=i;j=r[j])
					visit[cid[j]]=true;
		}
	}
	return res;
}
//******************************************************
int mi;
void search(int k,int sum){//����ʼ�ڼ�������,k�������������±�,sum�ǵ�ǰ�Ѿ����ٲ���
	if(sum+H()>=mi)
		return ;
	if(r[0]==0){
		mi=min(mi,sum);
		return;//�ҵ�һ���
	}
	int c,mi=1000000;
	for(int i=r[0];i!=0;i=r[i]){
		if(s[i]<mi){
			mi=s[i];
			c=i;
		}
	}
	for(int i=d[c];i!=c;i=d[i]){
		res[k]=rid[i];
		remove(i);
		for(int j=r[i];j!=i;j=r[j])
			remove(j);
		search(k+1,sum+1);
		for(int j=l[i];j!=i;j=l[j])
			backtrack(j);
		backtrack(i);
	}
}
/*
�������DLX�Ľ�ģģ�ͣ�0����Ϊ�˷����м��*��,���Ͻǵ��ǣ�0,0��
00000000
 *******
 *******
 *******
 *******
*/

void adapt(int n,int m){//����01����mat�Ĺ��,���亯������mat����dancing link ��
	memset(s,0,sizeof(s));//ÿ��Ԫ�ظ�����0
	l[0]=r[0]=0;   //��ͷ����(0,0)***********
	for(int i=1;i<=m;i++){ //�ܹ���m�У��ܱ�Ÿ��к���һ����****
		addlr(i-1,i);
		u[i]=d[i]=i;//�Գ�ѭ��
		lastc[i]=i; //������һ��Ԫ�غ���
	}
	int ind=m+1;//��m+1��ʼ��
	for(int i=1;i<=n;i++){
		bool isfirst=true;
		for(int j=1;j<=m;j++){
			if(mat[i][j]){
				if(isfirst){
					isfirst=false;
					l[ind]=r[ind]=ind;
				}else{
					addlr(ind-1,ind);
				}
				addud(lastc[j],ind);  lastc[j]=ind;
				cid[ind]=j; rid[ind]=i;
				s[j]++;  ind++;
			}
		}
	}
}
// int main(){
// 	int n,m;
// 	while(scanf("%d%d",&n,&m)!=EOF){
// 		int x,k;
// 		for(int i=1;i<=n;i++){
// 			scanf("%d",&x);
// 			for(int j=1;j<=x;j++)
// 				scanf("%d",&k),mat[i][k]=1;
// 		}
// 		adapt(n,m);
// 		mi=m;
// 		search(1,0);
// 		printf("%d\n",mi);
// 		memset(mat,0,sizeof(mat));
// 	}
// }

vector<int> adj[55];

void dfs(int u, int *dis, int d) {
	dis[u] = d;
	rep(i, 0, sz(adj[u])) {
		int v= adj[u][i];
		if(dis[v]>=0) continue;
		dfs(v, dis, d+1);
	}
}


int dis1[55], dis2[55];

int TPS::minimalBeacons(vector <string> linked) {
	int N = sz(linked);
	rep(i, 0, N) {
		adj[i].clear();
	}
	rep(i, 0, N) rep(j, 0, N) if(linked[i][j]=='Y') {
		adj[i].push_back(j);
	}
	clr(mat, 0);
	int n = N, m = 0;
	rep(i, 0, N) {
		clr(dis1, -1);
		dfs(i, dis1, 0);
		rep(j, i+1, N) {

			m++;
			clr(dis2, -1);
			dfs(j, dis2, 0);
			rep(x, 0, N) if(dis1[x] != dis2[x]) {
				mat[x+1][m] = 1;
			}
			
		}
	}

	cout<<n<<' '<<m<<endl;
	adapt(n, m);
	mi = n;
	search(1, 0);
	return mi;
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
			string linked[]           = {"NYNN",
 "YNYN",
 "NYNY",
 "NNYN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = TPS().minimalBeacons(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string linked[]           = {"NYYY",
 "YNNN",
 "YNNN",
 "YNNN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TPS().minimalBeacons(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string linked[]           = {"NNYNNNNNNN",
 "NNNNNYNNNN",
 "YNNYNNYNNN",
 "NNYNYNNYNN",
 "NNNYNYNNYN",
 "NYNNYNNNNY",
 "NNYNNNNNNN",
 "NNNYNNNNNN",
 "NNNNYNNNNN",
 "NNNNNYNNNN"}
;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = TPS().minimalBeacons(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string linked[]           = {"NYNYNNYNN",
 "YNYNYNNYN",
 "NYNNNYNNY",
 "YNNNNNNNN",
 "NYNNNNNNN",
 "NNYNNNNNN",
 "YNNNNNNNN",
 "NYNNNNNNN",
 "NNYNNNNNN"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = TPS().minimalBeacons(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string linked[]           = {"NYYYYYYYYY",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN"}
;
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = TPS().minimalBeacons(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string linked[]           = {"N"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = TPS().minimalBeacons(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string linked[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TPS().minimalBeacons(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string linked[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TPS().minimalBeacons(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string linked[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TPS().minimalBeacons(vector <string>(linked, linked + (sizeof linked / sizeof linked[0])));
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
