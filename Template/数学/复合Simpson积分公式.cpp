/*
复合Simpson积分公式
I(f) = ∫(a,b)f(x)dx = ∑k[0,n-1]∫(xk,x(k+1))f(x)dx
     = (h/6)*{f(a) + 4*∑k[0,n-1]f(x((2*k+1)/2))dx + 2*∑k[1,n-1]f(xk)dx + f(b)}
  xk = a+k*h(k = 0,1,...,n)
   h = (b-a) / n;
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;
const long double H = 5e-5;

long double r1, r2;

long double f(long double x) {//被积函数
    return x * x;
}

long double simpson(long double a, long double b) {
    long double sum = 0;
    sum += f(a) + f(b);
    int n = int((b - a) / H);
    long double h = (b - a) / n / 2;
    for (int i = 1; i < 2 * n; i++) {
        if (i & 1)
            sum += 4 * f(a + i * h);
        else
            sum += 2 * f(a + i * h);
    }
    return sum * H / 6;
}

int main() {
    int re;
    scanf("%d", &re);
    for (int ri = 1; ri <= re; ++ri) {
        scanf("%Lf%Lf", &r1, &r2);
        if (r1 > r2)
            swap(r1, r2);
        long double ans = simpson(0, r1);
        printf("%.6Lf\n", ans);
    }
    return 0;
}
