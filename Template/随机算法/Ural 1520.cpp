/*
ural 1520 给定一个圆，内部有N个点，求圆内一点，使得它和所有点的最短距离最大化
分析: 主体算法就是模拟退火,但是这个边界比较特殊,是一个圆形的.
由二分答案这个算法的思路我们可以发现,这个要求的点肯定在所有点的半径为r的圆之外,
那么问题来了,边界也是圆,所以很可能边界上的一点,它的进化(变好)的角度是非常小的(大圆和小圆相切的样子)
而如果边界是矩形的话,那么角度是不会这么刁钻的,所以本题中当所求点在边界上时,需要特判.
*/
#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
using namespace std;


const double PI=acos(-1.0);
#define eps 1e-8
inline int sgn(double a){
	return a>eps ? 1 : (a<-eps?-1:0);
}

struct P{double x,y;};
double xmult(P p1,P p2,P p0){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
double dist(P p1,P p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double disptoline(P p,P l1,P l2){
	return fabs(xmult(p,l1,l2))/dist(l1,l2);
}
//判直线和圆相交,包括相切
int intersect_line_circle(P c,double r,P l1,P l2){
	return disptoline(c,l1,l2)<r+eps;
}
P intersection(P u1,P u2,P v1,P v2){
	P ret=u1;
	double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
			/((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
	ret.x+=(u2.x-u1.x)*t;
	ret.y+=(u2.y-u1.y)*t;
	return ret;
}
//计算直线与圆的交点,保证直线与圆有交点
//计算线段与圆的交点可用这个函数后判点是否在线段上
void intersection_line_circle(P c,double r,P l1,P l2,P& p1,P& p2){
	P p=c;
	double t;
	p.x+=l1.y-l2.y;
	p.y+=l2.x-l1.x;
	p=intersection(p,c,l1,l2);
	t=sqrt(r*r-dist(p,c)*dist(p,c))/dist(l1,l2);
	p1.x=p.x+(l2.x-l1.x)*t;
	p1.y=p.y+(l2.y-l1.y)*t;
	p2.x=p.x-(l2.x-l1.x)*t;
	p2.y=p.y-(l2.y-l1.y)*t;
}

//矢量V逆时针旋转rad(弧度)
P rotate(P v,double rad){
	P ret; ret.x=ret.y=0;
	double px=cos(rad);
	double py=sin(rad);
	ret.x+=v.x*px-v.y*py;
	ret.y+=v.x*py+v.y*px;
	return ret;
}

inline double get_double(){ //返回一个0~1的浮点数
	return ( ( (int)rand()<<15 )|rand() )/(double)((1<<30)-1); //vs c++
	//return rand() / (double)RAND_MAX; //gcc
}
inline void get_vec(double r,double &x,double &y){ //获得一个长度为r,方向任意的向量
	x=r*get_double(), y=sqrt(r*r-x*x);
	if( rand()&1 ) x=-x;
	if( rand()&1 ) y=-y;
}
double min_dis(P *p,int N,P p1){
	double ret=1000000000.0;
	for(int i=1;i<=N;i++) ret=min(ret,dist(p[i],p1)); 
	return ret;
}
int main(){
	srand(time(NULL));  //有这个,wa了多次提交
	const double alf=0.90;//冷却系数
	const int S=7;        //并行解的个数
	const int L=15;       //调整尝试次数
	int N,R;
	while( scanf("%d %d",&N,&R)!=EOF ){
		P p[333],Z,p1,p2,tmp;
		Z.x=Z.y=0;
		for(int i=1;i<=N;i++) scanf("%lf %lf",&p[i].x,&p[i].y);
		if( N==1 && sgn(p[1].x)==0 && sgn(p[1].y)==0 ) {
			printf("%.8lf\n",(double)R);
			continue;
		}
		double ans=0;
		for(int i=1;i<=N;i++){ //答案是一个点和圆心连线和圆的交点处
			if( sgn(p[i].x) || sgn(p[i].y) ){
				intersection_line_circle(Z,R,p[i],Z,p1,p2);
				ans=max(ans,min_dis(p,N,p1));
				ans=max(ans,min_dis(p,N,p2));
			}
		}
		for(int i=1;i<=N;i++){ //答案是两个点的中垂线和圆的交点处
			for(int j=i+1;j<=N;j++){
				if( sgn(p[i].x-p[j].x)==0 && sgn(p[i].y-p[j].y)==0 )continue;
				P u,v; 
				u.x=(p[i].x+p[j].x)/2;
				u.y=(p[i].y+p[j].y)/2;
				v.x=(p[j].x-p[i].x);
				v.y=(p[j].y-p[i].y);
				v=rotate(v,PI/2);
				v.x+=u.x; v.y+=u.y;
				intersection_line_circle(Z,R,u,v,p1,p2);
				ans=max(ans,min_dis(p,N,p1));
				ans=max(ans,min_dis(p,N,p2));
			}
		}
		//下面是模拟退火
		P res[S]; double d[S];
		for(int i=0;i<S;i++){
			get_vec(rand()%R+1,res[i].x,res[i].y);
			d[i]=min_dis(p,N,res[i]);
		}
		double T=R;
		while( T>1e-7 ){
			for(int i=0;i<S;i++){
				for(int j=0;j<L;j++){
					double x,y,D;
					get_vec(T,x,y);
					tmp.x=res[i].x+x, tmp.y=res[i].y+y;
					if( dist(tmp,Z)>R ) continue;
					D=min_dis(p,N,tmp);
					if( D>d[i] ){ //随机因子不要了
						res[i]=tmp; d[i]=D; break;
					}
				}
			}
			T*=alf; //冷却
		}
		for(int i=0;i<S;i++) ans=max(ans,d[i]);
		printf("%.8lf\n",ans);
	}
}