/*
LCA离线tarjan算法, 可以是森林中两个同一颗树上的点的lca !!! rmq版本的是不支持的!!! 但是有爆栈危险!!
qq数组也是Edge类型,其中的val是询问的序号,即id, query要插双向边
eg.
adjq.insert(a,b,i);
adjq.insert(b,a,i);
...
tarjan.LCA(_N, adj.l,  adjq.l, E, E, ans);
*/
struct Tarjan {
    Edge *E, *qq; //qq表示query的边表指针
    int pa[maxn], *l, *lq, *ans;

    int find(int u) {
        return (pa[u] == u) ? u : (pa[u] = find(pa[u])); //爆栈
    }

    void _lca(int u) {//爆栈
        pa[u] = u;
        for (int p = l[u]; p != -1; p = E[p].next) {
            int v = E[p].v;
            if (pa[v] >= 0) continue;
            _lca(v);
            pa[v] = u; //其它点和v的lca至少是u以上的点了
        }
        for (int p = lq[u]; p != -1; p = qq[p].next) {
            int v = qq[p].v;
            if (pa[v] >= 0) ans[qq[p].val] = find(v);
        }
    }

    //0~N-1, 结果存在ans里
    void LCA(int N, int *_l, int *_lq, Edge *_E, int *_ans) { //l和lq同一性质的,E和qq同一性质的
        fill(pa, pa + N, -88); //负值=未访问
        l = _l;
        lq = _lq;
        qq = E = _E;
        ans = _ans;
        for (int i = 0; i < N; i++) {
            if (pa[i] < 0)
                _lca(i);
        }
    }
} tarjan; //---
