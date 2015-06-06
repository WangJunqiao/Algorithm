//************����ͼ���ƥ��,�ڽӾ���********
#define maxn 555
int nL, nR; //nL->nR   base1
int match[maxn]; //1~m
bool vst[maxn];
bool mat[maxn][maxn];

void init() {
    memset(match, -1, sizeof(match));
    memset(mat, false, sizeof(mat));
}

bool dfs(int u) { //�������ݹ�
    for (int v = 1; v <= nR; v++) {
        if (mat[u][v] && !vst[v]) {//vst��ֻ֤��һ��
            vst[v] = true;
            int tmp = match[v];
            match[v] = u;
            if (tmp == -1 || dfs(tmp))
                return true;
            match[v] = tmp;
        }
    }
    return false;
}

int max_match() {
    int ret = 0;
    memset(match, -1, sizeof(match));
    for (int i = 1; i <= nL; i++) {
        memset(vst, false, sizeof(vst));
        if (dfs(i)) ret++;
    }
    return ret;
}//***********����ģ��**********