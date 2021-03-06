//扩展KMP by zjut_dd
//后缀A[i]和B[i]和A的最长公共前缀长度
#include<iostream>

using namespace std;

#define maxn 200002
char A[maxn], B[maxn];
int AA_lcp[maxn], BA_lcp[maxn];

//分别记录后缀A[i]和B[i]和A的最长公共前缀长度 base1
void extend_kmp(char *A, char *B, int lenA, int lenB) { //base1
    //先计算AA_lcp数组
    AA_lcp[1] = lenA; //***必须的****
    int j = 0, k;
    while (A[1 + j] == A[2 + j] && 2 + j <= lenA) j++;//到了串未0是不可能再匹配下去的
    AA_lcp[2] = j, k = 2;
    for (int i = 3; i <= lenA; i++) { //k+AA_lcp[k]是不减的
        int Len = k + AA_lcp[k] - 1, L = AA_lcp[i - k + 1];//Len是A[k]延伸到的最远处
        if (Len - i + 1 > L)
            AA_lcp[i] = L;
        else {
            j = max(0, Len - i + 1);
            while (A[1 + j] == A[i + j] && i + j <= lenA) j++;

            AA_lcp[i] = j;
            k = i;
        }
    }
    //下面计算BA_lcp数组
    j = 0;
    while (B[1 + j] == A[1 + j] && 1 + j <= lenA && 1 + j <= lenB) j++;

    BA_lcp[1] = j, k = 1;
    for (int i = 2; i <= lenB; i++) {
        int Len = k + BA_lcp[k] - 1, L = AA_lcp[i - k + 1];
        if (Len - i + 1 > L)
            BA_lcp[i] = L;
        else {
            j = max(0, Len - i + 1);
            while (A[1 + j] == B[i + j] && 1 + j <= lenA && i + j <= lenB) j++;
            BA_lcp[i] = j;
            k = i;
        }
    }
}
