//单点k度限制最小生成树  pku1639 O(VlogE+E+V*K) 
//基于无重边的算法
//solu: 先计算一个度数最小的生成树,然后逐步调整,每次增加一个度数
#define maxn 1100
#define maxm 110000
#define inf 0x3fffffff
struct Edge {
    int v, val, sel, x;
} E[maxm];
//6倍边数
int e; //每个cas初始化
struct AdjList {
    int l[maxn];

    //
    void insert(int a, int b, int val = 0, int sel = 0) {
        E[e].v = b;
        E[e].val = val;
        E[e].sel = sel;
        E[e].x = l[a];
        l[a] = e++;
    }

    void init() { memset(l, -1, sizeof(l)); }
} adj, adj2;

struct DD {
    int v, val, eid;

    DD(int _v = 0, int _val = 0, int _eid = 0) : v(_v), val(_val), eid(_eid) { };

    bool operator<(const DD &b) const {
        return val > b.val;
    }
};

priority_queue <DD> pq;
int dis[maxn], vst[maxn];

int prim(int n, int r) {  //0~n-1的最小生成树，r为根,返回总权值
    fill(dis, dis + n, inf);
    fill(vst, vst + n, 0);
    pq.push(DD(r, 0, -1));
    dis[r] = 0;
    int ret = 0;
    while (!pq.empty()) {
        DD tmp = pq.top();
        pq.pop();
        if (vst[tmp.v]) continue;
        ret += tmp.val;
        vst[tmp.v] = 1; //加入生成树中
        if (tmp.eid >= 0) E[tmp.eid].sel = E[tmp.eid ^ 1].sel = 1; //选择
        for (int p = adj.l[tmp.v]; p >= 0; p = E[p].x) {
            int v = E[p].v;
            if (vst[v] == 0 && dis[v] > E[p].val) {
                dis[v] = E[p].val;
                pq.push(DD(v, dis[v], p));
            }
        }
    }
    return ret;
}

int de, ae; //delete eid, add eid
void dfs(int u, int D, int r, int meid) {
    vst[u] = 1;
    if (D >= 3) {
        for (int p = adj2.l[u]; p >= 0; p = E[p].x) {
            if (E[p].v != r) continue;
            if (de < 0 || E[meid].val - E[p].val > E[de].val - E[ae].val) {
                de = meid;
                ae = p;
            }
        }
    }
    for (int p = adj2.l[u]; p >= 0; p = E[p].x) {
        if (vst[E[p].v] || !E[p].sel) continue;
        int me = meid;
        if (D >= 2 && E[p].val > E[me].val) me = p;
        dfs(E[p].v, D + 1, r, me);
    }
}

int ve[maxm];

int MST_kD(int n, int r, int k) { //0~n-1, r为根,r有不超过k度限制
    const int A = 1000000; //大于总边权的一个值*******
    for (int p = adj.l[r]; p >= 0; p = E[p].x) E[p].val += A;
    int ret = prim(n, r), deg = ret / A; //deg当前度数
    if (k < deg) return -1; //无解
    ret = ret - A * deg;
    //精简化 adj2
    adj2.init();
    fill(ve, ve + e, 0);
    for (int i = 0; i < n; i++) {
        for (int p = adj.l[i]; p >= 0; p = E[p].x) {
            if (E[p].val >= A) E[p].val -= A;
            if ((i == r || E[p].sel) && !ve[p]) {
                adj2.insert(i, E[p].v, E[p].val, E[p].sel); //保持^1性质
                adj2.insert(E[p].v, i, E[p].val, E[p].sel);
                ve[p] = ve[p ^ 1] = 1;
            }
        }
    }
    int ie = e;
    e += 2;
    E[ie].val = -inf; //特别设计的
    while (deg < k) {
        fill(vst, vst + n, 0);
        de = ae = -1;
        dfs(r, 1, r, ie);
        if (de < 0 || E[de].val - E[ae].val <= 0) break;
        E[de].sel = E[de ^ 1].sel = 0;
        E[ae].sel = E[ae ^ 1].sel = 1;
        ret -= (E[de].val - E[ae].val);
        deg++;
    }
    return ret;
}// e=0; adj.init(); adj.insert(...); MST_kD(n,r,k)...

int main() {
    int n, k;
    while (cin >> n) {
        map <string, int> mp;
        e = 0;
        adj.init();
        for (int i = 0; i < n; i++) {
            string s1, s2;
            int val;
            cin >> s1 >> s2 >> val;
            if (mp.find(s1) == mp.end()) {
                int id = mp.size();
                mp[s1] = id;
            }
            if (mp.find(s2) == mp.end()) {
                int id = mp.size();
                mp[s2] = id;
            }
            adj.insert(mp[s1], mp[s2], val);
            adj.insert(mp[s2], mp[s1], val);
        }
        cin >> k;
        printf("Total miles driven: %d\n", MST_kD(mp.size(), mp["Park"], k));
    }
}