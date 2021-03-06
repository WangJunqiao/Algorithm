//差分约束系统，单源最短路径spfa
//最短路最长路都经过测试，差分约束hdu3666
//差分约束注意保持图的连通性，可以添加类似0<=x[i]<=1000000000之类的
template<typename ValueT>
struct SPFA {
#define MAXN 11000
#define INF 1000000000
    typedef pair <int, ValueT> EdgeT; //(to, dist)
    vector <EdgeT> adj[MAXN];
    ValueT dis[MAXN];

    queue <int> _q;
    int _inq[MAXN], _cnt[MAXN];
    bool shortest;

    void _update(int i, ValueT d) {
        if ((shortest && d < dis[i]) || (!shortest && d > dis[i])) {
            dis[i] = d;
            if (!_inq[i]) {
                _q.push(i);
                _inq[i] = 1;
                _cnt[i]++;
            }
        }
    }

    //是否是最短路模型
    void init(int n, bool _shortest = true) {
        for (int i = 0; i < n; i++) adj[i].clear();
        shortest = _shortest;
    }

    void addEdge(int u, int v, ValueT w) {
        adj[u].push_back(make_pair(v, w));
        //cout<<u<<" --> "<<v<<" : "<<w<<endl;
    }

    //增加限制条件: x[i] + a <= x[j] + b , 是否是最短路模型
    void addConstraint(int i, ValueT a, int j, ValueT b) {
        if (shortest)
            addEdge(j, i, b - a); //最短路模型
        else
            addEdge(i, j, a - b); //最长路模型
        //printf("%d -> %d : %lf\n", j, i, b-a);
    }

    bool spfa(int src, int n) {
        for (int i = 0; i < n; i++) {
            dis[i] = INF * (shortest ? 1 : -1);
            _inq[i] = _cnt[i] = 0;
        }
        while (!_q.empty()) _q.pop();

        _update(src, 0);
        while (!_q.empty()) {
            int u = _q.front();
            _q.pop();
            _inq[u] = 0;
            if (_cnt[u] > 2 * n)  //如果太慢可以试着改这里
                return false; //最短路存在负环，或者最长路存在正环
            for (int i = 0; i < (int) adj[u].size(); i++) {
                _update(adj[u][i].first, dis[u] + adj[u][i].second);
            }
        }
        return true;
    }
};

SPFA<double> dc;