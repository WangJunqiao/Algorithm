//codeforces 128E Birthday
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

#define eps 1e-8
const double PI = acos(-1.0);
struct P {
    double x, y;
};
P p[1100];
double r[1100];

//-----切水果------------------------------------------------------------
typedef pair<double, int> PDI;
PDI rng[1100 * 10];

void fix(double &x) {
    while (x < -PI) x += 2 * PI;
    while (x >= PI) x -= 2 * PI;
}

int FruitNinja(P *p, double *r, int n) { //一刀能切几个水果, 相切的不算!!!必须是真正的切割
    if (n == 0) return 0;
    int ret = 1, cnt;
    for (int i = 0; i < n; i++) {
        cnt = 0;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            double d = sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));
            double x = atan2(p[j].y - p[i].y, p[j].x - p[i].x);
            double y = PI / 2.0 - asin((r[i] - r[j]) / d);
            double z = PI / 2.0 - asin((r[i] + r[j]) / d);
            double deg1, deg2;

            //第一区块   圆1中的相应角度
            deg1 = x - y, deg2 = x - z;
            fix(deg1);
            fix(deg2);
            if (deg1 <= deg2) {
                rng[cnt++] = PDI(deg1 + eps, 1); //加上eps微调是为了能够切成两半
                rng[cnt++] = PDI(deg2 - eps, -1);
            } else {
                rng[cnt++] = PDI(deg1 + eps, 1);
                rng[cnt++] = PDI(PI - eps, -1);

                rng[cnt++] = PDI(-PI + eps, 1);
                rng[cnt++] = PDI(deg2 - eps, -1);
            }

            //第二区块
            deg1 = x + z, deg2 = x + y;
            fix(deg1);
            fix(deg2); //copy from above
            if (deg1 <= deg2) {
                rng[cnt++] = PDI(deg1 + eps, 1);
                rng[cnt++] = PDI(deg2 - eps, -1);
            } else {
                rng[cnt++] = PDI(deg1 + eps, 1);
                rng[cnt++] = PDI(PI - eps, -1);

                rng[cnt++] = PDI(-PI + eps, 1);
                rng[cnt++] = PDI(deg2 - eps, -1);
            }
        }
        sort(rng, rng + cnt);
        int tmp = 1; //算上自己
        for (int i = 0; i < cnt; i++) {
            tmp += rng[i].second;
            ret = max(ret, tmp);
        }
    }
    return ret;
}//------------------------------------------

int main() {
    int n, k;
    while (scanf("%d %d", &n, &k) != EOF) {
        for (int i = 0; i < n; i++) scanf("%lf %lf %lf", &p[i].x, &p[i].y, r + i);
        int ma = FruitNinja(p, r, n);
        cout << (ma - 1) * (long long) (k + 1) + 1 + k * (long long) (k + 1) / 2 + (n - ma) << endl;
    }
}
