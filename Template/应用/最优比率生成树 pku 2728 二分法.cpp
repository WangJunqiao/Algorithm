//pku 2728 最小比率生成树 二分参数搜索 2000ms
//稠密图不要用priority_queue，直接用一个for循环找到最小（大）值
//构造出来的那个函数是单调的，先取左边的l（代入是正值），再取一个右边的值r（代入是负值）
//每次把mid代入，解出一个解向量X，再缩小l和r的间距了，知道fabs(l-r)<1e-n........
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

int N;
bool visit[MAXN];

void prim(double r) {
    for (int i = 1; i <= N; i++)
        key[i] = 1000000000.0;
    memset(visit, false, sizeof(visit));
    key[1] = 0.0;
    int ind = 1, index;
    double mi;
    bool flag = true;
    for (int i = 1; i <= N; i++) {
        mi = 1000000006.0;
        for (int i = 1; i <= N; i++)
            if (!visit[i] && key[i] < mi)
                mi = key[i], index = i;
        visit[index] = true;
        if (flag)
            flag = false;
        else {
            t[ind].dis = d[index];
            t[ind++].height = h[index];
        }
        for (int i = 1; i <= N; i++)
            if (!visit[i] &&
                (fabs(p[index].z - p[i].z) - r * distance(p[index].x, p[index].y, p[i].x, p[i].y) < key[i])) {
                h[i] = fabs(p[index].z - p[i].z);
                d[i] = distance(p[index].x, p[index].y, p[i].x, p[i].y);
                key[i] = h[i] - r * d[i];
            }
    }
}

double cal(double k) {
    double m = 0;
    for (int i = 1; i <= N; i++)
        m += t[i].height - k * t[i].dis;
    return m;
}

int main() {
    while (scanf("%d", &N) != EOF && N) {
        for (int i = 1; i <= N; i++)
            scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
        double l = 0.0, r = 100.0, mid;
        while (1) {
            mid = (l + r) / 2.0;
            prim(mid);//代入求下一个解向量X
            double ttt = cal(mid);//代入mid解出构造出的函数的值
            if (fabs(l - r) < 1e-6)
                break;
            if (ttt >= 0)
                l = mid;
            else
                r = mid;
        }
        printf("%.3lf\n", r);
    }
}

