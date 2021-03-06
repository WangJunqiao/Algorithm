//Treap  = Tree+Heap
//如果Hkey确定了，那么Treap就是确定的

#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define maxn 110000

template<typename T>
struct Treap {
    struct Node {
        T val;
        int h;
        Node *ch[2];

        Node *_rot(int f) { //f=0: 向左旋
            Node *t = ch[!f];
            ch[!f] = t->ch[f];
            t->ch[f] = this;
            return t;
        }

        Node *mt() { //maintain
            if (ch[0] && ch[0]->h > h) return _rot(1);
            if (ch[1] && ch[1]->h > h) return _rot(0);
            return this;
        }
    };

    Node *_alloc(T val) {
        Node *t = new Node();
        t->h = rand();
        t->val = val;
        return t;
    }

    Node *_insert(Node *r, T val) {
        if (r == NULL) return _alloc(val);
        if (val < r->val) {
            r->ch[0] = _insert(r->ch[0], val);
        } else {
            r->ch[1] = _insert(r->ch[1], val);
        }
        return r->mt();
    }

    Node *root;

    Treap() { root = NULL; }

    void clear() {
        _free(root);
        root = NULL;
    }

    void insert(T val) { root = _insert(root, val); }


    void _free(Node *p) {
        if (!p) return;
        _free(p->ch[0]);
        _free(p->ch[1]);
        delete p;
    }

    int depth(Node *p) {
        if (!p) return 0;
        return 1 + max(depth(p->ch[0]), depth(p->ch[1]));
    }

    ~Treap() {
        _free(root);
        printf("~Treap called!");
    }
};


int main() {
    Treap<int> treap;
    for (int i = 0; i < 100000; i++) treap.insert(i);
    printf("depth=%d\n", treap.depth(treap.root));
}


