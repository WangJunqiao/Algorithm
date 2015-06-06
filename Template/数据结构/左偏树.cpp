//zjut 1567 ���е���
#include<iostream>
#include<algorithm>

using namespace std;

//�ɲ��ѣ�Ĭ�����ѣ�, ������ƫ���ʵĶ��������   --zjut_DD
#define maxn 55002
typedef int type; //typeҪ��operator<
struct Node {
    type key;
    //����
    int dis;
    Node *ls, *rs, *pa;

    void init(type _key) {
        key = _key;
        dis = 0;
        ls = rs = pa = NULL;
    }
} dd[maxn];

int e;  //ÿ�γ�ʼ��Ϊ0
struct LeftistTree {
    Node *root;
    int size;

    LeftistTree() { clear(); }

    void clear() {
        root = NULL;
        size = 0;
    }

    void push(type key) { //����һ��Ԫ��
        size++;
        dd[e].init(key);
        root = _Merge(root, &dd[e++]);
    }

    void pop() { //ɾ������Ԫ��
        size--;
        root = _Merge(root->ls, root->rs);
    }

    type &top() const { return root->key; } //ȡ����Ԫ��
    void putAll(LeftistTree &L) { //����������
        size += L.size;
        root = _Merge(root, L.root);
    }

    int _d(Node *p) { return p ? p->dis : -1; }

    Node *_Merge(Node *A, Node *B) {
        if (A == NULL) return B;
        if (B == NULL) return A;
        if (A->key < B->key) swap(A, B);//���͵���
        A->rs = _Merge(A->rs, B);
        A->rs->pa = A;
        if (_d(A->ls) < _d(A->rs)) swap(A->ls, A->rs);
        A->dis = _d(A->rs) + 1;
        return A;
    }
} st[maxn];//*************ģ�����****************







int a[maxn], N;
int l[maxn], r[maxn]; //��i������a�����е����ұ߽�
int work() { //�����������е����
    int t = 0;
    for (int i = 1; i <= N; i++) {
        st[t].clear();
        l[t] = r[t] = i;
        st[t].push(a[i]);
        while (t && st[t].top() < st[t - 1].top()) {
            st[t - 1].putAll(st[t]);
            r[t - 1] = r[t];
            t--;
            while (st[t].size > (r[t] - l[t] + 2) / 2) st[t].pop();
        }
        t++;
    }
    int ret = 0;
    for (int i = 0; i < t; i++) {
        for (int j = l[i]; j <= r[i]; j++)
            ret += abs(st[i].top() - a[j]);
    }
    return ret;
}

int main() {
    while (scanf("%d", &N) != EOF) {
        for (int i = 1; i <= N; i++) scanf("%d", a + i);
        int ans = 0x3fffffff;
        e = 0;
        ans = min(ans, work());
        reverse(a + 1, a + 1 + N);
        e = 0;
        ans = min(ans, work());
        printf("%d\n", ans);
    }
}
