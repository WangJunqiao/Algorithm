/*
author: zjut_DD
��SBTƽ����, ��̬�ڴ�, �޸��Գ������SBT, û��SBTƽ��, ����SBT����д
ƽ���Ի�����������:
����A=sigma(depth(i)), ÿ��_rot����ʹA��С
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

        Node *_rot(int f) { //f=0: ������ת,  ���ظ�
            Node *t = ch[!f];
            ch[!f] = t->ch[f];
            t->ch[f] = this;
            update();
            return t;
        }

        Node *mt() { //ά��ƽ��, ���ظ�
            if (ch[0] && _sz(ch[0]->ch[0]) > _sz(ch[1])) //
                return _rot(1)->mt();
            if (ch[1] && _sz(ch[1]->ch[1]) > _sz(ch[0])) //
                return _rot(0)->mt();
            update();
            return this;
        }

        T kth(int k) { //��k��Ԫ��, base1
            if (k <= _sz(ch[0])) return ch[0]->kth(k);
            if (k == _sz(ch[0]) + 1) return val;
            return ch[1]->kth(k - 1 - _sz(ch[0]));
        }

        int less(T v) { //С��v ��Ԫ�ظ���
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

    Node *_insert(Node *p, T v) { //����
        if (!p) return _alloc(v);
        int f = (v > p->val);
        p->ch[f] = _insert(p->ch[f], v);
        return p->mt();
    }

    Node *_rel(Node *p) { //ɾ��������Ǹ�
        if (p->ch[0]) {
            p->ch[0] = _rel(p->ch[0]);
            return p->mt();
        } else {
            return p->ch[1]; //�ڴ�й©
        }
    }

    Node *_remove(Node *p, T val) { //ɾ��һ��val
        if (p == NULL) return p;
        if (val < p->val) {
            p->ch[0] = _remove(p->ch[0], val);
        } else if (val > p->val) {
            p->ch[1] = _remove(p->ch[1], val);
        } else {
            if (!p->ch[0]) return p->ch[1]; //�ڴ�й©
            if (!p->ch[1]) return p->ch[0]; //�ڴ�й©
            p->val = p->ch[1]->kth(1);
            p->ch[1] = _rel(p->ch[1]);
        }
        return p->mt();
    }

    //--------�ͷ��ڴ�-----
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

    //-----�����Ƕ���Ľӿں���------
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
    printf("�������%d����, ����=%d\n", maxn, ddt.depth(ddt.root));

    ddt.clear();
    for (int i = 0; i < maxn; i++) ddt.insert(i);
    printf("˳�����%d����, ����=%d\n", maxn, ddt.depth(ddt.root));

    ddt.clear();
    for (int i = 0; i < maxn; i++) ddt.insert(maxn - i);
    printf("�������%d����, ����=%d\n", maxn, ddt.depth(ddt.root));
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
            if (op == 'I') {       //����
                scanf("%d", &val);
                sbt.insert(val);
            } else if (op == 'D') { //ɾ��
                scanf("%d", &val);
                sbt.remove(val);
            } else if (op == 'N') { //�м�����<=val
                scanf("%d", &val);
                printf("%d\n", sbt.less(val + 1));
            } else if (op == 'F') { //��������Ϊr��Ԫ��
                scanf("%d", &r);
                printf("%d\n", sbt.kth(r));
            }
        }
    }
}