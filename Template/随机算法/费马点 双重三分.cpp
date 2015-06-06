#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
using namespace std;

//求多边形费马点 双重三分  (精度1e-4无压力)
const double PI=acos(-1.0);
const double eps=1e-7;
const double alf=0.45; //<0.5 !!! 0.49就接近二分了
int N=4; //N边形

struct P{
	double x,y;
	P(double _x=0,double _y=0):x(_x),y(_y){};
	double dis(const P &b)const{
		return sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
	}
}p[5555];

double all_dis(P a){
	double ret=0;
	for(int i=0;i<N;i++) ret+=a.dis(p[i]);
	return ret;
}

double miX,maX,miY,maY;//三分的范围,要初始化

double min_disX(double x,double &y){//x为定值,三分y
	double l=miY,r=maY, d1,d2;
	while( r-l>eps ){
		double y1=l+(r-l)*alf, y2=r-(r-l)*alf;
		d1=all_dis(P(x,y1)), d2=all_dis(P(x,y2));
		if( d1>d2 ) l=y1;
		else r=y2;
	}
	y=l;
	return all_dis(P(x,y));
}

double min_dis(double &x,double &y){//三分x
	double l=miX,r=maX, d1,d2;
	while( r-l>eps ){
		double x1=l+(r-l)*alf, x2=r-(r-l)*alf;
		d1=min_disX(x1,y), d2=min_disX(x2,y);
		if( d1>d2 ) l=x1;
		else r=x2;
	}
	x=l;
	return min_disX(x,y);
}

int main(){
	while( scanf("%d",&N)!=EOF ){
		miX=miY=1000000000.0; maX=maY=0;
		for(int i=0;i<N;i++) {
			scanf("%lf %lf",&p[i].x,&p[i].y);
			miX=min(miX,p[i].x);
			miY=min(miY,p[i].y);
			maX=max(maX,p[i].x);
			maY=max(maY,p[i].y);
		}
		double x,y,ans;
		ans=min_dis(x,y);
		printf("(%.3lf,%.3lf) %.4lf\n",x,y,ans);
	}
}

