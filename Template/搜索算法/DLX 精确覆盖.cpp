//dancing link
//pku 3740
#include<iostream>
#include<cstdio>
#include<cstring>

#define MAXR 16*16*16//row
#define MAXC 16*16*4//column
#define TOTAL (MAXR+1)*(MAXC+1)
using namespace std;

int mat[MAXR][MAXC];
//初始矩阵，0或1，从1，1开始用
int cid[TOTAL], rid[TOTAL], s[MAXC];
int l[TOTAL], r[TOTAL], u[TOTAL], d[TOTAL];
int lastc[MAXC];

//第i列的最下面一个元素
void remove(const int &col) {
    l[r[col]] = l[col];
    r[l[col]] = r[col];
    for (int i = d[col]; i != col; i = d[i]) { //枚举每一行
        for (int j = r[i]; j != i; j = r[j]) { //枚举每一列
            d[u[j]] = d[j];
            u[d[j]] = u[j];
            s[cid[j]]--;
        }
    }
}

void resume(const int &col) { //回溯
    for (int i = u[col]; i != col; i = u[i]) {
        for (int j = l[i]; j != i; j = l[j]) {
            d[u[j]] = j;
            u[d[j]] = j;
            s[cid[j]]++;
        }
    }
    l[r[col]] = col;
    r[l[col]] = col;
}

inline void addlr(const int &ln, const int &rn) { //完了后还是成环的
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

int res[MAXR], ind;

//每次取的哪行
bool search(int k) { //将开始第几层搜索
    if (r[0] == 0) {
        ind = k;
        return true;//找到一组解
    }
    int c, mi = 100000000;
    for (int i = r[0]; i != 0; i = r[i]) {
        if (s[i] <= mi) {  //诡异，要<=,列的顺序是行->列->宫->格子，估计是后面的宫的那个限制条件卡的紧一些，所有先选后面的会好些
            mi = s[i];
            c = i;
        }
    }
    if (mi == 0) return false; //可以不要，包括在下面这个for里的
    remove(c);
    for (int i = d[c]; i != c; i = d[i]) {
        res[k] = rid[i];//选择了哪一行，这个数组可以用来输出选择了那些东东
        for (int j = r[i]; j != i; j = r[j]) remove(cid[j]);
        if (search(k + 1)) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(cid[j]);
    }
    resume(c);
    return false;
}

/* 链表的形状类似这样
####### 
 . . ..
 ... .
  . ..
*/
void adapt(int n, int m) { //传入01矩阵mat的规格,适配函数（由mat构造dancing link 表）
    memset(s, 0, sizeof(s));//每列元素个数清0
    l[0] = r[0] = 0;
    for (int j = 1; j <= m; j++) {
        addlr(j - 1, j);
        u[j] = d[j] = lastc[j] = j;
    }
    int c = m + 1;//从m+1开始用
    for (int i = 1; i <= n; i++) {
        bool f = true;
        for (int j = 1; j <= m; j++) {
            if (mat[i][j]) {
                if (f) {
                    f = false;
                    l[c] = r[c] = c;
                } else {
                    addlr(c - 1, c);
                }
                addud(lastc[j], c);
                rid[c] = i;
                cid[c] = j;
                s[j]++;
                lastc[j] = c++;
            }
        }
    }
}

//********************模板结束***********
int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", mat[i] + j);
        adapt(n, m);
        if (search(1))
            cout << "Yes, I found it\n";
        else
            cout << "It is impossible\n";
    }
}