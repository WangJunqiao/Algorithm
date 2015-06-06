//矩形内n个点,求一个点到所有点最短距离最大  pku 1379 模拟退火

/*
Algorithm SA
① 在矩形中取p 个点作为初始解
② 取一个足够大的步长delta
while delta>epsilon
	for 每个候选解
		for i from 1 to L
		随机一个模长为delta，方向随机的向量加到点上作为新解
		试图用最优的合法新解替代原解
	Delta *= 0.8
取目标函数值最大（距最近的陷阱距离最大）的解作为答案
*/
#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
using namespace std;

#define maxn 1005
const double PI=acos(-1.0);
struct P{
	double x,y;
	P(double _x=0,double _y=0):x(_x),y(_y){};
	double dis(const P &b)const{
		return sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
	}
}p[maxn];
int X,Y,n;

double min_dis(P a){
	double ret=1e20;
	for(int i=1;i<=n;i++) ret=min(ret,a.dis(p[i]));
	return ret;
}

inline double get_double(){
	return ( ( (int)rand()<<15 )|rand() )/(double)((1<<30)-1); //vs c++
	//return rand() / (double)RAND_MAX; //gcc
}

int main(){
	srand(time(NULL));  //有这个,wa了多次提交
	const double eps=1e-3; //精度要求
	const double alf=0.90; //冷却系数
	const double T=10000.0; //初始温度    (这里是点的可跳半径)
	const int S=10;    //并行解的个数
	const int L=10;    //调整尝试次数
	int cas; scanf("%d",&cas);
	while( cas-- && scanf("%d %d %d",&X,&Y,&n)!=EOF ){
		for(int i=1;i<=n;i++) scanf("%lf %lf",&p[i].x,&p[i].y);
		P res[S];
		double t=T,d[S];
		for(int i=0;i<S;i++){ //随机初始解集
			res[i].x=get_double()*X;
			res[i].y=get_double()*Y;
			d[i]=min_dis(res[i]);
		}
		while( t>eps ){
			for(int i=0;i<S;i++){
				for(int j=0;j<L;j++){ //尝试调整
					double rad=2*PI*get_double();
					P tmp;
					tmp.x=res[i].x+t*cos(rad);
					tmp.y=res[i].y+t*sin(rad);
					if( tmp.x<0 || tmp.x>X || tmp.y<0 || tmp.y>Y ) continue;
					double D=min_dis(tmp);
					//exp(-(d[i]-D)/t)太大了,要弱化它的作用,或者干脆去掉
					if( D>d[i] || get_double()<exp(-(d[i]-D)/t)*0.00001 ){ 
						res[i]=tmp; d[i]=D; break;
					}
				}
			}
			t*=alf; //冷却
		}
		int id=0;
		for(int i=0;i<S;i++){
			if( d[i]>d[id] ) id=i;
		}
		printf("The safest point is (%.1lf, %.1lf).\n",res[id].x,res[id].y);
	}
}

