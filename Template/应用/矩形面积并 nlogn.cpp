//矩形面积并 nlogn
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long int64;
#define maxn 110000
int y[maxn]; //离散化了的y轴
struct _Node {
    int val;
    int64 len; // 统计信息
    //
    int l, r; //boudd
    void init(int _l, int _r) {
        l = _l, r = _r;
        val = 0;
    }

    int mid() { return (l + r) >> 1; }
} dd[maxn * 5];

void update(int i) {
    if (dd[i].val) dd[i].len = y[dd[i].r] - y[dd[i].l];
    else if (dd[i].l + 1 == dd[i].r) dd[i].len = 0;
    else dd[i].len = dd[i * 2].len + dd[i * 2 + 1].len;
}

void makeTree(int i, int l, int r) {
    dd[i].init(l, r);
    if (l + 1 == r) {
        dd[i].len = 0;
        return;
    }
    int mid = dd[i].mid();
    makeTree(i * 2, l, mid);
    makeTree(i * 2 + 1, mid, r);
    update(i);
}

void modify(int i, int l, int r, int val) {
    if (dd[i].l == l && dd[i].r == r) {
        dd[i].val += val;
        update(i);
        return;
    }
    int mid = dd[i].mid();
    if (r <= mid) modify(i * 2, l, r, val);
    else if (l >= mid) modify(i * 2 + 1, l, r, val);
    else {
        modify(i * 2, l, mid, val);
        modify(i * 2 + 1, mid, r, val);
    }
    update(i);
}

//**************线段树模板结束********************
struct Rec {
    int x1, y1, x2, y2;
} r[maxn];

struct Line {
    int x, y1, y2, val; //al=1左边，val=-1右边
    void init(int _x, int _y1, int _y2, int _val) {
        x = _x;
        y1 = _y1;
        y2 = _y2;
        val = _val;
    }

    bool operator<(const Line &b) const {
        if (x != b.x) return x < b.x;
        return val > b.val;
    }
} l[2 * maxn];

int64 calc_area(Rec *r, int n) { // base0
    if (n == 0) return 0;
    int yid = 0, lid = 0;
    for (int i = 0; i < n; i++) {
        l[lid++].init(r[i].x1, r[i].y1, r[i].y2, 1);
        l[lid++].init(r[i].x2, r[i].y1, r[i].y2, -1);
        y[yid++] = r[i].y1;
        y[yid++] = r[i].y2;
    }
    sort(l, l + lid);
    sort(y, y + yid);
    yid = unique(y, y + yid) - y;

    makeTree(1, 0, yid - 1);
    int64 area = 0;
    for (int i = 0; i < lid - 1; i++) {
        int d = lower_bound(y, y + yid, l[i].y1) - y;
        int u = lower_bound(y, y + yid, l[i].y2) - y;
        modify(1, d, u, l[i].val);
        area += dd[1].len * (l[i + 1].x - l[i].x);
    }
    return area;
}//**************矩形面积并模板结束********************

int main() {
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i++) cin >> r[i].x1 >> r[i].y1 >> r[i].x2 >> r[i].y2;
        cout << calc_area(r, n) << endl;
    }
}

