#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;


/*一般图最大匹配，基于Tutte Matrix的算法，复杂度O(n^3)  modify from ftiasch@sjtu
原理：Given a graph G = (V = [2n], E), its Tutte matrix T is a 2n × 2n matrix defined as :
Aij =  xij if {i, j} ∈ E and i < j
      -xij if {i, j} ∈ E and i > j
	    0 otherwise
where the xij are indeterminates. The polynomial det(T) is not identically zero if and only if G contains a perfect matching.
由此可以导出，一个一般图的最大匹配其实等于Tutte Matrix的秩的一半！
*/
const int MOD = 1000000000 + 7;
int n, a[200][200];

int inverse(int a) { //计算a在模MOD下的逆元
    return a == 1 ? 1 : (long long) (MOD - MOD / a) * inverse(MOD % a) % MOD;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a[i][j]); //读取邻接矩阵，01矩阵
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j]) {
                a[i][j] = rand() % MOD;
                a[j][i] = MOD - a[i][j]; //随机赋值
            }
        }
    }
    int rank = 0;
    for (int i = 0; i < n; ++i) {//计算矩阵的秩
        int pivot = rank;
        while (pivot < n && !a[pivot][i]) {
            pivot++;
        }
        if (pivot < n) {
            for (int j = 0; j < n; ++j) {
                swap(a[rank][j], a[pivot][j]);
            }
            {
                int times = inverse(a[rank][i]);
                for (int j = 0; j < n; ++j) {
                    a[rank][j] = (long long) a[rank][j] * times % MOD;
                }
                for (int k = 0; k < n; ++k) {
                    if (k != rank && a[k][i]) {
                        int times = a[k][i];
                        for (int j = 0; j < n; ++j) {
                            (a[k][j] += MOD - (long long) a[rank][j] * times % MOD) %= MOD;
                        }
                    }
                }
            }
            rank++;
        }
    }
    printf("%d\n", rank >> 1);
    return 0;
}
