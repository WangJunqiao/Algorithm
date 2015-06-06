//串的最小表示 kmp求循环节  hdu 3374
#include<iostream>

using namespace std;

#define maxn 1000005

//串的最小表示,下标从1开始,返回下标
int min_present(char *ch, int len) {
    int p1 = 1, p2 = 2, k = 0;
    while (p1 <= len && p2 <= len && k < len) { //找不到比它还小的了 或者 完全匹配上了
        int n1 = p1 + k;
        if (n1 > len) n1 -= len;
        int n2 = p2 + k;
        if (n2 > len) n2 -= len;
        if (ch[n1] == ch[n2]) k++; // 相等的话,检测长度加1
        else if (ch[n1] > ch[n2]) p1 += k + 1, k = 0; //大于的话,说明p1肯定不是最小表示(必须的)
        else p2 += k + 1, k = 0; //理由同上
        if (p1 == p2) p2++;
    }
    return min(p1, p2);
}

//串的最大表示,base1,返回下标
int max_present(char *ch, int len) {
    int p1 = 1, p2 = 2, k = 0;
    while (p1 <= len && p2 <= len && k < len) {
        int n1 = p1 + k;
        if (n1 > len) n1 -= len;
        int n2 = p2 + k;
        if (n2 > len) n2 -= len;
        if (ch[n1] == ch[n2]) k++;
        else if (ch[n1] < ch[n2]) p1 += k + 1, k = 0;
        else p2 += k + 1, k = 0;
        if (p1 == p2) p2++;
    }
    return min(p1, p2);
}

int next[maxn];

int kmp(char *ch, int len) { //找循环节长度
    int q = 0;
    next[1] = 0;
    for (int i = 2; i <= len; i++) {
        while (q != 0 && ch[q + 1] != ch[i]) q = next[q];
        if (ch[q + 1] == ch[i]) q++;
        next[i] = q;
    }
    int t = len - next[len];
    if (len % t) return len;
    else return t;
}

char ch[maxn];

int main() {
    while (gets(ch + 1) > 0) {
        int len = strlen(ch + 1);
        int minp = min_present(ch, len);
        int maxp = max_present(ch, len);
        int t = len / kmp(ch, len);
        printf("%d %d %d %d\n", minp, t, maxp, t);
    }
}
