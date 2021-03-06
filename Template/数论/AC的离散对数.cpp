//Author : AekdyCoin

#include<iostream>
#include<map>
#include<cmath>

using namespace std;
typedef long long LL;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int ext_gcd(int a, int b, int &x, int &y) {
    int t, ret;
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ret = ext_gcd(b, a % b, x, y);
    t = x, x = y, y = t - a / b * y;
    return ret;
}

int Inval(int a, int b, int n) {
    int x, y, e;
    ext_gcd(a, n, x, y);
    e = (LL) x * b % n;
    return e < 0 ? e + n : e;
}

int pow_mod(LL a, int b, int c) {
    LL ret = 1 % c;
    while (b) {
        if (b & 1)ret = ret * a % c;
        a = a * a % c;
        b >>= 1;
    }
    return ret;
}

int BabyStep(int A, int B, int C) {//A^x = B(mod C)
    map<int, int> Hash;
    LL buf = 1 % C, D = buf, K;
    int i, d = 0, tmp;
    for (i = 0; i <= 100; buf = buf * A % C, ++i)if (buf == B)return i;
    while ((tmp = gcd(A, C)) != 1) {
        if (B % tmp)return -1;
        ++d;
        C /= tmp;
        B /= tmp;
        D = D * A / tmp % C;
    }
    Hash.clear();
    int M = sqrt(C + 0.0);
    for (buf = 1 % C, i = 0; i <= M; buf = buf * A % C, ++i)if (Hash.find(buf) == Hash.end())Hash[buf] = i;

    for (i = 0, K = pow_mod(A, M, C); i <= M; D = D * K % C, ++i) {
        tmp = Inval(D, B, C);
        if (tmp > 0 && Hash.find(tmp) != Hash.end())return i * M + Hash[tmp] + d;
    }
    return -1;
}

int main() {
    int A, B, C;
    while (scanf("%d%d%d", &A, &C, &B) != EOF) {
        if (B >= C) {
            puts("Orz,I can��t find D!");
            continue;
        }
        int tmp = BabyStep(A, B, C);
        if (tmp < 0)puts("Orz,I can��t find D!");
        else printf("%d\n", tmp);
    }
    return 0;
}
