//解Pell方程 x^2-N*y^2=1

#define maxn 100000
int p[maxn], q[maxn];
int g[maxn], h[maxn];
int a[maxn];

void Pell(int N, int &x, int &y) { //N为非完全平方数
    p[0] = 0, p[1] = 1;
    q[0] = 1, q[1] = 0;
    a[2] = (int) sqrt(N * 1.0);
    g[1] = 0;
    h[1] = 1;
    for (int i = 2; i < 100000; i++) {
        g[i] = -g[i - 1] + a[i] * h[i - 1];
        h[i] = (N - g[i] * g[i]) / h[i - 1];
        a[i + 1] = (g[i] + a[2]) / h[i];
        p[i] = a[i] * p[i - 1] + p[i - 2];
        q[i] = a[i] * q[i - 1] + q[i - 2];
        if (p[i] * p[i] - N * q[i] * q[i] == 1) {
            x = p[i], y = q[i];
            return;
        }
    }
}

int main() {
    int N;
    while (cin >> N) {
        int x = 0, y = 0;
        Pell(N, x, y);
        printf("%d*%d-%d*%d*%d=1\n", x, x, N, y, y);
    }
}