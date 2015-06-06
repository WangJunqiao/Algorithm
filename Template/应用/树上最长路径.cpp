//hdu 3534 树上最长路径,条数
#include<iostream>

using namespace std;

#define maxn 100005

struct Edge {
    int v, val, x;
} E[2 * maxn];
int l[maxn], e;

void init() {
    e = 0;
    memset(l, -1, sizeof(l));
}

void insert(int a, int b, int val) {
    E[e].v = b;
    E[e].val = val;
    E[e].x = l[a];
    l[a] = e++;
}

bool vst[maxn];

struct PII {
    int len, num;
} ans;

void insert(PII &p1, PII &p2, PII p3) {
    if (p3.len == p1.len) { //需要化归
        if (p3.len + p1.len > ans.len) {
            ans.len = p3.len + p1.len;
            ans.num = p3.num * p1.num;  //溢出?
        } else if (p3.len + p1.len == ans.len) {
            ans.num += p3.num * p1.num;
        }
        p1.num += p3.num;
    } else if (p3.len > p1.len) {
        p2 = p1;
        p1 = p3;
    } else if (p3.len >= p2.len) {
        p2 = p3;
    }
}

PII dfs(int u) { //<len,num>
    vst[u] = true;
    PII p1, p2, tmp;
    p1.len = p2.len = 0;
    p1.num = p2.num = 1;
    for (int i = l[u]; i >= 0; i = E[i].x) {
        int v = E[i].v;
        if (vst[v]) continue;
        tmp = dfs(v);
        tmp.len += E[i].val;
        insert(p1, p2, tmp);
    }
    if (p1.len + p2.len > ans.len) {
        ans.len = p1.len + p2.len;
        ans.num = p1.num * p2.num;      //溢出?
    } else if (p1.len + p2.len == ans.len) {
        ans.num += p1.num * p2.num;
    }
    return p1;
}

int main() {
    int n, a, b, val;
    while (scanf("%d", &n) != EOF) {
        init();
        for (int i = 1; i < n; i++) {
            scanf("%d %d %d", &a, &b, &val);
            insert(a, b, val);
            insert(b, a, val);
        }
        memset(vst, false, sizeof(vst));
        ans.len = -1;
        dfs(1);
        printf("%d %d\n", ans.len, ans.num);
    }
}

