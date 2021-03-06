typedef long long LL;

//扩展欧几里得
LL ext_gcd(LL a, LL b, LL &x, LL &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    LL d = ext_gcd(b, a % b, x, y), temp = x;
    x = y, y = temp - a / b * y;
    return d;
}

//利用若干个a和b，能不能使得和为c
bool can_makec(LL a, LL b, int c) {
    LL x, y;
    LL g = ext_gcd(a, b, x, y);
    if (c % g) return false;
    x *= c / g;
    y *= c / g;
    if (x < 0) {
        swap(a, b);
        swap(x, y);
    }
    LL t = x / (b / g);
    if (y + a / g * t >= 0) return true;
    return false;
}