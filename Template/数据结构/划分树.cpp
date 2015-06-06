/*
划分树
从整体来看是一棵二叉树,最顶上是一个节点,第二层是两个节点...
其次还是一棵划分树,第k+1层是对第k层的一个划分(二分)
*/

//hdu 3473 给你区间[a,b],求sigma| x-val[i] |的最小值

#include<iostream>
#include<algorithm>

using namespace std;

typedef long long int64;
#define maxn 100005

struct Node {
    int L, R;
} node[5 * maxn];//二叉树节点

int val[18][maxn], sorted[maxn];
int _left[18][maxn];
//分到左边有几个
int64 sum[18][maxn];//和

void divide(int d, int hid, int L, int R) { //要对第几层d划分,左右边界,二叉树节点下标heap-id
    node[hid].L = L;
    node[hid].R = R;
    if (L == R) return;
    int mid = (L + R) >> 1, same = 0, midval = sorted[mid];
    for (int i = L; i <= R; i++) if (val[d][i] < midval) same++;
    same = mid - L + 1 - same;//有这些个和midval一样的要分到左边

    int lp = L, rp = mid + 1;
    for (int i = L; i <= R; i++) {
        if (i == L) _left[d][i] = 0;
        else _left[d][i] = _left[d][i - 1];

        if (val[d][i] < midval || (val[d][i] == midval && same != 0)) {
            val[d + 1][lp++] = val[d][i];
            _left[d][i]++;
            if (val[d][i] == midval) same--;
        } else {
            val[d + 1][rp++] = val[d][i];
        }
    }
    divide(d + 1, hid * 2, L, mid);
    divide(d + 1, hid * 2 + 1, mid + 1, R);
    //以上是必须的
}

int64 ans = 0;

int query(int d, int hid, int L, int R, int rank) {
    int toL1, toL2, toR1, toR2; // |---******-----|,*为我们的[L,R]区间,
    int BL = node[hid].L, BR = node[hid].R, Bmid = (BL + BR) >> 1;//bound 区间边界
    if (L == BL) {
        toL1 = toR1 = 0;
        toL2 = _left[d][R];
        toR2 = (R - L + 1) - toL2;
    } else {
        toL1 = _left[d][L - 1];
        toR1 = L - BL - toL1;
        toL2 = _left[d][R] - toL1;
        toR2 = (R - L + 1) - toL2;
    }
    //以上这些是必须的
    if (L == R) return val[d][L];
    if (toL2 >= rank) { //rank分在左边
        int key = query(d + 1, hid * 2, BL + toL1, BL + toL1 + toL2 - 1, rank);
        ans += sum[d + 1][Bmid + toR1 + toR2] - sum[d + 1][Bmid + toR1] - (int64) key * toR2;
        return key;
    } else {
        int key = query(d + 1, hid * 2 + 1, Bmid + toR1 + 1, Bmid + toR1 + toR2, rank - toL2);
        ans += (int64) key * toL2 - (sum[d + 1][BL + toL1 + toL2 - 1] - sum[d + 1][BL + toL1 - 1]);
        return key;
    }
}

int main() {
    int cas, Te = 1, N, Q, L, R;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++) scanf("%d", val[0] + i);
        memcpy(sorted, val[0], sizeof(sorted));
        sort(sorted + 1, sorted + 1 + N);
        divide(0, 1, 1, N);

        for (int i = 0; i < 18; i++) {
            for (int j = 1; j <= N; j++)
                sum[i][j] = sum[i][j - 1] + val[i][j];
        }
        scanf("%d", &Q);
        printf("Case #%d:\n", Te++);
        while (Q--) {
            scanf("%d%d", &L, &R);
            L++, R++;
            ans = 0;
            query(0, 1, L, R, (R - L + 2) / 2);
            printf("%I64d\n", ans);
        }
        puts("");
    }
}
