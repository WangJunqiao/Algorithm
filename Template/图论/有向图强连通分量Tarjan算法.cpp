/*
有向图强连通分量Tarjan算法
如果一个节点是根,那么DFN(深度优先序号)==Low(能达到的最低标号)
*/
#define maxn 11000

struct Tarjan {
    vector <int> *adj;
    bool in[maxn];
    int DFN[maxn], Low[maxn], st[maxn], top, *label, compo, deep; //深度必须是一个全局量!!!!
    //处理0~N-1,结果存在label数组里,label[i]表示i这个节点属于谁,返回收缩后还有几个点base0
    int dirGraphShrink(int N, vector <int> *adj, int *label) {
        this->adj = adj;
        this->label = label;
        memset(in, false, sizeof(in));
        memset(DFN, 0, sizeof(DFN));
        top = compo = deep = 0;
        for (int i = 0; i < N; i++) if (DFN[i] == 0) _tarjan(i);
        return compo;
    }

    void _tarjan(int u) {
        DFN[u] = Low[u] = ++deep;
        st[top++] = u;
        in[u] = true;
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (DFN[v] == 0) {
                _tarjan(v);
                Low[u] = min(Low[u], Low[v]);
            } else if (in[v])//防止uv是横叉边****必须在栈中
                Low[u] = min(Low[u], DFN[v]);
        }
        if (Low[u] == DFN[u]) {
            int v;
            do {
                v = st[--top];
                label[v] = compo;
                in[v] = false;
            } while (v != u);
            compo++;
        }
    }
} dir_tarjan;//**************模板结束************************