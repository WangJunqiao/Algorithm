//ʵ���򣬷�������LUP�ֽ⣬�����Է����飬��������-----zjut_DD
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<ctime>

using namespace std;

#define maxn 7

//����A��LU�ֽ⣬A=LU
void LU_Decomposition(double A[][maxn], double L[][maxn], double U[][maxn]) {
    int N = maxn - 1;//�����СΪN*N

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

//����A��LUP�ֽ⣬PA=LU
int PI[maxn];

//��¼ת�þ���PI[i]=j��ʾP�е�i�е�j����1
bool LUP_Decomposition(double A[][maxn])//��A��ԭ�ؼ���L��U�ģ��Խ�����U�ģ���ΪL�ĶԽ���ȫ��1
{
    int N = maxn - 1;//�����С
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

        //�������LU
        for (int i = k + 1; i <= N; i++) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j <= N; j++) {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }
    return true;
}

//�����Է�����AX=b
//����A�ѽ���LUP�ֽ�
void LUP_Solve(double L[][maxn], double U[][maxn], int *PI, double *b, double *X) {
    int N = maxn - 1;
    double Y[maxn];//�м��Y=Ux
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