//pku 2728 ��С���������� Dinkelbach ���������ƽ�
//����ͼ��Ҫ��priority_queue��ֱ����һ��forѭ���ҵ���С����ֵ
//�Աߵ�ѡ��*************************
//r = ��(benifit[i] * x[i]) / ��(cost[i]*x[i]), 0��i<m .Ϊ��ʹ r ���, 
//r����Ҫ��Ĳ���*************��������һ������������************
//���һ��������---> �� z = ��(benifit[i]*x[i]) - k*��(cost[i] * x[i]) 
//= ��(d[i] * x[i]) ��� (d[i] = benifit[i] - k* cost[i]) , ����Ϊz(k). 
//���ǿ����˸߲��ҵذ�z(l)������dΪ��Ȩ���������������Ȩֵ.

#include<iostream>
#include<cmath>
#include<queue>

#define MAXN 1005
using namespace std;
struct point {
    double x, y, z;
} p[MAXN];
struct T {
    double height, dis;
} t[MAXN];
double h[MAXN], d[MAXN], key[MAXN];

inline double distance(double &x1, double &y1, double &x2, double &y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

struct Node {
    int id;
    double key;

    Node(int _id = 0, double _key = 0.0) : id(_id), key(_key) { };
};

inline bool operator<(const Node &a, const Node &b) {
    return a.key > b.key;
}

int N;
bool visit[MAXN];

void prim(double r) {
    priority_queue<Node> pq;
    memset(visit, false, sizeof(visit));
    for (int i = 1; i <= N; i++)
        key[i] = 1000000000.0;
    pq.push(Node(1, 0.0));
    int ind = 1;
    bool flag = true;
    double hh, dd;
    while (!pq.empty()) {
        int id = pq.top().id;
        pq.pop();
        if (visit[id])
            continue;
        visit[id] = true;
        if (flag)
            flag = false;
        else {
            t[ind].dis = d[id];
            t[ind++].height = h[id];
        }
        for (int i = 1; i <= N; i++)
            if (!visit[i]) {
                hh = fabs(p[id].z - p[i].z);
                dd = distance(p[id].x, p[id].y, p[i].x, p[i].y);
                if (hh - r * dd < key[i]) {//��������ĺ���
                    h[i] = hh;
                    d[i] = dd;
                    key[i] = h[i] - r * d[i];
                    pq.push(Node(i, key[i]));
                }
            }
    }
}

int main() {
    double r, temp;
    while (scanf("%d", &N) != EOF && N) {
        for (int i = 1; i <= N; i++)
            scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
        r = 0.0;
        while (1) {
            prim(r);             //��һ������ȥ���һ��������
            double m = 0.0;
            for (int i = 1; i < N; i++)
                m += t[i].dis;
            temp = 0.0;            //������εĲ���ֵ
            for (int i = 1; i < N; i++)
                temp += t[i].height / m;
            if (fabs(temp - r) < 1e-4) //ǰ�����������Ĳ���С��ʱ��
                break;
            r = temp;
        }
        printf("%.3lf\n", r);
    }
}
/* ����ͼ�������������
void prim(double r){
	for(int i=1;i<=N;i++)
		key[i]=1000000000.0;
	memset(visit,false,sizeof(visit));
	key[1]=0.0;
	int ind=1,index;
	double mi;
	bool flag=true;
	for(int i=1;i<=N;i++){
		mi=1000000006.0;
		for(int i=1;i<=N;i++)
			if(!visit[i]&&key[i]<mi)
				mi=key[i],index=i;
		visit[index]=true;
		if(flag)
			flag=false;
		else{
			t[ind].dis=d[index];
			t[ind++].height=h[index];
		}
		for(int i=1;i<=N;i++)
			if(!visit[i]&&(fabs(p[index].z-p[i].z)-r*distance(p[index].x,p[index].y,p[i].x,p[i].y)<key[i])){
				h[i]=fabs(p[index].z-p[i].z);
				d[i]=distance(p[index].x,p[index].y,p[i].x,p[i].y);
				key[i]=h[i]-r*d[i];
			}
	}
}