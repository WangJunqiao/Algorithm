/*
problem : 给你一些线段,求最多能找到几条是相互之间都没有交叉关系的

分析下解的结构: 解是由一些线段组成,而这些线段的上面还有线段(被它包含着的),那么很明显这是个递归定义的结构
如果我们在原来基础上再加上一条[-inf,inf]的线段,那么解就有更加清晰地子结构了...

算法1： 可以将一条线段拆分成两个点,然后变成了2*n个点,对这些点排序后进行dp,复杂度为(2*n)^3
算法2： 我们设计一个基于递归定义的状态,dp[i][j]表示线段i之后以线段j结束的结构的最大值,这样可以枚举结束点来转移 复杂度n^3
*/

#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cmath>
#include<string.h>

using namespace std;

#define maxn 305

struct DD {
    int L, R;

    bool operator<(const DD &b) const {
        if (L != b.L) return L < b.L;
        return R > b.R;
    }
} dd[maxn];

int dp[maxn][maxn]; //dp[i][j]表示第i段上面以第j段为最后的结构最多有几段
int mdp[maxn]; //mdp[i]表示第i段上面连同自己共有几段

int main() {
    int n, cas;
    cin >> cas;
    while (cas-- && cin >> n) {
        for (int i = 0; i < n; i++) cin >> dd[i].L >> dd[i].R;
        dd[n].L = -0x6fffffff, dd[n++].R = 0x6fffffff;
        sort(dd, dd + n);
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) mdp[i] = 1;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (dd[j].R > dd[i].R) continue;
                int ma = 1 + mdp[j];
                for (int k = i + 1; k < j; k++) {
                    if (dd[k].R <= dd[i].R && dd[k].R <= dd[j].L) //k在i内,且和j不相交
                        ma = max(ma, dp[i][k] + mdp[j]);
                }
                dp[i][j] = max(dp[i][j], ma);
                mdp[i] = max(mdp[i], ma);
                //printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
            }
        }
        cout << mdp[0] - 1 << endl;
    }
}