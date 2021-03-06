/*有源汇可行流  输出方案 http://poj.org/problem?id=2396 已AC
prob: 一个N*M的矩阵, 给出每行每列的和, 每个格子的上下限制, 求一种可行方案
solu: 其实是一个s->t的有源汇可行流。做法是t->s连无穷大的边, 转化为无源汇可行流。
*/

#include "无源汇上下界可行流.txt"

int l[222][22], h[222][22];//确定上下界

void read_constraint(int N, int M) {
    int con;
    scanf("%d", &con);
    while (con--) {
        int r, c, val;
        char op;
        scanf(" %d %d %c %d", &r, &c, &op, &val);
        if (op == '<') val--;
        else if (op == '>') val++;
        for (int i = (r == 0 ? 1 : r); i <= (r == 0 ? N : r); i++) {
            for (int j = (c == 0 ? 1 : c); j <= (c == 0 ? M : c); j++) {
                if (op == '=') {
                    l[i][j] = max(l[i][j], val);
                    h[i][j] = min(h[i][j], val);
                } else if (op == '<') {
                    h[i][j] = min(h[i][j], val);
                } else if (op == '>') {
                    l[i][j] = max(l[i][j], val);
                } else {
                    assert(false);
                }
            }
        }
    }
}

int main() {
    int N, M, cas, ttt = 0;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d", &N, &M);
        int S = N + M + 1, T = N + M + 2;
        vector <Edge> es;
        for (int i = 1; i <= N; i++) {//每行的和
            int b;
            scanf("%d", &b);
            es.push_back(Edge(S, i, b, b));
        }
        for (int j = 1; j <= M; j++) { //每列的和
            int b;
            scanf("%d", &b);
            es.push_back(Edge(N + j, T, b, b));
        }
        for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) l[i][j] = 0, h[i][j] = INF;//每个格子的上下限
        read_constraint(N, M); //读取限制条件

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                es.push_back(Edge(i, N + j, l[i][j], h[i][j]));
            }
        }
        es.push_back(Edge(T, S, 0, INF));//从T引一条无穷大的边到S,绝对不能少!!

        if (ttt++) puts("");
        if (no_src_feasible_flow(es) == false) {
            puts("IMPOSSIBLE");
        } else {
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= M; j++)
                    printf("%d%s", h[i][j] - flow.cap[i][N + j], j == M ? "\n" : " ");
        }
    }
}

