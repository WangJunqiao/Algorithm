#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
using namespace std;

//求多边形费马点 模拟退火
const double PI=acos(-1.0);
int N=4; //N边形

const double eps=1e-5; //精度要求
const double alf=0.95; //冷却系数
const int S=3;      //并行解的个数
const int L=3;      //调整尝试次数
const int F=10;     //360度 等分数
const double A=2*PI/F; //每次累加弧度
const int BS=10000;   //随机化池的大小
double one[BS][F][2]; //随机化单位向量池

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
inline double get_double(){
	return ( ( (int)rand()<<15 )|rand() )/(double)((1<<30)-1); //vs c++
}
void initOne(){ //初始化等分单位向量
	for(int i=0;i<BS;i++){
		double bas=get_double()*A;
		for(int j=0;j<F;j++){
			one[i][j][0]=cos(bas+j*A);
			one[i][j][1]=sin(bas+j*A);
		}
	}
}
int main(){
	freopen("in.txt","r",stdin);
	freopen("out7.txt","w",stdout);
	
	srand(time(NULL));
	initOne();
	while( scanf("%d",&N)!=EOF ){
		for(int i=0;i<N;i++) scanf("%lf %lf",&p[i].x,&p[i].y);
		if( p[1].x<0 ) break;
		P res[S];
		double d[S];
		double T=2000;
		for(int i=0;i<S;i++){ //随机初始解集
			int tx,ty,sx=0,sy=0;
			res[i].x=res[i].y=0;
			for(int k=0;k<N;k++){
				tx=rand()%1000; sx+=tx;
				ty=rand()%1000; sy+=ty;
				res[i].x+=p[k].x*tx;
				res[i].y+=p[k].y*ty;
			}
			res[i].x/=sx;
			res[i].y/=sy;
			//printf("%.3lf %.3lf\n",res[i].x,res[i].y);
			d[i]=all_dis(res[i]);
		}
		while( T>eps ){
			for(int i=0;i<S;i++){
				P cur=res[i];
				for(int j=0;j<L;j++){ //尝试调整
					int ind=rand()%BS;
					for(int k=0;k<F;k++){
						P tmp;
						tmp.x=cur.x+T*one[ind][k][0];
						tmp.y=cur.y+T*one[ind][k][1];
						double D=all_dis(tmp);
						if( D<d[i] ){ 
							res[i]=tmp; d[i]=D; //break;
						}
					}
				}
			}
			T*=alf; //冷却
		}
		int id=0;
		for(int i=0;i<S;i++){
			if( d[i]<d[id] ) id=i;
		}
		printf("(%.3lf,%.3lf) %.4lf\n",res[id].x,res[id].y,d[id]);
	}
}

