//��̬������ hdu2475 ��̬��ѯ����˭   hdu3966ҲAC��,�ӳٱ��û����
//Link-Cut-Tree
#include<iostream>
#include<string.h>
#include<stdio.h>

using namespace std;
#define maxn 100005

struct Node {
    int id;
    //����
    Node *up;
    Node *ch[2], *f;
    int size;

    void init() {
        up = f = ch[0] = ch[1] = NULL;
        size = 1;
    }

    void rot(int c) {  //c=0����,c=1����
        Node *y = f, *z = y->f;
        //y->push_down(); push_down();//������ӳ���Ϣ,����ɾ
        y->ch[!c] = ch[c];
        if (ch[c]) ch[c]->f = y;
        f = z;
        if (z) if (y == z->ch[0]) z->ch[0] = this; else z->ch[1] = this;
        ch[c] = y;
        y->f = this;
        y->update();//x�ڵ�����ά����
    }

    void splay(Node *fa) {//���Լ���ת��f����
        for (push_down(); f != fa;) {
            if (f->f == fa) {
                //f->push_down(); push_down(); //�����rev����,�������ɾ��
                if (f->ch[0] == this) rot(1);
                else rot(0);
            } else {
                Node *y = f, *z = y->f;
                //z->push_down(); y->push_down(); push_down();//�����rev����,�������ɾ��
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
        update(); //���ά�����x�ڵ�
    }

    Node *find(int r) {  //�ҵ������е�rank��ĵ�ַ
        //push_down(); //������ӳ���Ϣ,����ɾ
        int L = 0;
        if (ch[0]) L += ch[0]->size;
        if (r <= L) return ch[0]->find(r);
        if (r == L + 1) return this;
        return ch[1]->find(r - (L + 1));
    }

    void update() {
        size = 1;
        if (ch[0]) size += ch[0]->size;
        if (ch[1]) size += ch[1]->size;  //���ϱ���
    }

    void push_down() {//���ӳٱ��push��ȥ
    }
} dd[maxn];
//һ��preferred path����չ�����Ǵ�С���,����A->B->C->D,��A��ʾ��С,D���

void init(int n) { //��ʼ��,��Ҫ��д
    for (int i = 0; i <= n; i++) dd[i].init(), dd[i].id = i;
}

void access(Node *p) {//s��p����һ��·���ĸ��ڵ�
    Node *s = NULL;
    while (p != NULL) {
        p->splay(NULL);
        if (p->ch[1]) { //���ٺ��
            p->ch[1]->find(1)->splay(p);
            p->ch[1]->up = p;
            p->ch[1]->f = NULL; //f=NULL��ʾ��������Ϊ����
        } //p�Ǹ�
        p->ch[1] = s;
        if (s) {
            s->up = NULL;
            s->f = p;
            s->splay(NULL);
        }//����  s��ת����,���ָ��ָ��£��ӳ���Ϣ
        else {
            s = p;
            s->update();
        } //s�Ǹ���
        p = s->find(1)->up;
    }
}

Node *find_root(Node *s) { //��̬��������
    access(s);
    s->splay(NULL);
    return s->find(1);
}

void link(Node *s, Node *f) { //����f->s, ��֤s��һ����,
    s->up = f;
    access(s); //���ָ��ָ��£��ӳ���Ϣ
}

void cut(Node *s) {         //��ȥs���丸�׵Ĺ�ϵ
    access(s);
    s->splay(NULL);
    if (s->ch[0] == NULL) return; //û�и���
    s->ch[0]->f = NULL;
    s->ch[0] = s->up = NULL;
}

bool isAncester(Node *f, Node *s) { //�ж�f�ǲ���s������
    access(s);
    f->splay(NULL);
    while (s->f)s = s->f;
    return s == f;
}
//********************ģ�����***********************

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


