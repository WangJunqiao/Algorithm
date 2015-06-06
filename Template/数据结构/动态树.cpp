//动态树问题 hdu2475 动态查询根是谁   hdu3966也AC了,延迟标记没问题
//Link-Cut-Tree
#include<iostream>
#include<string.h>
#include<stdio.h>

using namespace std;
#define maxn 100005

struct Node {
    int id;
    //上面
    Node *up;
    Node *ch[2], *f;
    int size;

    void init() {
        up = f = ch[0] = ch[1] = NULL;
        size = 1;
    }

    void rot(int c) {  //c=0左旋,c=1右旋
        Node *y = f, *z = y->f;
        //y->push_down(); push_down();//如果有延迟信息,则不能删
        y->ch[!c] = ch[c];
        if (ch[c]) ch[c]->f = y;
        f = z;
        if (z) if (y == z->ch[0]) z->ch[0] = this; else z->ch[1] = this;
        ch[c] = y;
        y->f = this;
        y->update();//x节点最后才维护的
    }

    void splay(Node *fa) {//将自己旋转到f下面
        for (push_down(); f != fa;) {
            if (f->f == fa) {
                //f->push_down(); push_down(); //如果有rev操作,这个不能删了
                if (f->ch[0] == this) rot(1);
                else rot(0);
            } else {
                Node *y = f, *z = y->f;
                //z->push_down(); y->push_down(); push_down();//如果有rev操作,这个不能删了
                if (y->ch[0] == this) {
                    if (z->ch[0] == y) {
                        y->rot(1);
                        rot(1);
                    }
                    else {
                        rot(1);
                        rot(0);
                    }
                } else {
                    if (z->ch[0] != y) {
                        y->rot(0);
                        rot(0);
                    }
                    else {
                        rot(0);
                        rot(1);
                    }
                }
            }
        }
        update(); //最后维护这个x节点
    }

    Node *find(int r) {  //找到数列中第rank大的地址
        //push_down(); //如果有延迟信息,则不能删
        int L = 0;
        if (ch[0]) L += ch[0]->size;
        if (r <= L) return ch[0]->find(r);
        if (r == L + 1) return this;
        return ch[1]->find(r - (L + 1));
    }

    void update() {
        size = 1;
        if (ch[0]) size += ch[0]->size;
        if (ch[1]) size += ch[1]->size;  //以上必须
    }

    void push_down() {//将延迟标记push下去
    }
} dd[maxn];
//一条preferred path在伸展树中是从小大的,比如A->B->C->D,则A表示最小,D最大

void init(int n) { //初始化,需要重写
    for (int i = 0; i <= n; i++) dd[i].init(), dd[i].id = i;
}

void access(Node *p) {//s是p下面一条路径的根节点
    Node *s = NULL;
    while (p != NULL) {
        p->splay(NULL);
        if (p->ch[1]) { //安顿后继
            p->ch[1]->find(1)->splay(p);
            p->ch[1]->up = p;
            p->ch[1]->f = NULL; //f=NULL表示将它设置为树根
        } //p是根
        p->ch[1] = s;
        if (s) {
            s->up = NULL;
            s->f = p;
            s->splay(NULL);
        }//连接  s旋转到根,保持各种更新，延迟信息
        else {
            s = p;
            s->update();
        } //s是根了
        p = s->find(1)->up;
    }
}

Node *find_root(Node *s) { //动态树的树根
    access(s);
    s->splay(NULL);
    return s->find(1);
}

void link(Node *s, Node *f) { //增加f->s, 保证s是一个根,
    s->up = f;
    access(s); //保持各种更新，延迟信息
}

void cut(Node *s) {         //除去s和其父亲的关系
    access(s);
    s->splay(NULL);
    if (s->ch[0] == NULL) return; //没有父亲
    s->ch[0]->f = NULL;
    s->ch[0] = s->up = NULL;
}

bool isAncester(Node *f, Node *s) { //判断f是不是s的祖先
    access(s);
    f->splay(NULL);
    while (s->f)s = s->f;
    return s == f;
}
//********************模板结束***********************

int main() {
    int n, Te = 0;
    while (scanf("%d", &n) != EOF) {
        init(n);
        for (int i = 1; i <= n; i++) {
            int f;
            scanf("%d", &f);
            dd[i].up = &dd[f];
        }
        int Q;
        scanf("%d", &Q);
        if (Te++) puts("");
        while (Q--) {
            char sign[10];
            scanf(" %s", sign);
            if (sign[0] == 'M') {
                int a, b;
                scanf("%d%d", &a, &b);
                if (isAncester(&dd[a], &dd[b])) continue;
                cut(&dd[a]);
                link(&dd[a], &dd[b]);
            } else {
                int a;
                scanf("%d", &a);
                access(&dd[a]);
                dd[a].splay(NULL);
                printf("%d\n", dd[a].find(2)->id);
            }
        }
    }
}


