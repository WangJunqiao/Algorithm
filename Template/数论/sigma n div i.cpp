//n/1+n/2+...+n/n �����ܿ�,���Ӷ��ܱ�֤
inline int big(int n, int val) { //����retʹ��n/ret = val
    return n / val;
}

int get(int n) { //����1,2,3��...,n��������Ŀ֮��,������n/1+n/2+...+n/n
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        int val = n / i, R = big(n, val);
        ret += val * (R - i + 1);
        i = R;
    }
    return ret;
}