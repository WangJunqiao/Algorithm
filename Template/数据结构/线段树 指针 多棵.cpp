#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

//�߶���ģ��, ����n����,ÿ�ζ�[a,b]�������ͬʱ+val, ��ѯ[a,b]�ĺ�
//���߶���ģ������Ҫ�������ʱ��(���ĵ�·���ʷֵ�)ʹ��
typedef long long int64;
#define maxn 110000
int d[maxn];

struct Node {
    int64 add; //�ӳٲ�����Ϣ
    int64 sum; //ͳ����Ϣ
    //
    int l, r;
    Node *ls, *rs; //���Ҷ���
    void init(int _l, int _r) {
        l = _l, r = _r;
        ls = rs = NULL;
        add = 0; //�ӳ���Ϣ������0!!!
    }

    int mid() { return (l + r) >> 1; }

    int len() { return (r - l + 1); }

    void push_down() { //��֤�ж���
        if (add == 0) return;
        ls->add += add;
        ls->sum += ls->len() * add; //push��ȥ��ʱ��,ͳ����ϢҲҪ����
        rs->add += add;
        rs->sum += rs->len() * add;
        add = 0; //ȥ��
    }

    void update() { //��֤�ж���
        sum = ls->sum + rs->sum;   //����ͳ����Ϣ
    }

    void modify(int a, int b, int val) {
        if (l == a && r == b) {
            add += val;
            sum += (int64) len() * val;
            return;
        }
        push_down(); //Ҫ��������,��Ҫ���������ӳ���Ϣpush��ȥ
        if (b <= mid()) ls->modify(a, b, val);
        else if (a > mid()) rs->modify(a, b, val);
        else {
            ls->modify(a, mid(), val);
            rs->modify(mid() + 1, b, val);
        }
        update();
    }

    int64 query(int a, int b) {
        if (l == a && r == b) return sum;
        push_down();   //��Ϊ��ѯ��ʱ��û�и����κ���Ϣ, ���Բ���update����
        if (b <= mid()) return ls->query(a, b);
        else if (a > mid()) return rs->query(a, b);
        else {
            return ls->query(a, mid()) + rs->query(mid() + 1, b);
        }
    }
} dd[maxn * 5];

int e; // ��ʼ��
Node *_alloc(int l, int r) {
    dd[e].init(l, r);
    return &dd[e++];
}

Node *_make(int l, int r) { //����һ����,����������
    Node *p = _alloc(l, r);
    if (l == r) {
        p->add = 0, p->sum = d[l];
        return p; //�����õ�d����,��Ҫ��ʼ��
    }
    p->ls = _make(l, p->mid());
    p->rs = _make(p->mid() + 1, r);
    p->update();
    return p;
}

//********************�߶���ģ�����******************
//��ʼ�� e=0;   ������ʽ Node* root=_make(1,N);   
int main() {
    int N, Q, Te = 1;
    while (scanf("%d %d", &N, &Q) != EOF) {
        e = 0; //
        for (int i = 1; i <= N; i++) scanf("%d", d + i);
        Node *root = _make(1, N);
        printf("case #%d:\n", Te++);
        for (int i = 1; i <= Q; i++) {
            char op;
            scanf(" %c", &op);
            int l, r, val;
            if (op == 'a') { //������Ӳ���
                scanf("%d %d %d", &l, &r, &val);
                root->modify(l, r, val);
            } else {   //�������
                scanf("%d %d", &l, &r);
                printf("%lld\n", root->query(l, r));
            }
        }
    }
}

