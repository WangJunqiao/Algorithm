#include<iostream>
using namespace std;
//二维线段树 四分树  w=h=2^n
//两种操作,给x,y点增加一个数值,查询(x1,x2,y1,y2)矩形内的数字和
typedef long long int64;
#define maxn 510000
struct Node{
	int64 sum;
	int x1,x2,y1,y2;
	Node *lu,*ld,*ru,*rd;
	void init(int _x1,int _x2,int _y1,int _y2){
		x1=_x1,x2=_x2;
		y1=_y1,y2=_y2;
		lu=ld=ru=rd=NULL;
		sum=0;
	}
	void update(){
		sum=0;
		if( lu ) sum+=lu->sum;
		if( ld ) sum+=ld->sum;
		if( ru ) sum+=ru->sum;
		if( rd ) sum+=rd->sum;
	}
}dd[maxn],*root;
int e; //初始化为0
Node* _alloc(int x1,int x2,int y1,int y2){
	dd[e].init(x1,x2,y1,y2); return &dd[e++];
}
void insert(Node *p,int x,int y,int g){
	if( p->x1==p->x2 && p->y1==p->y2 ) {
		p->sum+=g;
		return;
	}
	int midx=(p->x1+p->x2)/2;
	int midy=(p->y1+p->y2)/2;
	if( x<=midx && y>midy ) {
		if( p->lu==NULL ) p->lu=_alloc(p->x1,midx,midy+1,p->y2);
		insert(p->lu,x,y,g);
	}else if( x<=midx && y<=midy ){
		if( p->ld==NULL ) p->ld=_alloc(p->x1,midx,p->y1,midy);
		insert(p->ld,x,y,g);
	}else if( x>midx && y>midy ){
		if( p->ru==NULL ) p->ru=_alloc(midx+1,p->x2,midy+1,p->y2);
		insert(p->ru,x,y,g);
	}else{
		if( p->rd==NULL ) p->rd=_alloc(midx+1,p->x2,p->y1,midy);
		insert(p->rd,x,y,g);
	}
	p->update();
}
int64 query(Node *p,int x1,int x2,int y1,int y2){
	if( p==NULL ) return 0;
	x1=max(x1,p->x1);
	y1=max(y1,p->y1);
	x2=min(x2,p->x2);
	y2=min(y2,p->y2);
	if( x1>x2 || y1>y2 ) return 0;

	if( x1==p->x1 && x2==p->x2 && y1==p->y1 && y2==p->y2 ) return p->sum;
	return query(p->lu,x1,x2,y1,y2) + query(p->ld,x1,x2,y1,y2)+
		   query(p->ru,x1,x2,y1,y2) + query(p->rd,x1,x2,y1,y2);
}
int main(){
	char buf[222];
	bool ins=false;
	while( gets(buf) ){
		if( buf[0]=='E' ) break;
		if( buf[0]=='I' ){
			e=0;
			dd[e].init(1,32768,1,32768); //32768=2^31
			root=&dd[e++];
			ins=true; continue;
		}
		if( buf[0]=='Q' ){
			ins=false; continue;
		}
		if( ins ) {
			int x,y,g;
			sscanf(buf,"%d %d %d",&x,&y,&g);
			insert(root,x,y,g);
		}else{
			int x1,x2,y1,y2;
			sscanf(buf,"%d %d %d %d",&x1,&x2,&y1,&y2);
			printf("%lld\n",query(root,x1,x2,y1,y2));
		}
	}
}