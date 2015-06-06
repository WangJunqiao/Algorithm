#include <vector>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <cassert>

using namespace std;

//----------------------zjut_DD for Topcoder-------------------------------
typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
#define PB push_back
#define MP make_pair
#define sz(v) (int)v.size()
#define all(c) c.begin(),c.end()
#define clr(buf, val) memset(buf,val,sizeof(buf))
#define rep(i, l, r) for(int i=(l);i<(r);i++)
#define repv(i, v)  for(int i=0;i<(int)v.size();i++)
#define reps(i, s)  for(int i=0;i<(int)s.length();i++)
#define repi(it, c) for(typeof(c.begin()) it=c.begin();it!=c.end();++it)
//------------------------------------------------------------------------

//http://codeforces.com/problemset/problem/147/B
//prob: ����һ��n=300���������ͼ, Ȩֵ�����и�, ��ͼ�г�����̵�����. 
//solu: floyd-warshall �㷨����.
int d[10][310][310]; //d[x][i][j]��ʾi->j��������, �м���Լ��0~2^x����.
int l[310][310], tmp[310][310];

void update(int &a, int b) {
    if (a < b) a = b;
}

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF) {
        clr(d, 0xf0);
        rep(i, 0, m) {
            int a, b, ab, ba;
            scanf("%d %d %d %d", &a, &b, &ab, &ba);
            d[0][a - 1][b - 1] = ab;
            d[0][b - 1][a - 1] = ba;
        }
        clr(l, 0xf0);
        rep(i, 0, n) d[0][i][i] = l[i][i] = 0;
        rep(x, 0, 9) rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
                        update(d[x + 1][i][j], d[x][i][k] + d[x][k][j]);
        int ans = 0;
        for (int x = 9; x >= 0; x--) { //�����ʵ��һ�����ֵĹ���, ѡ���Ǹ��պ�û�������ĳ���, ��ô+1�͸պ���������..
            clr(tmp, 0xf0);
            rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) update(tmp[i][j], l[i][k] + d[x][k][j]);
            int i;
            for (i = 0; i < n; i++) if (tmp[i][i] > 0) break;
            if (i == n) {
                ans += (1 << x);
                memcpy(l, tmp, sizeof(l));
            }
        }
        if (ans >= n) puts("0");
        else printf("%d\n", ans + 1);
    }
}

