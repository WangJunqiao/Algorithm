#include <iostream>
using namespace std;

#define maxn 110000
int v[maxn];
//�����߶���ģ��, zjut1708 n����,ÿ�ζ�[a,b]�������ͬʱ+val, ��ѯ[a,b]�ĺ�
typedef long long int64;
struct _Node{
	int64 add; //�ӳ���Ϣ(������Ϊ�·�,����������)
	int64 sum; //ͳ����Ϣ
	//
	int l,r; //boudd
	void init(int _l,int _r){
		l=_l, r=_r;  add=0;//��ʼ��ʱ,�ӳ���Ϣ������0
	}
	int len() { return r-l+1; }
	int mid() { return (l+r)>>1; }
}dd[maxn*5];
void push_down(int i){ //��֤�ж���
	int64 &add=dd[i].add;
	if( add==0 ) return;
	dd[i*2  ].add+=add;  dd[i*2  ].sum+=add*dd[i*2  ].len();  //push��ȥ��ʱ��,ͳ����ϢҲҪ����
	dd[i*2+1].add+=add;  dd[i*2+1].sum+=add*dd[i*2+1].len();
	add=0;   //ȥ��
}
void update(int i){ //��֤�ж���
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
//******ģ�����*******
int main(){
	int N,Q,Te=1;
	while( scanf("%d %d",&N,&Q)!=EOF ){
		for(int i=1;i<=N;i++) scanf("%d",v+i);
		makeTree(1,1,N);
		printf("case #%d:\n",Te++);
		for(int i=1;i<=Q;i++){
			char op; scanf(" %c",&op);
			int l,r,val; 
			if( op=='a' ){ //������Ӳ���
				scanf("%d %d %d",&l,&r,&val);
				modify(1,l,r,val);
			}else{   //�������
				scanf("%d %d",&l,&r);
				printf("%lld\n",query(1,l,r));
			}
		}
	}
}
