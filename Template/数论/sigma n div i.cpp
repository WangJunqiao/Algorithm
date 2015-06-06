//n/1+n/2+...+n/n 收敛很快,复杂度能保证
inline int big(int n, int val) { //最大的ret使得n/ret = val
    return n / val;
}

int get(int n) { //计算1,2,3，...,n的因子数目之和,就是算n/1+n/2+...+n/n
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        int val = n / i, R = big(n, val);
        ret += val * (R - i + 1);
        i = R;
    }
    return ret;
}