//----------------------------矩阵--------------------------
const int mod = 1000000007;
#define maxn 110
typedef int Type;

struct Matrix {
    Type d[maxn][maxn];
    int R, C;

    Matrix(int r = 0, int c = 0) : R(r), C(c) { memset(d, 0, sizeof(d)); }

    Type *operator[](int i) { return d[i]; }
};

Matrix operator*(const Matrix &a, const Matrix &b) {
    assert(a.C == b.R); //
    Matrix r;
    r.R = a.R;
    r.C = b.C;
    for (int i = 0; i < r.R; i++) {
        for (int j = 0; j < r.C; j++) {
            Type tmp = 0;
            for (int k = 0; k < a.C; k++) {
                if (a.d[i][k] && b.d[k][j])
                    tmp = (tmp + (long long) a.d[i][k] * b.d[k][j]) % mod;
            }
            r.d[i][j] = tmp;
        }
    }
    return r;
}

Matrix operator^(const Matrix &a, long long m) {
    assert(a.R == a.C);
    Matrix ret(a.R, a.C), A = a;
    for (int i = 0; i < a.R; i++) ret[i][i] = 1; //单位阵
    for (; m; m /= 2) {
        if (m & 1) ret = ret * A;
        A = A * A;
    }
    return ret;
}//-------------------模板结束-----------------------------------