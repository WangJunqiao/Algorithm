#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


const int inf = 1000000000;

//����� dinic  http://acm.hdu.edu.cn/showproblem.php?pid=3046��AC
template<typename FLOW_TYPE = int, int MAXN = 20010, int MAXE = 60000>
struct Netflow {
    int L[MAXN], Q[MAXN]; //L=level  Q=queue
    struct Edge {
        int v, x;
        FLOW_TYPE c;
    } E[MAXE]; //c:ʣ������������capacity
    int X[MAXN], e; //�ڽӱ�
    void init() {
        e = 0;
        memset(X, -1, sizeof(X));
    }

    void add_edge(int u, int v, FLOW_TYPE f, FLOW_TYPE invf) { //u->v=f   v->u=invf
        E[e].v = v;
        E[e].c = f;
        E[e].x = X[u];
        X[u] = e++;
        E[e].v = u;
        E[e].c = invf;
        E[e].x = X[v];
        X[v] = e++;
    }

    bool _bfs(int S, int T) { //��S��ʼ����, �����level(ֻȡ��������0�ı�)
        int head = 0, tail = 0;
        memset(L, -1, sizeof(L));
        L[S] = 0;
        Q[tail++] = S;
        while (head < tail) {
            int u = Q[head++];
            for (int x = X[u]; x >= 0; x = E[x].x)
                if (E[x].c > 0 && L[E[x].v] == -1)
                    L[(Q[tail++] = E[x].v)] = L[u] + 1;
        }
        return L[T] != -1;
    }

    FLOW_TYPE _find(int u, FLOW_TYPE in, int T) { //in:������u�ڵ���������. ����u�ڵ����������������
        if (u == T) return in;
        FLOW_TYPE tmp, w = 0; //w��ʾ�Ѿ���u������������
        for (int x = X[u]; x >= 0 && w < in; x = E[x].x) {
            if (E[x].c > 0 && L[E[x].v] == L[u] + 1) {
                if (tmp = _find(E[x].v, min(E[x].c, in - w), T)) {
                    E[x].c -= tmp;
                    E[x ^ 1].c += tmp; //�����ʾ����
                    w += tmp;        //��·�������ƾ޴�
                }
            }
        }
        if (w < in) L[u] = -1;//�ؼ���һ�仰
        return w;
    }

    FLOW_TYPE dinic(int S, int T) { //�ڵ�ǰ�Ĳ���������S��T�������
        FLOW_TYPE f, res = 0;
        while (_bfs(S, T)) while (f = _find(S, inf, T)) res += f;
        return res;
    }
}; //********ģ�����***********
Netflow<int, 41000, 300000> flow;
// ʹ�÷���:
// flow.init();
// flow.add_edge(0, 1, 1, 0);
// flow.add_edge(1, 2, 2, 0);
// cout<<flow.dinic(0, 2)<<endl;

vector<string> vs[555];
char ch[55555];

int main() {
    freopen("C:\\Users\\dd\\Downloads\\C-large-practice.in", "r", stdin);
    freopen("C:\\Users\\dd\\Downloads\\C-large-practice.out", "w", stdout);

    int Te; scanf("%d", &Te);
    for (int te = 1; te <= Te; te ++) {
        int N;
        scanf("%d", &N);
        gets(ch);
        map<string, int> mp;

        for (int i = 0; i < N; i ++) {
            gets(ch);
            istringstream sin(ch);
            string s;
            vs[i].clear();
            while (sin >> s) {
                vs[i].push_back(s);
                mp[s] = 0;
            }
        }

        int words = mp.size(), src = 0, sink = N + 2 * words + 1;

        int i = N + 1;
        for (map<string, int>::iterator it = mp.begin(); it != mp.end(); ++ it) {
            mp[it->first] = i ++;
        }

        flow.init();
        flow.add_edge(src, 1, inf, 0);
        flow.add_edge(2, sink, inf, 0);
        for (int i = 0; i < words; i ++) {
            flow.add_edge(i + N + 1, i + N + 1 + words, 1, 0); //�ֵ㣬��֤1��
        }
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < vs[i].size(); j ++) {
                int wid = mp[vs[i][j]];
                flow.add_edge(i + 1, wid, 1, 0); //������ϵ
                flow.add_edge(wid + words, i + 1, 1, 0);
            }
        }

        printf("Case #%d: %d\n", te, flow.dinic(src, sink));

    }
    system("pause");
}