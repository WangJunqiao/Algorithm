#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

//hdu 3311
#define maxn 1100

struct Edge {
    int v, val, next;
} E[55555];
int l[maxn], e;

void init() {
    e = 0;
    memset(l, -1, sizeof(l));
}

inline void insert(int a, int b, int val) {
    E[e].v = b;
    E[e].val = val;
    E[e].next = l[a];
    l[a] = e++;
}

//斯坦纳树 部分点的最小生成树 复杂度O(n*3^sel)
int dp[1 << 6][maxn];  // dp[s][j]表示状态s含有的点连在一起了，出口点是j
queue<int> q;
bool inq[1 << 6][maxn];
#define inf (1<<30)

int steiner(int n, vector<int> sel) { //0~n-1, sel里面的点需要构成最小生成树
    int sz = sel.size();
    for (int s = 0; s < (1 << sz); s++) {
        for (int j = 0; j < n; j++) {
            dp[s][j] = inf;
            inq[s][j] = false;
        }
    }
    while (!q.empty()) q.pop();
    for (int i = 0; i < sz; i++) {
        int s = (1 << i), u = sel[i];
        dp[s][u] = 0;
        q.push(s);
        q.push(u);
        inq[s][u] = true;
    }

    while (!q.empty()) { //spfa的写法
        int s = q.front();
        q.pop();
        int u = q.front();
        q.pop();
        inq[s][u] = false;

        for (int p = l[u]; p >= 0; p = E[p].next) { //出口点改变
            int v = E[p].v;
            if (dp[s][v] > dp[s][u] + E[p].val) {
                dp[s][v] = dp[s][u] + E[p].val;
                if (inq[s][v] == false) {
                    q.push(s);
                    q.push(v);
                    inq[s][v] = true;
                }
            }
        }
        int bb = (1 << sz) - 1 - s;
        for (int msk = bb; msk; msk = (msk - 1) & bb) { //结合
            int ns = s | msk;
            if (dp[ns][u] > dp[s][u] + dp[msk][u]) {
                dp[ns][u] = dp[s][u] + dp[msk][u];
                if (inq[ns][u] == false) {
                    q.push(ns);
                    q.push(u);
                    inq[ns][u] = true;
                }
            }
        }
    }
    int ret = inf;
    for (int i = 0; i < n; i++) ret = min(ret, dp[(1 << sz) - 1][i]);
    return ret;
} //----------------------------------------------------------


int main() {
    int n, m, ee;
    while (scanf("%d %d %d", &n, &m, &ee) != EOF) {
        init();
        for (int i = 1; i <= n + m; i++) {
            int c;
            scanf("%d", &c);
            insert(0, i, c);
            insert(i, 0, c);
        }
        for (int i = 0; i < ee; i++) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            insert(a, b, c);
            insert(b, a, c);
        }
        vector<int> sel;
        for (int i = 0; i <= n; i++) sel.push_back(i);
        printf("%d\n", steiner(n + m + 1, sel));
    }
}