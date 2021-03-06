#pragma comment(linker, "/STACK:16777216")

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;


//Link-Cut-Tree hdu4010
#define maxn 330000

//伸展树用来维护树链，一条树链比如A->B->C->D(A是根),则A表示最小,D最大
struct Node {
    int w;
    int add; //延迟标记
    int maw; //更新信息
    //以上为可修改数据
    bool flip; //翻转延迟
    Node *real_fa; //真实的父节点, 一条path只有根节点这个值才是有效的
    Node *ch[2], *f;
    int size; //维护preferred path的伸展树信息
    void init() {
        real_fa = f = ch[0] = ch[1] = NULL;
        size = 1;
        flip = false;
        add = 0;
    }

    void _rot_up(int c) {  //c=0左上旋,c=1右上旋, 只在splay函数中使用
        Node *y = f, *z = y->f;  //this=x 和 y都是没有延迟了的
        y->ch[!c] = ch[c];
        if (ch[c]) ch[c]->f = y;
        f = z;
        if (z) z->ch[y == z->ch[0] ? 0 : 1] = this;
        ch[c] = y;
        y->f = this;
        y->update();//x节点最后才维护的
    }

    void splay(Node *fa) {//将自己旋转到f下面，并清除延迟标记
        for (push_down(); f != fa;) {
            if (f->f == fa) {
                f->push_down();
                push_down();
                if (f->ch[0] == this) _rot_up(1);
                else _rot_up(0);
            } else {
                Node *y = f, *z = y->f;
                z->push_down();
                y->push_down();
                push_down();
                if (y->ch[0] == this) { //这样转可以降低树的高度
                    if (z->ch[0] == y) {
                        y->_rot_up(1);
                        _rot_up(1);
                    }
                    else {
                        _rot_up(1);
                        _rot_up(0);
                    }
                } else {
                    if (z->ch[0] != y) {
                        y->_rot_up(0);
                        _rot_up(0);
                    }
                    else {
                        _rot_up(0);
                        _rot_up(1);
                    }
                }
            }
        }
        update(); //update x=this
    }

    Node *find(int r) {//find rank r's element,base1
        push_down();
        int L = ch[0] ? ch[0]->size : 0;
        if (r <= L) return ch[0]->find(r);
        if (r == L + 1) return this;
        return ch[1]->find(r - (L + 1));
    }

    void update() {
        size = 1;
        if (ch[0]) size += ch[0]->size;
        if (ch[1]) size += ch[1]->size;  //以上必须
        maw = w;
        if (ch[0]) maw = max(maw, ch[0]->maw);
        if (ch[1]) maw = max(maw, ch[1]->maw);
    }

    void do_flip() { //每个延迟标记都要搞一个do函数
        flip = !flip;
        swap(ch[0], ch[1]);
    }

    void do_add(int a) {
        add += a;
        w += a;
        maw += a;
    }

    void push_down() {
        if (flip) {
            if (ch[0]) ch[0]->do_flip();
            if (ch[1]) ch[1]->do_flip();
            flip = false;
        } //以上必须
        if (add) {
            if (ch[0]) ch[0]->do_add(add);
            if (ch[1]) ch[1]->do_add(add);
            add = 0;
        }
    }
} dd[maxn];

//access之后，树链a->b->c->d->...->p形成一棵完整的伸展树，并清除延迟标记
void access(Node *p) {
    Node *s = NULL; //s是p下面一条路径的某个节点
    while (p != NULL) {
        p->splay(NULL); //去掉了p的延迟标记
        if (p->ch[1]) {
            p->ch[1]->f = NULL;
            p->ch[1]->find(1)->real_fa = p;
        }
        p->ch[1] = s;
        if (s) s->f = p; //
        p->update();
        p = (s = p)->find(1)->real_fa;
    }
}

Node *find_root(Node *s) {
    access(s);
    s->splay(NULL);
    return s->find(1);
}

void link(Node *s, Node *f) { //增加f->s, 保证s是一个根,
    s->real_fa = f;
    access(s); //保持各种更新，延迟信息
}

void cut(Node *s) {         //除去s和其父亲的关系
    access(s);
    s->splay(NULL);
    if (s->ch[0] == NULL) return; //没有父亲
    s->ch[0]->f = NULL;
    s->ch[0] = NULL;
    s->real_fa = NULL;
}

bool isAncester(Node *f, Node *s) { //判断f是不是s的祖先
    access(s);
    f->splay(NULL);
    while (s->f) s = s->f;
    return s == f;
}

void make_root(Node *s) { //使得s变成根
    access(s);
    s->splay(NULL);
    s->do_flip();
    s->real_fa = NULL;
}
//********************模板结束***********************
//dd[i].init(); dd[i].real_fa=...

bool vst[maxn];
vector<int> adj[maxn];
int w[maxn];

void dfs(Node *fa, int u) {
    vst[u] = true;
    dd[u].init();
    dd[u].w = w[u];
    dd[u].add = 0;
    dd[u].real_fa = fa;
    for (int i = 0; i < (int) adj[u].size(); i++) {
        int v = adj[u][i];
        if (vst[v] == false) {
            dfs(dd + u, v);
        }
    }
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        for (int i = 1; i <= N; i++) adj[i].clear();
        for (int i = 1; i < N; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        for (int i = 1; i <= N; i++) scanf("%d", w + i);
        memset(vst, false, sizeof(vst));
        dfs(NULL, 1);
        int Q;
        scanf("%d", &Q);
        while (Q--) {
            int op;
            scanf("%d", &op);
            if (op == 1) {
                int x, y;
                scanf("%d %d", &x, &y);
                make_root(dd + x);
                if (find_root(dd + y) == dd + x) {
                    puts("-1");
                } else {
                    link(dd + x, dd + y);
                }
            } else if (op == 2) {
                int x, y;
                scanf("%d %d", &x, &y);
                make_root(dd + x);
                if (x == y || find_root(dd + y) != dd + x) {
                    puts("-1");
                } else {
                    cut(dd + y);
                }
            } else if (op == 3) {
                int w, x, y;
                scanf("%d %d %d", &w, &x, &y);
                make_root(dd + x);
                if (find_root(dd + y) != dd + x) {
                    puts("-1");
                } else {
                    access(dd + y);
                    dd[y].splay(NULL);
                    dd[y].do_add(w);
                }
            } else {
                int x, y;
                scanf("%d %d", &x, &y);
                make_root(dd + x);
                if (find_root(dd + y) != dd + x) {
                    puts("-1");
                } else {
                    access(dd + y);
                    dd[y].splay(NULL);
                    printf("%d\n", dd[y].maw);
                }
            }
        }
        puts("");
    }
}