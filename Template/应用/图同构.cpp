/*
无向图可以看成有向图!!!
有向图同构,输出对应点 pku2040
因为是图,不是树,因此没有拓扑结构,我们只有综合考虑所有的点.
我们采用迭代的思想,每次用第i层所有点的哈希值,计算出第i+1层的哈希值,
为了防止最后趋于稳定,我们选取一个播种源x.
h[i+1][u]=a*h[i][u] + b*h[i][v] + c*h[i][w] + d; 
其中u->v,w->u属于边集E,当u==x时d才不为0!!
为了让x的种子遍布整个图(连通吗?),至少迭代n次
*/
#define maxn 100
#define maxm 30005
typedef unsigned int uint;
struct Edge {
    int v, val, next;
} E[maxm];
int e;

struct AdjList {
    int l[maxn]; //
    void insert(int a, int b, int val = 0) { //单向边
        E[e].v = b;
        E[e].val = val;
        E[e].next = l[a];
        l[a] = e++;
    }

    void init() {
        memset(l, -1, sizeof(l));
    }
} adj[2];

//计算哈希值,0~n-1,播种点,哈希值数组,邻接表,4个参数
void calc(int n, int x, uint *h, AdjList &adj, uint a, uint b, uint c, uint d) {
    uint tmp[maxn] = {0};
    for (int i = 0; i < n; i++) {
        tmp[i] += a * h[i];
        if (i == x) tmp[i] += d;
        for (int j = adj.l[i]; j >= 0; j = E[j].next) {
            int v = E[j].v;
            tmp[i] += b * h[v];
            tmp[v] += c * h[i];
        }
    }
    memcpy(h, tmp, sizeof(uint) * n);
}

bool same(uint *d, int n) {
    for (int i = 0; i < n; i++) for (int j = 0; j < i; j++) if (d[i] == d[j]) return true;
    return false;
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out8.txt", "w", stdout);
    int n, Te = 0;
    while (cin >> n && n) {
        e = 0;
        map <string, int> mp[2];
        string s[2][maxn];
        for (int i = 0; i < 2; i++) {
            adj[i].init();
            mp[i].clear();
            for (int j = 0; j < n; j++) {
                string s1, s2;
                cin >> s1 >> s2;
                if (mp[i].find(s1) == mp[i].end()) {
                    int t = mp[i].size();
                    mp[i][s1] = t;
                }
                if (mp[i].find(s2) == mp[i].end()) {
                    int t = mp[i].size();
                    mp[i][s2] = t;
                }
                adj[i].insert(mp[i][s1], mp[i][s2]);
            }
            for (map<string, int>::iterator it = mp[i].begin(); it != mp[i].end(); ++it)
                s[i][it->second] = it->first;
        }//以上建图
        int W = mp[0].size(), cnt;
        uint h[2][maxn];
        pair <string, string> ans[maxn];
        for (int x = 0; x < W; x++) { //枚举第一副图中0和谁对应
            for (int j = 0; j < W; j++) h[0][j] = h[1][j] = 1; //初始化
            int ti = 0;
            while (true) { //迭代,至少W次, tle??
                ti++;
                if (ti >= W && !same(h[0], W) && !same(h[1], W)) break;
                calc(W, 0, h[0], adj[0], 5423, 899535389, 1467557, 5433525);
                calc(W, x, h[1], adj[1], 5423, 899535389, 1467557, 5433525);
            }
            cnt = 0;
            for (int i = 0; i < W; i++) { //一一匹配
                for (int j = 0; j < W; j++) {
                    if (h[0][i] == h[1][j]) {
                        ans[cnt].first = s[0][i];
                        ans[cnt].second = s[1][j];
                        cnt++;
                        break;
                    }
                }
            }
            if (cnt == W) break;
        }
        if (Te++) puts("");
        sort(ans, ans + W);
        for (int i = 0; i < W; i++) {
            cout << ans[i].first << "/" << ans[i].second << '\n';
        }
    }
}