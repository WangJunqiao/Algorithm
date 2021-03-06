//zjut 1462 N*M数码可达性判断问题
//分情况讨论
//1：当N=1即0不能上下移动时。。
//2：当M为奇数时除0外的逆序数的奇偶性必须相同
//3：当M为偶数时，0上下移动一次，逆序数改变，但0的行号也改变，抓住这个
//以上所说的逆序数都是去掉0后的。。。
#include<iostream>

using namespace std;

int a[2600];
int b[2600];

int sum[2600];

inline int lowbit(int t) { return t & (-t); }

void update(int i) {
    while (i < 2600) {
        sum[i]++;
        i += lowbit(i);
    }
}

int getsum(int i) {
    int s = 0;
    while (i >= 1) {
        s += sum[i];
        i -= lowbit(i);
    }
    return s;
}

int work(int *t, int num) { //用树状数组求逆序数
    memset(sum, 0, sizeof(sum));
    int ret = 0;
    for (int i = num; i >= 1; i--) {
        ret += getsum(t[i]);
        update(t[i]);
    }
    return ret;
}

int main() {
    int N, M;
    while (scanf("%d%d", &N, &M) != EOF) {
        int v, ind = 1, ax, ay, bx, by;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                scanf("%d", &v);
                if (v) a[ind++] = v;
                else ax = i, ay = j;
            }
        }
        ind = 1;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                scanf("%d", &v);
                if (v) b[ind++] = v;
                else bx = i, by = j;
            }
        }
        bool flag = true;
        if (N == 1) { //特殊考虑
            for (int i = 1; i < ind; i++)
                if (a[i] != b[i]) {
                    flag = false;
                    break;
                }
            if (flag) puts("YES");
            else puts("NO");
        } else {
            int suma = work(a, ind - 1);
            int sumb = work(b, ind - 1);
            if (M % 2) {
                if (suma % 2 == sumb % 2) puts("YES");
                else puts("NO");
            } else {
                suma += ax - 1;
                sumb += bx - 1;
                if (suma % 2 == sumb % 2) puts("YES");
                else puts("NO");
            }
        }
    }
}