#include<set>
#include<map>
#include<iostream>
#include<string>
#include<algorithm>
#include<cstring>
#include<stdio.h>
#include<queue>
#include<cmath>
#include<deque>
#include<vector>

using namespace std;

/*
problem: ƽ����һЩ��(û�����㹲��),ͳ��һ���������ڲ��м�����
algorithm: ����������εĸ������ӳ�,��ƽ��ֳ���7������,Ȼ��ӼӼ�������������,����м��ǿ�
���Ӷ� O( n^2logn + Q )
*/
#define maxn 1000

struct Point {
    int pid, x, y;
    double r;

    //
    friend bool operator<(const Point &a, const Point &b) {
        return a.r < b.r;
    }
} p[maxn], p0, sorted[maxn][maxn];

int n;
short dp[maxn][maxn][2];
//�����ߵ���ߺ��ұ߸��м�����,0��ʾ��1��ʾ��
const double PI = acos(-1.0);
short pid2id[maxn][maxn];

//����һ��ֱ�ߵ�������м�����(û�����㹲�������)
void calSidePoint(int n) {//0~n-1����
    int i, j, k, sel, id;
    for (sel = 0; sel < n; sel++) {//Ԥ�����sorted�����pid2id����
        j = 0;
        for (k = 0; k < n; k++) {
            if (k == sel) continue;
            sorted[sel][j] = p[k];
            sorted[sel][j].x -= p[sel].x;
            sorted[sel][j].y -= p[sel].y;
            sorted[sel][j].r = atan2((double) sorted[sel][j].y, (double) sorted[sel][j].x);
            j++;
        }
        sort(sorted[sel], sorted[sel] + n - 1);
        for (i = 0; i < n - 1; i++) pid2id[sel][sorted[sel][i].pid] = i;
    }
    for (sel = 0; sel < n; sel++) {//ע��*******sel������ʵ��pid
        id = 0, i = 0;
        for (; i < n - 1 && sorted[sel][i].r <= 0; i++) { //�����ߵ����ұ��м�����,�ֳ������ּ���
            while (id < n - 1 && sorted[sel][id].r <= sorted[sel][i].r + PI) id++;
            dp[sel][sorted[sel][i].pid][0] = id - 1 - i;
            dp[sel][sorted[sel][i].pid][1] = n - 2 - dp[sel][sorted[sel][i].pid][0];
        }
        for (id = 0; i < n - 1; i++) {
            while (id < n - 1 && sorted[sel][id].r <= sorted[sel][i].r - PI) id++;
            dp[sel][sorted[sel][i].pid][0] = n - 2 - i + id;
            dp[sel][sorted[sel][i].pid][1] = n - 2 - dp[sel][sorted[sel][i].pid][0];
        }
    }
}

int id1, id2;

inline int radio(int &pid0, int &pid1, int &pid2) {
    id1 = pid2id[pid0][pid1];
    id2 = pid2id[pid0][pid2];
    if (fabs(sorted[pid0][id1].r - sorted[pid0][id2].r) < PI)
        return abs(id1 - id2) - 1;
    else
        return n - 2 - abs(id1 - id2);
}

int main() {
    int cas, Te = 1;
    scanf("%d", &cas);
    while (cas--) {
        int Q, pid1, pid2, pid3;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d%d", &p[i].x, &p[i].y), p[i].pid = i;
        calSidePoint(n);

        scanf("%d", &Q);
        printf("Case %d:\n", Te++);
        int A, B, C, x21, y21, x31, y31, sign;
        for (int i = 0; i < Q; i++) {
            scanf("%d%d%d", &pid1, &pid2, &pid3);
            A = 0, B = 0, C = radio(pid1, pid2, pid3) + radio(pid2, pid1, pid3) + radio(pid3, pid1, pid2);
            x21 = p[pid2].x - p[pid1].x;
            y21 = p[pid2].y - p[pid1].y;
            x31 = p[pid3].x - p[pid1].x;
            y31 = p[pid3].y - p[pid1].y;
            if ((long long) x31 * y21 - (long long) y31 * x21 > 0) sign = 0;
            else sign = 1;
            A = dp[pid1][pid2][sign] + dp[pid2][pid3][sign] + dp[pid3][pid1][sign];
            B = dp[pid1][pid2][!sign] + dp[pid2][pid3][!sign] + dp[pid3][pid1][!sign];
            B -= 3;
            printf("%d\n", C - (2 * B - A) / 3);
        }
    }
}
