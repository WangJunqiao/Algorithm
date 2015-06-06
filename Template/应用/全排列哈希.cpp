int getHash(int *a, int n) {     //全排列的完美哈希,复杂度O(n^2),判重用的
    int ret = 0, mul = 1;
    for (int i = 1; i < n; i++) {
        int rev = 0;
        for (int j = 0; j < i; j++) if (a[j] > a[i]) rev++;
        ret += mul * rev;
        mul *= (i + 1);
    }
    return ret;
}