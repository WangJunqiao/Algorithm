/*
Algorithm: LCA _rmq 必须保证是一棵树,完全连通的,不是森林!!
Author: zjut_DD
*/
#define maxn 110000

struct LCA_RMQ {
    vector <int> *adj;

    //***********以上需要外部赋值********
    void LCA(int N, int root = 0) {//0~N-1,进行lca预处理
        fill(dep, dep + N, -1); //未访问
        sid = 0;
        _dfs(root);
        _rmq(N * 2 - 1);
    }

    void _dfs(int root) { //模拟递归， 生成_dfs序列
        dep[root] = 0;
        ver.push(root);
        ind.push(0);
        while (!ver.empty()) {
            int u = ver.top(), &p = ind.top();
            pos[u] = sid;
            seq[sid++] = u;
            repeat:;
            if (p < adj[u].size()) {
                int v = adj[u][p++];
                if (dep[v] >= 0) goto repeat;
                dep[v] = dep[u] + 1;
                ver.push(v);
                ind.push(0);
            } else {
                ver.pop();
                ind.pop();
            }
        }
    }

    void _rmq(int len) {
        int M = _get(len);
        for (int i = 0; i < len; i++) mi[i][0] = seq[i];
        for (int g = 1; g <= M; g++) {
            int L = len - (1 << g);
            for (int i = 0; i <= L; i++) {
                mi[i][g] = dep[mi[i][g - 1]] < dep[mi[i + (1 << (g - 1))][g - 1]] ?
                           mi[i][g - 1] : mi[i + (1 << (g - 1))][g - 1];//888888888
            }
        }
    }

    int _get(int L) {//查询太多， 需要预处理
        return int(log(L * 1.0) / log(2.0));
    }

    int query(int a, int b) {//询问a和b的lca,返回编号
        if (pos[a] > pos[b]) swap(a, b);
        int wa = pos[a], wb = pos[b];
        int g = _get(wb - wa + 1);
        return dep[mi[wa][g]] < dep[mi[wb - (1 << (g)) + 1][g]] ?
               mi[wa][g] : mi[wb - (1 << (g)) + 1][g];//****和上面不一样的
    }

    int dep[maxn]; //每个节点的_dfs深度
    int seq[2 * maxn], sid;
    //seq存节点，长度为2*N-1
    int mi[maxn * 2][20];
    //比较的是dep[ seq[i] ]
    int pos[maxn];
    //节点i在seq里的最后一个位置
    stack <int> ver, ind;
} lca_rmq;