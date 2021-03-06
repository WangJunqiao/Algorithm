/*有源汇上下界最大流  zju3229
solu:把必要流分离,集中到新的原汇点上,对于新的原汇点求一次最大流,判断是否有解.
再对于原来的原汇点求一次最大流就可以了.
*/
#define MAXN 1400
#define MAXE 1000000
#define inf  0x3f3f3f3f
struct Edge {
    int v, c, x;
} E[MAXE]; //指向的节点, 剩余可增广的流量
int l[MAXN], e;                     //必须保证e的初始值是偶数
void init() {
    e = 0;
    memset(l, -1, sizeof(l));
}

inline void insert(int u, int v, int f, int invf) { //u->v=f   v->u=invf
    E[e].v = v;
    E[e].c = f;
    E[e].x = l[u];
    l[u] = e++;
    E[e].v = u;
    E[e].c = invf;
    E[e].x = l[v];
    l[v] = e++;
}

struct Netflow {
    int src, sink; //需要初始化
    //以上
    int L[MAXN], Q[MAXN];

    int _bfs() {
        int s = 0, t = 0, u;
        memset(L, 0xff, sizeof(L));
        L[src] = 0;
        Q[t++] = src;
        while (s < t) {
            u = Q[s++];
            for (int p = l[u]; p >= 0; p = E[p].x)
                if (E[p].c && L[E[p].v] == -1)
                    L[(Q[t++] = E[p].v)] = L[u] + 1;
        }
        return L[sink] != -1;
    }

    int _find(int u, int in) {
        if (u == sink) return in;
        int t, w = 0;
        for (int p = l[u]; p >= 0 && w < in; p = E[p].x) {
            if (E[p].c > 0 && L[E[p].v] == L[u] + 1) {
                if (t = _find(E[p].v, min(E[p].c, in - w))) {
                    E[p].c -= t;
                    E[p ^ 1].c += t;
                    w += t;
                }
            }
        }
        if (w < in)L[u] = -1;
        return w;
    }

    int dinic() {
        int t, res = 0;
        while (_bfs())while (t = _find(src, inf))res += t;
        return res;
    }
} flow; //********模板结束***********
//init(); insert(...); flow.src=.. ; flow.dinic();

//插入 u->v b<=f<=c 新增源汇为ns,nt
void ins_l(int u, int v, int b, int c, int ns, int nt) {
    insert(u, nt, b, 0);
    insert(ns, v, b, 0);
    insert(u, v, c - b, 0);
}

int f[1400][1400];

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) != EOF) {
        //os,ot是建模的时候添加的, ns,nt是求解的时候添加的
        int os = 0, ot = N + M + 1, ns = ot + 1, nt = ns + 1; //old new
        int sum = 0;
        init();
        for (int i = 0; i <= nt; i++) fill(f[i], f[i] + nt + 1, -1);
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
            ins_l(os, i, 0, D, ns, nt);
            for (int k = 0; k < C; k++) {
                int T, l, r;
                scanf("%d %d %d", &T, &l, &r);
                T += N + 1; //(i->T) <l,r>
                f[i][T] = r;
                ins_l(i, T, l, r, ns, nt);
                sum += l;
            }
        }
        ins_l(ot, os, 0, inf, ns, nt); //转化

        flow.src = ns;
        flow.sink = nt;
        if (flow.dinic() != sum) { //判断可行流是否存在
            puts("-1\n");
            continue; //无解
        }
        //adj[ot][os]=adj[os][ot]=0; //由于流量是最后统计的(不会统计os->ot边),所以这些东西都不用删了
        //for(int i=0;i<n;i++) adj[ns][i]=adj[nt][i]=0;
        flow.src = os;
        flow.sink = ot;
        flow.dinic();
        sum = 0; //统计流量
        for (int i = 1; i <= N; i++) {
            for (int p = l[i]; p >= 0; p = E[p].x) {
                int v = E[p].v;
                if (!(v > N && v <= N + M)) continue;
                f[i][v] -= E[p].c;
                sum += f[i][v];
            }
        }
        printf("%d\n", sum); //输出每条边的容量
        for (int i = 1; i <= N; i++) for (int j = N + 1; j <= N + M; j++) if (f[i][j] >= 0) printf("%d\n", f[i][j]);
        puts("");
    }
}





