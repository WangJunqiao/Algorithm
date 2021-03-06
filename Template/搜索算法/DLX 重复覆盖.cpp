//dancing link
//重复覆盖问题 NUAA 1507
#include<iostream>

#define MAXR 62//row
#define MAXC 62//column
#define TOTAL (MAXR+1)*(MAXC+1)
using namespace std;

int n, m, mat[MAXR][MAXC];
//初始矩阵，0或1，从1，1开始用
int cid[TOTAL], rid[TOTAL], s[MAXC];
//显示行号，列号，每列的总个数
int res[MAXR];
//每次取的哪行
int l[TOTAL], r[TOTAL], u[TOTAL], d[TOTAL];
int lastc[MAXC];//第i列的最下面一个元素

void remove(const int &col) {//这一整列没了，包括列头**********
    for (int i = d[col]; i != col; i = d[i]) {
        r[l[i]] = r[i];
        l[r[i]] = l[i];
    }
}

void backtrack(const int &col) {
    for (int i = u[col]; i != col; i = u[i]) {
        r[l[i]] = i;
        l[r[i]] = i;
    }
}

inline void addlr(const int &ln, const int &rn) {//完了后还是成环的
    l[r[ln]] = rn;
    r[rn] = r[ln];
    r[ln] = rn;
    l[rn] = ln;
}

inline void addud(const int &un, const int &dn) {
    u[d[un]] = dn;
    d[dn] = d[un];
    d[un] = dn;
    u[dn] = un;
}

//*********************************************************
bool visit[MAXC];

int H() {//估价函数，表示要重复覆盖全部还至少需要几行
    int res = 0;
    memset(visit, false, sizeof(visit));
    for (int c = r[0]; c != 0; c = r[c]) {
        if (!visit[c]) {
            res++;
            visit[c] = true;
            for (int i = d[c]; i != c; i = d[i])
                for (int j = r[i]; j != i; j = r[j])
                    visit[cid[j]] = true;
        }
    }
    return res;
}

//******************************************************
int mi;

void search(int k, int sum) {//将开始第几层搜索,k是输出答案数组的下表,sum是当前已经多少层了
    if (sum + H() >= mi)
        return;
    if (r[0] == 0) {
        mi = min(mi, sum);
        return;//找到一组解
    }
    int c, mi = 1000000;
    for (int i = r[0]; i != 0; i = r[i]) {
        if (s[i] < mi) {
            mi = s[i];
            c = i;
        }
    }
    for (int i = d[c]; i != c; i = d[i]) {
        res[k] = rid[i];
        remove(i);
        for (int j = r[i]; j != i; j = r[j])
            remove(j);
        search(k + 1, sum + 1);
        for (int j = l[i]; j != i; j = l[j])
            backtrack(j);
        backtrack(i);
    }
}

/*
这个就是DLX的建模模型，0都是为了服务中间的*的,左上角的是（0,0）
00000000
 *******
 *******
 *******
 *******
*/

void adapt(int n, int m) {//传入01矩阵mat的规格,适配函数（由mat构造dancing link 表）
    memset(s, 0, sizeof(s));//每列元素个数清0
    l[0] = r[0] = 0;   //总头子是(0,0)***********
    for (int i = 1; i <= m; i++) { //总共有m列，总编号跟列号是一样的****
        addlr(i - 1, i);
        u[i] = d[i] = i;//自成循环
        lastc[i] = i; //最下面一个元素号码
    }
    int ind = m + 1;//从m+1开始用
    for (int i = 1; i <= n; i++) {
        bool isfirst = true;
        for (int j = 1; j <= m; j++) {
            if (mat[i][j]) {
                if (isfirst) {
                    isfirst = false;
                    l[ind] = r[ind] = ind;
                } else {
                    addlr(ind - 1, ind);
                }
                addud(lastc[j], ind);
                lastc[j] = ind;
                cid[ind] = j;
                rid[ind] = i;
                s[j]++;
                ind++;
            }
        }
    }
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        int x, k;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            for (int j = 1; j <= x; j++)
                scanf("%d", &k), mat[i][k] = 1;
        }
        adapt(n, m);
        mi = m;
        search(1, 0);
        printf("%d\n", mi);
        memset(mat, 0, sizeof(mat));
    }
}