//实数域，非奇异阵LUP分解，解线性方程组，矩阵求逆-----zjut_DD
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<ctime>

using namespace std;

#define maxn 7

//矩阵A的LU分解，A=LU
void LU_Decomposition(double A[][maxn], double L[][maxn], double U[][maxn]) {
    int N = maxn - 1;//矩阵大小为N*N

    memset(L, 0, maxn * maxn * sizeof(double));
    memset(U, 0, maxn * maxn * sizeof(double));
    for (int i = 1; i <= N; i++)
        L[i][i] = 1;

    for (int k = 1; k <= N; k++) {
        U[k][k] = A[k][k];
        for (int i = k + 1; i <= N; i++) {
            L[i][k] = A[i][k] / U[k][k];
            U[k][i] = A[k][i];
        }

        for (int i = k + 1; i <= N; i++) {
            for (int j = k + 1; j <= N; j++) {
                A[i][j] -= L[i][k] * U[k][j];
            }
        }
    }
}

//矩阵A的LUP分解，PA=LU
int PI[maxn];

//记录转置矩阵，PI[i]=j表示P中第i行第j列是1
bool LUP_Decomposition(double A[][maxn])//在A中原地计算L和U的，对角线是U的，因为L的对角线全是1
{
    int N = maxn - 1;//矩阵大小
    for (int i = 1; i <= N; i++)
        PI[i] = i;
    for (int k = 1; k <= N; k++) {
        double ma = 0;
        int kk;
        for (int i = k; i <= N; i++) {
            if (fabs(A[i][k]) > ma) {
                ma = fabs(A[i][k]);
                kk = i;
            }
        }
        if (ma < 1e-9) {
            cout << "singular matrix." << endl;
            return false;
        }

        swap(PI[k], PI[kk]);
        for (int i = 1; i <= N; i++)
            swap(A[k][i], A[kk][i]);

        //下面计算LU
        for (int i = k + 1; i <= N; i++) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j <= N; j++) {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }
    return true;
}

//解线性方程组AX=b
//其中A已进行LUP分解
void LUP_Solve(double L[][maxn], double U[][maxn], int *PI, double *b, double *X) {
    int N = maxn - 1;
    double Y[maxn];//中间解Y=Ux
    for (int i = 1; i <= N; i++) {
        double sum = 0;
        for (int j = 1; j < i; j++)
            sum += L[i][j] * Y[j];
        Y[i] = b[PI[i]] - sum;
    }

    for (int i = N; i >= 1; i--) {
        double sum = 0;
        for (int j = i + 1; j <= N; j++)
            sum += U[i][j] * X[j];
        X[i] = (Y[i] - sum) / U[i][i];
    }
}

template<class T>
void Print(T p[][maxn]) {
    for (int i = 1; i < maxn; i++) {
        for (int j = 1; j < maxn; j++)
            printf("%12.2lf ", p[i][j]);
        cout << endl;
    }
    puts("\n\n");
}

template<class T>
void Matrix_Mul(T A[][maxn], T B[][maxn], T res[][maxn]) {
    for (int i = 1; i < maxn; i++) {
        for (int j = 1; j < maxn; j++) {
            res[i][j] = 0;
            for (int k = 1; k < maxn; k++)
                res[i][j] += A[i][k] * B[k][j];
        }
    }
}

int main() {
    srand(time(NULL));

    double A[maxn][maxn], L[maxn][maxn], U[maxn][maxn];

    for (int i = 1; i < maxn; i++)
        for (int j = 1; j < maxn; j++)
            A[i][j] = rand();
    Print(A);
    double AA[maxn][maxn];
    memcpy(AA, A, sizeof(A));

    LUP_Decomposition(A);

    memset(L, 0, sizeof(L));
    memset(U, 0, sizeof(U));
    for (int i = 1; i < maxn; i++)
        L[i][i] = 1, U[i][i] = A[i][i];
    for (int i = 1; i < maxn; i++)
        for (int j = i + 1; j < maxn; j++)
            U[i][j] = A[i][j];
    for (int i = 1; i < maxn; i++)
        for (int j = 1; j < i; j++)
            L[i][j] = A[i][j];

    double A_1[maxn][maxn];
    double b[maxn], X[maxn];
    for (int j = 1; j < maxn; j++) {
        memset(b, 0, sizeof(b));
        b[j] = 1;
        LUP_Solve(L, U, PI, b, X);
        for (int i = 1; i < maxn; i++)
            A_1[i][j] = X[i];
    }
    double res[maxn][maxn];
    Matrix_Mul(AA, A_1, res);
    Print(res);
}