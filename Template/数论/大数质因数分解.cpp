//hdu 3864 大数质因数分解
#include<algorithm>
#include<ctime>
#include<iostream>
#include<vector>

using namespace std;

namespace RHO {  //modified from MatRush
    typedef unsigned long long LL;
    const int MAXT = 100; //max Test
    const int MAXN = 30;

    LL random() {
        return rand() * (LL) rand() * rand() * rand();
    }

    LL mul(LL a, LL b, LL c) { // a*b %c 全是非负的
        LL ret = 0, tmp = a % c;
        for (; b; b >>= 1) {
            if (b & 1) if ((ret += tmp) >= c) ret -= c;
            if ((tmp <<= 1) >= c) tmp -= c;
        }
        return ret;
    }

    LL power(LL a, LL b, LL c) { // a^b %c 全是非负的
        LL res = 1;
        for (; b; b >>= 1) {
            if (b & 1) res = mul(res, a, c);
            a = mul(a, a, c);
        }
        return res;
    }

    bool Miller_Rabin(LL n) { //n是不是素数
        if (n < 2) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        LL m, a;
        int i, j, k;
        for (m = n - 1, k = 0; !(m & 1); m >>= 1, k++);
        for (i = 0; i < MAXT; i++) {  //保守出错率为 1/(2^MAXT)
            a = power(random() % (n - 1) + 1, m, n);
            if (a == 1) continue;
            for (j = 0; j < k; j++) {
                if (a == n - 1) break;
                a = mul(a, a, n);
            }
            if (j == k) return false;
        }
        return true;
    }

    LL gcd(LL a, LL b) {
        return b ? gcd(b, a % b) : a;
    }

    LL f(LL x, LL n) { //x^2+1 %n
        return (mul(x, x, n) + 1) % n;
    }

    LL Pollard_Rho(LL n) { //寻找n的一个因子
        if (n <= 2) return 0;
        if (!(n & 1)) return 2;
        for (int i = 1; i < MAXT; i++) {
            LL x = random() % n;
            LL xx = f(x, n);
            LL p = gcd((xx + n - x) % n, n);
            while (p == 1) {
                x = f(x, n);
                xx = f(f(xx, n), n);
                p = gcd((xx + n - x) % n, n) % n;
            }
            if (p) return p;
        }
        return 0;
    }

    LL Prime(LL a) { //寻找a的一个素因子
        if (Miller_Rabin(a)) return a;
        return Prime(Pollard_Rho(a));
    }

    vector<long long> fenjie(LL a) {//返回所有a的素约数
        vector<long long> fac;
        while (a > 1) {
            if (Miller_Rabin(a)) break;
            LL t = Prime(a);
            fac.push_back(t);
            a /= t;
        }
        if (a > 0) fac.push_back(a);
        return fac;
    }//*******************大数分解素因子************************
}// srand(time(NULL));