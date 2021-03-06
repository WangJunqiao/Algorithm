/*
pku 3177 pku 3352 hdu 4005
*/
//无向图边双连通(点的集合),以桥为分割. 8字形变成一个点
struct bidirGraph {
    int dep[maxn], low[maxn], q[maxn];
    int *l;
    Edge *E;

    void _tarjan(int u, int D, int _i) { //当前点,深度,入边序号
        low[u] = dep[u] = D;
        for (int i = l[u]; i >= 0; i = E[i].next) {
            if ((i ^ 1) == _i) continue;
            int v = E[i].v;
            if (dep[v] < 0) {
                _tarjan(v, D + 1, i);
                low[u] = min(low[u], low[v]);
            } else
                low[u] = min(low[u], dep[v]);
        }
    }

    bool qiao(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        return low[v] > dep[u];
    }

    //n点数0~n-1, label每个点在新图中的编号,可以根据label来rebuild
    int main(int n, int *_l, Edge *_E, int *label) {
        l = _l, E = _E;
        for (int i = 0; i < n; i++) dep[i] = label[i] = -1;
        for (int i = 0; i < n; i++) if (dep[i] < 0) _tarjan(i, 0, -1);
        int c = 0, s, t;
        for (int i = 0; i < n; i++) {
            if (label[i] >= 0) continue;
            s = t = 0;
            q[t++] = i;
            label[i] = c;
            while (s < t) { //bfs
                int u = q[s++], v;
                for (int j = l[u]; j >= 0; j = E[j].next) {
                    v = E[j].v;
                    if (qiao(u, v) || label[v] >= 0) continue;
                    q[t++] = v;
                    label[v] = c;
                }
            }
            c++;
        }
        return c;
    }
} ins;

//-----end-----
int label[maxn];

void rebuild(int n) {
    for (int i = 0; i < n; i++) {
        for (int p = adj.l[i]; p >= 0; p = E[p].next) {
            int j = E[p].v;
            if (ins.qiao(i, j)) {
                adj2.insert(label[i], label[j], E[p].val);
                adj2.insert(label[j], label[i], E[p].val);
            }
        }
    }
}//----