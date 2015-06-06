/*
Problem: TSP
Algorithm: Genetic Algorithm
Ahthor: �����0801 ������
*/
#include<glut.h>   //��Ҫ���ú�glut���ܱ���������δ���
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<algorithm>
#include<vector>
using namespace std;

typedef pair<double,double> Point;
typedef vector< Point > VP; 
VP city;           //TSP����ĵ�
vector<int> permut;//�������

///********************************************************
void draw(){  //glut �ص�����
	double maxX=-100000,minX=-maxX;  
	double maxY=-100000,minY=-maxY;
	for(int i=0;i<city.size();i++){
		maxX=max(maxX,city[i].first);
		minX=min(minX,city[i].first);
		maxY=max(maxY,city[i].second);
		minY=min(minY,city[i].second);
	}
	double aveX=(minX+maxX)/2, _X=1.2*(aveX-minX);
	double aveY=(minY+maxY)/2, _Y=1.2*(aveY-minY);  //�ȱ�������

	glClearColor(1.0, 1.0 , 1.0, 0); //�װ�
	glClear(GL_COLOR_BUFFER_BIT); //��λ
	glPointSize(10); //���õ�Ĵ�С,���������ģʽѡ��֮ǰ
	glLineWidth(5);  //�����߿�

	glBegin(GL_POINTS);    //����
	for(int i=0;i<city.size();i++){
		glColor3f(1,0,0);
		double x=(city[i].first-aveX)/_X;
		double y=(city[i].second-aveY)/_Y;
		glVertex2f(x,y);
	}
	glEnd();

	glBegin(GL_LINE_LOOP); //����
	for(int i=0;i<city.size();i++){
		glColor3f(0,1,0);
		double x=(city[ permut[i] ].first- aveX)/_X; //permutation
		double y=(city[ permut[i] ].second-aveY)/_Y;
		glVertex2f(x,y);
	}
	glEnd();

	glutSwapBuffers();
}
void OpenGLInit(){ //��ʼ��OpenGL
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutInitDisplayString("double rgb depth>=24");//depth>=24�����пո�
	glutCreateWindow("OpenGL��ͼ���� --TSP����");
}////***********************�����Ǽ����ͼ�����***********************

double getDouble(int len=2){ //���һ������Ϊlen��double,0~1
	double ret=0, mul=1;
	for(int i=1;i<=len;i++){
		mul*=0.1;
		ret+=rand()%10 * mul;
	}
	return ret;
}
inline double getDis(const Point &p1,const Point &p2){ //�����������
	return sqrt( (p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second) );
}
void roll(vector<int> &v,int src,int des){//���±�Ϊsrc�ķ���des����һ��
	if( src>des ){
		while( src!=des+1 ){
			swap(v[src],v[src-1]);
			src--;
		}
	}else{
		while( src!=des ){ //��Ϊǰ��һλ����
			swap(v[src],v[src+1]);
			src++;
		}
	}
}

struct Individual{ //������
	vector<int> v; //Ⱦɫ��,��0~n-1��һ��ȫ����
	double dis, fit; //��Ӧ�Ⱥ���ֵ
	Individual(){}
	Individual(vector<int> v){
		this->v=v;	
	}
	void calFitness(){ //��Ӧ�Ⱥ���ֵΪ����͵ĵ���
		dis=0;
		for(int i=0;i<v.size();i++){
			int id1=v[i],id2=v[(i+1)%v.size()];
			dis+=getDis(city[id1],city[id2]);
		}
		fit=1.0/dis;
	}
	Individual cross(Individual &b)const{ //����,������һ������,���ｻ�����˳����뽻������
		vector<int> nxt=v;
		for(int i=0;i<b.v.size();i++){
			int val1=b.v[i], val2=b.v[ (i+1)%b.v.size() ];
			int j=0,m=0;
			while( nxt[j] != val1 ) j++;
			while( nxt[m] != val2 ) m++;
			//�����ж�m�ǲ���Ӧ����j����һλ   ����������ôѡ���õ���˫�׵����ʻ���*****
			Point pj=city[nxt[j]] ,pj1, pm=city[nxt[m]],pm1,pm_1;
			if( j==nxt.size()-1 ) pj1=city[nxt[0]]; else pj1=city[nxt[j+1]];
			if( m==nxt.size()-1 ) pm1=city[nxt[0]]; else pm1=city[nxt[m+1]];
			if( m==0 ) pm_1=city[nxt[ nxt.size()-1]]; else pm_1=city[nxt[m-1]];
			double cur=getDis(pj,pj1)+getDis(pm_1,pm)+getDis(pm,pm1);
			double xor=getDis(pj,pm)+getDis(pm,pj1)+getDis(pm_1,pm1);
			if( cur > xor ) roll(nxt,m,j); //���ȷʵ�����ڵ�Ҫ��
		}
		return Individual(nxt);
	}
	void mutate(double pm){ //����,����������
		for(int i=0;i<v.size()/2;i++){ //����***
			if( getDouble(4) < pm ){
				int id1,id2;  //���ѡ����������
				do{
					id1=rand()%v.size();
					id2=rand()%v.size();
				}while( id1==id2 );
				swap(v[id1],v[id2]);
			}
		}
	}
	bool operator<(const Individual &b)const{ //�Ƚ�
		return dis < b.dis;
	}
};

