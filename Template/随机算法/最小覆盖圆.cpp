//最小覆盖圆,随即增量算法O(n) zju 1450
/*
algorithm:
A、令Ci表示为前i个点的最小覆盖圆。当加入新点pi时如果pi不在Ci-1里那么pi必定在Ci的边界上。
B、再从新考虑这样一个问题，Ci为前i个点最小覆盖圆且p在Ci的的边界上！同理加入新点pi时如果pi不在Ci-1里那么pi必定在Ci的边界上。这时我们就包含了两个点在这个最小圆的边界上。
C、再从新考虑这样一个问题，Ci为前i个点最小覆盖圆且有两个确定点再边界上！此时先让
*/
#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cmath>
using namespace std;
struct Point{
	double x,y;
};
int n;
Point p[200000],O;
double r,eps=1e-8;
double dist(Point a,Point b){
	return sqrt( (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y) );
}
//注意到三角形里两条中垂线不可能平行，所以不会产生除0错误
void calc(double a,double b,double c,double d,double e,double f){  //给出两条直线ax+by+c=0,dx+ey+f=0 求交点                      
	O.y=(c*d-f*a)/(b*d-e*a);
	O.x=(c*e-f*b)/(a*e-b*d);
}
int main(){
	srand(time(NULL));
	while(scanf("%d",&n)!=EOF && n ){
		for (int i=1;i<=n;++i) scanf("%lf%lf",&p[i].x,&p[i].y);
		for(int i=1;i<=n;i++){ //将点随机化，防止线性递增的序列使得复杂度变成n^3
			swap(p[i],p[rand()%n+1]);
		}
		O=p[1];r=0;                  //初始C1
		for (int i=2;i<=n;++i){     
			if (dist(O,p[i])<r+eps) continue;  //有1/i的概率不continue
			O=p[i];r=0;
			for (int j=1;j<=i-1;++j) {    
				if (dist(O,p[j])<r+eps) continue;   //有1/j的概率不continue
				O.x=(p[i].x+p[j].x)/2;O.y=(p[i].y+p[j].y)/2;r=dist(O,p[j]);
				for (int k=1;k<=j-1;++k){ 
					if (dist(O,p[k])<r+eps) continue;   //有1/k的概率不continue
					calc(p[j].x-p[i].x,p[j].y-p[i].y,(p[j].x*p[j].x+p[j].y*p[j].y-p[i].x*p[i].x-p[i].y*p[i].y)/2,
						p[k].x-p[i].x,p[k].y-p[i].y,(p[k].x*p[k].x+p[k].y*p[k].y-p[i].x*p[i].x-p[i].y*p[i].y)/2); 
					r=dist(O,p[k]);
				}
			}
		}
		printf("%.2lf %.2lf %.2lf\n",O.x,O.y,r);
	}
	return 0;
}
