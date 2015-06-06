#include <iostream>

using namespace std;


#define MAXN 110000
#define LLL (2 * i)
#define RRR (2 * i + 1)

int v[MAXN];

//�����߶���ģ��, zjut1708 n����,ÿ�ζ�[a,b]�������ͬʱ+val, ��ѯ[a,b]�ĺ�
typedef long long int64;

struct _Node {
    int64 add; //�ӳ���Ϣ(������Ϊ�·�,����������)
    int64 sum; //ͳ����Ϣ
    //
    int l, r; //bound

    int len() { return r - l + 1; }

    int mid() { return (l + r) >> 1; }
} dd[MAXN * 5];

void push_down(int i) {
    int64 &add = dd[i].add;
    dd[LLL].add += add;
    dd[LLL].sum += add * dd[LLL].len();  //push��ȥ��ʱ��,ͳ����ϢҲҪ����
    dd[RRR].add += add;
    dd[RRR].sum += add * dd[RRR].len();
    add = 0;   //ȥ��
}

void update(int i) { //��֤�ж���
    dd[i].sum = dd[LLL].sum + dd[RRR].sum;
}

void makeTree(int i, int l, int r) {
    dd[i].l = l;
    dd[i].r = r;
    dd[i].add = 0; // set delayed mark

    if (l == r) {  //leaf node
        dd[i].sum = v[l];
        return;
    }

    int mid = dd[i].mid();
    makeTree(LLL, l, mid);
    makeTree(RRR, mid + 1, r);

    update(i); //set statistic mark
}

void modify(int i, int l, int r, int val) {
    if (dd[i].l == l && dd[i].r == r) {
        dd[i].add += val;
        dd[i].sum += (int64) val * dd[i].len(); //delay mark is effective for son nodes
        return;
    }

    push_down(i);

    int mid = dd[i].mid();
    if (r <= mid) {
        modify(LLL, l, r, val);
    } else if (l > mid) {
        modify(RRR, l, r, val);
    } else {
        modify(LLL, l, mid, val);
        modify(RRR, mid + 1, r, val);
    }
    update(i);
}

int64 query(int i, int l, int r) {
    if (dd[i].l == l && dd[i].r == r) {
        return dd[i].sum;
    }
    push_down(i);

    int mid = dd[i].mid();
    if (r <= mid) {
        return query(LLL, l, r);
    } else if (l > mid) {
        return query(RRR, l, r);
    } else {
        return query(LLL, l, mid) + query(RRR, mid + 1, r);
    }
}

//******ģ�����*******
int main() {
    int N, Q, Te = 1;
    while (scanf("%d %d", &N, &Q) != EOF) {
        for (int i = 1; i <= N; i++) scanf("%d", v + i);
        makeTree(1, 1, N);
        printf("case #%d:\n", Te++);
        for (int i = 1; i <= Q; i++) {
            char op;
            scanf(" %c", &op);
            int l, r, val;
            if (op == 'a') { //������Ӳ���
                scanf("%d %d %d", &l, &r, &val);
                modify(1, l, r, val);
            } else {   //�������
                scanf("%d %d", &l, &r);
                printf("%lld\n", query(1, l, r));
            }
        }
    }
}

