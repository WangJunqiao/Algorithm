//Hopcroft Karp算法在增加匹配集合M时,每次寻找多条增广路,复杂度O(V^0.5*E)
#include <iostream>

using namespace std;
const int MAXN = 50005;
const int MAXM = 150005;
int nx, ny, m, x, y, ans;
int edge, head[MAXN], nxt[MAXM], e[MAXM];
int cx[MAXN], cy[MAXN];
// cx[i]表示xi对应的匹配,cy[i]表示yi对应的匹配.
int distx[MAXN], disty[MAXN]; // 层的概念,即在BFS中的第几层.
int que[MAXN];

void init() {
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    memset(head, -1, sizeof(head));
    edge = 0;
    ans = 0;
}

inline void addedge(int u, int v) {
    e[edge] = v;
    nxt[edge] = head[u];
    head[u] = edge++;
}

bool BFS() {
    bool flag = 0;
    memset(distx, 0, sizeof(distx));
    memset(disty, 0, sizeof(disty));
    int l = 0, r = 0, h, t;
    for (int i = 1; i <= nx; i++)
        if (cx[i] == -1)
            que[r++] = i;
    while (l != r) {
        for (h = l, t = r; h != t; h = (h + 1) % MAXN) {
            int u = que[h];
            for (int i = head[u]; i != -1; i = nxt[i]) {
                int v = e[i];
                if (!disty[v]) {
                    disty[v] = distx[u] + 1;
                    if (cy[v] == -1) flag = 1;
                    else {
                        distx[cy[v]] = disty[v] + 1;
                        que[r] = cy[v];
                        r = (r + 1) % MAXN;
                    }
                }
            }
        }
        l = t;
    }
    return flag;
}

bool DFS(int u) { //递归层数为sqrt(n)
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = e[i];
        if (disty[v] == distx[u] + 1) { //说明v是u的后继结点.
            disty[v] = 0; // v被用过了,不能再作为其他点的后继结点了.
            if (cy[v] == -1 || DFS(cy[v])) {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

void Hopcroft_Karp() {
    while (BFS())
        for (int i = 1; i <= nx; i++)
            if (cx[i] == -1 && DFS(i))
                ans++;
}

int main() {
    while (scanf("%d %d %d", &nx, &ny, &m) != EOF) {
        init();
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &x, &y);
            addedge(x, y);
        }
        Hopcroft_Karp();
        printf("%d\n", ans);
    }
}
