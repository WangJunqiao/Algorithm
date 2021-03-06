//大组合数取模P,P是一个素数p的t次幂,复杂度O(P) 已测试hdu3439

#include<iostream>

using namespace std;
/*
Lucas定理:
求C(n,m)%p (p是素数)
n=a0+a1*p+...+ak*p^k
m=b0+b1*p+...+bk*p^k
则C(n,m)=C(a0,b0)*C(a1,b1)*...*C(ak,bk)%p

注意***
t!的逆元 = t!%p的逆元  
*/
int mul[100005] = {1};

//mul[i]=i!
void e_gcd(int a, int b, int &x, int &y) { //扩展欧几里得定理：解ax+by=gcd(a,b)。
    if (!b) {
        x = 1;
        y = 0;
    } else {
        e_gcd(b, a % b, x, y);
        int temp = x;
        x = y;
        y = temp - a / b * y;
    }
}

//算逆元
int get_ni(int a, int p) { //返回x,ax=1 (mod p) ap互质
    int x, y;
    e_gcd(a, p, x, y);
    return x;
}

int Power(int a, int b, int p) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = (long long) ret * a % p;
        a = (long long) a * a % p;
        b >>= 1;
    }
    return ret;
}

//计算n!中有几个p,放在num里,其它相乘结果放在res
void Calculate(int n, int p, int mod, int &res, int &num) {
    res = 1;
    num = 0;
    while (n != 0) {
        res = (long long) res * Power(mul[mod], n / mod, mod) % mod;
        res = (long long) res * mul[n % mod] % mod;//注意这里是mod 不是 p
        num += n / p;
        n /= p;
    }
}

//n!/( m!*(n-m)! )
int Chose(int n, int m, int p, int t) { //N中选M,结果模P^t,P是素数
    int MM = 1;
    for (int i = 1; i <= t; i++) MM *= p;
    if (m > n) return 0;
    for (int i = 1; i <= min(MM, n); i++) { //mul[i]是i!中不包含p的乘积
        if (i % p == 0) mul[i] = mul[i - 1]; //i%p==0是另外考虑的
        else mul[i] = (long long) mul[i - 1] * i % MM;//mul[0]=1;
    }
    int fenzi = 0, fenmu = 0, num, res, ans = 1;
    Calculate(n, p, MM, res, num);
    ans = (long long) ans * res % MM;
    fenzi += num;
    Calculate(m, p, MM, res, num);
    ans = (long long) ans * get_ni(res, MM) % MM;
    fenmu += num;
    m = n - m;
    Calculate(m, p, MM, res, num);
    ans = (long long) ans * get_ni(res, MM) % MM;
    fenmu += num;
    if (fenzi - fenmu >= t) return 0;
    ans = (long long) ans * Power(p, fenzi - fenmu, MM) % MM;
    return (ans + MM) % MM;
}

int main() {
    int n, m, p, t, cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d%d", &n, &m, &p);
        printf("%d\n", Chose(n + m, m, p, 1));
    }
}