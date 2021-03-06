//树上基于点的分治      Spoj 1825. Free tour II
//题意: 题目大意：给定一棵带权树，节点分黑白两色，求一条最长的简单路径的长度，且满足路径上黑点不超过K
#define maxn 420005
#define maxm 3000005
struct Edge {
    int v, val, next;
} E[maxm];

struct AdjList {
    static int e; //每个case初始化为0
    int l[maxn]; //
    void insert(int a, int b, int val = 0) { //单向边**************
        E[e].v = b;
        E[e].val = val;
        E[e].next = l[a];
        l[a] = e++;
    }

    void init() {
        memset(l, -1, sizeof(l));
    }
} adj;

int AdjList::e;
//****************模板结束***************
const int inf = -(1 << 29);

bool isr[maxn]; //是否被选为了根
int _st[maxn], _i[maxn], top; //栈
int vst[maxn], cnt; //标记
//对一颗子树进行拓扑排序,返回的arr中树根在前,子树在后,c base0
void topo_sort(int u, int *arr, int &c) {
    c = top = 0;
    cnt++;
    _st[++top] = u, _i[top] = adj.l[u], arr[c++] = u, vst[u] = cnt;
    while (top) {
        u = _st[top];
        if (_i[top] == -1) --top;
        else {
            int v = E[_i[top]].v;
            _i[top] = E[_i[top]].next;
            if (vst[v] == cnt || isr[v]) continue;
            _st[++top] = v, _i[top] = adj.l[v], arr[c++] = v, vst[v] = cnt;
        }
    }
}

int n, K, m;
bool black[maxn];
int num[maxn];

int _b[maxn], _b2[maxn], *ptr; //缓冲区

int findRoot(int u) { //在一颗子树中寻找一个合适的根
    int n;
    topo_sort(u, _b, n); //n=子树大小
    cnt++;
    for (int i = n - 1; i >= 0; i--) { //calc num[] array
        int a = _b[i], f = 1;
        num[a] = 1;
        for (int j = adj.l[a]; j != -1; j = E[j].next) {
            int b = E[j].v;
            if (vst[b] == cnt && !isr[b]) {
                num[a] += num[b];
                if (num[b] > n / 2) f = 0;
            }
        }
        vst[a] = cnt;
        if (n - num[a] > n / 2) f = 0;
        if (f) return a;
    }
}
//以上函数可以通用 ******************************************************


struct DD {
    int *d, s;

    bool operator<(const DD &b) const {
        return s < b.s;
    }
} dd[maxn];

int ind;


typedef pair <int, int> PII;
PII p[maxn];

int ans;

inline void check(int &a, int b) {
    if (a < b) a = b;
}

void dfs(int u) {
    int r = findRoot(u), c;  //printf("root: %d\n",r);
    isr[r] = true;
    ptr = _b2;
    ind = 0;

    for (int j = adj.l[r]; j != -1; j = E[j].next) {
        int v = E[j].v;
        if (isr[v]) continue; //
        topo_sort(v, _b, c);
        for (int i = 0; i <= c; i++) ptr[i] = inf;
        p[v] = PII(black[v], E[j].val); //
        cnt++;
        for (int i = 0; i < c; i++) {
            int sa = _b[i];
            check(ptr[p[sa].first], p[sa].second);
            for (int k = adj.l[sa]; k != -1; k = E[k].next) {
                int sb = E[k].v;
                if (vst[sb] == cnt || isr[sb]) continue;
                p[sb].first = p[sa].first + black[sb];
                p[sb].second = p[sa].second + E[k].val;
            }
            vst[sa] = cnt;
        }
        for (int i = 0; i <= c; i++) {
            if (i) check(ptr[i], ptr[i - 1]);
            if (i + black[r] <= K) check(ans, ptr[i]);
        }
        dd[ind].d = ptr, dd[ind++].s = c;
        ptr += (c + 1);
    }
    sort(dd, dd + ind);
    //merge
    for (int i = 1; i < ind; i++) {
        for (int j = 0; j <= dd[i].s; j++) {
            int t = K - j - black[r];
            if (t < 0) continue;
            if (t <= dd[i - 1].s) check(ans, dd[i].d[j] + dd[i - 1].d[t]);
            else check(ans, dd[i].d[j] + dd[i - 1].d[dd[i - 1].s]);
        }
        for (int j = 0; j <= dd[i].s; j++) {
            if (j <= dd[i - 1].s) check(dd[i].d[j], dd[i - 1].d[j]);
            if (j) check(dd[i].d[j], dd[i].d[j - 1]);
        }
    }
    for (int j = adj.l[r]; j != -1; j = E[j].next) {
        int v = E[j].v;
        if (!isr[v]) dfs(v);
    }
}

int main() {
//freopen("in.txt","r",stdin);
    while (scanf("%d %d %d", &n, &K, &m) != EOF) {
        memset(isr, false, sizeof(isr));
        memset(black, false, sizeof(black));
        adj.init();
        int id;
        AdjList::e = 0;
        for (int i = 1; i <= m; i++) scanf("%d", &id), black[id] = true;
        for (int i = 1; i < n; i++) {
            int a, b, val;
            scanf("%d %d %d", &a, &b, &val);
            adj.insert(a, b, val);
            adj.insert(b, a, val);
        }
        ans = 0;
        dfs(1);
        cout << ans << endl;
    }
}