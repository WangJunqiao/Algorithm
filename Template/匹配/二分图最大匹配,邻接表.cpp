#define maxn 1100
struct Edge {
    int v, x;
} E[1000000];
int l[maxn], e;

void init() {
    memset(l, -1, sizeof(l));
    e = 0;
}

void insert(int a, int b) { //�����
    E[e].v = b;
    E[e].x = l[a];
    l[a] = e++;
}

int pre[maxn], vst[maxn]; //pre�� �ұ�->zuobian , vst��ǵ����ұߵĵ�
int dfs(int i) { //�������ݹ�,ÿ�εݹ鶼Ҫ��clear vst����
    for (int p = l[i]; p != -1; p = E[p].x) {
        int v = E[p].v;
        if (!vst[v]) {//������Ա�֤�����ͷ��************
            vst[v] = 1;//�����Ҫ���ݣ���Ϊ��β��У��´�һ������
            int tmp = pre[v];
            pre[v] = i;
            if (tmp == -1 || dfs(tmp)) return 1;
            pre[v] = tmp;
        }
    }
    return 0;
}

int max_match(int n, int m) {//base0
    memset(pre, -1, sizeof(pre));
    int ret = 0;
    for (int i = 0; i < n; i++) {
        fill(vst, vst + m, 0);
        ret += dfs(i);
    }
    return ret;
}// init(); insert(...); max_match();
