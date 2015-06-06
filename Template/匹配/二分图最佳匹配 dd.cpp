#include <iostream>
#include <cstring>

using namespace std;
/*
KM算法的正确性基于以下定理：
任意时刻A[i]+B[j]>=w[i,j]始终成立。若由二分图中所有满足A[i]+B[j]=w[i,j]的边(i,j)构成的子图（称做相等子图）有完备匹配，那么这个完备匹配就是二分图的最大权匹配。
这个定理是显然的。因为对于二分图的任意一个匹配，如果它包含于相等子图，那么它的边权和等于所有顶点的顶标和；如果它有的边不包含于相等子图，那么它的边权和小于所有顶点的顶标和。所以相等子图的完备匹配一定是二分图的最大权匹配。
*/

typedef int type;
const int MAX = 55;
const type inf = 1 << 30;

struct BestMatch {
    //二分图最大权值(权值可正可负)匹配,KM算法  O(max(L, R)^3)
    //modified by zjut_DD
    int m, match[MAX];       // match:Y->X
    type w[MAX][MAX];        // 权值
    type lx[MAX], ly[MAX];    // 标号
    bool sx[MAX], sy[MAX];    // 是否被搜索过
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

    //二分图最大权匹配,权值改成负的最小权匹配, 左边L个点，右边R个点(LR的大小无限制)，base0
    type bestmatch(int L, int R) {
        m = max(L, R);
        if (L < R) { //补成m*m
            for (int i = L; i < m; i++) for (int j = 0; j < m; j++) w[i][j] = 0;
        }
        if (L > R) {
            for (int i = 0; i < m; i++) for (int j = R; j < m; j++) w[i][j] = 0;
        }
        for (int i = 0; i < m; i++) {
            lx[i] = -inf;
            ly[i] = 0;
            for (int j = 0; j < m; j++) { //任意时刻,两定标和>=边权
                if (lx[i] < w[i][j]) lx[i] = w[i][j];
            }
        }
        memset(match, -1, sizeof(match));
        for (int u = 0; u < m; u++) {
            while (1) {
                memset(sx, 0, sizeof(sx));
                memset(sy, 0, sizeof(sy));
                if (dfs(u)) break; //能增广了
                type dx = inf; // 修改标号
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