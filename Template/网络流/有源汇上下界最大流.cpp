/*��Դ�����½������  zju3229
solu:�ѱ�Ҫ������,���е��µ�ԭ�����,�����µ�ԭ�����һ�������,�ж��Ƿ��н�.
�ٶ���ԭ����ԭ�����һ��������Ϳ�����.  �ڶ��ַ����Ƕ���,�����½���С��һ��.
*/
#define maxn 1400
#define inf  0x3f3f3f3f
int n, adj[maxn][maxn], src, sink; //�ܽڵ���n(base0), ������adj, Դs��t
int L[maxn], Q[maxn]; //L=level  Q=queue
int _bfs() { //����,�����level(ֻȡ��������0�ı�)
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

int _find(int u, int in) { //in:������u�ڵ���������. ����u�ڵ����������������
    if (u == sink) return in;
    int t, w = 0; //w��ʾ�Ѿ���u������������
    for (int v = 0; v < n && w < in; v++) {
        if (adj[u][v] && L[v] == L[u] + 1) {
            if (t = _find(v, min(adj[u][v], in - w))) {
                adj[u][v] -= t;
                adj[v][u] += t;
                w += t;
            }
        }
    }
    if (w < in)L[u] = -1;//�ؼ���һ�仰
    return w;
}

int dinic() {
    int t, res = 0;
    while (_bfs())while (t = _find(src, inf))res += t;
    return res;
}//n,adj,src,sink��ֵ֮��,����dinic().....

struct Edge {
    int u, v, b, c;// b<=f<=c ���½�
} e[400004];

//���� u->v b<=f<=c ����Դ��Ϊns,nt
void ins_l(int u, int v, int b, int c, int ns, int nt) {
    adj[u][nt] += b;
    adj[ns][v] += b;
    adj[u][v] += c - b;
}

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) != EOF) {
        //os,ot�ǽ�ģ��ʱ����ӵ�, ns,nt������ʱ����ӵ�
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
            continue; // �޽�
        }
        //adj[ot][os]=adj[os][ot]=0; //�������������ͳ�Ƶ�(����ͳ��os->ot��),������Щ����������ɾ��
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
