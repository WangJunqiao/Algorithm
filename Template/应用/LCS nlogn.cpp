/*
設有序列A，B。
記序列A中各個元素在B 中的位子(降序排列)
然後按在A中的位置依次列
出按後求A的最長遞增子序列
例如：有A={a,b,a,c,x}，B={b,a,a,b,c,a}
則有a={6,3,2},b={4,1},c={5};x=/;（注意降序排列）
然後按A中次序排出
{a(6,3,2),b(4,1),a(6,3,2),c(5),x()}={6,3,2,4,1,6,3,2,5}；
對此序列求最長遞增子序列即可~~
*/
int sq[100005], inds;
//0~inds-1
int y[10005][12];
//
int iy[10005]; //存放下标
int a[100010], b[100010];

int LCS(int n, int m) {//最长公共子序列nlogn
    int len = n * m;
    memset(iy, 0, sizeof(iy));
    for (int i = 1; i <= len; i++) {
        int v = a[i];
        y[v][iy[v]++] = i;
    }
    for (int i = 1; i < n; i++) {
        sort(y[i], y[i] + m);
    }
    inds = 0;
    for (int i = 1; i <= len; i++) {
        for (int j = m - 1; j >= 0; j--) {
            int v = y[b[i]][j];//1~100000
            if (inds == 0) {
                sq[inds++] = v;
                continue;
            }
            int left = 0, right = inds - 1;
            if (sq[left] >= v) {
                sq[left] = min(sq[left], v);
                continue;
            }
            if (sq[right] < v) {
                sq[inds++] = v;
                continue;
            }
            while (left + 1 < right) {
                int mid = (left + right) >> 1;
                if (sq[mid] >= v) right = mid;
                else left = mid;
            }
            sq[right] = min(sq[right], v);
        }
    }
    return inds;
}