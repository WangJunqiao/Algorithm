//10^3.542 = 10^3 * 10^0.542 = 1000 * 10^0.542

//可见真正的数字还是靠幂的小数部分的

int E(int a, int b, int l) {
    double ret = b * 1.0 * log10((double) a);
    ret -= floor(ret);
    ret = pow(10.0, ret);
    while (--l)
        ret *= 10.0;
    return (int) floor(ret);
}