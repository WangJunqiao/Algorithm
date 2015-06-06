/*
LCA����tarjan�㷨, ������ɭ��������ͬһ�����ϵĵ��lca !!! rmq�汾���ǲ�֧�ֵ�!!! �����б�ջΣ��!!
qq����Ҳ��Edge����,���е�val��ѯ�ʵ����,��id, queryҪ��˫���
eg.
adjq.insert(a,b,i);
adjq.insert(b,a,i);
...
tarjan.LCA(_N, adj.l,  adjq.l, E, E, ans);
*/
struct Tarjan {
    Edge *E, *qq; //qq��ʾquery�ı߱�ָ��
    int pa[maxn], *l, *lq, *ans;

    int find(int u) {
        return (pa[u] == u) ? u : (pa[u] = find(pa[u])); //��ջ
    }

    void _lca(int u) {//��ջ
        pa[u] = u;
        for (int p = l[u]; p != -1; p = E[p].next) {
            int v = E[p].v;
            if (pa[v] >= 0) continue;
            _lca(v);
            pa[v] = u; //�������v��lca������u���ϵĵ���
        }
        for (int p = lq[u]; p != -1; p = qq[p].next) {
            int v = qq[p].v;
            if (pa[v] >= 0) ans[qq[p].val] = find(v);
        }
    }

    //0~N-1, �������ans��
    void LCA(int N, int *_l, int *_lq, Edge *_E, int *_ans) { //l��lqͬһ���ʵ�,E��qqͬһ���ʵ�
        fill(pa, pa + N, -88); //��ֵ=δ����
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
