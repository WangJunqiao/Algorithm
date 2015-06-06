//次小生成树 O(n^2) pku1679 Ural 1416
//solu: 先算出一棵mst,然后枚举根dfs,然后枚举添加edge[u][root]删除root->u最大边
#define maxn 510
#define inf 0x1fffffff

struct Edge {
    int v, val, x;
} E[11000];
int l[maxn], e;

void init() {
    e = 0;
    memset(l, -1, sizeof(l));
}

void insert(int a, int b, int val = 0) { //单向边
    E[e].v = b;
    E[e].val = val;
    E[e].x = l[a];
    l[a] = e++;
}

int N, M, cost, cost2;
//点数N base0,边数,最小,次小
int mi[maxn], pre[maxn], vst[maxn];
int dis[maxn][maxn];

void MST(int N, int r) {
    fill(pre, pre + N, 0);
    fill(mi, mi + N, inf);
    cost = mi[r] = 0;
    for (int i = 0; i < N; i++) {
        int v = -1;
        for (int j = 0; j < N; j++) {
            if (pre[j] < 0)continue;
            if (v < 0 || mi[j] < mi[v]) v = j;
        }
        if (v != r) {
            insert(pre[v], v, dis[pre[v]][v]);
            insert(v, pre[v], dis[pre[v]][v]);
        }
        for (int j = 0; j < N; j++) {
            if (pre[j] >= 0 && mi[j] > dis[v][j]) {
                mi[j] = dis[v][j];
                pre[j] = v;
            }
        }
        cost += mi[v];
        pre[v] = -1; //标记已选择
    }
}

void dfs(int u, int r, int D, int maxE) {
    if (D >= 3) cost2 = min(cost2, cost + dis[u][r] - maxE);
    vst[u] = 1;
    for (int p = l[u]; p >= 0; p = E[p].x) {
        int v = E[p].v;
        if (vst[v]) continue;
        dfs(v, r, D + 1, max(maxE, E[p].val));
    }
}

int main() {
    while (scanf("%d %d", &N, &M) != EOF) {
        for (int i = 0; i < N; i++) fill(dis[i], dis[i] + N, inf);
        for (int i = 0; i < M; i++) {
            int a, b, val;
            scanf("%d %d %d", &a, &b, &val);
            a--, b--;
            dis[a][b] = dis[b][a] = min(dis[a][b], val);
        }
        init();
        MST(N, 0);
        cost2 = inf;
        for (int i = 0; i < N; i++) {
            fill(vst, vst + N, 0);
            dfs(i, i, 1, 0); //基于无重边的算法
        }
        if (cost2 == inf) cost2 = -1;
        printf("Cost: %d\nCost: %d\n", cost, cost2);
    }
}