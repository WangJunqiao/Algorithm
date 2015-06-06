//��С����Բ,�漴�����㷨O(n) zju 1450
/*
algorithm:
A����Ci��ʾΪǰi�������С����Բ���������µ�piʱ���pi����Ci-1����ôpi�ض���Ci�ı߽��ϡ�
B���ٴ��¿�������һ�����⣬CiΪǰi������С����Բ��p��Ci�ĵı߽��ϣ�ͬ������µ�piʱ���pi����Ci-1����ôpi�ض���Ci�ı߽��ϡ���ʱ���ǾͰ������������������СԲ�ı߽��ϡ�
C���ٴ��¿�������һ�����⣬CiΪǰi������С����Բ��������ȷ�����ٱ߽��ϣ���ʱ����
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
//ע�⵽�������������д��߲�����ƽ�У����Բ��������0����
void calc(double a,double b,double c,double d,double e,double f){  //��������ֱ��ax+by+c=0,dx+ey+f=0 �󽻵�                      
	O.y=(c*d-f*a)/(b*d-e*a);
	O.x=(c*e-f*b)/(a*e-b*d);
}
int main(){
	srand(time(NULL));
	while(scanf("%d",&n)!=EOF && n ){
		for (int i=1;i<=n;++i) scanf("%lf%lf",&p[i].x,&p[i].y);
		for(int i=1;i<=n;i++){ //�������������ֹ���Ե���������ʹ�ø��Ӷȱ��n^3
			swap(p[i],p[rand()%n+1]);
		}
		O=p[1];r=0;                  //��ʼC1
		for (int i=2;i<=n;++i){     
			if (dist(O,p[i])<r+eps) continue;  //��1/i�ĸ��ʲ�continue
			O=p[i];r=0;
			for (int j=1;j<=i-1;++j) {    
				if (dist(O,p[j])<r+eps) continue;   //��1/j�ĸ��ʲ�continue
				O.x=(p[i].x+p[j].x)/2;O.y=(p[i].y+p[j].y)/2;r=dist(O,p[j]);
				for (int k=1;k<=j-1;++k){ 
					if (dist(O,p[k])<r+eps) continue;   //��1/k�ĸ��ʲ�continue
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
