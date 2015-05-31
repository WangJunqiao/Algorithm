//通过了 pku2135 pku3422 hdu3667 hdu 3376
//最小费用最大流 dd实现
#define maxn 10005
#define maxm 300005
#define inf 0x3fffffff
struct Edge {
    int u, v, cap, cost, x;
} E[maxm];
int e, l[maxn];

inline void init() {
    e = 0;
    memset(l, -1, sizeof(l));
}

inline void insert(int u, int v, int cap, int cost) { //单向边
    E[e].u = u;
    E[e].v = v;
    E[e].cap = cap;
    E[e].cost = cost;
    E[e].x = l[u];
    l[u] = e++;
    E[e].u = v;
    E[e].v = u;
    E[e].cap = 0;
    E[e].cost = -cost;
    E[e].x = l[v];
    l[v] = e++;
}

int q[20 * maxn], s, t, inq[maxn], dis[maxn], eid[maxn];

void min_cost_max_flow(int src, int sink, int &cap, int &cost) {//0~n-1
    cost = cap = 0;
    while (true) { //不断增广
        //begin spfa
        for (int i = 0; i < maxn; i++) dis[i] = inf; //-inf  最大费
        s = t = 0;
        q[t++] = src;
        inq[src] = 1;
        dis[src] = 0;
        while (s < t) {
            int u = q[s++];
            inq[u] = 0;
            for (int p = l[u]; p >= 0; p = E[p].x) {
                if (E[p].cap <= 0) continue;
                int v = E[p].v;
                if (dis[v] > dis[u] + E[p].cost) {  //<
                    dis[v] = dis[u] + E[p].cost;
                    eid[v] = p;
                    if (inq[v] == 0) {
                        inq[v] = 1;
                        q[t++] = v;
                    }
                }
            }
        } //end spfa
        if (dis[sink] >= inf) return;  //<=-inf
        int c = inf;
        for (int i = sink; i != src; i = E[eid[i]].u) c = min(c, E[eid[i]].cap);
        cost += dis[sink] * c;
        cap += c;
        for (int i = sink; i != src; i = E[eid[i]].u) {
            int p = eid[i];
            E[p].cap -= c;
            E[p ^ 1].cap += c;
        }
    }
}

//*****************模板结束*******************
int main() {
    int n, m, u, v, cap, cost;
    while (scanf("%d%d", &n, &m) != EOF) {
        init(); //初始化
        for (int i = 1; i <= m; i++) {
            scanf("%d %d %d %d", &u, &v, &cap, &cost);
            insert(u, v, cap, cost);
        }
        min_cost_max_flow(0, n - 1, cap, cost);
        printf("capicity: %d cost: %d\n", cap, cost);
    }
}
