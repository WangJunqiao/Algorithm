#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

//树同构判定  pku1635

typedef vector<int> VI;
#define maxn 11000
VI adj[maxn]; //init---
int vst[maxn];

int _dfs(int u, int mod) {
    VI h;
    vst[u] = 1;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (vst[v]) continue;
        h.push_back(_dfs(v, mod));
    }
    sort(h.begin(), h.end());
    int ret = 1;
    for (int i = 0; i < h.size(); i++) {
        ret = ((ret * (long long) 10007 + h[i]) ^ 123456789) % mod;
    }
    return ret;
}

//有根树的hash值, 传入根,左移(用于多次判定),gcd(32,shl)=1
int hash(int root, int mod) {
    fill(vst, vst + maxn, 0);
    return _dfs(root, mod);
}//*******树的哈希**************


//http://acm.fafu.edu.cn/showproblem?problem_id=1024 
//无根树同构,枚举根计算全部的hash值,排序后比较 O(n^2)
int main() {
    int n1, n2;
    while (scanf("%d%d", &n1, &n2) != EOF) {
        for (int i = 1; i <= n1; i++) adj[i].clear();
        for (int i = 1; i < n1; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int h[110], t[110];
        for (int i = 1; i <= n1; i++) h[i] = hash(i, 1000000007);

        for (int i = 1; i <= n2; i++) adj[i].clear();
        for (int i = 1; i < n2; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 1; i <= n2; i++) t[i] = hash(i, 1000000007);

        sort(h + 1, h + 1 + n1);
        sort(t + 1, t + 1 + n2);
        bool same = (n1 == n2);
        for (int i = 1; i <= n1; i++) if (h[i] != t[i]) same = false;
        if (same) puts("same");
        else puts("different");
    }
}





