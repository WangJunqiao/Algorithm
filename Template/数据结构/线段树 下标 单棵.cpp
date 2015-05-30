#include <iostream>
using namespace std;

#define maxn 110000
int v[maxn];
//单棵线段树模板, zjut1708 n个数,每次对[a,b]区间的数同时+val, 查询[a,b]的和
typedef long long int64;
struct _Node{
	int64 add; //延迟信息(作用域为下方,不包括自身)
	int64 sum; //统计信息
	//
	int l,r; //boudd
	void init(int _l,int _r){
		l=_l, r=_r;  add=0;//初始化时,延迟信息必须清0
	}
	int len() { return r-l+1; }
	int mid() { return (l+r)>>1; }
}dd[maxn*5];
void push_down(int i){ //保证有儿子
	int64 &add=dd[i].add;
	if( add==0 ) return;
	dd[i*2  ].add+=add;  dd[i*2  ].sum+=add*dd[i*2  ].len();  //push下去的时候,统计信息也要更新
	dd[i*2+1].add+=add;  dd[i*2+1].sum+=add*dd[i*2+1].len();
	add=0;   //去掉
}
void update(int i){ //保证有儿子
	dd[i].sum=dd[i*2].sum + dd[i*2+1].sum;
}
void makeTree(int i,int l,int r){ 
	dd[i].init(l,r);
	if( l==r ) { dd[i].sum=v[l]; return; }
	int mid=dd[i].mid();
	makeTree(i*2,l,mid);
	makeTree(i*2+1,mid+1,r);
	update(i);
}
void modify(int i,int l,int r,int val){
	if( dd[i].l==l && dd[i].r==r ){
		dd[i].add+=val; dd[i].sum+=(int64)val*dd[i].len();
		return;
	}
	push_down(i);
	int mid=dd[i].mid();
	if( r<=mid) modify(i*2,l,r,val);
	else if( l>mid ) modify(i*2+1,l,r,val);
	else {
		modify(i*2,l,mid,val);
		modify(i*2+1,mid+1,r,val);
	}
	update(i);
}
int64 query(int i,int l,int r){
	if( dd[i].l==l && dd[i].r==r ) return dd[i].sum;
	push_down(i);
	int mid=dd[i].mid();
	if( r<=mid ) return query(i*2,l,r);
	else if( l>mid ) return query(i*2+1,l,r);
	else return query(i*2,l,mid) + query(i*2+1,mid+1,r);
}
//******模板结束*******
int main(){
	int N,Q,Te=1;
	while( scanf("%d %d",&N,&Q)!=EOF ){
		for(int i=1;i<=N;i++) scanf("%d",v+i);
		makeTree(1,1,N);
		printf("case #%d:\n",Te++);
		for(int i=1;i<=Q;i++){
			char op; scanf(" %c",&op);
			int l,r,val; 
			if( op=='a' ){ //对区间加操作
				scanf("%d %d %d",&l,&r,&val);
				modify(1,l,r,val);
			}else{   //区间求和
				scanf("%d %d",&l,&r);
				printf("%lld\n",query(1,l,r));
			}
		}
	}
}
