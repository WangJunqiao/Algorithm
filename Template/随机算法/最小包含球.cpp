//PKU2069 Super Star  最小包含球
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
using namespace std;
const int MAX=120;
const double INF=1e20;
const double eps=1e-6;
struct point{
	double x,y,z;
}ps[MAX],q;             //q是球心***************
int n;                  //多少个点,标号0~n-1

double dist(point a,point b){
	a.x-=b.x;
	a.y-=b.y;
	a.z-=b.z;
	return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}
int maxD(point p){
	double res=0;
	int k=0;
	for(int i=0;i<n;++i){
		double tmp=dist(p,ps[i]);
		if(tmp>res){
			k=i;
			res=dist(p,ps[i]);
		}
	}
	return k;
}
double min_ball(){
	double step=100; //精度************
	double radius=INF;
	q.x=q.y=q.z=0.0;
	int k=1;
	while(step>eps){ //精度没到,继续做
		int d=maxD(q);
		double tmp=dist(ps[d],q);
		if(tmp<radius)
			radius=tmp;
		double dx=ps[d].x-q.x;
		double dy=ps[d].y-q.y;
		double dz=ps[d].z-q.z;
		dx/=tmp;dy/=tmp;dz/=tmp;
		q.x=q.x+dx*step;
		q.y=q.y+dy*step;
		q.z=q.z+dz*step;
		step*=0.98;
	}
	return radius+1e-7;
}
int main(){
	while(scanf("%d",&n),n){
		for(int i=0;i<n;++i)
			scanf("%lf%lf%lf",&ps[i].x,&ps[i].y,&ps[i].z);
		//printf("%lf %lf %lf\n",q.x,q.y,q.z);
		printf("%.5f\n",min_ball() );
	}
	return 0;
}