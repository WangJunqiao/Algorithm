#include <iostream>
#include <cstring>

using namespace std;
/*
KM�㷨����ȷ�Ի������¶���
����ʱ��A[i]+B[j]>=w[i,j]ʼ�ճ��������ɶ���ͼ����������A[i]+B[j]=w[i,j]�ı�(i,j)���ɵ���ͼ�����������ͼ�����걸ƥ�䣬��ô����걸ƥ����Ƕ���ͼ�����Ȩƥ�䡣
�����������Ȼ�ġ���Ϊ���ڶ���ͼ������һ��ƥ�䣬����������������ͼ����ô���ı�Ȩ�͵������ж���Ķ���ͣ�������еı߲������������ͼ����ô���ı�Ȩ��С�����ж���Ķ���͡����������ͼ���걸ƥ��һ���Ƕ���ͼ�����Ȩƥ�䡣
*/

typedef int type;
const int MAX = 55;
const type inf = 1 << 30;

struct BestMatch {
    //����ͼ���Ȩֵ(Ȩֵ�����ɸ�)ƥ��,KM�㷨  O(max(L, R)^3)
    //modified by zjut_DD
    int m, match[MAX];       // match:Y->X
    type w[MAX][MAX];        // Ȩֵ
    type lx[MAX], ly[MAX];    // ���
    bool sx[MAX], sy[MAX];    // �Ƿ�������
    bool dfs(int u) {
        sx[u] = true;
        for (int v = 0; v < m; v++) {
            if (!sy[v] && lx[u] + ly[v] == w[u][v]) {
                sy[v] = true;
                if (match[v] == -1 || dfs(match[v])) {
                    match[v] = u;
                    return true;
                }
            }
        }
        return false;
    }

    //����ͼ���Ȩƥ��,Ȩֵ�ĳɸ�����СȨƥ��, ���L���㣬�ұ�R����(LR�Ĵ�С������)��base0
    type bestmatch(int L, int R) {
        m = max(L, R);
        if (L < R) { //����m*m
            for (int i = L; i < m; i++) for (int j = 0; j < m; j++) w[i][j] = 0;
        }
        if (L > R) {
            for (int i = 0; i < m; i++) for (int j = R; j < m; j++) w[i][j] = 0;
        }
        for (int i = 0; i < m; i++) {
            lx[i] = -inf;
            ly[i] = 0;
            for (int j = 0; j < m; j++) { //����ʱ��,�������>=��Ȩ
                if (lx[i] < w[i][j]) lx[i] = w[i][j];
            }
        }
        memset(match, -1, sizeof(match));
        for (int u = 0; u < m; u++) {
            while (1) {
                memset(sx, 0, sizeof(sx));
                memset(sy, 0, sizeof(sy));
                if (dfs(u)) break; //��������
                type dx = inf; // �޸ı��
                for (int i = 0; i < m; i++) {
                    if (!sx[i]) continue;
                    for (int j = 0; j < m; j++) {
                        if (sy[j]) continue;
                        dx = min(lx[i] + ly[j] - w[i][j], dx);
                    }
                }
                for (int i = 0; i < m; i++) if (sx[i]) lx[i] -= dx;
                for (int j = 0; j < m; j++) if (sy[j]) ly[j] += dx;
            }
        }
        type sum = 0;
        for (int j = 0; j < m; j++) sum += w[match[j]][j];
        return sum;
    }
} MM;

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) scanf("%d", MM.w[i] + j);
        printf("%d\n", MM.bestmatch(n, m));
    }
}