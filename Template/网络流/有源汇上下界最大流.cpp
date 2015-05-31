/*有源汇上下界最大流  zju3229
solu:把必要流分离,集中到新的原汇点上,对于新的原汇点求一次最大流,判断是否有解.
再对于原来的原汇点求一次最大流就可以了.  第二种方法是二分,跟上下界最小流一样.
*/
#define maxn 1400
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
}//n,adj,src,sink赋值之后,调用dinic().....

struct Edge {
    int u, v, b, c;// b<=f<=c 上下界
} e[400004];

//插入 u->v b<=f<=c 新增源汇为ns,nt
void ins_l(int u, int v, int b, int c, int ns, int nt) {
    adj[u][nt] += b;
    adj[ns][v] += b;
    adj[u][v] += c - b;
}

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) != EOF) {
        //os,ot是建模的时候添加的, ns,nt是求解的时候添加的
        int os = N + M + 1, ot = N + M + 2, ns = 0, nt = N + M + 3; //old new
        n = nt + 1;
        src = ns;
        sink = nt;
        int sum = 0;
        for (int i = 0; i < n; i++) fill(adj[i], adj[i] + n, 0);
        for (int j = N + 1; j <= N + M; j++) {
            int g;
            scanf("%d", &g);// (j->ot) >=g
            ins_l(j, ot, g, inf, ns, nt);
            sum += g;
        }
        int id = 0;
        for (int i = 1; i <= N; i++) {
            int C, D;
            scanf("%d %d", &C, &D); //(os->i) <=D
            adj[os][i] += D;
            for (int k = 0; k < C; k++) {
                int T, l, r;
                scanf("%d %d %d", &T, &l, &r);
                T += N + 1; //(i->T) <l,r>
                e[id].u = i;
                e[id].v = T;
                e[id].b = l;
                e[id++].c = r;
                ins_l(i, T, l, r, ns, nt);
                sum += l;
            }
        }
        adj[ot][os] += inf;
        if (dinic() != sum) {
            puts("-1\n");
            continue; // 无解
        }
        //adj[ot][os]=adj[os][ot]=0; //由于流量是最后统计的(不会统计os->ot边),所以这些东西都不用删了
        //for(int i=0;i<n;i++) adj[ns][i]=adj[nt][i]=0;
        src = os;
        sink = ot;
        dinic();
        sum = 0;
        for (int i = 0; i < id; i++) {
            e[i].c -= adj[e[i].u][e[i].v];
            sum += e[i].c;
        }
        printf("%d\n", sum);
        for (int i = 0; i < id; i++) printf("%d\n", e[i].c);
        puts("");
    }
}
