//***********四向循环网状链表的节点类************
#define MAXR 1005
#define MAXC 1005

struct Node {
    int row, col;
    Node *u, *d, *l, *r;

    void init(int _r = 0, int _c = 0) {
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
} dd[MAXR][MAXC];

//******************************
void remove(int r, int c) { //删除第r行,第c列
    //remove row
    for (Node *ptr = dd[r][c].r; ptr != &dd[r][c]; ptr = ptr->r) {
        ptr->remove_ud();
    }
    //remove col
    for (Node *ptr = dd[r][c].u; ptr != &dd[r][c]; ptr = ptr->u) {
        ptr->remove_lr();
    }
}


