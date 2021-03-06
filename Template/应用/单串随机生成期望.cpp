//单串随即生成期望问题 zju 2916 Generator
//套用抛硬币的结论
#include<iostream>

using namespace std;
char s[14];
int pi[14];
long long int a[14];

void kmp() {//计算fail指针，即next函数
    pi[1] = 0;
    int len = strlen(s + 1), q = 0;
    for (int i = 2; i <= len; i++) {
        while (q > 0 && s[q + 1] != s[i])
            q = pi[q];
        if (s[q + 1] == s[i])
            q++;
        pi[i] = q;
    }
    return;
}

int main() {
    int cas, N, t = 1;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d", &N);
        scanf("%s", s + 1);
        kmp();
        int len = strlen(s + 1);
        a[0] = 1;//N的几次方，每次产生的东西有N中可能性
        for (int i = 1; i <= len; i++)
            a[i] = N * a[i - 1];
        long long int ans = 0;
        ans += a[len];//套抛硬币的结论
        int q = pi[len];
        while (q) {
            ans += a[q];//套抛硬币的结论
            q = pi[q];
        }
        if (t != 1)
            puts("");
        printf("Case %d:\n%lld\n", t++, ans);
    }
}