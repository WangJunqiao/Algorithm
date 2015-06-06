//最小树形图,复杂度O(VE),可以打印树的构造---------zjut_DD
//hdu 2121 一个有向图,找一个根然后使最小树形图权值最小
#include<iostream>
#include<cmath>

using namespace std;

typedef int type;
#define inf 0x7fffffff
#define maxn 1005
#define maxm 10005
struct Edge {
    //入边表
    int iu, iv, ru, rv;
    //虚(imagine),实(real)  u->v
    type val;
    int next;
} E[2][maxm];
int l[2][maxn], e[2];
int ip[maxn], rp[maxn];
//rp是实际的点的父节点,用于输出怎么构造
int sign[maxn], ID[maxn];
type In[maxn];

void init(bool f = false) {//默认参数为第一次调用服务
    memset(l[f], -1, sizeof(l[f]));
    e[f] = 0;
}

inline void _ins(bool f, int iu, int iv, int ru, int rv, type val) {
    E[f][e[f]].iu = iu;
    E[f][e[f]].iv = iv;
    E[f][e[f]].ru = ru;
    E[f][e[f]].rv = rv;
    E[f][e[f]].val = val;
    E[f][e[f]].next = l[f][iv];
    l[f][iv] = e[f]++;
}

inline void insert(int u, int v, type val) {
    if (u == v) return;
    _ins(false, u, v, u, v, val);
}

bool Directed_MST(int root, int N, type &ret) { //0~N-1
    ret = 0;
    bool f = false;//从f到!f
    while (true) {
        //找最小入边
        for (int i = 0; i < N; i++) {
            if (i == root) continue;
            In[i] = inf;
            int ind;
            for (int p = l[f][i]; p >= 0; p = E[f][p].next) {
                //下面这个判断是基于最小编号考虑的,hdu2121
                if ((E[f][p].val < In[i]) || (
                        (E[f][p].val == In[i]) && (E[f][p].rv < E[f][ind].rv))) {
                    In[i] = E[f][p].val;
                    ind = p;
                }
            }
            if (In[i] < inf) {
                ret += In[i];
                ip[E[f][ind].iv] = E[f][ind].iu;
                rp[E[f][ind].rv] = E[f][ind].ru;
            } else
                return false; //无解
        }
        //找环,重新标号
        memset(sign, -1, sizeof(sign));
        memset(ID, -1, sizeof(ID));
        int cnt = 0;

        for (int i = 0; i < N; i++) {
            int v = i;
            while (sign[v] == -1 && v != root) { //没搜到过 & 不是根
                sign[v] = i;
                v = ip[v];
            }
            if (sign[v] == i) {
                int u = v;
                do {
                    ID[v] = cnt;
                    v = ip[v];
                } while (v != u);
                cnt++;
            }
        }
        if (cnt == 0) break;
        for (int i = 0; i < N; i++) if (ID[i] == -1) ID[i] = cnt++;
        //转移为下一幅图
        init(!f);
#define EE (E[f][p])
        for (int i = 0; i < N; i++) {
            for (int p = l[f][i]; p != -1; p = E[f][p].next) {
                if (ID[EE.iu] != ID[EE.iv]) {
                    _ins(!f, ID[EE.iu], ID[EE.iv], EE.ru, EE.rv, EE.val - In[EE.iv]);
                }
            }
        }
        N = cnt;
        root = ID[root];
        f = !f;
    }
    return true;
}//****************模板结束****************

int main() {
    int N, M;
    while (scanf("%d%d", &N, &M) != EOF) {
        init();
        int a, b, c;
        for (int i = 0; i < M; i++) {
            scanf("%d%d%d", &a, &b, &c);
            insert(a, b, c);
        }
        int KKK = 100000000, ret;
        for (int i = 0; i < N; i++) insert(N, i, KKK);
        Directed_MST(N, N + 1, ret);
        if (ret < 2 * KKK) {
            int t = 0;
            while (rp[t] != N) t++; //找根
            printf("%d %d\n", ret - KKK, t);
        }
        else
            puts("impossible");
        puts("");
    }
}