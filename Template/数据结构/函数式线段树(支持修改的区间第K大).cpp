typedef long long LL;
typedef pair <int, int> PII;
typedef vector <int> VI;
typedef vector <string> VS;

#define sz(X) ((int)(X.size()))
#define all(x) x.begin(),x.end()
#define clr(x, c) memset(x,c,sizeof(x))
#define rep(i, s, e) for(int i=s;i<e;i++)


//http://www.lydsy.com/JudgeOnline/problem.php?id=1901  zju2112的小数据版本
//支持修改的区间第K大，在线算法，树状数组套函数式线段树，不保存历史版本，节点动态创建
//初始化复杂度n*log(n)*log(max_int)，查询复杂度log(n)*log(max_int), 更新复杂度log(n)*log(max_int)，空间复杂度n*log(n)*log(max_int)
//如果maxn比较大，就需要离散化了
#define maxn 10010
#define maxq 10010
#define maxm 3000000
struct Node {
    int num;
    Node *ch[2];
} dd[maxm];
int eid; //每个case赋值成1, &dd[0]当做NULL用
Node *root[maxn]; //root[i]保存的是区间[i-lowbit(i)+1, i]的信息

#define null (&dd[0])

void init(Node *p) {
    p->num = 0;
    p->ch[0] = p->ch[1] = null;
}

//修改之后，这个版本就没用了，所以不用新建节点
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

void modify(int x, int val, int num, int N) { //原始数组x（base1）位置多了num个val
    for (; x <= N; x += lowbit(x))
        modify(root[x], MIN_INDEX, MAX_INDEX, val, num);
}

void get_roots(Node **rt, int &sz, int x) {
    for (sz = 0; x; x -= lowbit(x))
        rt[sz++] = root[x];
}


Node *rtL[55], *rtR[55];
int sL, sR;

int find(int l, int r, int k) { //查询区间[l, r]第k大
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
        init(&dd[0]); //初始化null
        eid = 1;

        rep(i, 1, n + 1) scanf("%d", val + i);
        rep(i, 1, n + 1) root[i] = null;
        rep(i, 1, n + 1) modify(i, val[i], 1, n); //初始化

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