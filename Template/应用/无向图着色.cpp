/*
hdu 3762 无向图着色    贪心
思路: 假设现在图可以被k种颜色着色,
那么先考虑度数最小的点u,他肯定可以被着色. 那么u的着色放在最后.
去掉u后,再去找度数最小的,递归下去....
*/

#include<iostream>
#include<cassert>
#include<ctime>
#include<queue>

using namespace std;

#define maxn 11000
struct Edge {
    int v, x;
} E[210000];
int l[maxn], e;

void init() {
    e = 0;
    memset(l, -1, sizeof(l));
}

inline void insert(int u, int v) {
    E[e].v = v;
    E[e].x = l[u];
    l[u] = e++;
}

struct DD {
    int d, v; //degree, vertex
    DD(int _d = 0, int _v = 0) : d(_d), v(_v) { };

    bool operator<(const DD &b) const {
        return d > b.d;
    }
};

priority_queue<DD> pq;
int n, m;
int deg[maxn], col[maxn], tmp[maxn];
int o[maxn]; //贪心的顺序
bool vst[maxn];

void paint() {
    int k = 0, oid = 0; //k种颜色
    for (int i = 1; i <= n; i++) {
        col[i] = -1;
        vst[i] = false;
        tmp[i] = deg[i];
        pq.push(DD(tmp[i], i));
        k = max(k, deg[i]);
    }
    if (k % 2 == 0) k++;
    printf("%d\n", k);//题目规定是奇数

    while (!pq.empty()) {
        DD d = pq.top();
        pq.pop();
        if (tmp[d.v] != d.d) continue;
        o[oid++] = d.v;
        vst[d.v] = true;
        for (int p = l[d.v]; p >= 0; p = E[p].x) {
            int v = E[p].v;
            if (vst[v]) continue; //已经取出来了
            tmp[v]--;
            pq.push(DD(tmp[v], v));
        }
    }
    for (int i = oid - 1; i >= 0; i--) { //从后往前
        int u = o[i], s;
        fill(vst, vst + min(k + 1, deg[u] + 2), false); //暴力染色
        for (int p = l[u]; p >= 0; p = E[p].x) {
            int v = E[p].v;
            if (col[v] >= 0) vst[col[v]] = true;
        }
        for (s = 1; vst[s]; s++);
        col[u] = s;  //if( s>k ) while(1) puts("f");
    }
}

int main() {
    int cas = 1;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d %d", &n, &m);
        init();
        memset(deg, 0, sizeof(deg));
        for (int i = 1; i <= m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            deg[u]++;
            deg[v]++;
            insert(u, v);
            insert(v, u);
        }
        paint();
        for (int i = 1; i <= n; i++) printf("%d\n", col[i]);
    }
}


