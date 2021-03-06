/*
无向图点双连通(边的集合),以割点为分割. 8字形变成3个点.
1， 求割点测试过pku 1144, 返回的点双连通个数正确
2， hdu 3749点双连通,p2c,c2e集合测试正确
3,  hdu 3686测试 e2c数组正确, rebuild之后的图正确
4,  bupt 邀请赛B,割点测试正确
*/
//p->割点  c->点双连通  e->边
typedef pair <int, int> PII;
set <int> p2c[maxn]; //每个点属于哪些点双连通 //点双连通的编号
set <PII> c2e[maxm]; //每个点双连通有哪些边
map <PII, int> e2c;   //每条边属于哪个点双连通
int cp2n[maxn];     //重构图后割点对应的新节点号,非割点一律为-1(cp2n[i]>0可用来判断割点)
int dep[maxn], low[maxn];

struct Bidir_Tarjan {
    int *l;
    Edge *E; //init
    int N, cnt, root, top;
    PII st[maxm], tmp;

    //0~n-1的无向图,返回有几个点双连通base0
    //点双联通，边双联通的话调用之后找桥
    int bidirGraphCut(int n, int *_l, Edge *_E) {
        N = n;
        l = _l;
        E = _E;
        for (int i = 0; i < N; i++) dep[i] = cp2n[i] = -1;
        e2c.clear();
        for (int i = 0; i < N; i++) p2c[i].clear(), c2e[i].clear(); //最多N-1个点双连通
        cnt = 0; //
        for (int i = 0; i < N; i++) {
            if (dep[i] >= 0) continue;
            top = 0, root = i;
            _dfs(i, 0, -1);
            assert(top == 0);
        }
        return cnt; //返回点双连通的个数
    }

    //N个点rebuild之后可能变成2N个点
    //rebuild之后前cnt个点都是点双连通的点
    //新图中只有 割点和点双连通,是一棵树, 割点和点双连通连边叶子都是点双连通,割点都在内部
    int rebuild(AdjList &adj) {
        int c = cnt; //点双连通序号保持不变
        for (int i = 0; i < N; i++) if (cp2n[i] > 0) cp2n[i] = c++;
        adj.init(); //
        set<int>::iterator it;
        for (int i = 0; i < N; i++) {
            if (cp2n[i] == -1) continue;
            for (it = p2c[i].begin(); it != p2c[i].end(); ++it) {
                adj.insert(cp2n[i], *it);
                adj.insert(*it, cp2n[i]);
            }
        }
        return c; //新图中点的数目
    }

    bool isBridge(int u, int v) { //u,v有边
        if (dep[u] > dep[v]) swap(u, v);//保证_dfs中u->v的
        return low[v] > dep[u];
    }

    void _pop(PII p) {
        do {
            tmp = st[--top];
            p2c[tmp.first].insert(cnt);
            p2c[tmp.second].insert(cnt);
            if (tmp.first > tmp.second) swap(tmp.first, tmp.second);
            c2e[cnt].insert(tmp);
            e2c[tmp] = cnt;
        } while (top > 0 && st[top] != p);
        cnt++;
    }

    void _dfs(int u, int D, int _ind) { //当前节点, 深度, 边序号
        dep[u] = low[u] = D;
        int c = 0;
        for (int p = l[u]; p != -1; p = E[p].next) {
            if ((p ^ 1) == _ind) continue;
            int v = E[p].v;
            st[top++] = PII(u, v);
            if (dep[v] >= 0) {
                if (dep[v] > dep[u]) top--; //这样的边必须弹出来!!!**********
                low[u] = min(low[u], dep[v]);  //it is dep, not low
                continue;
            }
            _dfs(v, D + 1, p);
            c++;
            if (low[v] >= dep[u]) {
                if (u != root || c >= 2) cp2n[u] = 1; //
                _pop(PII(u, v));
            } else {
                low[u] = min(low[u], low[v]); //这个是这个里面_dfs的，故要更新的是low[v],而不是dep[v]
            }
        }
    }
} bidir_tarjan;//*********模板结束***************************