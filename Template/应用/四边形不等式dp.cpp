״̬ת�Ʒ�������:
        dp
[i][j]=min{
dp[i][k]+dp[k+1][j]+w[i][j] }

Ȼ����� k1<k2
< k3<k4 ��:
        w[k2][k3] <= w[k1][k4]                           //�������������
w[k1][k3] + w[k2][k4] <= w([k2][k3] + w[k1][k4]  //�ı��β���ʽ


//hdu 3516 Tree construction �ı��β���ʽ
/*
dp[i][j]=min{ dp[i][k]+dp[k+1][j] + x[k+1]-x[i] + y[k]-y[j] } (i<=k<j )  ***ע�������Χ

��dp[i][j]+x[i]+y[j] = m[i][j]

��m[i][j]=min{ m[i][k]+m[k+1][j] - (x[i]+y[j]) } (i<=k<j) ����Ȩֵ��k�޹���****

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

                for (int k = sel[i][j - 1]; k <= sel[i + 1][j] && k < j; k++)//����k<jһ��Ҫ����ȥ,�Ƶ��������Ͻ���
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