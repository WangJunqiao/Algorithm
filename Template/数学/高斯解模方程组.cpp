#include<iostream>
#include<cassert>
#include<algorithm>

using namespace std;

#define maxn 55
typedef long long LL;
const LL mod = 200000000000000003ll;

inline void fix(LL &a) {
    if (a <= -mod) a += mod;
    if (a >= mod) a -= mod;
}

LL mul(LL a, LL b, LL mod) { //b为正数,否则死循环
    LL ret = 0;
    bool flag = false;
    if (b < 0) {
        b = -b;
        flag = true;
    }
    while (b) {
        if (b & 1) ret = (ret + a), fix(ret);
        a <<= 1;
        fix(a);
        b >>= 1;
    }
    if (flag) return -ret;
    return ret;
}

void e_gcd(LL a, LL b, LL &x, LL &y) {
    if (!b) {
        x = 1;
        y = 0;
    } else {
        e_gcd(b, a % b, x, y);
        LL temp = x;
        x = y;
        y = temp - mul(a / b, y, mod);
    }
}

LL get_ni(LL a, LL p) {//返回x,ax=1 (mod p) p是素数
    LL x, y;
    e_gcd(a, p, x, y);
    return x;
}

/*
高斯解模方程组,当无解或者无限组解时会assertRE,有解会放在x里面
c[1][1]*x[1]+c[1][2]*x[2]+...+c[1][n]*x[n]=b[1]
c[2][1]*x[1]+c[2][2]*x[2]+...+c[2][n]*x[n]=b[2]
....
c[n][1]*x[1]+c[n][2]*x[2]+...+c[n][n]*x[n]=b[n]
*/
LL c[maxn][maxn], x[maxn], b[maxn];

void gauss(int N) { //C*X=B
    for (int i = 1, k; i <= N; i++) {
        if (c[i][i] == 0) {
            LL ma = 0;
            for (int j = i; j <= N && ma == 0; j++) {
                if (c[j][i] != ma) {
                    ma = c[j][i];
                    k = j;
                }
            }
            for (int j = i; j <= N; j++) swap(c[i][j], c[k][j]);
            swap(b[i], b[k]);
        }

        if (c[i][i] < 0) {
            for (int j = i; j <= N; j++) c[i][j] = -c[i][j];
            b[i] = -b[i];
        }
        assert(c[i][i] != 0);//*****等于0的话无解或者有无限组解
        for (int k = i + 1; k <= N; k++) {
            if (c[k][i] == 0) continue;
            LL m = get_ni(c[i][i], mod);
            m = mul(m, c[k][i], mod);
            for (int j = i; j <= N; j++) {
                c[k][j] -= mul(m, c[i][j], mod);
                fix(c[k][j]);
            }
            assert(c[k][i] == 0);
            b[k] -= mul(m, b[i], mod);
            fix(b[k]);
        }
    }
    for (int i = N; i >= 1; i--) {
        for (int j = i + 1; j <= N; j++) {
            b[i] -= mul(c[i][j], x[j], mod);
            fix(b[i]);
        }
        x[i] = mul(b[i], get_ni(c[i][i], mod), mod);
    }
}//--------------------模板结束--------------------

int main() {
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> c[i][j];
        for (int i = 1; i <= n; i++) cin >> b[i];
        gauss(n);
        for (int i = 1; i <= n; i++) printf("%I64d ", x[i]);
        puts("");
    }
}
/*
input:
3
1 2 3
4 5 6
7 8 10
33 75 124
output: 
2 5 7
*/

