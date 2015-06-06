//浮点型高斯消元,返回是否有确定解
double a[MAXN][MAXN], x[MAXN], b[MAXN];

bool gauss() {
    for (int i = 0; i < n; i++) { //下半角全部清0
        double m = abs(a[i][i]);   //注意m的初值
        index = i;
        for (int j = i + 1; j < n; j++) { //找到绝对值最大的一行
            if (abs(a[j][i]) > m) {
                m = abs(a[j][i]);
                index = j;
            }
        }
        if (m < eps)return false;  //下面的全是0时，返回无解
        if (index != i) {
            swap(b[i], b[index]); //整个增广矩阵的两行交换下
            for (int k = 0; k < n; k++)
                swap(a[i][k], a[index][k]);
        }
        for (int k = i + 1; k < n; k++) { //下面是第i行去减第k行，第k行的0~i-1已经全是0的了
            double d = a[k][i] / a[i][i]; //算出比例
            b[k] -= b[i] * d;
            for (int p = i; p < n; p++)
                a[k][p] -= a[i][p] * d;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++)
            b[i] -= x[j] * a[i][j];
        x[i] = b[i] / a[i][i];
    }
    return true;
}
