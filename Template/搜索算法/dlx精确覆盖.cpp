//dancing link----------DD
//通过 pku 3740, hust 1017测试
//速度比udlr数组的慢4倍. 问题在于寻址跨度是4倍.
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

#define maxr 1100
#define maxc 1100

struct Node { //四向循环网状链表
    int row, col;
    Node *u, *d, *l, *r;

    void init(int _r, int _c) {
        u = d = l = r = this;
        row = _r;
        col = _c;
    }

    void add_lr(Node &b) {
        b.r = r;
        r->l = &b;
        r = &b;
        b.l = this;
    }  //在右边增加一个节点b
    void add_ud(Node &b) {
        b.d = d;
        d->u = &b;
        d = &b;
        b.u = this;
    }  //在下方增加一个节点b
    void remove_lr() {
        l->r = r;
        r->l = l;
    }   //解除当前节点的左右链接
    void remove_ud() {
        u->d = d;
        d->u = u;
    }   //解除当前节点的上下链接
    void resume_lr() {
        l->r = this;
        r->l = this;
    } //恢复当前节点的左右链接
    void resume_ud() {
        u->d = this;
        d->u = this;
    } //恢复当前节点的上下链接
} dd[maxr * maxc], *root, *lastc[maxc];

#define replr(p, x) for(Node*p=x->l; p!=x; p=p->l)
#define repud(p, x) for(Node*p=x->u; p!=x; p=p->u)

int mat[maxr][maxc];
//初始矩阵，0或1，从1，1开始用
int s[maxc];

void remove(Node *c) {
    c->remove_lr();
    repud(x, c) replr(p, x) {
            p->remove_ud();
            s[p->col]--;
        }
}

void resume(Node *c) {
    repud(x, c) replr(p, x) {
            p->resume_ud();
            s[p->col]++;
        }
    c->resume_lr();
}

int res[maxr], ind;

//每次取的哪行
bool search(int k) { //将开始第几层搜索
    if (root->r == root) {
        ind = k;
        return true;//找到一组解
    }
    Node *c = root->r;
    replr(i, root) if (s[i->col] <= s[c->col]) c = i;
    if (s[c->col] == 0) return false; //剪枝
    remove(c);
    repud(i, c) {
        res[k] = i->row;//记录
        replr(j, i) remove(dd + j->col);
        if (search(k + 1)) return true;
        replr(j, i) resume(dd + j->col);
    }
    resume(c);
    return false;
}

/*
链表的形状类似这样
####### 
 . . ..
 ... .
  . ..
*/
void adapt(int n, int m) { //传入01矩阵mat的规格,适配函数（由mat构造dancing link 表）
    fill(s, s + m + 1, 0);
    int e = 0;
    dd[e].init(0, 0);
    root = &dd[e++];

    for (int j = 1; j <= m; j++) {
        dd[e].init(0, j);
        lastc[j] = &dd[e];
        dd[j - 1].add_lr(dd[e++]);
    }
    for (int i = 1; i <= n; i++) {
        Node *tmp = NULL;
        for (int j = 1; j <= m; j++)
            if (mat[i][j]) {
                dd[e].init(i, j);
                if (tmp) tmp->add_lr(dd[e]);
                lastc[j]->add_ud(dd[e]);
                s[j]++;
                tmp = lastc[j] = &dd[e++];
            }
    }
}

//------------------------------模板结束-----------------------
int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", mat[i] + j);
        adapt(n, m);
        if (search(1))
            cout << "Yes, I found it\n";
        else
            cout << "It is impossible\n";
    }
}

