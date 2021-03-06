/*
主要思想仍然是找增广路，只是有了一些优化在里边。原来我们找增广路主要是依靠最短路算法，如SPFA。因此此算法的时间复杂度主要就取决于增广的次数和每次增广的耗费。由于每一次找增广路是都是重新算一遍，这样似乎显得有些浪费，如果我们能够缩短找增广路的时间，那必定会大大地优化算法。
值得注意的是，在寻求最短路得过程中，设dis[i]为i到起点的距离，对于每一条由i引向j的边，必有dis[j]<=dis[i]+map[i][j]；既然满足这样的恒等式，我们就可以借用KM算法的调整思想来寻求最短路，每次只走dis[j]=dis[i]+map[i][j]的路径，一旦不存在到达终点的路径，就扫描每一条边，找到最小的距离增加值，使得有至少一条新边被加入相等子图。
据我的实际运用，ZKW费用流在二分图类的网络流图中非常快，而在稀疏图中却不是一般的慢。据我的分析，这主要是由于ZKW的增广方法是深搜，而SPFA是宽搜，这就是这两种算法最本质的区别。
*/
//最小费用最大流ZKW算法, 稠密图用这个比spfa的快，因为这个是深搜，而spfa是宽搜，本质区别。
#define maxn 350
#define maxm 4*120*120
const int inf = 0x3f3f3f3f;
#define th(x) this->x=x;

struct Edge {
    int v, cap, cost, next, flow;

    //flow表示已经流过的流量,便于输出方案
    void init(int v, int cap, int cost, int next) {
        th(v);
        th(cap);
        th(cost);
        th(next);
    }
};

struct ZKW {
    int nxt[maxn], eid, n;
    int pi[maxn], source, sink, flow, cost;
    //标号，最大流,最小费
    bool vis[maxn];
    Edge e[maxm];

    void init(int n) { //base0
        th(n);
        memset(nxt, -1, sizeof(nxt));
        eid = 0;
    }

    void add_edge(int i, int j, int cap, int cst) {
        e[eid].init(j, cap, cst, nxt[i]);
        nxt[i] = eid++;
        e[eid].init(i, 0, -cst, nxt[j]);
        nxt[j] = eid++;
    }

    int _dfs(int idx, int maxCap) {
        if (idx == sink) {
            cost += pi[source] * maxCap;
            flow += maxCap;
            return maxCap;
        }
        vis[idx] = true;
        for (int i = nxt[idx]; i != -1; i = e[i].next) {
            Edge &nod = e[i];
            if (nod.cap - nod.flow > 0 && !vis[nod.v] && pi[nod.v] + nod.cost == pi[idx]) {
                if (int d = _dfs(nod.v, min(maxCap, nod.cap - nod.flow))) {
                    nod.flow += d;
                    e[i ^ 1].flow -= d;
                    return d;
                }
            }
        }
        return 0;
    }

    bool _modLabel() {
        int d = inf;
        for (int i = 0; i < n; i++)
            if (vis[i]) {
                for (int j = nxt[i]; j != -1; j = e[j].next) {
                    Edge &nod = e[j];
                    if (nod.cap - nod.flow > 0 && !vis[nod.v]) {
                        d = min(d, nod.cost - pi[i] + pi[nod.v]);
                    }
                }
            }
        if (d == inf) return false;
        for (int i = 0; i < n; i++) if (vis[i]) pi[i] += d;
        return true;
    }

    void solve(int source, int sink) {
        th(source);
        th(sink);
        flow = cost = 0;
        memset(pi, 0, sizeof(pi));
        for (int i = 0; i < eid; i++) e[i].flow = 0;
        do {
            do {
                memset(vis, 0, sizeof(vis));
            } while (_dfs(source, inf));
        } while (_modLabel());
    }
} mc; //mc.init(n); mc.add_edge(..); mc.solve();