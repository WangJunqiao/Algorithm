//***********分数类*********************************
typedef long long int64;

template<typename T>
T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

struct Fraction {
    int64 n, d; // n/d
    Fraction(int64 _n = 0, int64 _d = 1) {
        assert(_n || _d); //   0/0
        n = _n, d = _d;
        int64 g = gcd(n, d);
        n /= g, d /= g;
        if (d < 0) n = -n, d = -d;
    }

    void print() { cout << n << '/' << d << '\n'; }
};

Fraction operator+(const Fraction &L, const Fraction &R) {
    return Fraction(L.n * R.d + L.d * R.n, L.d * R.d);
}

Fraction operator-(const Fraction &L, const Fraction &R) {
    return Fraction(L.n * R.d - L.d * R.n, L.d * R.d);
}

Fraction operator*(const Fraction &L, const Fraction &R) {
    return Fraction(L.n * R.n, L.d * R.d);
}

Fraction operator/(const Fraction &L, const Fraction &R) {
    return Fraction(L.n * R.d, L.d * R.n);
}

bool operator<(const Fraction &L, const Fraction &R) {
    return L.n * R.d < R.n * L.d;//要比大小用这个
}
//************************************************