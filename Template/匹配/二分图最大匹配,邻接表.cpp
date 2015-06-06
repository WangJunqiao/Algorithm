#define maxn 1100
struct Edge {
    int v, x;
} E[1000000];
int l[maxn], e;

void init() {
    memset(l, -1, sizeof(l));
    e = 0;
}

void insert(int a, int b) { //单向边
    E[e].v = b;
    E[e].x = l[a];
    l[a] = e++;
}

int pre[maxn], vst[maxn]; //pre是 右边->zuobian , vst标记的是右边的点
int dfs(int i) { //匈牙利递归,每次递归都要先clear vst数组
    for (int p = l[i]; p != -1; p = E[p].x) {
        int v = E[p].v;
        if (!vst[v]) {//这里可以保证不会回头的************
            vst[v] = 1;//这个不要回溯，因为这次不行，下次一样不行
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
