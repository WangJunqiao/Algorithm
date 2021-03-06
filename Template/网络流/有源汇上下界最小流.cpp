//有源汇上下界最小流  sgu176
//solu: 二分答案mid, t->s的流量为mid,看是否有无源汇可行流
#define maxn 140
#define inf  0x3f3f3f3f
int n, adj[maxn][maxn], src, sink; //总节点数n(base0), 流网络adj, 源s汇t
int L[maxn], Q[maxn]; //L=level  Q=queue
int _bfs() { //广搜,并标记level(只取流量大于0的边)
    int s = 0, t = 0, u;
    memset(L, 0xff, sizeof(L));
    L[src] = 0;
    Q[t++] = src;
    while (s < t) {
        u = Q[s++];
        for (int v = 0; v < n; v++)
            if (adj[u][v] && L[v] == -1)
                L[Q[t++] = v] = L[u] + 1;
    }
    return L[sink] != -1;
}

int _find(int u, int in) { //in:能流入u节点的最大流量. 返回u节点能流出的最大流量
    if (u == sink) return in;
    int t, w = 0; //w表示已经从u流出的总流量
    for (int v = 0; v < n && w < in; v++) {
        if (adj[u][v] && L[v] == L[u] + 1) {
            if (t = _find(v, min(adj[u][v], in - w))) {
                adj[u][v] -= t;
                adj[v][u] += t;
                w += t;
            }
        }
    }
    if (w < in)L[u] = -1;//关键的一句话
    return w;
}

int dinic() {
    int t, res = 0;
    while (_bfs())while (t = _find(src, inf))res += t;
    return res;
}

//n,adj,src,sink赋值之后,调用dinic().....
struct Edge {
    int u, v, b, c;// b<=f<=c 上下界
} e[40004];

//计算无源汇上下界可行流, 传入无源汇边集, cnt base0, 选取的src和sink, 总节点数n base0
bool no_src_feasible_flow(Edge *e, int cnt, int ns, int nt, int n) {
    ::n = n;
    src = ns;
    sink = nt;
    for (int i = 0; i < n; i++) fill(adj[i], adj[i] + n, 0);
    int sf = 0;
    for (int i = 0; i < cnt; i++) {
        int u = e[i].u, v = e[i].v, b = e[i].b, c = e[i].c;
        if (b > c || c < 0) return false; //无解
        adj[u][sink] += b;
        adj[src][v] += b;
        adj[u][v] += c - b;
        sf += b;
    }
    return dinic() == sf;
}//----over----

int main() {
    int N, E;
    while (scanf("%d %d", &N, &E) != EOF) {
        //os,ot是建模的时候的, ns,nt是求解的时候添加的
        int os = 1, ot = N, ns = 0, nt = N + 1; //old new

        for (int j = 0; j < E; j++) {
            int u, v, b, s;
            scanf("%d %d %d %d", &u, &v, &b, &s);
            assert(u * v > 0);
            e[j].u = u;
            e[j].v = v;
            e[j].c = b;
            if (s == 0) {            //不必满流
                e[j].b = 0;
            } else {                 //必须满流
                e[j].b = b;
            }
        }
        e[E].u = ot;
        e[E].v = os;
        e[E].b = 0;

        int l = 0, r = 100000005;
        e[E].c = r;
        if (no_src_feasible_flow(e, E + 1, ns, nt, nt + 1) == false) {
            puts("Impossible");
            continue; // 无解
        }
        e[E].c = 0;
        if (no_src_feasible_flow(e, E + 1, ns, nt, nt + 1) == true) {
            l = r = 0;
            goto output;
        }
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            e[E].c = mid;
            if (no_src_feasible_flow(e, E + 1, ns, nt, nt + 1)) r = mid;
            else l = mid;
        }
        output:;
        e[E].c = r;
        no_src_feasible_flow(e, E + 1, ns, nt, nt + 1);
        printf("%d\n", r);
        for (int i = 0; i < E; i++) printf("%d%s", e[i].c - adj[e[i].u][e[i].v], (i == E - 1 ? "\n" : " "));
    }
}
