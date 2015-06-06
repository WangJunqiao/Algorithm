//pku 2728 最小比率生成树 Dinkelbach 参数迭代逼近
//稠密图不要用priority_queue，直接用一个for循环找到最小（大）值
//对边的选择*************************
//r = ∑(benifit[i] * x[i]) / ∑(cost[i]*x[i]), 0≤i<m .为了使 r 最大, 
//r就是要求的参数*************构造另外一个函数来求它************
//设计一个子问题---> 让 z = ∑(benifit[i]*x[i]) - k*∑(cost[i] * x[i]) 
//= ∑(d[i] * x[i]) 最大 (d[i] = benifit[i] - k* cost[i]) , 并记为z(k). 
//我们可以兴高采烈地把z(l)看做以d为边权的最大生成树的总权值.

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
                if (hh - r * dd < key[i]) {//构造出来的函数
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
            prim(r);             //用一个参数去解出一个解向量
            double m = 0.0;
            for (int i = 1; i < N; i++)
                m += t[i].dis;
            temp = 0.0;            //计算这次的参数值
            for (int i = 1; i < N; i++)
                temp += t[i].height / m;
            if (fabs(temp - r) < 1e-4) //前后两个参数的差距很小的时候
                break;
            r = temp;
        }
        printf("%.3lf\n", r);
    }
}
/* 稠密图用下面这个更快
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