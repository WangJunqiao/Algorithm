//�������ȡģ ����  O(p)

#include<iostream>

using namespace std;
/*
Lucas����:
��C(n,m)%p (p������)
n=a0+a1*p+...+ak*p^k
m=b0+b1*p+...+bk*p^k
��C(n,m)=C(a0,b0)*C(a1,b1)*...*C(ak,bk)%p
*/
const int mod = 10567201;
int mul[100005] = {1};

//mul[i]=i!
void e_gcd(int a, int b, int &x, int &y) {//��չŷ����ö�����ax+by==1��
    if (!b) {
        x = 1;
        y = 0;
    }
    else {
        e_gcd(b, a % b, x, y);
        int temp = x;
        x = y;
        y = temp - a / b * y;
    }
}

//����Ԫ,ע��***��һ������ȡ��Ԫ��û�������
int get_ni(int a, int p) { //����x,ax=1 (mod p) p������
    int x, y;
    e_gcd(a, p, x, y);
    return x;
}

inline int C(int n, int m, int mod) {
    if (m > n) return 0;
    return ((long long) mul[n] * get_ni(mul[m], mod) % mod * get_ni(mul[n - m], mod) % mod + mod) % mod;
}

int main() {
    int n, m, p, cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d%d", &n, &m, &p);
        n += m;
        for (int i = 1; i <= p; i++) mul[i] = (long long) mul[i - 1] * i % p;
        long long ret = 1;
        while (n) {
            ret = ret * C(n % p, m % p, p) % p;
            n /= p;
            m /= p;
        }
        printf("%d\n", ret);
    }
}