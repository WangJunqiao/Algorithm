#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

//线段树模板, 给定n个数,每次对[a,b]区间的数同时+val, 查询[a,b]的和
//此线段树模板在需要多棵树的时候(树的的路径剖分等)使用
typedef long long int64;
#define maxn 110000
int d[maxn];

struct Node {
    int64 add; //延迟操作信息
    int64 sum; //统计信息
    //
    int l, r;
    Node *ls, *rs; //左右儿子
    void init(int _l, int _r) {
        l = _l, r = _r;
        ls = rs = NULL;
        add = 0; //延迟信息必须清0!!!
    }

    int mid() { return (l + r) >> 1; }

    int len() { return (r - l + 1); }

    void push_down() { //保证有儿子
        if (add == 0) return;
        ls->add += add;
        ls->sum += ls->len() * add; //push下去的时候,统计信息也要更新
        rs->add += add;
        rs->sum += rs->len() * add;
        add = 0; //去掉
    }

    void update() { //保证有儿子
        sum = ls->sum + rs->sum;   //更新统计信息
    }

    void modify(int a, int b, int val) {
        if (l == a && r == b) {
            add += val;
            sum += (int64) len() * val;
            return;
        }
        push_down(); //要进入子树,先要把树根的延迟信息push下去
        if (b <= mid()) ls->modify(a, b, val);
        else if (a > mid()) rs->modify(a, b, val);
        else {
            ls->modify(a, mid(), val);
            rs->modify(mid() + 1, b, val);
        }
        update();
    }

    int64 query(int a, int b) {
        if (l == a && r == b) return sum;
        push_down();   //因为查询的时候没有更新任何信息, 所以不用update上来
        if (b <= mid()) return ls->query(a, b);
        else if (a > mid()) return rs->query(a, b);
        else {
            return ls->query(a, mid()) + rs->query(mid() + 1, b);
        }
    }
} dd[maxn * 5];

int e; // 初始化
Node *_alloc(int l, int r) {
    dd[e].init(l, r);
    return &dd[e++];
}

Node *_make(int l, int r) { //构造一棵树,并返回树根
    Node *p = _alloc(l, r);
    if (l == r) {
        p->add = 0, p->sum = d[l];
        return p; //这里用到d数组,需要初始化
    }
    p->ls = _make(l, p->mid());
    p->rs = _make(p->mid() + 1, r);
    p->update();
    return p;
}

//********************线段树模板结束******************
//初始化 e=0;   建树方式 Node* root=_make(1,N);   
int main() {
    int N, Q, Te = 1;
    while (scanf("%d %d", &N, &Q) != EOF) {
        e = 0; //
        for (int i = 1; i <= N; i++) scanf("%d", d + i);
        Node *root = _make(1, N);
        printf("case #%d:\n", Te++);
        for (int i = 1; i <= Q; i++) {
            char op;
            scanf(" %c", &op);
            int l, r, val;
            if (op == 'a') { //对区间加操作
                scanf("%d %d %d", &l, &r, &val);
                root->modify(l, r, val);
            } else {   //区间求和
                scanf("%d %d", &l, &r);
                printf("%lld\n", root->query(l, r));
            }
        }
    }
}

