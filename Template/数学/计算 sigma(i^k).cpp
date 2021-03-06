#include<iostream>
#include<vector>
#include<cassert>
#include<string>
#include<sstream>

using namespace std;

typedef __int64 int64;

/*
1^0 + 2^0 + 3^0 + 4^0 + ...
1^1 + 2^1 + 3^1 + 4^1 + ...
1^2 + 2^2 + 3^2 + 4^2 + ...
1^3 + 2^3 + 3^3 + 4^3 + ...
1^4 + 2^4 + 3^4 + 4^4 + ...
...
1^k + 2^k + 3^k + 4^k + ...

x^k=(x-1 + 1)^k = (y+1)^k=C(k,0)*y^0 + C(k,1)*y^1 + ... + C(k,k)*y^k

|x^0,x^1,x^2,...,x^k,sum|
*/


//**************����ģ��***********
#define maxn 64
typedef __int64 type;
type tmp[maxn][maxn];

struct Matrix {
    int R, C, mod; //0~R-1,   0~C-1
    type m[maxn][maxn];

    void init(int r, int c, int _mod) {
        R = r, C = c;
        mod = _mod;
        for (int i = 0; i < r; i++) fill(m[i], m[i] + c, 0);
    }

    void set(int i, int j, int val) { m[i][j] = val; }

    friend void mul(const Matrix &s1, const Matrix &s2, Matrix &des) { //des=s1 * s2
        int i, j, k;
        assert(s1.C == s2.R); //ȷ����������
        for (i = 0; i < s1.R; i++) {
            for (j = 0; j < s2.C; j++) {
                type p = 0;
                for (k = 0; k < s1.C; k++) {
                    p = (p + s1.m[i][k] * s2.m[k][j]) % s1.mod;
                }
                tmp[i][j] = p;
            }
        }
        des.R = s1.R, des.C = s2.C;
        for (i = 0; i < s1.R; i++) memcpy(des.m[i], tmp[i], sizeof(type) * s2.C);
    }
} mat1, mat2; //*************************ģ�����**************

int C[100][100];

int calc(int n, int k, int mod) { // ���� 1^k + 2^k + 3^k + 4^k + ...
    if (n == 0) return 0;
    int i, j;
    for (i = 0; i < 100; i++) C[i][0] = 1;
    for (i = 1; i < 100; i++) for (j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;

    mat1.init(1, k + 2, mod);
    mat2.init(k + 2, k + 2, mod);

    for (j = 0; j < k + 2; j++) mat1.set(0, j, 1);
    for (j = 0; j < k + 1; j++) {
        for (int i = 0; i <= j; i++) mat2.set(i, j, C[j][i]);
    }
    for (i = 0; i <= k; i++) mat2.m[i][k + 1] = mat2.m[i][k];
    mat2.m[k + 1][k + 1] = 1;
    n--;
    while (n) {
        if (n & 1) mul(mat1, mat2, mat1);
        mul(mat2, mat2, mat2);
        n /= 2;
    }
    return mat1.m[0][k + 1];
}//******************************************************************