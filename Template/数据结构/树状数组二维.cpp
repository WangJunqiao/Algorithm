#define maxn 1010
#define maxm 1010
struct IndexArray2{
	int s[maxn][maxm],N,M;
	inline int lowbit(int t){ return t&(-t); }
	void init(int n,int m){
		N=n; M=m;
		for(int i=1;i<=n;i++) for(int j=0;j<=m;j++) s[i][j]=0;
	}
	int getsum(int r,int c){ //求和
		int ret=0;
		for(int tmp;r>=1;r-=lowbit(r)){
			for(tmp=c;tmp>=1;tmp-=lowbit(tmp))
				ret+=s[r][tmp];
		}
		return ret;
	}
	void update(int r,int c,int val){ //[r,c]增加val
		for(int tmp;r<=N;r+=lowbit(r)){
			for(tmp=c;tmp<=M;tmp+=lowbit(tmp))
				s[r][tmp]+=val;
		}
	}
}ins;//*****************