/*
有向图强连通分量Kosaraju算法,两次dfs
必须在反向图上第二次dfs的***
*/
struct Kosaraju {
    Edge *E;
    bool vst[maxn];
    int buf[maxn], top, *list, *label, compo;
    AdjList _adj; //反向图邻接表
    //处理0~N-1,结果存在label数组里,label[i]表示i这个节点属于谁,返回收缩后还有几个点base0
    int DirGraphShrink(int N, int *list, Edge *E, int *label) {
        this->E = E;
        this->list = list;
        this->label = label;
        compo = top = 0;
        fill(vst, vst + N, false);
        for (int i = 0; i < N; i++) if (!vst[i]) _dfs1(i);
        _adj.init();
        for (int i = 0; i < N; i++) {
            for (int p = list[i]; p != -1; p = E[p].next) _adj.insert(E[p].v, i);
        }
        fill(vst, vst + N, false);
        for (int i = top - 1; i >= 0; i--)
            if (!vst[buf[i]]) {
                _dfs2(buf[i]);
                compo++;
            }
        return compo;
    }

    void _dfs1(int u) {
        vst[u] = true;
        for (int p = list[u]; p != -1; p = E[p].next)
            if (!vst[E[p].v]) _dfs1(E[p].v);
        buf[top++] = u;
    }

    void _dfs2(int u) {
        vst[u] = true;
        label[u] = compo;
        for (int p = _adj.list[u]; p != -1; p = E[p].next)
            if (!vst[E[p].v]) _dfs2(E[p].v);
    }
} kosaraju;//***********模板结束*****************