struct Population{ //��Ⱥ��
	vector<Individual> pop;
	double pc,pm;
	Population(int N=10,int S=20,double pc=0.85, double pm=0.05){ //������Ŀ, ��Ⱥ��Ŀ
		this->pc=pc, this->pm=pm; //����***
		vector<int> v(N);
		for(int i=0;i<N;i++) v[i]=i;
		for(int i=0;i<S;i++){ //��ʼ����ȺS��
			for(int j=0;j<30*N;j++){ //���������
				int id1=rand()%N;
				int id2=rand()%N;
				swap(v[id1],v[id2]);
			}
			pop.push_back(Individual(v));
			pop[i].calFitness();
		}
	}
	/*
	void getNext(){ //��һ��,�������̶�ѡ��
		vector<Individual> npop;
		double sumFit=0,last=0;
		//sort(pop.begin(),pop.end());
		for(int i=0;i<pop.size();i++){ //������һ��,2������
			int a=i,b=(i+1)%pop.size(); 
			if( getDouble(4) < pc ) //��һ���ĸ��ʽ���
				npop.push_back(pop[a].cross(pop[b]));
			else 
				npop.push_back(pop[a]);
			npop[ npop.size()-1 ].calFitness();
			sumFit+=npop[ npop.size()-1 ].fit;

			if( getDouble(4) < pc ) //��һ���ĸ��ʽ���
				npop.push_back(pop[b].cross(pop[a]));
			else 
				npop.push_back(pop[b]);
			npop[npop.size()-1].calFitness();
			sumFit+=npop[npop.size()-1].fit;
		}
		for(int i=0;i<npop.size();i++){ //����
			npop[i].fit/=sumFit;
			npop[i].fit+=last;
			last=npop[i].fit;
		}
		int S=pop.size(); pop.clear();
		for(int i=0;i<S;i++){  //���̶�ѡ��
			double t=getDouble(4);
			int sel=0;
			while( npop[sel].fit < t ) sel++;
			pop.push_back(npop[sel]);
		}
	}
	*/
	void getNext(){ //��һ��,���ñ�ը�Է�ֳ,ѡ�����ʺ��
		int mul=20;
		vector<Individual> npop(mul*pop.size());
		for(int i=0;i<pop.size()*mul;i++){ //������һ��
			int a,b; 
			do{
				a=rand()%pop.size();
				b=rand()%pop.size();
			}while( a==b );
			if( getDouble(4) < pc ) //��һ���ĸ��ʽ���
				npop[i]=pop[a].cross(pop[b]);
			else 
				npop[i]=pop[a];
			npop[i].calFitness();
		}
		sort(npop.begin(),npop.end());
		//ѡ����õ�
		int S=pop.size(); pop.clear();
		for(int i=0;i<S;i++){
			pop.push_back(npop[i]);
		}
	}
	Individual getBest(){ //�����õĸ���
		int sel; double ma=0;
		for(int i=0;i<pop.size();i++){
			pop[i].calFitness();
			if( pop[i].fit > ma ){
				ma=pop[i].fit;
				sel=i;
			}
		}
		return pop[sel];
	}
};

int main(){
	srand(time(NULL)); //û�����ÿ�ε����н������ͬ
	int N,T,S;
	double pc,pm;
	printf("ע��: ��ϵͳ���ݶ���������ɵ�,����ÿ�����еĳ���������ܲ�ͬ,���Ҳ���ܲ�ͬ!!\n\n");
	printf("������TSP���������Ŀ(10-50),GA�㷨��������(100-1000),��Ⱥ��С(50-100),�������(0.9����),�������(0.05����)\n");
	while(cin>>N>>T>>S>>pc>>pm){ 
		clock_t Time=clock();
		city.clear();
		printf("������������:\n");
		for(int i=0;i<N;i++){ //�����������
			double a=rand()%5000, b=rand()%5000;
			city.push_back(Point(a,b));
			printf("(%5.0lf,%5.0lf)\n",a,b);
		}
		double mi=1000000000.0; //��¼��С�����
		Population p(N,S,pc,pm); //������Ⱥ
		for(int i=0;i<T;i++){   //����T��
			p.getNext();
			mi=min(mi,p.getBest().dis); //������С�����
		}
		permut=p.getBest().v;  //��ֹ״̬��Ⱥ����Ѹ���
		printf("·��Ϊ: ");
		for(int i=0;i<permut.size();i++){
			if( i!=0 ) printf("-->");
			printf("%d",permut[i]);
			if( i==permut.size()-1 ) puts("");
		}
		printf("�����г��ֹ�����С�����Ϊ: %.1lf  ���վ����Ϊ: %.1lf\n",mi,p.getBest().dis);
		printf("�����ʱ: %.3lf ��\n",(clock()-Time)/1000.0);

		OpenGLInit();
		glutDisplayFunc(draw);
		glutMainLoop();
	}
}
/*
��������: (һ��һ��,�ֱ��ʾ������,��������,��Ⱥ��ģ,������,������)
10 50 50 0.9 0.05
20 100 50 0.9 0.05
30 300 50 0.9 0.05
40 400 50 0.9 0.05
50 500 100 0.9 0.05
75 500 100 0.9 0.05
75 1000 100 0.9 0.05
*/