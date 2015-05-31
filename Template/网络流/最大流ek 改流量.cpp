//������㷨ek,�ڽ���, ��·����,���Ӷ�O(VE^2)
#define maxn 222
#define inf 0x3f3f3f3f

int n, adj[maxn][maxn], s, t; //�ܽڵ���n(base0), ������adj, Դs��t
int pre[maxn]; //bfs֮��ÿ�����ǰ���ڵ�,pre[s]=-1;
int vst[maxn]; //���S={vst[i]=1}|{vst[i]=0}=T��ɸ�,������㷨��֤|S|��С
int bfs() {
    fill(pre, pre + n, -1);
    fill(vst, vst + n, 0);
    queue <int> q;
    q.push(s);
    vst[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i <= n; i++) {
            if (adj[u][i] > 0 && !vst[i]) {
                vst[i] = 1;
                pre[i] = u;
                q.push(i);
                if (i == t) return 1;
            }
        }
    }
    return 0;
}

int edmonds_karp() {
    int f = 0;
    while (bfs()) {
        int mi = inf;
        for (int i = t; pre[i] != -1; i = pre[i]) {
            mi = min(mi, adj[pre[i]][i]);
        }
        f += mi;
        for (int i = t; pre[i] != -1; i = pre[i]) {
            adj[pre[i]][i] -= mi;
            adj[i][pre[i]] += mi;
        }
    }
    return f;
}//n=...; clear(adj); adj[i][j]=...; ans=edmonds_karp(); 

//�޸�������������(�ؼ�����Ѱ������·(��·��)�Ͷ������Ŀ���...)
//UVA 4957 ����:һ��R*C��01������ÿ�еĺ�ΪR[i],ÿ�еĺ�ΪC[j],��һ���ֵ�����С����
int main() {
    int R, C, Te = 0;
    while (cin >> R >> C && (R || C)) {
        int s1 = 0, s2 = 0, a;
        n = R + C + 2;
        s = 0;
        t = n - 1;
        memset(adj, 0, sizeof(adj));
        for (int i = 1; i <= R; i++) {
            cin >> a;
            s1 += a;
            adj[s][i] = a;
        }
        for (int j = 1; j <= C; j++) {
            cin >> a;
            s2 += a;
            adj[R + j][t] = a;
        }
        for (int i = 1; i <= R; i++) for (int j = 1; j <= C; j++) adj[i][R + j] = 1;
        if (Te++) puts("");
        if (s1 != s2 || edmonds_karp() != s1) {
            puts("Impossible");
            continue;
        }
        for (int i = 1; i <= R; i++) {//���ȷ��
            for (int j = 1; j <= C; j++) {
                if (adj[i][R + j] == 1) {
                    adj[i][R + j] = 0; //�������ٱ��޸�
                    putchar('N');
                    continue;
                }
                s = i;
                t = R + j;
                if (bfs()) {
                    putchar('N');
                    for (int k = t; k != s; k = pre[k]) {
                        adj[pre[k]][k] -= 1;
                        adj[k][pre[k]] += 1;
                    }
                    adj[R + j][i] = 0; //�������ٱ��޸�
                } else {
                    putchar('Y');
                    adj[R + j][i] = 0; //�������ٱ��޸�
                }
            }
            puts("");
        }
    }
}
