//矩形面积并，复杂度n^3
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long int64;
#define maxn 1005
struct Rec{
	int x1,y1,x2,y2;
	bool operator<(const Rec &b)const{
		return (x2-x1)*(y2-y1) > (b.x2-b.x1)*(b.y2-b.y1);
	}
}r[maxn];
int n; int64 ans; //n base0
void dfs(int x1,int y1,int x2,int y2,int i){
	if( i==n || x1==x2 || y1==y2 ) return;
	int _x1=max(x1,r[i].x1);
	int _y1=max(y1,r[i].y1);
	int _x2=min(x2,r[i].x2);
	int _y2=min(y2,r[i].y2);
	if( _x1<_x2 && _y1<_y2 ){
		ans+=(_x2-_x1)*(int64)(_y2-_y1);
		dfs( x1, y1,_x1, y2,i+1);
		dfs(_x2, y1, x2, y2,i+1);
		dfs(_x1, y1,_x2,_y1,i+1);
		dfs(_x1,_y2,_x2, y2,i+1);
	}else{
		dfs(x1,y1,x2,y2,i+1);
	}
}
int64 calc_area(){ //矩形面积并，复杂度n^3
	sort(r,r+n); 
	int x1=1<<30,y1=x1,x2=-x1,y2=x2;
	for(int i=0;i<n;i++){
		x1=min(x1,r[i].x1);
		y1=min(y1,r[i].y1);
		x2=max(x2,r[i].x2);
		y2=max(y2,r[i].y2);
	}
	ans=0;
	dfs(x1,y1,x2,y2,0);
	return ans;
}//********************模板结束**************
int main(){
	while(cin>>n){
		for(int i=0;i<n;i++) cin>>r[i].x1>>r[i].y1>>r[i].x2>>r[i].y2;
		cout<<calc_area()<<endl;
	}
}

