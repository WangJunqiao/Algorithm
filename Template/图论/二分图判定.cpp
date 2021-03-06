//-----------------------二分图判定-------
#define maxn 310
int adj[maxn][maxn]; //adj[i][j] = 1表示连通
int col[maxn]; //col=1白色，col=2黑色
bool dfs_bipartite(int n, int u, int c) {
    col[u] = c;
    for (int i = 0; i < n; i++)
        if (adj[u][i] == 1) { //连接的
            if (col[i] == 0) {
                if (!dfs_bipartite(n, i, 3 - c))
                    return false;
            } else if (col[i] == c) {
                return false;
            }
        }
    return true;
}

bool check_bipartite(int n) {
    memset(col, 0, sizeof(col));
    for (int i = 0; i < n; i++) {
        if (col[i] == 0) {
            if (dfs_bipartite(n, i, 1) == false)
                return false;
        }
    }
    return true;
}//------------------------------