#include <iostream>

using namespace std;

namespace Math { //modify from 仙剑魔
    //求sigma(i^k), 复杂度O(k^2), 结果取的模必须是素数
    typedef long long LL;
    const int mod = 1000000007, maxk = 60;
    int C[maxk + 2][maxk + 2], buff[maxk + 1];
    int imul[maxk + 2]; //imul[i]是i的逆元

    int pow(int x, int k, int p) { // x^k % p
        int r = 1;
        for (; k; k >>= 1) {
            if (k & 1) r = (r * (LL) x) % p;
            x = (x * (LL) x) % p;
        }
        return r;
    }

    int dfs(int n, int k) {//计算(1^k+2^k+3^k+...+n^k) %mod
        if (k == 1) {
            return buff[k] = ((LL) (n + 1) * n / 2) % mod;
        } else if (buff[k] != 0) {
            return buff[k];
        } else {
            int sum = 0;
            for (int i = 0; i < k; i++) {
                sum = (sum + (LL) C[k + 1][i] * dfs(n, i)) % mod;
            }
            sum = ((pow(n + 1, k + 1, mod) - sum) % mod + mod) % mod;
            return buff[k] = ((LL) sum * imul[k + 1]) % mod;
        }
    }

    int pow_sum(int n, int k) {
        if (k == 0) return n % mod; //因为0没有逆元, 所以特判
        if (n <= 0) return 0;
        for (int i = 0; i <= maxk + 1; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++)
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
            if (i) imul[i] = pow(i, mod - 2, mod);
        }
        memset(buff, 0, sizeof(buff));
        return dfs(n, k);
    }
}

int main() {
    int n, k;
    while (cin >> n >> k) {
        cout << Math::pow_sum(n, k) << endl;
    }
}

