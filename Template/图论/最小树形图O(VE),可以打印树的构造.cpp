//��С����ͼ,���Ӷ�O(VE),���Դ�ӡ���Ĺ���---------zjut_DD
//hdu 2121 һ������ͼ,��һ����Ȼ��ʹ��С����ͼȨֵ��С
#include<iostream>
#include<cmath>

using namespace std;

typedef int type;
#define inf 0x7fffffff
#define maxn 1005
#define maxm 10005
struct Edge {
    //��߱�
    int iu, iv, ru, rv;
    //��(imagine),ʵ(real)  u->v
    type val;
    int next;
} E[2][maxm];
int l[2][maxn], e[2];
int ip[maxn], rp[maxn];
//rp��ʵ�ʵĵ�ĸ��ڵ�,���������ô����
int sign[maxn], ID[maxn];
type In[maxn];

void init(bool f = false) {//Ĭ�ϲ���Ϊ��һ�ε��÷���
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
    bool f = false;//��f��!f
    while (true) {
        //����С���
        for (int i = 0; i < N; i++) {
            if (i == root) continue;
            In[i] = inf;
            int ind;
            for (int p = l[f][i]; p >= 0; p = E[f][p].next) {
                //��������ж��ǻ�����С��ſ��ǵ�,hdu2121
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
                return false; //�޽�
        }
        //�һ�,���±��
        memset(sign, -1, sizeof(sign));
        memset(ID, -1, sizeof(ID));
        int cnt = 0;

        for (int i = 0; i < N; i++) {
            int v = i;
            while (sign[v] == -1 && v != root) { //û�ѵ��� & ���Ǹ�
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
        //ת��Ϊ��һ��ͼ
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
}//****************ģ�����****************

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
            while (rp[t] != N) t++; //�Ҹ�
            printf("%d %d\n", ret - KKK, t);
        }
        else
            puts("impossible");
        puts("");
    }
}