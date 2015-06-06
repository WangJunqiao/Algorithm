//pku 3710 多棵树,树上有环 树的删边游戏
#include<iostream>

using namespace std;

#define maxn 105
struct Edge {
    int v, next;
} E[4 * maxn];
int list[maxn], eid;
bool visN[maxn], visM[4 * maxn];
//点访问,边访问
bool inner[maxn]; //是否是环的内部点,不包括环和树的公共点
int st[maxn], top; //节点的访问栈

void init() {
    memset(list, -1, sizeof(list));
    memset(visN, false, sizeof(visN));
    memset(visM, false, sizeof(visM));
    memset(inner, false, sizeof(inner));
    eid = 0;
    top = 0;
}

void insert(int a, int b) {
    E[eid].v = b;
    E[eid].next = list[a];
    list[a] = eid++;
    E[eid].v = a;
    E[eid].next = list[b];
    list[b] = eid++;
}

int dfs(int u) {
    visN[u] = true;
    int nim = 0;
    st[++top] = u;
    for (int p = list[u]; p != -1; p = E[p].next) {
        if (visM[p]) continue;
        visM[p] = visM[p ^ 1] = true; //
        int ret, v = E[p].v;
        if (!visN[v]) {
            ret = dfs(v);
        } else {
            while (st[top] != v) {
                inner[st[top--]] = true;
            }
            return 1;
        }
        if (inner[v]) nim ^= (!ret);
        else nim ^= (ret + 1);
    }
    return nim;
}

int main() {
    int Tree, nim;
    while (scanf("%d", &Tree) != EOF) { //几棵树
        nim = 0;
        for (int T = 1; T <= Tree; T++) {
            init();
            int N, M;
            scanf("%d%d", &N, &M);
            for (int i = 1; i <= M; i++) {
                int a, b;
                scanf("%d%d", &a, &b);
                insert(a, b);
            }
            nim ^= dfs(1);
        }
        //cout<<nim<<endl;
        if (nim) puts("Sally");
        else puts("Harry");
    }
}
