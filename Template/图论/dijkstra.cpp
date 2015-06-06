#define MAXN 11000
//dijkstra 
#define inf 0x3fffffff //���ֵ
typedef int ValueT;
typedef pair <int, ValueT> Edge;
vector <Edge> adj[MAXN];
ValueT dis[MAXN];

struct DD {
    int v;
    ValueT dis;

    DD(int _v = 0, ValueT _dis = 0) : v(_v), dis(_dis) { };

    bool operator<(const DD &b) const {
        return dis > b.dis;
    }
};

void dijkstra(int source) {//Դ��Ϊsource
    for (int i = 0; i < MAXN; i++) dis[i] = inf;
    priority_queue <DD> pq;
    dis[source] = 0;
    pq.push(DD(source, 0));
    while (!pq.empty()) {
        DD temp = pq.top();
        pq.pop();
        int u = temp.v;
        if (temp.dis > dis[u]) continue; //֮ǰ��չ��
        for (int p = 0; p < (int) adj[u].size(); p++) {
            int v = adj[u][p].first;
            if (dis[v] > dis[u] + adj[u][p].second) {
                dis[v] = dis[u] + adj[u][p].second;
                pq.push(DD(v, dis[v]));
            }
        }
    }
}

void init(int n) {
    for (int i = 0; i <= n; i++) {
        adj[i].clear();
    }
}

void addEdge(int u, int v, ValueT val) { //���뵥���
    adj[u].push_back(Edge(v, val));
}