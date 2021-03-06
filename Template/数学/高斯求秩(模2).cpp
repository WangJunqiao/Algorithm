//模2情况下, c[][] * x[] = b[]
//高斯法求秩,判断方程组是否有解,-1表示无解
int gauss(int n, int m, int c[][maxm], int *b) { //会改变c和b数组
    int zhi = 0, k, i, j;
    for (i = 1, j = 1; i <= n && j <= m;) {
        int cur = 0;
        for (k = i; cur == 0 && k <= n; k++) {
            if (c[k][j]) {
                cur = 1;
                break;
            }
        }
        if (cur == 0) {
            j++;
            continue;
        } //
        for (int jj = j; jj <= m; jj++) swap(c[i][jj], c[k][jj]);
        swap(b[i], b[k]);
        for (k = i + 1; k <= n; k++) {
            if (c[k][j]) {
                for (int jj = j; jj <= m; jj++)
                    c[k][jj] ^= c[i][jj];
                b[k] ^= b[i];
            }
        }
        zhi++, i++, j++;
    }
    while (i <= n) if (b[i++]) return -1;
    return zhi;
}