/*
size balanced tree   -------------zjut_DD实现
为什么maintain不会死循环,这个可以从_rot函数看到
定义A=sigma(depth(i))/N,那么每次_rot都会使得A减少,故不会死循环
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
    if (SZ(p->ch[f]) < SZ(p->ch[!f]->ch[!f])) { //手画画
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

///-----------部分查询函数-------
int main() {
    int Q, val, r;
    while (scanf("%d", &Q) != EOF) {
        e = 0; //初始化
        Node *root = NULL;
        for (int i = 1; i <= Q; i++) {
            char op;
            scanf(" %c", &op);
            if (op == 'I') {       //插入
                scanf("%d", &val);
                insert(root, val);
            } else if (op == 'D') { //删除
                scanf("%d", &val);
                remove(root, val);
            } else if (op == 'N') { //有几个数<=val
                scanf("%d", &val);
                printf("%d\n", upper_bound(root, val) - 1);
            } else if (op == 'F') { //查找排名为r的元素
                scanf("%d", &r);
                printf("%d\n", find(root, r));
            }
        }
    }
}


