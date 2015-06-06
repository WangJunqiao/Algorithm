/*
Algorithm: LCA _rmq ���뱣֤��һ����,��ȫ��ͨ��,����ɭ��!!
Author: zjut_DD
*/
#define maxn 110000

struct LCA_RMQ {
    vector <int> *adj;

    //***********������Ҫ�ⲿ��ֵ********
    void LCA(int N, int root = 0) {//0~N-1,����lcaԤ����
        fill(dep, dep + N, -1); //δ����
        sid = 0;
        _dfs(root);
        _rmq(N * 2 - 1);
    }

    void _dfs(int root) { //ģ��ݹ飬 ����_dfs����
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

    int _get(int L) {//��ѯ̫�࣬ ��ҪԤ����
        return int(log(L * 1.0) / log(2.0));
    }

    int query(int a, int b) {//ѯ��a��b��lca,���ر��
        if (pos[a] > pos[b]) swap(a, b);
        int wa = pos[a], wb = pos[b];
        int g = _get(wb - wa + 1);
        return dep[mi[wa][g]] < dep[mi[wb - (1 << (g)) + 1][g]] ?
               mi[wa][g] : mi[wb - (1 << (g)) + 1][g];//****�����治һ����
    }

    int dep[maxn]; //ÿ���ڵ��_dfs���
    int seq[2 * maxn], sid;
    //seq��ڵ㣬����Ϊ2*N-1
    int mi[maxn * 2][20];
    //�Ƚϵ���dep[ seq[i] ]
    int pos[maxn];
    //�ڵ�i��seq������һ��λ��
    stack <int> ver, ind;
} lca_rmq;