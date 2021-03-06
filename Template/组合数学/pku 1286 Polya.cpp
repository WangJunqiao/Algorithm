//pku 1286 Polya
//题意: 用三种颜色的珠子组成总共有n个珠子的项链，问总共有多少种不同组法。2种项链旋转，翻转后能变为同一种的，看做是相同的
#include<iostream>

using namespace std;

__int64 _pow(int a, int b) {
    __int64 ans = 1;
    while (b) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    int temp;
    while (a % b) {
        temp = a % b;
        a = b;
        b = temp;
    }
    return b;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF && n != -1) {
        if (n == 0) {
            printf("0\n");
            continue;
        }
        __int64 ans = 0;
        for (int i = 0; i < n; i++)
            ans += _pow(3, gcd(i, n));
        if (n & 1)
            ans += _pow(3, n / 2 + 1) * n;
        else
            ans += _pow(3, n / 2) * n / 2 + _pow(3, n / 2 + 1) * n / 2;
        printf("%I64d\n", ans / 2 / n);
    }
}