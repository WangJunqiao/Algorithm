//无源汇可行流  输出方案 http://acm.sgu.ru/problem.php?problem=194 已AC
//增加源汇,对于(u->v, b, c) 增加(src->v, b),(u->sink, b)跑最大流。满流则有解。

#include "最大流dinic 邻接矩阵.txt"

Netflow <int, 210> flow;

struct Edge {
    int u, v, b, c;

    // b<=f<=c 上下界
    Edge(int _u, int _v, int _b, int _c) : u(_u), v(_v), b(_b), c(_c) { };
};

//计算无源汇上下界可行流, 传入无源汇边集
bool no_src_feasible_flow(vector < Edge > es) {
    int n = 0;
    for (int i = 0; i < es.size(); i++) n = max(n, max(es[i].u, es[i].v)); //找到最大的节点编号
    int s = ++n, t = ++n;
    flow.init(n + 1);
    int sf = 0;
    for (int i = 0; i < es.size(); i++) {
        int u = es[i].u, v = es[i].v, b = es[i].b, c = es[i].c;
        if (b > c || c < 0) return false; //无解
        flow.cap[u][t] += b;
        flow.cap[s][v] += b;
        flow.cap[u][v] += c - b;
        sf += b;
    }
    return flow.dinic(s, t) == sf;
}//----over----

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        vector <Edge> es;
        for (int i = 0; i < m; i++) {
            int u, v, b, c; //u->v的流量必须在[b, c]之间
            scanf("%d %d %d %d", &u, &v, &b, &c);
            es.push_back(Edge(u, v, b, c));
        }
        if (!no_src_feasible_flow(es)) { //看所有下限是否都能满足
            puts("NO");
        } else {
            puts("YES");
            for (int i = 0; i < m; i++) {
                int u = es[i].u, v = es[i].v;
                printf("%d\n", es[i].c - flow.cap[u][v]);//无重边
            }
        }
    }
}
