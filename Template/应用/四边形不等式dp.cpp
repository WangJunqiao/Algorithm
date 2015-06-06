状态转移方程形如:
        dp
[i][j]=min{
dp[i][k]+dp[k+1][j]+w[i][j] }

然后对于 k1<k2
< k3<k4 有:
        w[k2][k3] <= w[k1][k4]                           //区间包含单调性
w[k1][k3] + w[k2][k4] <= w([k2][k3] + w[k1][k4]  //四边形不等式


//hdu 3516 Tree construction 四边形不等式
/*
dp[i][j]=min{ dp[i][k]+dp[k+1][j] + x[k+1]-x[i] + y[k]-y[j] } (i<=k<j )  ***注意变量范围

令dp[i][j]+x[i]+y[j] = m[i][j]

则m[i][j]=min{ m[i][k]+m[k+1][j] - (x[i]+y[j]) } (i<=k<j) 发现权值和k无关了****

*/

#include<iostream>

using namespace std;

int m[1005][1005], sel[1005][1005];
int x[1005], y[1005];

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);

        for (int i = 1; i <= n; i++) {
            m[i][i] = x[i] + y[i];
            sel[i][i] = i;
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 1; i + len - 1 <= n; i++) {
                int j = i + len - 1;

                int mi = 1000000000, s;

                for (int k = sel[i][j - 1]; k <= sel[i + 1][j] && k < j; k++)//这里k<j一定要加上去,推导必须是严谨的
                {
                    if (m[i][k] + m[k + 1][j] < mi) {
                        mi = m[i][k] + m[k + 1][j];
                        s = k;
                    }
                }

                m[i][j] = mi - x[i] - y[j];
                sel[i][j] = s;
            }
        }


        int ans = m[1][n] - x[1] - y[n];

        cout << ans << endl;
    }
}