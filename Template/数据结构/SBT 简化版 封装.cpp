/*
author: zjut_DD
类SBT平衡树, 动态内存, 修改自陈启峰的SBT, 没有SBT平衡, 但比SBT简单易写
平衡性基于如下性质:
定义A=sigma(depth(i)), 每次_rot都会使A变小
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;


template<typename T>
struct DDTree {
#define _sz(p) (!(p)?0:(p)->size)

    struct Node {
        T val;
        Node *ch[2];
        int size;

        void update() { size = 1 + _sz(ch[0]) + _sz(ch[1]); }

        Node *_rot(int f) { //f=0: 往左旋转,  返回根
            Node *t = ch[!f];
            ch[!f] = t->ch[f];
            t->ch[f] = this;
            update();
            return t;
        }

        Node *mt() { //维护平衡, 返回根
            if (ch[0] && _sz(ch[0]->ch[0]) > _sz(ch[1])) //
                return _rot(1)->mt();
            if (ch[1] && _sz(ch[1]->ch[1]) > _sz(ch[0])) //
                return _rot(0)->mt();
            update();
            return this;
        }

        T kth(int k) { //第k大元素, base1
            if (k <= _sz(ch[0])) return ch[0]->kth(k);
            if (k == _sz(ch[0]) + 1) return val;
            return ch[1]->kth(k - 1 - _sz(ch[0]));
        }

        int less(T v) { //小于v 的元素个数
            if (val < v) return 1 + _sz(ch[0]) + (ch[1] ? ch[1]->less(v) : 0);
            return (ch[0] ? ch[0]->less(v) : 0);
        }
    };

    Node *_alloc(T val) {
        Node *p = new Node();
        p->size = 1;
        p->val = val;
        return p;
    }

    Node *_insert(Node *p, T v) { //插入
        if (!p) return _alloc(v);
        int f = (v > p->val);
        p->ch[f] = _insert(p->ch[f], v);
        return p->mt();
    }

    Node *_rel(Node *p) { //删除最左的那个
        if (p->ch[0]) {
            p->ch[0] = _rel(p->ch[0]);
            return p->mt();
        } else {
            return p->ch[1]; //内存泄漏
        }
    }

    Node *_remove(Node *p, T val) { //删除一个val
        if (p == NULL) return p;
        if (val < p->val) {
            p->ch[0] = _remove(p->ch[0], val);
        } else if (val > p->val) {
            p->ch[1] = _remove(p->ch[1], val);
        } else {
            if (!p->ch[0]) return p->ch[1]; //内存泄漏
            if (!p->ch[1]) return p->ch[0]; //内存泄漏
            p->val = p->ch[1]->kth(1);
            p->ch[1] = _rel(p->ch[1]);
        }
        return p->mt();
    }

    //--------释放内存-----
    void _free(Node *p) {
        if (!p) return;
        _free(p->ch[0]);
        _free(p->ch[1]);
        delete p;
    }

    ~DDTree() {
        //printf("~DDTree called!\n");
        _free(root);
    }

    //-----下面是对外的接口函数------
    Node *root;

    DDTree() { root = NULL; }

    void clear() {
        _free(root);
        root = NULL;
    }

    int size() { return _sz(root); }

    int less(T val) { return root ? root->less(val) : 0; }

    void insert(T val) { root = _insert(root, val); }

    void remove(T val) { root = _remove(root, val); }

    T kth(int k) { return root->kth(k); }

    //debug
    int depth(Node *p) {
        if (!p) return 0;
        return 1 + max(depth(p->ch[0]), depth(p->ch[1]));
    }
};


void test() {
    int maxn = 1000000;
    DDTree<int> ddt;
    srand(time(NULL));

    ddt.clear();
    for (int i = 0; i < maxn; i++) ddt.insert(rand() % 10000 * rand() % 10000000);
    printf("随机插入%d个数, 树高=%d\n", maxn, ddt.depth(ddt.root));

    ddt.clear();
    for (int i = 0; i < maxn; i++) ddt.insert(i);
    printf("顺序插入%d个数, 树高=%d\n", maxn, ddt.depth(ddt.root));

    ddt.clear();
    for (int i = 0; i < maxn; i++) ddt.insert(maxn - i);
    printf("逆序插入%d个数, 树高=%d\n", maxn, ddt.depth(ddt.root));
}


int main() {

    //test(); return 0;

    //freopen("in.txt", "r", stdin);
    //freopen("out6.txt", "w", stdout);
    int Q, val, r;
    while (scanf("%d", &Q) != EOF) {
        DDTree<int> sbt;
        for (int i = 1; i <= Q; i++) {
            char op;
            scanf(" %c", &op);
            if (op == 'I') {       //插入
                scanf("%d", &val);
                sbt.insert(val);
            } else if (op == 'D') { //删除
                scanf("%d", &val);
                sbt.remove(val);
            } else if (op == 'N') { //有几个数<=val
                scanf("%d", &val);
                printf("%d\n", sbt.less(val + 1));
            } else if (op == 'F') { //查找排名为r的元素
                scanf("%d", &r);
                printf("%d\n", sbt.kth(r));
            }
        }
    }
}