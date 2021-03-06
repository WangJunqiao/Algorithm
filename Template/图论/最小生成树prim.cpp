//最小生成树 prim，需要临界表**************************
struct DD {
    int v, val;

    DD(int _v = 0, int _val = 0) : v(_v), val(_val) { };

    bool operator<(const DD &b) const {
        return val > b.val;
    }
};

priority_queue <DD> pq;
int dis[maxn];
bool vst[maxn];

int prim(int n) {  //0~n-1的最小生成树，返回总权值
    const int inf = 1 << 29;
    while (!pq.empty()) pq.pop();
    for (int i = 0; i < n; i++) dis[i] = inf, vst[i] = false;
    pq.push(DD(0, 0));
    dis[0] = 0;
    while (!pq.empty()) {
        DD temp = pq.top();
        pq.pop();
        if (vst[temp.v]) continue;
        vst[temp.v] = true; //加入生成树中
        for (int p = list[temp.v]; p != -1; p = E[p].next) {
            int v = E[p].v;
            if (vst[v] == false && dis[v] > E[p].val) {
                dis[v] = E[p].val;
                pq.push(DD(v, dis[v]));
            }
        }
    }
    int ret = 0;
    for (int i = 0; i < n; i++) ret += dis[i];
    return ret;
}//***********************模板结束**************************