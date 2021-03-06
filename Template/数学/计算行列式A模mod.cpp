//http://www.spoj.pl/problems/DETER3/
//计算行列式|A|%mod, 复杂度n^3logC  算法: 一行将另一行消去的时候,采用欧几里得算法,辗转相消
//初始化 A数组, N, mod
typedef long long int64;
#define maxn 202
int A[maxn][maxn], N, mod; //N*N的方阵, base1
void _swap(int r1, int r2) {
    for (int j = 1; j <= N; j++) swap(A[r1][j], A[r2][j]);
}

void _dec(int r1, int r2, int mul) { //r1行减去 mul*r2行
    for (int j = 1; j <= N; j++) A[r1][j] = (A[r1][j] - (int64) A[r2][j] * mul) % mod;
}

int calc_delta() { //结果模mod
    bool neg = false;
    for (int k = 1; k <= N; k++) {
        for (int i = k + 1; i <= N; i++) {
            while (true) {//循环logC次
                if (A[k][k] == 0 || A[i][k] == 0) break;
                if (abs(A[k][k]) >= abs(A[i][k])) {
                    _dec(k, i, A[k][k] / A[i][k]);
                } else {
                    _dec(i, k, A[i][k] / A[k][k]);
                }
            }
            if (A[i][k] != 0) _swap(i, k), neg = !neg; //两行互换,需要修改符号的
        }
        if (A[k][k] == 0) return 0;
    }
    int64 ret = neg ? -1 : 1;
    for (int k = 1; k <= N; k++) ret = ret * A[k][k] % mod;
    return (int) ret;
}//**********************************************************

int main() {
    while (scanf("%d%d", &N, &mod) != EOF) {
        for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) scanf("%d", A[i] + j);
        printf("%d\n", (calc_delta() + mod) % mod);
    }
}