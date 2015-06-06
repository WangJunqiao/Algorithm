typedef long long LL;
typedef pair <int, int> PII;
typedef vector <int> VI;
typedef vector <string> VS;

#define sz(X) ((int)(X.size()))
#define all(x) x.begin(),x.end()
#define clr(x, c) memset(x,c,sizeof(x))
#define rep(i, s, e) for(int i=s;i<e;i++)


//http://www.lydsy.com/JudgeOnline/problem.php?id=1901  zju2112��С���ݰ汾
//֧���޸ĵ������K�������㷨����״�����׺���ʽ�߶�������������ʷ�汾���ڵ㶯̬����
//��ʼ�����Ӷ�n*log(n)*log(max_int)����ѯ���Ӷ�log(n)*log(max_int), ���¸��Ӷ�log(n)*log(max_int)���ռ临�Ӷ�n*log(n)*log(max_int)
//���maxn�Ƚϴ󣬾���Ҫ��ɢ����
#define maxn 10010
#define maxq 10010
#define maxm 3000000
struct Node {
    int num;
    Node *ch[2];
} dd[maxm];
int eid; //ÿ��case��ֵ��1, &dd[0]����NULL��
Node *root[maxn]; //root[i]�����������[i-lowbit(i)+1, i]����Ϣ

#define null (&dd[0])

void init(Node *p) {
    p->num = 0;
    p->ch[0] = p->ch[1] = null;
}

//�޸�֮������汾��û���ˣ����Բ����½��ڵ�
void modify(Node *&rt, int l, int r, int x, int add) {
    if (rt == null) {
        rt = &dd[eid++];
        assert(eid <= maxm);
        init(rt);
    }
    rt->num += add;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        modify(rt->ch[0], l, mid, x, add);
    else
        modify(rt->ch[1], mid + 1, r, x, add);
}


int lowbit(int x) {
    return x & (-x);
}

int MIN_INDEX, MAX_INDEX;

void modify(int x, int val, int num, int N) { //ԭʼ����x��base1��λ�ö���num��val
    for (; x <= N; x += lowbit(x))
        modify(root[x], MIN_INDEX, MAX_INDEX, val, num);
}

void get_roots(Node **rt, int &sz, int x) {
    for (sz = 0; x; x -= lowbit(x))
        rt[sz++] = root[x];
}


Node *rtL[55], *rtR[55];
int sL, sR;

int find(int l, int r, int k) { //��ѯ����[l, r]��k��
    if (l == r) return l;
    int sumL = 0, sumR = 0;
    rep(i, 0, sL) sumL += rtL[i]->ch[0]->num;
    rep(i, 0, sR) sumR += rtR[i]->ch[0]->num;
    int mid = (l + r) >> 1;
    if (sumR - sumL >= k) {
        rep(i, 0, sL) rtL[i] = rtL[i]->ch[0];
        rep(i, 0, sR) rtR[i] = rtR[i]->ch[0];
        return find(l, mid, k);
    } else {
        k -= (sumR - sumL);
        rep(i, 0, sL) rtL[i] = rtL[i]->ch[1];
        rep(i, 0, sR) rtR[i] = rtR[i]->ch[1];
        return find(mid + 1, r, k);
    }
} //---------------


int val[maxn];

int main() {
    int n, m;
    MIN_INDEX = 0;
    MAX_INDEX = 1000000000;
    while (scanf("%d %d", &n, &m) != EOF) {
        init(&dd[0]); //��ʼ��null
        eid = 1;

        rep(i, 1, n + 1) scanf("%d", val + i);
        rep(i, 1, n + 1) root[i] = null;
        rep(i, 1, n + 1) modify(i, val[i], 1, n); //��ʼ��

        rep(i, 0, m) {
            char op;
            int a, b, c;
            scanf(" %c", &op);
            if (op == 'Q') {
                scanf("%d %d %d", &a, &b, &c);
                get_roots(rtL, sL, a - 1);
                get_roots(rtR, sR, b);
                printf("%d\n", find(MIN_INDEX, MAX_INDEX, c));
            } else {
                scanf("%d %d", &a, &b);
                modify(a, val[a], -1, n);
                val[a] = b;
                modify(a, val[a], 1, n);
            }
        }
    }
}