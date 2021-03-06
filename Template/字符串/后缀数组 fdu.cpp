//用法: 1,赋值data(base1). 2,赋值n(串长). 3,make_SA(). 4,make_H().
char data[maxn];
//SA是后缀数组,SA[i]表示排第i位的后缀是谁
//rnk是排名数组,rnk[i]表示后缀i排第几
//H是高度数组,H[i]为SA[i]和SA[i-1]的LCP,故从2开始
int SA[maxn], rnk[maxn], H[maxn], n;  //n字符串长度
#define getR(a)((a)>n?0:rnk[a])

inline bool cmp(int a, int b) { return data[a] < data[b]; }

int c[maxn], a[maxn], _SA[maxn], _rnk[maxn], _h[maxn], L;

void Double() {
    memset(c, 0, sizeof(int) * (n + 1));
    int i;
    for (i = 1; i <= n; i++) c[getR(i + L)]++;
    a[0] = 1;
    for (i = 1; i <= n; i++) a[i] = a[i - 1] + c[i - 1];
    for (i = 1; i <= n; i++) _SA[a[getR(i + L)]++] = i;
    memset(c, 0, sizeof(int) * (n + 1));
    for (i = 1; i <= n; i++) c[getR(i)]++;
    a[0] = 1;
    for (i = 1; i <= n; i++) a[i] = a[i - 1] + c[i - 1];
    for (i = 1; i <= n; i++) SA[a[getR(_SA[i])]++] = _SA[i];
    _rnk[SA[1]] = 1;
    for (i = 2; i <= n; i++)
        if (getR(SA[i]) == getR(SA[i - 1]) && getR(SA[i] + L) == getR(SA[i - 1] + L))
            _rnk[SA[i]] = _rnk[SA[i - 1]];
        else
            _rnk[SA[i]] = _rnk[SA[i - 1]] + 1;
    memcpy(rnk, _rnk, sizeof(int) * (n + 1));
    L <<= 1;
}

void make_SA() { //跟字符串值大小无关的!!
    int i;
    for (i = 1; i <= n; i++) SA[i] = i;
    sort(SA + 1, SA + n + 1, cmp);
    rnk[SA[1]] = 1;
    for (i = 2; i <= n; i++)
        if (data[SA[i]] == data[SA[i - 1]]) rnk[SA[i]] = rnk[SA[i - 1]];
        else rnk[SA[i]] = rnk[SA[i - 1]] + 1;
    L = 1;
    while (L < n) Double();
}

void make_H() {
    int i;
    memset(_h, 0, sizeof(int) * (n + 1));
    for (i = 1; i <= n; i++)
        if (rnk[i] == 1) _h[i] = 0;
        else if (i == 1 || _h[i - 1] <= 1)
            while (data[i + _h[i]] == data[SA[rnk[i] - 1] + _h[i]]) _h[i]++;
        else {
            _h[i] = _h[i - 1] - 1;
            while (data[i + _h[i]] == data[SA[rnk[i] - 1] + _h[i]]) _h[i]++;
        }
    for (i = 1; i <= n; i++) H[rnk[i]] = _h[i];
}//*************模板结束***************