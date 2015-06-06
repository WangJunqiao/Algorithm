#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;
typedef unsigned long long LL;
const int MAXT = 100;
const int MAXN = 30;
LL len, dig, limit;

LL random() {
    LL a = rand() * rand();
    a *= a;
    return a;
}

LL mul(LL a, LL b, LL c) { // a * b % c
    LL ret = 0, tmp = a % c;
    for (; b; b >>= 1) {
        if (b & 1) if ((ret += tmp) >= c)
            ret -= c;
        if ((tmp <<= 1) >= c)
            tmp -= c;
    }
    return ret;
}

LL power(LL a, LL b, LL c) { // a^b % c
    LL res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = mul(res, a, c);
        a = mul(a, a, c);
    }
    return res;
}

bool Miller_Rabin(LL n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (!(n & 1)) return false;
    LL i, j, k, m, a;
    for (m = n - 1, k = 0; !(m & 1); m >>= 1, k++);
    for (i = 0; i < MAXT; i++) {
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

LL f(LL x, LL n) {
    return (mul(x, x, n) + 1) % n;
}

LL Pollard_Rho(LL n) {
    if (n <= 2) return 0;
    if (!(n & 1)) return 2;
    for (LL i = 1; i < MAXT; i++) {
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

LL factor[MAXN], m;

LL Prime(LL a) {
    if (Miller_Rabin(a)) return 0;
    LL t = Pollard_Rho(a);
    LL p = Prime(t);
    if (p) return p;
    return t;
}

void fenjie(LL a) {//所有素约数保存于factor[]中,m为其个数
    m = 0;
    while (a > 1) {
        if (Miller_Rabin(a)) break;
        LL t = Prime(a);
        factor[m++] = t;
        a /= t;
    }
    if (a > 0) factor[m++] = a;
}//*******************大数分解素因子************************

typedef pair<LL, int> PLI;
//
vector<PLI> ex;
LL ff[1000000], tt; //p-1的约数
void _dfs(int i, LL f) {
    if (i == ex.size()) {
        ff[tt++] = f;
        return;
    }
    LL m = 1;
    for (int j = 0; j <= ex[i].second; j++) {
        _dfs(i + 1, f * m);
        m *= ex[i].first;
    }
}

int primitive_root(LL p) { //求大素数的原根
    fenjie(p - 1);
    ex.clear();
    sort(factor, factor + m);
    for (int i = 0; i < m; i++) {
        int j = i;
        while (j + 1 < m && factor[j + 1] == factor[i]) j++;
        ex.push_back(PLI(factor[i], j - i + 1));
        i = j;
    }
    tt = 0;
    _dfs(0, 1);
    for (int r = 2; ; r++) { //Tle ???
        bool fail = false;
        for (int i = 0; i < tt && !fail; i++) {
            if (ff[i] == p - 1) continue;
            if (power(r, ff[i], p) == 1) fail = true;
        }
        if (!fail) return r;
    }
}//**********模板结束**********************

int main() {
    srand(time(NULL));
    LL n;
    while (cin >> n) {
        cout << primitive_root(n) << endl;
    }
}
