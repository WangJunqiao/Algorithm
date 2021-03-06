#define INF 0x3f3f3f3f

template<typename FLOW_TYPE = int, int MAXN = 210>
struct Netflow {
    FLOW_TYPE cap[MAXN][MAXN]; //cap: 残余网络的容量
    int n, L[MAXN], Q[MAXN]; //总节点数n(base0), L=level  Q=queue
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cap[i][j] = 0;
    }

    void add_edge(int u, int v, FLOW_TYPE f, FLOW_TYPE inf) { //每个pair(u, v)只能插入一次
        cap[u][v] += f;
        cap[v][u] += inf;
    }

    int _bfs(int S, int T) { //广搜,并标记level(只取流量大于0的边)
        int head = 0, tail = 0;
        memset(L, 0xff, sizeof(L));
        L[S] = 0;
        Q[tail++] = S;
        while (head < tail) {
            int u = Q[head++];
            for (int v = 0; v < n; v++)
                if (cap[u][v] > 0 && L[v] == -1)
                    L[Q[tail++] = v] = L[u] + 1;
        }
        return L[T] != -1;
    }

    FLOW_TYPE _find(int u, FLOW_TYPE in, int T) { //in:能流入u节点的最大流量. 返回u节点能流出的最大流量
        if (u == T) return in;
        FLOW_TYPE tmp, w = 0; //w表示已经从u流出的总流量
        for (int v = 0; v < n && w < in; v++) {
            if (cap[u][v] > 0 && L[v] == L[u] + 1) {
                if (tmp = _find(v, min(cap[u][v], in - w), T)) {
                    cap[u][v] -= tmp;
                    cap[v][u] += tmp;
                    w += tmp;
                }
            }
        }
        if (w < in) L[u] = -1;//关键的一句话
        return w;
    }

    FLOW_TYPE dinic(int S, int T) {
        FLOW_TYPE f, res = 0;
        while (_bfs(S, T)) while (f = _find(S, INF, T)) res += f;
        return res;
    }
};

Netflow<int, 210> flow;
//usage:
// flow.init(3);
// flow.add_edge(0, 1, 1, 0);
// flow.add_edge(1, 2, 2, 0);
// cout<<flow.dinic(0, 2)<<endl;