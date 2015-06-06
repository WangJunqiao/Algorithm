//二维RMQ
#define maxn 152
#define LOG 8
int _log[maxn + 1];

inline int getlog(int m) {
    return _log[m];
}

void RMQ(int d[][maxn], int M, int N, int ret[][maxn][LOG][LOG]) { //下标从1开始,M是行,N是列
    for (int m = 1; m <= maxn; m++)            //需要计算很多次时耗时很大!!!需要预处理
        _log[m] = (int) (log(m * 1.0) / log(2.0));
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
            ret[i][j][0][0] = d[i][j];
    int row = getlog(M), col = getlog(N);
    for (int R = 0; R <= row; R++) {
        for (int C = 0; C <= col; C++) {
            for (int i = 1; i + (1 << R) - 1 <= M; i++) {
                for (int j = 1; j + (1 << C) - 1 <= N; j++) {
                    if (R == 0 && C == 0) continue;
                    if (R == 0)
                        ret[i][j][R][C] = max(ret[i][j][R][C - 1], ret[i][j + (1 << (C - 1))][R][C - 1]);
                    else if (C == 0)
                        ret[i][j][R][C] = max(ret[i][j][R - 1][C], ret[i + (1 << (R - 1))][j][R - 1][C]);
                    else
                        ret[i][j][R][C] = max(max(ret[i][j][R - 1][C - 1], ret[i + (1 << (R - 1))][j][R - 1][C - 1]),
                                              max(ret[i][j + (1 << (C - 1))][R - 1][C - 1],
                                                  ret[i + (1 << (R - 1))][j + (1 << (C - 1))][R - 1][C - 1])
                        );
                }
            }
        }
    }
}

inline int query(int r1, int c1, int r2, int c2, int ret[][maxn][LOG][LOG]) {
    int R = getlog(r2 - r1 + 1);
    int C = getlog(c2 - c1 + 1);
    return max(max(ret[r1][c1][R][C], ret[r2 - (1 << R) + 1][c1][R][C]),
               max(ret[r1][c2 - (1 << C) + 1][R][C],
                   ret[r2 - (1 << R) + 1][c2 - (1 << C) + 1][R][C])
    );
}