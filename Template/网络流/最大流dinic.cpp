//最大流 dinic  http://acm.hdu.edu.cn/showproblem.php?pid=3046已AC
template<typename FLOW_TYPE = int, int MAXN = 20010, int MAXE = 60000>
struct Netflow {
    int L[MAXN], Q[MAXN]; //L=level  Q=queue
    struct Edge {
        int v, x;
        FLOW_TYPE c;
    } E[MAXE]; //c:剩余可增广的流量capacity
    int X[MAXN], e; //邻接表
    void init() {
        e = 0;
        memset(X, -1, sizeof(X));
    }

    void add_edge(int u, int v, FLOW_TYPE f, FLOW_TYPE invf) { //u->v=f   v->u=invf
        E[e].v = v;
        E[e].c = f;
        E[e].x = X[u];
        X[u] = e++;
        E[e].v = u;
        E[e].c = invf;
        E[e].x = X[v];
        X[v] = e++;
    }

    bool _bfs(int S, int T) { //从S开始广搜, 并标记level(只取流量大于0的边)
        int head = 0, tail = 0;
        memset(L, -1, sizeof(L));
        L[S] = 0;
        Q[tail++] = S;
        while (head < tail) {
            int u = Q[head++];
            for (int x = X[u]; x >= 0; x = E[x].x)
                if (E[x].c > 0 && L[E[x].v] == -1)
                    L[(Q[tail++] = E[x].v)] = L[u] + 1;
        }
        return L[T] != -1;
    }

    FLOW_TYPE _find(int u, FLOW_TYPE in, int T) { //in:能流入u节点的最大流量. 返回u节点能流出的最大流量
        if (u == T) return in;
        FLOW_TYPE tmp, w = 0; //w表示已经从u流出的总流量
        for (int x = X[u]; x >= 0 && w < in; x = E[x].x) {
            if (E[x].c > 0 && L[E[x].v] == L[u] + 1) {
                if (tmp = _find(E[x].v, min(E[x].c, in - w), T)) {
                    E[x].c -= tmp;
                    E[x ^ 1].c += tmp; //这里表示必须
                    w += tmp;        //多路增广优势巨大
                }
            }
        }
        if (w < in) L[u] = -1;//关键的一句话
        return w;
    }

    FLOW_TYPE dinic(int S, int T) { //在当前的残余网络求S到T的最大流
        FLOW_TYPE f, res = 0;
        while (_bfs(S, T)) while (f = _find(S, inf, T)) res += f;
        return res;
    }
}; //********模板结束***********
Netflow<int, 41000, 300000> flow;
// 使用方法:
// flow.init();
// flow.add_edge(0, 1, 1, 0);
// flow.add_edge(1, 2, 2, 0);
// cout<<flow.dinic(0, 2)<<endl;