//author: momodi@whuacm
//ural 1099
//һ��ͼƥ��,�������㷨
//��ʼ����Ҫ n�Ĵ�С(base0),adj����

#include<iostream>

using namespace std;
#define maxn 1000
int n;
//�ڵ����,�õ���0~n-1,
int match[maxn];
//ÿ����ƥ�����
bool adj[maxn][maxn];

//�ڽ���,��ͨΪtrue
void clear() {
    memset(adj, 0, sizeof(adj));
    n = 0;
}

void insert(const int &u, const int &v) {
    adj[u][v] = adj[v][u] = 1;
}

int Q[maxn], pre[maxn], base[maxn];
bool _h[maxn];
bool in_blossom[maxn];

void argument(int u) {
    while (u != -1) {
        int v = pre[u];
        int k = match[v];
        match[u] = v;
        match[v] = u;
        u = k;
    }
}

void change_blossom(int b, int u) {
    while (base[u] != b) {
        int v = match[u];
        in_blossom[base[v]] = in_blossom[base[u]] = true;
        u = pre[v];
        if (base[u] != b) {
            pre[u] = v;
        }
    }
}

int find_base(int u, int v) {
    bool in_path[maxn] = {};
    while (true) {
        in_path[u] = true;
        if (match[u] == -1) {
            break;
        }
        u = base[pre[match[u]]];
    }
    while (!in_path[v]) {
        v = base[pre[match[v]]];
    }
    return v;
}

int contract(int u, int v) {
    memset(in_blossom, 0, sizeof(in_blossom));
    int b = find_base(base[u], base[v]);
    change_blossom(b, u);
    change_blossom(b, v);
    if (base[u] != b) {
        pre[u] = v;
    }
    if (base[v] != b) {
        pre[v] = u;
    }
    return b;
}

int bfs(int p) {
    memset(pre, -1, sizeof(pre));
    memset(_h, 0, sizeof(_h));
    for (int i = 0; i < n; ++i) {
        base[i] = i;
    }
    Q[0] = p;
    _h[p] = 1;
    for (int s = 0, t = 1; s < t; ++s) {
        int u = Q[s];
        for (int v = 0; v < n; ++v) {
            if (adj[u][v] && base[u] != base[v] && v != match[u]) {
                if (v == p || (match[v] != -1 && pre[match[v]] != -1)) {
                    int b = contract(u, v);
                    for (int i = 0; i < n; ++i) {
                        if (in_blossom[base[i]]) {
                            base[i] = b;
                            if (_h[i] == 0) {
                                _h[i] = 1;
                                Q[t++] = i;
                            }
                        }
                    }
                } else if (pre[v] == -1) {
                    pre[v] = u;
                    if (match[v] == -1) {
                        argument(v);
                        return 1;
                    }
                    else {
                        Q[t++] = match[v];
                        _h[match[v]] = 1;
                    }
                }
            }
        }
    }
    return 0;
}

int max_match() { //�ڵ��Ŵ�0~n-1
    memset(match, -1, sizeof(match));//ûƥ��ľ���-1
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (match[i] == -1) {
            ans += bfs(i);
        }
    }
    return ans;
}//**************ģ�����**************

int main() {
    int N, a, b;
    scanf("%d", &N);
    n = N;
    memset(adj, false, sizeof(adj));
    while (scanf("%d%d", &a, &b) != EOF) {
        adj[a - 1][b - 1] = adj[b - 1][a - 1] = true;
    }
    int ret = max_match();
    printf("%d\n", ret * 2);
    for (int i = 0; i < N; i++) {
        if (match[i] != -1) {
            printf("%d %d\n", i + 1, match[i] + 1);
            match[match[i]] = -1;
        }
    }
}











