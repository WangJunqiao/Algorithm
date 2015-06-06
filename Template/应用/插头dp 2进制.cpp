//hdu 1693 吃树 最简单的插头dp
#include<iostream>

using namespace std;

int mat[11][11];
__int64 dp[12][12][1 << 12];

inline bool test(int v, int w) { //测试整数v的第w位(base0)
    return v & (1 << w);
}

inline int set(int v, int w) {
    if (v & (1 << w)) return v;
    else return v | (1 << w);
}

inline int reset(int v, int w) {
    if (v & (1 << w)) return v ^ (1 << w);
    else return v;
}

int main() {
    int cas, n, m, Te = 1;
    cin >> cas;
    while (cas--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> mat[i][j];
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int s = 0; s < (1 << (m + 1)); s++) {
                    if (dp[i][j][s] == 0) continue;
                    if (mat[i][j] == 0) {
                        if ((s & (3 << j)) == 0) dp[i][j + 1][s] += dp[i][j][s];
                    } else {
                        if (test(s, j) == false && test(s, j + 1) == false) {
                            dp[i][j + 1][s + (3 << j)] += dp[i][j][s];
                        } else if (test(s, j) == true && test(s, j + 1) == false) {
                            dp[i][j + 1][s] += dp[i][j][s];
                            dp[i][j + 1][set(reset(s, j), j + 1)] += dp[i][j][s];
                        } else if (test(s, j) == false && test(s, j + 1) == true) {
                            dp[i][j + 1][s] += dp[i][j][s];
                            dp[i][j + 1][set(reset(s, j + 1), j)] += dp[i][j][s];
                        } else {
                            dp[i][j + 1][reset(reset(s, j + 1), j)] += dp[i][j][s];
                        }
                    }
                }
            }
            for (int s = 0; s < (1 << (m)); s++) {
                dp[i + 1][0][s << 1] = dp[i][m][s];
            }
        }
        printf("Case %d: There are %I64d ways to eat the trees.\n", Te++, dp[n][0][0]);
        //cout<<dp[n][0][0]<<endl;
    }
}