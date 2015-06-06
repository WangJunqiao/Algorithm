//Hopcroft Karp�㷨������ƥ�伯��Mʱ,ÿ��Ѱ�Ҷ�������·,���Ӷ�O(V^0.5*E)
#include <iostream>

using namespace std;
const int MAXN = 50005;
const int MAXM = 150005;
int nx, ny, m, x, y, ans;
int edge, head[MAXN], nxt[MAXM], e[MAXM];
int cx[MAXN], cy[MAXN];
// cx[i]��ʾxi��Ӧ��ƥ��,cy[i]��ʾyi��Ӧ��ƥ��.
int distx[MAXN], disty[MAXN]; // ��ĸ���,����BFS�еĵڼ���.
int que[MAXN];

void init() {
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    memset(head, -1, sizeof(head));
    edge = 0;
    ans = 0;
}

inline void addedge(int u, int v) {
    e[edge] = v;
    nxt[edge] = head[u];
    head[u] = edge++;
}

bool BFS() {
    bool flag = 0;
    memset(distx, 0, sizeof(distx));
    memset(disty, 0, sizeof(disty));
    int l = 0, r = 0, h, t;
    for (int i = 1; i <= nx; i++)
        if (cx[i] == -1)
            que[r++] = i;
    while (l != r) {
        for (h = l, t = r; h != t; h = (h + 1) % MAXN) {
            int u = que[h];
            for (int i = head[u]; i != -1; i = nxt[i]) {
                int v = e[i];
                if (!disty[v]) {
                    disty[v] = distx[u] + 1;
                    if (cy[v] == -1) flag = 1;
                    else {
                        distx[cy[v]] = disty[v] + 1;
                        que[r] = cy[v];
                        r = (r + 1) % MAXN;
                    }
                }
            }
        }
        l = t;
    }
    return flag;
}

bool DFS(int u) { //�ݹ����Ϊsqrt(n)
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = e[i];
        if (disty[v] == distx[u] + 1) { //˵��v��u�ĺ�̽��.
            disty[v] = 0; // v���ù���,��������Ϊ������ĺ�̽����.
            if (cy[v] == -1 || DFS(cy[v])) {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

void Hopcroft_Karp() {
    while (BFS())
        for (int i = 1; i <= nx; i++)
            if (cx[i] == -1 && DFS(i))
                ans++;
}

int main() {
    while (scanf("%d %d %d", &nx, &ny, &m) != EOF) {
        init();
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &x, &y);
            addedge(x, y);
        }
        Hopcroft_Karp();
        printf("%d\n", ans);
    }
}
