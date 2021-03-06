//模mod加法群域，矩阵求逆 O(N^3) ----------zjut_DD
#include<iostream>
#include<cmath>
#include<ctime>

using namespace std;

#define mod    2116261633//大素数
#define maxn 10
typedef long long LL;

LL ABS(LL a) {
    return a > 0 ? a : -a;
}

//扩展Euclid求解gcd(a,b)=ax+by
LL ext_gcd(LL a, LL b, LL &x, LL &y) {
    LL t, ret;
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ret = ext_gcd(b, a % b, x, y);
    t = x, x = y, y = t - a / b * y;
    return ret;
}

LL get_ni(LL m, LL Mod) { //返回模mod的m的乘法逆元
    LL x, y;
    ext_gcd(m, Mod, x, y);
    return (x % Mod + Mod) % Mod;
}

//矩阵A的LU分解，A=LU
void LU_Decomposition(double A[][maxn], double L[][maxn], double U[][maxn]) {
    LL N = maxn - 1;//矩阵大小为N*N
    memset(L, 0, maxn * maxn * sizeof(double));
    memset(U, 0, maxn * maxn * sizeof(double));
    for (LL i = 1; i <= N; i++) L[i][i] = 1;
    for (LL k = 1; k <= N; k++) {
        U[k][k] = A[k][k];
        for (LL i = k + 1; i <= N; i++) {
            L[i][k] = A[i][k] / U[k][k];
            U[k][i] = A[k][i];
        }
        for (LL i = k + 1; i <= N; i++) {
            for (LL j = k + 1; j <= N; j++) {
                A[i][j] -= L[i][k] * U[k][j];
            }
        }
    }
}

//矩阵A的LUP分解，PA=LU
LL PI[maxn];

//记录转置矩阵，PI[i]=j表示P中第i行第j列是1
bool LUP_Decomposition(LL A[][maxn]) { //在A中原地计算L和U的，对角线是U的，因为L的对角线全是1
    LL N = maxn - 1;//矩阵大小
    for (LL i = 1; i <= N; i++)
        PI[i] = i;
    for (LL k = 1; k <= N; k++) {
        LL ma = 0, kk;
        for (LL i = k; i <= N; i++) {
            if (ABS(A[i][k]) > ma) {
                ma = ABS(A[i][k]);
                kk = i;
            }
        }
        if (ma < 1) {
            cout << "singular matrix." << endl;
            return false;
        }
        swap(PI[k], PI[kk]);
        for (LL i = 1; i <= N; i++)
            swap(A[k][i], A[kk][i]);
        //下面计算LU
        for (LL i = k + 1; i <= N; i++) {
            LL ni = get_ni(A[k][k], mod);
            A[i][k] = (A[i][k] * ni) % mod;
            for (LL j = k + 1; j <= N; j++) {
                A[i][j] -= A[i][k] * A[k][j] % mod;
                A[i][j] = (A[i][j] % mod + mod) % mod;
            }
        }
    }
    return true;
}

//解线性方程组AX=b
//其中A已进行LUP分解
void LUP_Solve(LL L[][maxn], LL U[][maxn], LL *PI, LL *b, LL *X) {
    LL N = maxn - 1;
    LL Y[maxn];//中间解Y=Ux
    for (LL i = 1; i <= N; i++) {
        LL sum = 0;
        for (LL j = 1; j < i; j++)
            sum = (sum + L[i][j] * Y[j]) % mod;
        Y[i] = b[PI[i]] - sum;

        Y[i] = (Y[i] % mod + mod) % mod;
    }
    for (LL i = N; i >= 1; i--) {
        LL sum = 0;
        for (LL j = i + 1; j <= N; j++)
            sum = (sum + U[i][j] * X[j]) % mod;
        LL ni = get_ni(U[i][i], mod);
        X[i] = ((Y[i] - sum) * ni % mod + mod) % mod;//*********
    }
}

template<class T>
void Print(T p[][maxn]) {
    for (LL i = 1; i < maxn; i++) {
        for (LL j = 1; j < maxn; j++)
            printf("%10d ", p[i][j]);
        cout << endl;
    }
    puts("\n\n");
}

template<class T>
void Matrix_Mul(T A[][maxn], T B[][maxn], T res[][maxn]) {
    for (LL i = 1; i < maxn; i++) {
        for (LL j = 1; j < maxn; j++) {
            res[i][j] = 0;
            for (LL k = 1; k < maxn; k++)
                res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % mod;
            res[i][j] = (res[i][j] + mod) % mod;
        }
    }
}

void work(LL A[][maxn], LL A_1[][maxn]) {//求A的逆矩阵，保存在A_1
    LL L[maxn][maxn], U[maxn][maxn], P[maxn][maxn];
    memset(P, 0, sizeof(P));

    LUP_Decomposition(A);
    for (int i = 1; i < maxn; i++)
        P[i][PI[i]] = 1;

    memset(L, 0, sizeof(L));
    memset(U, 0, sizeof(U));
    for (LL i = 1; i < maxn; i++)
        L[i][i] = 1, U[i][i] = A[i][i];
    for (LL i = 1; i < maxn; i++)
        for (LL j = i + 1; j < maxn; j++)
            U[i][j] = A[i][j];
    for (LL i = 1; i < maxn; i++)
        for (LL j = 1; j < i; j++)
            L[i][j] = A[i][j];

    printf("L矩阵:\n");
    Print(L);
    printf("U矩阵:\n");
    Print(U);
    printf("P矩阵:\n");
    Print(P);

    LL b[maxn], X[maxn];
    for (LL j = 1; j < maxn; j++) {
        memset(b, 0, sizeof(b));
        b[j] = 1;
        LUP_Solve(L, U, PI, b, X);
        for (LL i = 1; i < maxn; i++)
            A_1[i][j] = X[i];
    }
}

int main() {
    freopen("out.txt", "w", stdout);
    srand(time(NULL));

    LL res[maxn][maxn];
    LL A[maxn][maxn];
    LL CopyA[maxn][maxn];
    LL A_1[maxn][maxn];

    for (LL i = 1; i < maxn; i++)
        for (LL j = 1; j < maxn; j++)
            A[i][j] = rand() * rand() % mod;
    printf("A矩阵:\n");
    Print(A);

    memcpy(CopyA, A, sizeof(A));
    work(CopyA, A_1);

    printf("A的逆矩阵A_1:\n");
    Print(A_1);

    Matrix_Mul(A, A_1, res);
    printf("A*A_1的矩阵:\n");
    Print(res);
}