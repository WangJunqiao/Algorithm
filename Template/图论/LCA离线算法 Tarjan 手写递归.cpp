//lca��tarjan�㷨��ͨ��zjut1504
#define maxn 110000
typedef pair <int, int> PII;

struct Tarjan {
    vector <int> adj[maxn];  //�ڽӱ�,˫���
    vector <PII> query[maxn];
    //��ѯ��˫�򣩣�u.pb(v, query_id)  v.pb(u, query_id)
    int out[maxn];          //ÿ��query_id��Ӧ��lca
    //----������Ҫ�ⲿ��ֵ------------------
    void init(int N) {// base0, ÿ��case����
        fill(pa, pa + N, -1);
    }

    int find(int u) {
        return (pa[u] == u) ? u : (pa[u] = find(pa[u]));
    }

    void lca(int r) {//��д�ݹ�, ���������� �����ɭ�ֿ��Զ�ε���
        top = 0;
        st[top++] = r;
        st[top++] = 0;
        pa[r] = r;
        while (top) {
            int u = st[top - 2], &ind = st[top - 1];
            if (ind >= adj[u].size()) {
                top -= 2;
                for (int i = 0; i < query[u].size(); i++) {
                    int qv = query[u][i].first;
                    if (pa[qv] >= 0) out[query[u][i].second] = find(qv);
                }
                if (top) pa[u] = st[top - 2]; //�������Ҫ
            } else {
                int v = adj[u][ind++];
                if (pa[v] >= 0) continue;
                st[top++] = v;
                st[top++] = 0;
                pa[v] = v;
            }
        }
    }

    int pa[maxn], st[maxn * 2], top;
} tarjan; //ʹ�÷�������adj��query��ֵ֮�󣬵���init��lca��