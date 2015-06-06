//������n����,��һ���㵽���е���̾������  pku 1379 ģ���˻�

/*
Algorithm SA
�� �ھ�����ȡp ������Ϊ��ʼ��
�� ȡһ���㹻��Ĳ���delta
while delta>epsilon
	for ÿ����ѡ��
		for i from 1 to L
		���һ��ģ��Ϊdelta����������������ӵ�������Ϊ�½�
		��ͼ�����ŵĺϷ��½����ԭ��
	Delta *= 0.8
ȡĿ�꺯��ֵ��󣨾���������������󣩵Ľ���Ϊ��
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
	srand(time(NULL));  //�����,wa�˶���ύ
	const double eps=1e-3; //����Ҫ��
	const double alf=0.90; //��ȴϵ��
	const double T=10000.0; //��ʼ�¶�    (�����ǵ�Ŀ����뾶)
	const int S=10;    //���н�ĸ���
	const int L=10;    //�������Դ���
	int cas; scanf("%d",&cas);
	while( cas-- && scanf("%d %d %d",&X,&Y,&n)!=EOF ){
		for(int i=1;i<=n;i++) scanf("%lf %lf",&p[i].x,&p[i].y);
		P res[S];
		double t=T,d[S];
		for(int i=0;i<S;i++){ //�����ʼ�⼯
			res[i].x=get_double()*X;
			res[i].y=get_double()*Y;
			d[i]=min_dis(res[i]);
		}
		while( t>eps ){
			for(int i=0;i<S;i++){
				for(int j=0;j<L;j++){ //���Ե���
					double rad=2*PI*get_double();
					P tmp;
					tmp.x=res[i].x+t*cos(rad);
					tmp.y=res[i].y+t*sin(rad);
					if( tmp.x<0 || tmp.x>X || tmp.y<0 || tmp.y>Y ) continue;
					double D=min_dis(tmp);
					//exp(-(d[i]-D)/t)̫����,Ҫ������������,���߸ɴ�ȥ��
					if( D>d[i] || get_double()<exp(-(d[i]-D)/t)*0.00001 ){ 
						res[i]=tmp; d[i]=D; break;
					}
				}
			}
			t*=alf; //��ȴ
		}
		int id=0;
		for(int i=0;i<S;i++){
			if( d[i]>d[id] ) id=i;
		}
		printf("The safest point is (%.1lf, %.1lf).\n",res[id].x,res[id].y);
	}
}

