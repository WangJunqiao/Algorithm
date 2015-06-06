/*
AC: zju2112 支持修改的第k小数      线段树套平衡树 
*/
#include<iostream>
#include<cstdio>

using namespace std;

#define maxn 50005*20
typedef int type;

struct Node {
    type key;
    Node *ch[2];
    int size;

    friend int SZ(Node *p) { return p == NULL ? 0 : p->size; }

    void init(type _key = 0) {
        key = _key;
        size = 1;
        ch[0] = ch[1] = NULL;
    }

    //必须初始化
    void update() { size = 1 + SZ(ch[0]) + SZ(ch[1]); }
} dd[maxn];

int e; //初始化为0
Node *_alloc(type val) {
    dd[e].init(val);
    return &dd[e++];
}

void _rot(Node *&p, int f) { //f=0为 往 左旋
    Node *tmp = p->ch[!f];
    p->ch[!f] = tmp->ch[f];
    tmp->ch[f] = p;
    p->update();
    tmp->update();
    p = tmp;
}

void _m(Node *&p, int f) { //维护函数, 检查p->ch[f]是否满足>=p->c[!f]->ch[0,1]
    if (!p || !p->ch[!f]) return;
    if (SZ(p->ch[f]) < SZ(p->ch[!f]->ch[!f])) { //按照论文
        _rot(p, f);
        _m(p->ch[f], 0);
        _m(p->ch[f], 1);
    } else if (SZ(p->ch[f]) < SZ(p->ch[!f]->ch[f])) {
        _rot(p->ch[!f], !f);
        _rot(p, f);
        _m(p->ch[!f], f);
        _m(p->ch[f], !f);
    } else return; //
    _m(p, 0);
    _m(p, 1); //保驾护航
}

void insert(Node *&p, type v) { //插入
    if (p == NULL) {
        p = _alloc(v);
        return;
    }
    bool f = (v > p->key);
    insert(p->ch[f], v);
    p->update();
    _m(p, !f);
}

type _rev(Node *&p) {
    if (p->ch[0]) {
        type tmp = _rev(p->ch[0]);
        p->update();
        _m(p, 0);
        return tmp;
    } else {
        type tmp = p->key;
        p = p->ch[1];
        return tmp;
    }
}

void remove(Node *&p, type key) { //删除,如果有多个则删除一个
    if (p == NULL) return; //删除一个SBT里没有的值
    if (key < p->key) {
        remove(p->ch[0], key);
        p->update();
        _m(p, 0);
    } else if (key > p->key) {
        remove(p->ch[1], key);
        p->update();
        _m(p, 1);
    } else {
        if (p->ch[0] == NULL) p = p->ch[1];
        else if (p->ch[1] == NULL) p = p->ch[0];
        else {
            p->key = _rev(p->ch[1]);
            p->update();
            _m(p, 1);
        }
    }
}

///-----------SBT----------------
int lower_bound(Node *p, type key) { //查找排名
    if (!p) return 1;
    if (key > p->key) return SZ(p->ch[0]) + 1 + lower_bound(p->ch[1], key);
    else return lower_bound(p->ch[0], key);
}

int upper_bound(Node *p, type key) {
    return lower_bound(p, key + 1);
}

type find(Node *p, int r) { //查询排名为r的元素
    if (r <= SZ(p->ch[0])) return find(p->ch[0], r);
    else r -= SZ(p->ch[0]);
    if (r == 1) return p->key; else r--;
    return find(p->ch[1], r);
}
///-----------部分查询函数--------------------------------

int N, M, val[50005];
struct ST {
    int L, R;
    Node *root;
} st[50005 * 5];

void makeTree(int i, int L, int R) {
    st[i].L = L;
    st[i].R = R;
    st[i].root = NULL;
    for (int j = L; j <= R; j++)
        insert(st[i].root, val[j]);
    if (L == R) return;
    int mid = (L + R) >> 1;
    makeTree(i * 2, L, mid);
    makeTree(i * 2 + 1, mid + 1, R);
}

void change(int i, int t, int V) {
    remove(st[i].root, val[t]);
    insert(st[i].root, V);
    if (st[i].L == st[i].R) {
        val[t] = V;
        return;
    }
    int mid = (st[i].L + st[i].R) >> 1;
    if (t <= mid) change(i * 2, t, V);
    else change(i * 2 + 1, t, V);
}

int get_num(int i, int L, int R, int V) { //小于等于V的有几个
    if (st[i].L == L && st[i].R == R) {
        return upper_bound(st[i].root, V) - 1;
    }
    int mid = (st[i].L + st[i].R) >> 1;
    if (R <= mid) return get_num(i * 2, L, R, V);
    else if (L > mid) return get_num(i * 2 + 1, L, R, V);
    else {
        return get_num(i * 2, L, mid, V) +
               get_num(i * 2 + 1, mid + 1, R, V);
    }
}

int find(int a, int b, int rank) {
    int L = 0, R = 0x7fffffff, mid;
    while (L + 1 < R) {
        mid = (L + R) >> 1;
        if (get_num(1, a, b, mid) >= rank) R = mid;
        else L = mid;
    }
    return R;
}

int main() {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d", &N, &M);
        for (int i = 1; i <= N; i++) scanf("%d", val + i);
        e = 0;
        makeTree(1, 1, N);
        for (int i = 1; i <= M; i++) {
            char sign;
            scanf(" %c", &sign);
            if (sign == 'C') {
                int t, V;
                scanf("%d%d", &t, &V);
                change(1, t, V);
            } else {
                int a, b, rank;
                scanf("%d%d%d", &a, &b, &rank);
                printf("%d\n", find(a, b, rank));
            }
        }
    }
}

