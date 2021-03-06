#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<queue>

using namespace std;

//树链剖分  hdu3966  给定一棵树，动态改变一些树链上点的权值，动态查询
#define maxn 55000

struct Node {
    int val;
    int add; //延迟标记
    //
    int l, r;
    Node *ls, *rs; //左右儿子
    void init(int _l, int _r) {
        l = _l, r = _r;
        ls = rs = NULL;
        add = 0;//延迟信息必须清0!!!
    }

    int mid() { return (l + r) >> 1; }

    void push_down() { //保证有儿子
        ls->add += add;
        rs->add += add;
        add = 0;
        if (ls->l == ls->r) {
            ls->val += ls->add;
            ls->add = 0;
        }
        if (rs->l == rs->r) {
            rs->val += rs->add;
            rs->add = 0;
        }
    }

    void update() { //保证有儿子
    }

    void modify(int a, int b, int val) {
        if (l == a && r == b) {
            add += val;
            if (a == b) {
                this->val += add;
                add = 0;
            }
            return;
        }
        push_down(); //要进入子树,先要把树根的延迟信息push下去
        if (b <= mid()) ls->modify(a, b, val);
        else if (a > mid()) rs->modify(a, b, val);
        else {
            ls->modify(a, mid(), val);
            rs->modify(mid() + 1, b, val);
        }
    }

    int query(int id) {
        if (l == r) return val;
        push_down();
        if (id <= mid()) return ls->query(id);
        else return rs->query(id);
    }
} dd[maxn * 5];

int e; // 初始化
Node *_alloc(int l, int r) {
    dd[e].init(l, r);
    return &dd[e++];
}

int d[maxn], ind;

Node *_make(int l, int r) { //构造一棵树,并返回树根
    Node *p = _alloc(l, r);
    if (l == r) {
        p->val = d[l];
        return p; //这里用到d数组,需要初始化
    }
    p->ls = _make(l, p->mid());
    p->rs = _make(p->mid() + 1, r);
    return p;
}//********************线段树模板结束******************

vector<int> adj[maxn]; //邻接表

struct Tree {
    Node *root;
    int dep, pa; //这段树链的深度,父亲点
} tree[maxn];
int tid, sz[maxn], vst[maxn];

struct Info {
    int tid, tind; //每个节点所在的 树编号,树上的id
} info[maxn];

int count(int u) { //计算子树大小
    sz[u] = vst[u] = 1;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (vst[v] == 0) {
            sz[u] += count(v);
        }
    }
    return sz[u];
}

int v[maxn]; //初始值

queue<int> q; //son dep pa
void divide(int u, int dep, int pa) { //树链剖分 非递归写法
    q.push(u);
    q.push(dep);
    q.push(pa);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        dep = q.front();
        q.pop();
        pa = q.front();
        q.pop();
        ind = 0;
        while (true) {
            vst[u] = 1;
            info[u].tid = tid, info[u].tind = ind;
            d[ind++] = v[u];
            int ma = -1, ver = -1; // size,vertex
            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i];
                if (vst[v]) continue;
                if (ma == -1) {
                    ma = sz[v];
                    ver = v;
                } else if (sz[v] > ma) {
                    q.push(ver);
                    q.push(dep + 1);
                    q.push(u);
                    ma = sz[v], ver = v;
                } else {
                    q.push(v);
                    q.push(dep + 1);
                    q.push(u);
                }
            }
            if (ma < 0) break;
            u = ver;
        }
        tree[tid].dep = dep;
        tree[tid].pa = pa;
        tree[tid++].root = _make(0, ind);
    }
}

void paint(int a, int b, int val) { //a到b的树链上的前权值全部加val
    int ta = info[a].tid, tb = info[b].tid;
    int ida = info[a].tind, idb = info[b].tind;
    if (ta == tb) {
        if (ida > idb) swap(ida, idb);
        tree[ta].root->modify(ida, idb, val);
        return;
    }
    if (tree[ta].dep > tree[tb].dep) {
        tree[ta].root->modify(0, ida, val);
        paint(tree[ta].pa, b, val);
    } else {
        tree[tb].root->modify(0, idb, val);
        paint(a, tree[tb].pa, val);
    }
}

//*************以上必须***************************
int find(int u) {
    return tree[info[u].tid].root->query(info[u].tind);
}

int main() {
    int n, m, Q;
    while (scanf("%d %d %d", &n, &m, &Q) != EOF) {
        e = 0; //
        for (int i = 1; i <= n; i++) adj[i].clear();
        for (int i = 1; i <= n; i++) scanf("%d", v + i);
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        memset(vst, 0, sizeof(vst));
        count(1);
        memset(vst, 0, sizeof(vst));
        tid = 0;
        divide(1, 0, -1);

        while (Q--) {
            char op;
            scanf(" %c", &op);
            if (op == 'I') {
                int a, b, val;
                scanf("%d %d %d", &a, &b, &val);
                paint(a, b, val);
            } else if (op == 'D') {
                int a, b, val;
                scanf("%d %d %d", &a, &b, &val);
                paint(a, b, -val);
            } else {
                int u;
                scanf("%d", &u);
                printf("%d\n", find(u));
            }
        }
    }
}
