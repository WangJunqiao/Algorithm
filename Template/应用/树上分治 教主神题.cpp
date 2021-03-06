//pku 1741 树上点的分治 (递归版本)
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define maxn 10010

typedef pair<int, int> PII; //(v, cost)
vector<PII> adj[maxn];

int N, L, ans;
int vst[maxn], te = 1; //标记
bool isRoot[maxn]; //是否已经被选为根
int num[maxn];//子树有几个点

//下面两个的custom的具体计算函数
int calc(int *d, int ind, int L) { //计算有多少对d[i]+d[j]<=L(i可能等于j),下标从0开始
    int ret = 0;
    sort(d, d + ind);
    for (int i = 1, j = -1; i < ind; i++) {
        if (j >= 0 && d[i] + d[j] > L)
            while (j >= 0 && d[i] + d[j] > L)j--;
        else
            while (j + 1 < i && d[i] + d[j + 1] <= L)j++;
        ret += j + 1;
    }
    return ret;
}

int d[maxn], ind;

//距离数组
void _dis(int u, int D) { //算距离,需先初始化ind
    vst[u] = te;
    d[ind++] = D;
    for (int i = 0; i < (int) adj[u].size(); i++) {
        int v = adj[u][i].first;
        if (isRoot[v] || vst[v] == te) continue;
        _dis(v, D + adj[u][i].second);
    }
}

//以下可以重用
void tree_count(int u) { //统计节点个数
    vst[u] = te;
    num[u] = 1;
    for (int i = 0; i < (int) adj[u].size(); i++) {
        int v = adj[u][i].first;
        if (isRoot[v] || vst[v] == te) continue;
        tree_count(v);
        num[u] += num[v];
    }
}

int tree_find_root(int tot, int u) { //tot=当前子树总点数
    vst[u] = te;
    bool can = true;
    if (tot - num[u] > tot / 2) return -1; //
    for (int i = 0; i < (int) adj[u].size(); i++) {
        int v = adj[u][i].first, r;
        if (isRoot[v] || vst[v] == te) continue;
        if (num[v] > tot / 2) can = false;
        if ((r = tree_find_root(tot, v)) >= 0) return r;
    }
    if (can) return u;
    return -1;
}

void tree_dfs(int u) { //主递归过程
    te++;
    tree_count(u);
    te++;
    int r = tree_find_root(num[u], u);
    isRoot[r] = true;
    //下面这个+-的过程计算了经过节点r的所有路径
    te++;
    ind = 0;
    _dis(r, 0);
    ans += calc(d, ind, L);
    for (int i = 0; i < (int) adj[r].size(); i++) {
        int v = adj[r][i].first;
        if (isRoot[v]) continue;
        te++;
        ind = 0;
        _dis(v, 0);
        ans -= calc(d, ind, L - 2 * adj[r][i].second);
    }
    //递归
    for (int i = 0; i < (int) adj[r].size(); i++) {
        int v = adj[r][i].first;
        if (isRoot[v]) continue;
        tree_dfs(v);
    }
}

int main() {
    while (scanf("%d%d", &N, &L)) {
        if (N == 0 && L == 0) break;
        memset(isRoot, false, sizeof(isRoot));
        for (int i = 1; i <= N; i++) adj[i].clear();
        for (int i = 1; i < N; i++) {
            int a, b, val;
            scanf("%d%d%d", &a, &b, &val);
            adj[a].push_back(PII(b, val));
            adj[b].push_back(PII(a, val));
        }
        ans = 0;
        tree_dfs(1);
        printf("%d\n", ans);
    }
}