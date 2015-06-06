/*
求catalan数第n项， 
1,	C(n)=(2n)!/ (n! * (n+1)! )
2,	C(n)=(4*n-2)/(n+1) * C(n-1)  且 C(0)=1;
O(n)的算法

令外：
求前n项和模m
先将m分解质因数，然后将(4 * i - 2) 和 (i + 1) 和 c[i - 1]都分成两份，一份是与m互质的，另外一份是与由m包含的质因数构成的。然后分别维护这两份。前者只要用“数”来维护就好，对于前者，由于和m互质了，除数可以求逆元，然后与(4*i - 2)和c[i - 1]的第一份边乘边模，对于后者，可以用m的质因数表来维护。最后c[i]就是把质因数表中的数乘到第一份里，边乘边模m。注意可能超int的地方。
*/
#define MAXN 200005  // 2*n
typedef long long int64;
int isp[MAXN], num[MAXN], tmp[MAXN];

void init_isp() {
    memset(isp, 0, sizeof(isp));
    for (int i = 2; i * i < MAXN; i++) {
        if (isp[i]) continue;
        for (int j = i * i; j < MAXN; j += i)
            isp[j] = i;
    }
    //printf("init\n");
}

void resolve(int *num, int n) { //resolve n! to num array
    for (int i = 0; i <= n; i++) num[i] = 1;
    for (int i = n; i >= 4; i--) {
        if (isp[i] == 0) continue;
        num[isp[i]] += num[i];
        num[i / isp[i]] += num[i];
        num[i] = 0;
    }
}

int cal_catalan(int n, int mod) {//计算catalan数第n项，结果模mod
    static bool init = false;
    if (!init) init_isp(), init = true;
    resolve(num, 2 * n);
    resolve(tmp, n);
    for (int i = 2; i <= n; i++) num[i] -= tmp[i];
    resolve(tmp, n + 1);
    for (int i = 2; i <= n + 1; i++) num[i] -= tmp[i];
    int ret = 1;
    for (int i = 2; i <= 2 * n; i++) {
        for (int j = 1; j <= num[i]; j++)
            ret = (int64) ret * i % mod;
    }
    return ret;
}