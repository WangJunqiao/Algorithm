//����һ���߶��·���������Ŀ,�����ϱ߽�,������y=0���±߽�(x�ķ�ΧҲ��<n,��û�е���n)
//y=(a+d*x)/m   x����[0,n) 
int64 count(int64 a, int64 d, int64 m, int64 n) {
    int64 ret = 0;
    if (a / m) {
        ret += a / m * n;
        a %= m;
    }
    if (d / m) {
        ret += d / m * n * (n - 1) / 2;
        d %= m;
    }
    if (d == 0) return ret;
    int l = (a + d * n) / m;
    return ret + count((a + d * n) % m, m, d, l);
}