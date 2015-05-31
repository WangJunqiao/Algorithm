//��Դ�������  ������� http://acm.sgu.ru/problem.php?problem=194 ��AC
//����Դ��,����(u->v, b, c) ����(src->v, b),(u->sink, b)����������������н⡣

#include "�����dinic �ڽӾ���.txt"

Netflow <int, 210> flow;

struct Edge {
    int u, v, b, c;

    // b<=f<=c ���½�
    Edge(int _u, int _v, int _b, int _c) : u(_u), v(_v), b(_b), c(_c) { };
};

//������Դ�����½������, ������Դ��߼�
bool no_src_feasible_flow(vector < Edge > es) {
    int n = 0;
    for (int i = 0; i < es.size(); i++) n = max(n, max(es[i].u, es[i].v)); //�ҵ����Ľڵ���
    int s = ++n, t = ++n;
    flow.init(n + 1);
    int sf = 0;
    for (int i = 0; i < es.size(); i++) {
        int u = es[i].u, v = es[i].v, b = es[i].b, c = es[i].c;
        if (b > c || c < 0) return false; //�޽�
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
            int u, v, b, c; //u->v������������[b, c]֮��
            scanf("%d %d %d %d", &u, &v, &b, &c);
            es.push_back(Edge(u, v, b, c));
        }
        if (!no_src_feasible_flow(es)) { //�����������Ƿ�������
            puts("NO");
        } else {
            puts("YES");
            for (int i = 0; i < m; i++) {
                int u = es[i].u, v = es[i].v;
                printf("%d\n", es[i].c - flow.cap[u][v]);//���ر�
            }
        }
    }
}
