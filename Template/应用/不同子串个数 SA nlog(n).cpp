++++后缀数组模板++++

int diff_substr(char *str) { //计算不同子串个数nlog(n), str base1
    n = strlen(str + 1);
    memcpy(data, str, (n + 1) * sizeof(char));
    make_SA();
    make_H();
    int ret = n - SA[1] + 1;
    for (int i = 2; i <= n; i++) {
        int l = n - SA[i] + 1;
        if (l > H[i]) ret += l - H[i];
    }
    return ret;
} //diff_substr(str);...
