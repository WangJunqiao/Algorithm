//lca的tarjan算法，通过zjut1504
#define maxn 110000
typedef pair <int, int> PII;

struct Tarjan {
    vector <int> adj[maxn];  //邻接表,双向边
    vector <PII> query[maxn];
    //查询（双向），u.pb(v, query_id)  v.pb(u, query_id)
    int out[maxn];          //每个query_id对应的lca
    //----以上需要外部赋值------------------
    void init(int N) {// base0, 每个case调用
        fill(pa, pa + N, -1);
    }

    int find(int u) {
        return (pa[u] == u) ? u : (pa[u] = find(pa[u]));
    }

    void lca(int r) {//手写递归, 传入树根， 如果是森林可以多次调用
        top = 0;
        st[top++] = r;
        st[top++] = 0;
        pa[r] = r;
        while (top) {
            int u = st[top - 2], &ind = st[top - 1];
            if (ind >= adj[u].size()) {
                top -= 2;
                for (int i = 0; i < query[u].size(); i++) {
                    int qv = query[u][i].first;
                    if (pa[qv] >= 0) out[query[u][i].second] = find(qv);
                }
                if (top) pa[u] = st[top - 2]; //次序很重要
            } else {
                int v = adj[u][ind++];
                if (pa[v] >= 0) continue;
                st[top++] = v;
                st[top++] = 0;
                pa[v] = v;
            }
        }
    }

    int pa[maxn], st[maxn * 2], top;
} tarjan; //使用方法：对adj，query赋值之后，调用init，lca。