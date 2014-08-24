#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
const double eps = 1e-8;
const double pi = acos(-1.0);
const double inf = 1e200;
inline int sgn(double x) {
    return x < -eps ? -1 : x > eps;
}
inline double sqr(double x) {
    return x * x;
}
inline double a2r(double a) { //角度到弧度
    return a * pi / 180;
}
inline double r2a(double r) { //弧度到角度
    return r / pi * 180;
}
struct P {
    double x,y;
    P(double x = 0,double y = 0):x(x), y(y) {};
    friend bool operator ==(const P& p1, const P& p2) {
        return sgn(p1.x - p2.x) == 0 && sgn(p1.y - p2.y) == 0;
    }
    friend bool operator <(const P& p1, const P& p2) {
        return sgn(p1.x - p2.x) == 0 ? sgn(p1.y - p2.y) < 0 : sgn(p1.x - p2.x) < 0;
    }
    friend bool operator >(const P& p1, const P& p2) {
        return sgn(p1.x - p2.x) == 0 ? sgn(p1.y - p2.y) > 0 : sgn(p1.x - p2.x) > 0;
    }
    friend P operator +(const P& p1, const P& p2) {
        return P(p1.x + p2.x, p1.y + p2.y);
    }
    friend P operator -(const P& p1, const P& p2) {
        return P(p1.x - p2.x, p1.y - p2.y);
    }
    friend P operator *(const P& p, double a) {
        return P(p.x * a,p.y * a);
    }
    friend P operator /(const P& p, double a) {
        return P(p.x / a,p.y / a);
    }
    friend inline double operator ^(const P& p1, const P& p2) { //点乘
        return p1.x * p2.x + p1.y * p2.y;
    }
    friend inline double operator *(const P& p1, const P& p2) { //叉乘
        return p1.x * p2.y - p1.y * p2.x;
    }
    friend inline double dot(const P& o, const P& a, const P& b) {
        return (a - o) ^ (b - o);
    }
    friend inline double cross(const P& o, const P& a, const P& b) { //2倍三角形oab有向面积
        return (a - o) * (b - o);
    }
    friend double dist(const P& p1, const P& p2) {
        return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }
    friend double dist2(const P& p1, const P& p2) {
        return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    }
    double len() const {
        return sqrt(x * x + y * y);
    }
    double len2() const {
        return x * x + y * y;
    }
    //求向量v的极角，角度范围为 [0,2*pi)
    double angle() const {
        double t = atan2(y,x);
        return sgn(t) >= 0 ? t : t + 2 * pi;
    }
    P trunc(double l) const {
        l /= len();
        return P(x * l, y * l);
    }
    P turn_left() const { //法向量
        return P(-y, x);
    }
    P turn_right() const { //法向量
        return P(y, -x);
    }
    P rotate(double th, const P& p) const { //绕点p逆时针转th弧度
        double c = cos(th), s = sin(th);
        return P(c * (x - p.x) - s * (y - p.y) + p.x, s * (x - p.x) + c * (y - p.y) + p.y);
    }
    bool in() {
        return scanf("%lf %lf", &x, &y) == 2;
    }
    void out() const {
        printf("%lf %lf\n", x, y);
    }
};

//以下直线相关
struct line {
    P a, b;
    line() {}
    line(P a, P b):a(a), b(b) {}
    
    //点到直线距离
    friend double dist(const P& p, const line& l) {
        return fabs(cross(p, l.a, l.b)) / dist(l.a, l.b);//到线段所在直线距离
    }
    
    //判定两直线位置关系,并求出交点(如果存在).
    //完全重合(2),有交点(1),平行无交(0),参数错误(-1)
    friend int intersection(const line& l1, const line& l2, P& p) { //直线与直线相交
        if (l1.a == l1.b || l2.a == l2.b) return -1;
        double c1 = (l1.b - l1.a) * (l2.b - l2.a),//cross(l1.a,l1.b,l2.b);
               c2 = (l2.a - l1.a) * (l2.b - l2.a);//cross(l1.a,l2.a,l2.b);
        if (sgn(c1) == 0) {
            if (sgn(c2) == 0) {
                return 2;//两线重叠
            } else {
                return 0;//两线平行不重叠
            }
        } else {
            p = l1.a + (l1.b - l1.a) * (c2 / c1);
            return 1;
        }
    }

    friend bool sameside(const P& p1, const P& p2, const line& l) { //两个点是否在直线同侧,是则返回true
        return sgn(cross(p1, l.a, l.b) * cross(p2, l.a, l.b)) > 0;
    }
    
    //判断点是否在线段上 包含端点
    friend bool onseg(const P& p, const line& s) {
        if (sgn(cross(p, s.a, s.b)) == 0)//如果点保证在线段所在直线上，去掉此条件较好
            if (sgn(p.x - min(s.a.x, s.b.x)) >= 0 && sgn(p.x - max(s.a.x, s.b.x)) <= 0)
                if (sgn(p.y - min(s.a.y, s.b.y)) >= 0 && sgn(p.y - max(s.a.y, s.b.y)) <= 0)
                    return 1;
        return 0;
    }
    
    //判断点是否在线段上 不包含端点
    friend bool onseg2(const P& p, const line& s) {
        if (sgn(cross(p, s.a, s.b)) == 0)//如果点保证在线段所在直线上，去掉此条件较好
            if (sgn(p.x - min(s.a.x, s.b.x)) >= 0 && sgn(p.x - max(s.a.x, s.b.x)) <= 0)
                if (sgn(p.y - min(s.a.y, s.b.y)) >= 0 && sgn(p.y - max(s.a.y, s.b.y)) <= 0)
                    return !(p == s.a || p == s.b);
        return 0;
    }
    
    void in() {
        a.in(), b.in();
    }
};

//以下解析几何直线相关
struct L { //直线定义ax + by + c = 0
    double a, b, c;
    L(const P& p1, const P& p2) { //两点式到一般式
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p2 * p1;
        if (sgn(a) < 0) a *= -1,b *= -1,c *= -1;
    }
    L(double a = 0, double b = 0, double c = 0):a(a), b(b), c(c) {}
    L(line l) {
        *this = L(l.a, l.b);
    }
    
    //点到直线的距离
    friend double dist(const P& p, const L& l) {
        return fabs(l.a * p.x + l.b * p.y + l.c) / sqrt(sqr(l.a) + sqr(l.b));
    }
    
    //两个点是否在直线同侧,是则返回true
    friend bool sameside(const P& p1, const P& p2, const L& l) {
        return sgn((l.a * p1.x + l.b * p1.y + l.c) * (l.a * p2.x + l.b * p2.y + l.c)) > 0;
    }
    
    //求点p关于直线l的对称点
    friend P symmerty(const P& p, const L& l) {
        P t;
        t.x = ((sqr(l.b) - sqr(l.a)) * p.x - 2 * l.a * l.b * p.y - 2 * l.a * l.c) / (sqr(l.a) + sqr(l.b));
        t.y = ((sqr(l.a) - sqr(l.b)) * p.y - 2 * l.a * l.b * p.x - 2 * l.b * l.c) / (sqr(l.a) + sqr(l.b));
        return t;
    }
    
    //直线l1,l2是否相交
    bool intersection(const L& l1, const L& l2, P &p) {
        double d = l1.a * l2.b - l2.a * l1.b;
        if (sgn(d) == 0) return 0; // 不相交
        p.x = (l2.c * l1.b - l1.c * l2.b) / d;
        p.y = (l2.a * l1.c - l1.a * l2.c) / d;
        return 1;
    }
    
    //返回直线的斜率k,水平线返回 0,竖直线返回 1e200
    double slope(const L& l) {
        if (abs(l.a) < 1e-20) return 0;
        if (abs(l.b) < 1e-20) return inf;
        return -(l.a / l.b);
    }
    
    //返回直线的倾斜角alpha(0～pi)
    double alpha(const L& l) {
        if (sgn(l.a) == 0) return 0;
        if (sgn(l.b) == 0) return pi / 2;
        double k = slope(l);
        if (k > 0) return atan(k);
        else return pi + atan(k);
    }
    
    void input() {
        P p1, p2;
        p1.in(), p2.in();
        *this = L(p1, p2);
    }
    
    void out() {
        printf("%lfx", a);
        if (b >= 0) putchar('+');
        printf("%lfy", b);
        if (c >= 0) putchar('+');
        printf("%lf", c);
        printf(" = 0\n");
    }
};

//以下是线段相关
struct seg {
    P a, b;
    seg() {}
    seg(P a, P b):a(a), b(b) {}
    
    //点到线段距离 可以判点是否落在线段上
    friend double dist(const P& p, const seg& s) {
        if (sgn((s.b - s.a) ^ (p - s.a)) <= 0)
            return dist(s.a, p);
        if (sgn((s.a - s.b) ^ (p - s.b)) <= 0)
            return dist(s.b, p);
        return fabs((p - s.b) * (s.a - s.b)) / (s.a - s.b).len();
        //return cross(p,s.a,s.b) / (s.b - s.a).len();//到线段所在直线距离
    }
    
    //线段s1到线段s2最短距离
    //通过<,<=,来处理端点 如果相交可以返回交点
    friend double dist(const seg& s1, const seg& s2) {
        if (!((sgn(max(s1.a.x, s1.b.x) - min(s2.a.x, s2.b.x)) < 0) ||
              (sgn(max(s2.b.x, s2.a.x) - min(s1.a.x, s1.b.x)) < 0) ||
              (sgn(max(s1.a.y, s1.b.y) - min(s2.a.y, s2.b.y)) < 0) ||
              (sgn(max(s2.b.y, s2.a.y) - min(s1.a.y, s1.b.y)) < 0) )) {
                if (sgn(cross(s1.a, s2.a, s1.b) * cross(s1.a, s2.b, s1.b)) <= 0 &&
                    sgn(cross(s2.a, s1.a, s2.b) * cross(s2.a, s1.b, s2.b)) <= 0) {
                    /*double t = ((s1.a - s2.a) * (s2.a - s2.b)) / ((s1.a - s1.b) * (s2.a - s2.b));
                    P p = (s1.b - s1.a) * t;*/
                    return 0;
                }
            }
        //不相交
        return min(min(dist(s1.a, s2), dist(s1.b, s2)), min(dist(s2.a, s1),dist(s2.b, s1)));
    }
    
    //线段s与直线相交 叉积为负
    friend int intersection(seg s, line l, P& p) {
        P v1 = l.b - l.a, v2 = s.b - l.a, v3 = s.a - l.a, v4 = s.b - s.a;
        int sign = sgn((v2 * v1) * (v3 * v1));
        double t = (s.a * v4 + v4 * l.a) / (v1 * v4);
        p = l.a + (l.b - l.a) * t;
        return sign <= 0;
        //sign = 0交点为端点,sign = 1同侧不相交sign -1异侧相交
    }
    
    //两线段是否平行
    friend bool isparallel(seg a, seg b) {
        return sgn((a.a - a.b) * (b.a - b.b)) == 0;
    }
    
    //判定两线段位置关系,并求出交点(如果存在).
    //有重合:完全重合(6),1个端点重合且共线(5),部分重合(4)
    //无重合:两端点相交(3),交于线上(2),正交(1),无交(0),参数错误(-1)
    friend int intersection(seg a, seg b, P& p) {
        //保证参数p1!=p2,p3!=p4
        P &p1 = a.a, &p2 = a.b, &p3 = b.a, &p4 = b.b;
        if (p1 == p2 || p3 == p4) return -1; //返回-1代表至少有一条线段首尾重合,不能构成线段
        if (p1 > p2) swap(p1, p2); //为方便运算,保证各线段的起点在前,终点在后.
        if (p3 > p4) swap(p3, p4);
        P v1 = p2 - p1, v2 = p4 - p3; //求出两线段构成的向量
        double cross = v1 * v2; //求两向量外积,平行时外积为0
        if (p1 == p3 && p2 == p4) { //判定两线段是否完全重合,返回任意一个端点
            p = p1;
            return 6;
        }
        if (p1 == p3 || p2 == p4) { //起点或终点重合,共线(平行)返回5;不平行则交于端点,返回3
            p = p1 == p3 ? p1 : p2;
            return sgn(cross) == 0 ? 5 : 3;
        }
        if (p1 == p4 || p2 == p3) { //如果两线端首尾相连
            p = p1 == p4 ? p1 : p2;
            return 3;
        }
        //经过以上判断,首尾点相重的情况都被排除了
        //将线段按起点坐标排序.若线段1的起点较大,则将两线段交换
        if (p1 > p3) {
            swap(a, b);
            swap(v1, v2); //更新原先计算的向量及其外积
            cross = v1 * v2;
        }
        if (sgn(cross) == 0) { //处理两线段平行的情况
            P vs = p3 - p1; //做向量v1(p1, p2)和vs(p1,p3)的外积,判定是否共线
            if (sgn(v1 * vs) == 0 && p2 > p3) { //外积为0则两平行线段共线,前一条线的终点大于后一条线的起点,则判定存在重合
                p = p3;
                return 4; //返回值4代表线段部分重合
            }//若三点不共线,则这两条平行线段必不共线.
            return 0; //不共线或共线但无重合的平行线均无交点
        } //以下为不平行的情况,先进行快速排斥试验
        //x坐标已有序,可直接比较,y坐标要先求两线段的最大和最小值
        double ymax1 = p1.y, ymin1 = p2.y, ymax2 = p3.y, ymin2 = p4.y;
        if (ymax1 < ymin1) swap(ymax1, ymin1);
        if (ymax2 < ymin2) swap(ymax2, ymin2);
        if (p1.x > p4.x || p2.x < p3.x || ymax1 < ymin2 || ymin1 > ymax2) return 0;//如果以两线段为对角线的矩形不相交,则无交点
        //下面进行跨立试验
        P vs1 = p1 - p3, vs2 = p2 - p3, vt1 = p3 - p1, vt2 = p4 - p1;
        double s1v2 = vs1 * v2, s2v2 = vs2 * v2, t1v1 = vt1 * v1, t2v1 = vt2 * v1;
        //根据外积结果判定否交于线上
        if (sgn(s1v2) == 0 && p4 > p1 && p1 > p3) {
            p = p1;
            return 2;
        }
        if (sgn(s2v2) == 0 && p4 > p2 && p2 > p3) {
            p = p2;
            return 2;
        }
        if (sgn(t1v1) == 0 && p2 > p3 && p3 > p1) {
            p = p3;
            return 2;
        }
        if (sgn(t2v1) == 0 && p2 > p4 && p4 > p1) {
            p = p4;
            return 2;
        } //未交于线上,则判定是否相交
        if(s1v2 * s2v2 > 0 || t1v1 * t2v1 > 0) return 0;
        //以下为相交的情况,计算二阶行列式的两个常数项
        double A = p1 * v1,B = p3 * v2;
        //计算行列式D1和D2的值,除以系数行列式的值,得到交点坐标
        p.x = (B * v1.x - A * v2.x) / cross;
        p.y = (B * v1.y - A * v2.y) / cross;
        //正交返回1
        return 1;
    }
    
    //判断点是否在线段上 包含端点
    friend bool onseg(const P& p, const seg& s) {
        if (sgn(cross(p, s.a, s.b)) == 0)//如果点保证在线段所在直线上，去掉此条件较好
            if (sgn(p.x - min(s.a.x, s.b.x)) >= 0 && sgn(p.x - max(s.a.x, s.b.x)) <= 0)
                if (sgn(p.y - min(s.a.y, s.b.y)) >= 0 && sgn(p.y - max(s.a.y, s.b.y)) <= 0)
                    return 1;
        return 0;
    }
    
    //判断点是否在线段上 不包含端点
    friend bool onseg2(const P& p, const seg& s) {
        if (sgn(cross(p, s.a, s.b)) == 0)//如果点保证在线段所在直线上，去掉此条件较好
            if (sgn(p.x - min(s.a.x, s.b.x)) >= 0 && sgn(p.x - max(s.a.x, s.b.x)) <= 0)
                if (sgn(p.y - min(s.a.y, s.b.y)) >= 0 && sgn(p.y - max(s.a.y, s.b.y)) <= 0)
                    return !(p == s.a || p == s.b);
        return 0;
    }
    
    //线段垂直平移
    //线段向量ab往垂线方向左移r长度
    friend seg left(const seg& s, double r) {
        P p = (s.b - s.a).turn_left().trunc(r);
        return seg(s.a + p,s.b + p);
    }

    //获得线段s的中垂线向量
    //s.a在左边,即s.a在半平面内
    friend seg mid(const seg& s) {
        seg m;
        m.a = (s.a + s.b) / 2;
        m.b.x = m.a.x + s.a.y - s.b.y;
        m.b.y = m.a.y + s.b.x - s.a.x;
        return m;
    }
    
    //点与线段的关系
    //r = 0:P = A,r = 1:P = B,r < 0:P < AB,r > 1 :P > AB,0 < r < 1, P in AB
    friend double relation(const P& p, const seg& s) {
        return dot(p, s.b, s.a) / dist2(s.a, s.b);
    }
    
    //求点p到线段s所在直线的垂足
    friend P perpendicular(const P& p, const seg& s) {
        double r = relation(p, s);
        return s.a + r * (s.b - s.a);
    }
    
    void in() {
        a.in(), b.in();
    }
    
    void out() {
        a.out(), b.out();
    }
};

//以下圆相关
struct circle {
    P o;//圆心
    double r;
    circle():r(0) {}
    circle(P o,double r = 0):o(o), r(r) {}
    circle(const P& a, const P& b, const P& c) { //三角形abc构造外接圆
        // 先判(sgn((b - a) * (c - a)) != 0) 不共线
        double c1 = (sqr(a.x) + sqr(a.y) - sqr(b.x) - sqr(b.y)) / 2;
        double c2 = (sqr(a.x) + sqr(a.y) - sqr(c.x) - sqr(c.y)) / 2;
        o.x = (c1 * (a.y - c.y) - c2 * (a.y - b.y)) / ((a - b) * (a - c));
        o.y = (c1 * (a.x - c.x) - c2 * (a.x - b.x)) / ((a - c) * (a - b));
        r = dist2(o, a); 
    }
    
    //求圆外点到圆的切点
    friend void tangent(const P& p, const circle& c, P& p1, P& p2) {
        double d = dist(p, c.o);
        P t = c.o + (p - c.o) * (c.r / d);
        double th = acos(c.r / d);
        p1 = t.rotate(th, c.o);
        p2 = t.rotate(2 * pi - th, c.o);
    }
    
    //两圆关系
    //相交(1) 外切(2) 内切(3) 相离(4) 内含(5) 有误(0)
    friend int relation(const circle& c1, const circle& c2) {
        double d = dist(c1.o, c2.o);
        if (sgn(d - fabs(c1.r - c2.r)) > 0 && sgn(d - c1.r - c2.r) < 0) return 1; //相交
        if (sgn(d - c1.r - c2.r) == 0) return 2;//外切
        if (sgn(d - fabs(c1.r - c2.r)) == 0) return 3;//内切
        if (sgn(d - c1.r - c2.r) > 0) return 4;//相离
        if (sgn(d - fabs(c1.r - c2.r)) < 0) return 5;//内含
        return 0; //error
    }

    //圆与圆相交(相切)
    //返回交点(切点)个数 相离(0) 重合(3) 相切(1) 相交(2)
    friend int intersection(const circle& c1, const circle& c2, P& p1, P& p2) {
        double d = dist(c1.o, c2.o);
        if (sgn(d - (c1.r + c2.r)) > 0 || sgn(d - fabs(c1.r - c2.r)) < 0) { //相离
            return 0;
        }
        if (sgn(d) == 0 && sgn(c1.r - c2.r) == 0) { //重合
            return 3;
        }
        double cosa = (sqr(c1.r) + sqr(d) - sqr(c2.r)) / (2 * c1.r * d);
        double sina = sqrt(max(0., 1. - sqr(cosa)));
        p1 = p2 = c1.o;
        p1.x += c1.r / d * ((c2.o.x - c1.o.x) * cosa + (c2.o.y - c1.o.y) * -sina);
        p1.y += c1.r / d * ((c2.o.x - c1.o.x) * sina + (c2.o.y - c1.o.y) * cosa);
        p2.x += c1.r / d * ((c2.o.x - c1.o.x) * cosa + (c2.o.y - c1.o.y) * sina);
        p2.y += c1.r / d * ((c2.o.x - c1.o.x) * -sina + (c2.o.y - c1.o.y) * cosa);        
        if (sgn(p1.x - p2.x) == 0 && sgn(p1.y - p2.y) == 0) {
            return 1; //相切
        } else {
            return 2; //相交
        }
    }
    
    //圆与直线是否相交(相切)
    //返回交点(切点)个数 相离(0) 相切(1) 相交(2)
    friend int intersection(const circle& c, line& l, P& p1, P& p2) {
        if (c.o == l.a) swap(l.a, l.b);
        double d = fabs((c.o - l.a) * (l.b - l.a)) / (l.b - l.a).len();
        P v = (l.b - l.a).turn_right(), p;
        line mid(c.o, c.o + v);
        intersection(mid, l, p);
        int sign = sgn(d - c.r);
        if (sign < 0) { //相交 2个交点
            double d = dist(c.o, p);
            if (p == l.a) swap(l.a, l.b);
            P v1 = l.a - p;
            p1 = p + v1 * sqrt((sqr(c.r) - sqr(d))) / v1.len();
            p2 = p * 2 - p1; //p2 = p1.rotate(pi,p);
            return 2;
        } else if (sign == 0) { //相切
            p1 = p;
            return 1;
        } else {
            return 0; //相离
        }
    }
    
    //圆与线段是否相交(相切)
    friend int intersection(const circle& c, const seg& s, P& p1, P& p2) {
        if (sgn(dist(c.o,s.a) - c.r) < 0 && sgn(dist(c.o,s.b) - c.r) < 0) {
            return 0; //线段在圆内(不包括边界)视为相离
        }
        P v = (s.b - s.a).turn_right(), p;
        line l(c.o, c.o + v);
        if (intersection(s, l, p)) { //与垂线相交
            double d1 = dist(c.o,s.a), d2 = dist(c.o,s.b),
                   d3 = fabs((c.o - s.b) * (s.a - s.b)) / (s.a - s.b).len();
            int sign = sgn(d3 - c.r);
            if (sign < 0) {
                if (sgn(min(d1,d2) - c.r) < 0) { //只有一个交点
                    if (sgn(d1 - c.r) < 0) { //s.a在圆内
                        P v1 = s.b - p;
                        p1 = p + v1 * (sqrt(sqr(c.r) - sqr(d3)) / v1.len());
                    } else { //s.b在圆内
                        P v1 = s.a - p;
                        p1 = p + v1 * (sqrt(sqr(c.r) - sqr(d3)) / v1.len());
                    }
                    return 1;
                } else {
                    P v1 = s.a - p;
                    p1 = p + v1 * (sqrt(sqr(c.r) - sqr(d3)) / v1.len());
                    v1 = s.b - p;
                    p2 = p + v1 * (sqrt(sqr(c.r) - sqr(d3)) / v1.len());
                    return 2; //有2个交点
                }
            } else if (sign == 0) {
                p1 = p;
                return 3;//相切
            } else {
                return 0;
            }
        } else { //与垂线不相交 无相切
            double d1 = dist(c.o,s.a),d2 = dist(c.o,s.b),
                   d3 = fabs((c.o - s.b) * (s.a - s.b)) / (s.a - s.b).len();
            int sign = sgn(min(d1,d2) - c.r);
            if (sign < 0) {
                if (sgn(d1 - c.r) < 0) { //s.a在圆内
                    P v1 = s.b - s.a;
                    p1 = s.b + v1 * (sqrt(sqr(c.r) - sqr(d3)) - sqrt(sqr(d2) - sqr(d3))) / v1.len();
                } else { //s.b在圆内
                    P v1 = s.a - s.b;
                    p1 = s.a + v1 * (sqrt(sqr(c.r) - sqr(d3)) - sqrt(sqr(d1) - sqr(d3))) / v1.len();
                }
                return 1;//相交,最多一个交点
            }
            if (sign == 0) { //交于一点
                p1 = sgn(d1 - c.r) == 0 ? s.a : s.b;
                return 1;
            } else {
                return 0;
            }
        }
    }
    
    //圆C1和C2相交面积
    friend double intersectionarea(circle& C1, circle& C2) {
        P c1 = C1.o, c2 = C2.o;
        double r1 = C1.r, r2 = C2.r;
        if (r1 > r2) swap(c1, c2);
        double d, a1, a2, p, area;
        d = sqrt(sqr(c1.x - c2.x) + sqr(c1.y - c2.y));
        if (sgn(r1 + d - r2) <= 0) return pi * sqr(r1);
        if (sgn(r1 + r2 - d) <= 0) return 0;
        a1 = acos((sqr(r1) + sqr(d) - sqr(r2)) / (2 * r1 * d));
        a2 = acos((sqr(r2) + sqr(d) - sqr(r1)) / (2 * r2 * d));
        p = (r1 + r2 + d) / 2;
        area = 2 * sqrt(p * (p - r1) * (p - r2) * (p - d));
        area = a1 * sqr(r1) + a2 * sqr(r2) - area;
        return area;
    }
    
    //求两个圆的公切线，传入两圆，返回切线条数 * 2，存放在p[]中，(p[2*i], p[2*i+1])构成一条切线
    //两圆重合返回-1，无数条切线，内含返回0条切线
    //内切返回1条切线，相交返回2条切线，外切返回3条切线，相离返回4条切线
    //圆c1上：相交时则p[2]->p[0]对应的圆角度被覆盖
    //否则p[4]和p[6]也要考虑进去，即p[2]->p[6],p[4]->p[0]
    int tangentline(circle c1, circle c2, P p[]) {
        int n = 0;
        bool rev = false;
        if (c1.r < c2.r) {
            swap(c1, c2);
            rev = true;
        }
        double r = min(c1.r, c2.r), R = max(c1.r, c2.r);
        double d = dist(c1.o, c2.o), th;
        P v = c2.o - c1.o, v1 = v.trunc(c1.r), v2 = v.trunc(c2.r);
        if (sgn(d) == 0 && sgn(R - r) == 0) {//重合，无数条切线
            return -1;
        }
        if (sgn(d - R + r) < 0) {//内含，0切线
            return n;
        } else if (sgn(d - R + r) == 0) {//内切，1切线
            p[n++] = v2 + c2.o;
            p[n++] = v.rotate(pi / 2, P(0, 0)) + p[n - 2];
            return n;
        } else if (sgn(d - R + r) > 0) {//相交或相离，都有水平切线
            th = acos((R - r) / d);
            p[n++] = v1.rotate(th, P(0, 0)) + c1.o;
            p[n++] = v2.rotate(th, P(0, 0)) + c2.o;
            p[n++] = v1.rotate(2 * pi - th, P(0, 0)) + c1.o;
            p[n++] = v2.rotate(2 * pi - th, P(0, 0)) + c2.o;
        }
        if (sgn(d - R - r) == 0) {//外切，1条垂直切线
            p[n++] = v1 + c1.o;
            p[n++] = v.rotate(pi / 2, P(0, 0)) + p[n - 2];
        } else if (sgn(d - R - r) > 0) {//相离有2条交叉切线
            th = acos((R + r) / d);
            p[n++] = v1.rotate(th, P(0, 0)) + c1.o;
            p[n++] = v2.rotate(pi + th, P(0, 0)) + c2.o;
            p[n++] = v1.rotate(2 * pi - th, P(0, 0)) + c1.o;
            p[n++] = v2.rotate(pi - th, P(0, 0)) + c2.o;
        }
        if (rev) {
            for (int i = 0; i < n; i += 2) {
                swap(p[i], p[i + 1]);
            }
            //swap(p[0], p[2]);
        }
        return n;
    }
    
    //点是否在圆内(边上)
    friend int incircle(const P& p, const circle& c) {
        int sign = sgn(dist(p,c.o) - c.r);
        if (sign < 0) return 1; //相交
        else if (sign == 0) return 2; //相切
        else return 0; //相离
    }/*因为圆为凸集,所以判断点集,折线,多边形是否在圆内时,只需要逐一判断点是否在圆内即可*/
    
    //判断圆是否在多边形内
    friend bool inpolygon(const circle& c, P p[], int n) {
        double mi = inf;
        for (int i = 0; i < n; i++) {
            double t = dist(c.o, seg(p[i], p[(i + 1) % n]));
            mi = min(mi, t);
        }
        return sgn(mi - c.r) >= 0;
    }
    
    void in() {
        o.in();
        scanf("%lf", &r);
    }
    void out() {
        o.out();
        printf("%lf\n", r);
    }
    double area() {
        return pi * sqr(r);
    }
    double perimeter() {
        return 2 * pi * r;
    }
};

//以下椭圆相关

//椭圆可以利用2个参数d e得到:(x/d)^2+(y/e)^2=1

//直线与椭圆的交点,返回值为交点个数
//直线ax+by+c=0, 椭圆(x/d)^2+(y/e)^2=1
//x=(-c*ad*d±be*d*sqrt(ad^2+be^2-c^2))/(ad^2+be^2)
//y=(-c*be*e±ad*e*sqrt(ad^2+be^2-c^2))/(ad^2+be^2)
int line_ellipse_intersection(double d, double e, const L& l, P& p1, P& p2) {
    double ab = sqr(l.a) * sqr(d) + sqr(l.b) * sqr(e), delta = ab - sqr(l.c);
    if (sgn(delta) < 0) {
        return 0;
    } else if (sgn(delta) == 0) {
        p1.x = -l.c * l.a * sqr(d) / ab;
        p1.y = -l.c * l.b * sqr(e) / ab;
        return 1;
    } else {
        double sq = d * e * sqrt(delta);
        p1.x = (-l.c * l.a * sqr(d) + l.b * sq) / ab;
        p1.y = (-l.c * l.b * sqr(e) - l.a * sq) / ab;
        p2.x = (-l.c * l.a * sqr(d) - l.b * sq) / ab;
        p2.y = (-l.c * l.b * sqr(e) + l.a * sq) / ab;
        return 2;
    }
}

//以下矩形相关

//说明：因为矩形的特殊性,常用算法可以化简:
//1.判断矩形是否包含点:只要判断该点的横坐标和纵坐标是否夹在矩形的左右边和上下边之间 
//2.判断线段、折线、多边形是否在矩形中:因为矩形是个凸集,所以只要判断所有端点是否都在矩形中就可以了
//3.判断圆是否在矩形中:圆在矩形中的充要条件是:圆心在矩形中且圆的半径小于等于圆心到矩形四边的距离的最小值
struct rect {
    P A, B, C, D;//
    //已知矩形的三个顶点(a, b, c)(可以无序),计算第四个顶点d的坐标
    friend P rect4th(const P& a, const P& b, const P& c) {
        if (sgn(dot(c, a, b)) == 0) return a + b - c; //说明c点是直角拐角处
        if (sgn(dot(b, a, c)) == 0) return a + c - b; //说明b点是直角拐角处
        if (sgn(dot(a, c, b)) == 0) return c + b - a; //说明a点是直角拐角处
        return P(0, 0);//error
    }
};

//以下三角形相关
struct triangle {
    //三角形外接圆
    friend circle circumcircle(const P& a, const P& b, const P& c) { //三角形的外接圆
        circle C;
        double ab = dist(a,b), bc = dist(b,c), ac = dist(a,c),
               c1 = (sqr(a.x) + sqr(a.y) - sqr(b.x) - sqr(b.y)) / 2,
               c2 = (sqr(a.x) + sqr(a.y) - sqr(c.x) - sqr(c.y)) / 2;
        C.r = ab * bc * ac / (2 * fabs(cross(a, b, c)));
        C.o.x = (c1 * (a.y - c.y) - c2 * (a.y - b.y)) / ((a - b) * (a - c));
        C.o.y = (c1 * (a.x - c.x) - c2 * (a.x - b.x)) / ((a - c) * (a - b));
        return C;
    }//返回外接圆

    //三角形内切圆
    friend circle inscribedcircle(const P& a, const P& b, const P& c) { //三角形的内切圆
        circle C;
        double ab = dist(a,b), bc = dist(b,c), ac = dist(c,a);
        C.r = fabs(cross(a, b, c)) / (bc + ac + ab);//三角形内接圆的半径公式r = 2S/L
        C.o.x = (bc * a.x + ac * b.x + ab * c.x) / (bc + ac + ab);
        C.o.y = (bc * a.y + ac * b.y + ab * c.y) / (bc + ac + ab);
        return C;
    }//返回内切圆

    //三角形外心
    //三角形三条边的垂直平分线的交点,是外接圆的圆心
    //外心到三角形的三个顶点距离相等
    friend P circumcenter(const P& a, const P& b, const P& c) { //三角形外心
        line u, v;
        u.a = (a + b) / 2;
        u.b.x = u.a.x - a.y + b.y;
        u.b.y = u.a.y + a.x - b.x;
        v.a = (a + c) / 2;
        v.b.x = v.a.x - a.y + c.y;
        v.b.y = v.a.y + a.x - c.x;
        P p;
        intersection(u, v, p);
        return p;
    }

    //三角形内心
    //内心是三角形三条内角平分线的交点,是内切圆的圆心
    //内心到三边距离相等(为内切圆半径)
    friend P inscribedcenter(const P& a, const P& b, const P& c) {
        line u, v;
        double m, n;
        u.a = a;
        m = atan2(b.y - a.y, b.x - a.x);
        n = atan2(c.y - a.y, c.x - a.x);
        u.b.x = u.a.x + cos((m + n) / 2);
        u.b.y = u.a.y + sin((m + n) / 2);
        v.a = b;
        m = atan2(a.y - b.y, a.x - b.x);
        n = atan2(c.y - b.y, c.x - b.x);
        v.b.x = v.a.x + cos((m + n) / 2);
        v.b.y = v.a.y + sin((m + n) / 2);
        P p;
        intersection(u, v, p);
        return p;
    }

    //三角形垂心
    //三角形的三条高的交点叫做三角形的垂心
    //锐角三角形垂心在三角形内部
    //直角三角形垂心在三角形直角顶点
    //钝角三角形垂心在三角形外部
    friend P perpencenter(const P& a, const P& b, const P& c) {
        line u, v;
        u.a = c;
        u.b.x = u.a.x - a.y + b.y;
        u.b.y = u.a.y + a.x - b.x;
        v.a = b;
        v.b.x = v.a.x - a.y + c.y;
        v.b.y = v.a.y + a.x - c.x;
        P p;
        intersection(u, v, p);
        return p;
    }

    //三角形重心
    //三角形的三条中线相交的交点
    //到三角形三顶点距离的平方和最小的点
    //三角形内到三边距离之积最大的点
    //重心到顶点的距离与重心到对边中点的距离之比为2：1
    //重心和三角形3个顶点组成的3个三角形面积相等
    //重心和三角形3个顶点的连线的任意一条连线将三角形面积平分
    friend P barycenter(const P& a, const P& b, const P& c) {
        line u, v;
        u.a = (a + b) / 2;
        u.b = c;
        v.a = (a + c) / 2;
        v.b = b;
        P p;
        intersection(u, v, p);
        return p;
    }

    //三角形费马点
    //到三角形三顶点距离之和最小的点
    //(1)若三角形ABC的3个内角均小于120°，那么3条距离连线正好平分费马点所在的周角,故也称为三角形的等角中心。
    //三内角皆小于120°的三角形,分别以AB,BC,CA为边向三角形外侧做正三角形ABC1,ACB1,BCA1,
    //然后连接AA1,BB1,CC1,则三线交于一点P,则点P就是所求的费马点.
    //(2)若三角形有一内角不小于120度,则此钝角的顶点就是距离和最小的点。
    //(3)当△ABC为等边三角形时,此时外心与费马点重合
    friend P fermatpoint(const P& a, const P& b, const P& c) {
        //精度很差, 慎用!!!
        P u, v;
        double step = fabs(a.x) + fabs(a.y) + fabs(b.x) + fabs(b.y) + fabs(c.x) + fabs(c.y);
        u = (a + b + c) / 3;
        while (sgn(step) > 0) {
            for (int k = 0; k < 10; step /= 2, k++) {
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        v.x = u.x + step * i;
                        v.y = u.y + step * j;
                        if (dist(u, a) + dist(u, b) + dist(u, c) >
                            dist(v, a) + dist(v, b) + dist(v, c) )
                            u = v;
                    }
                }
            }
        }
        return u;
    }
};

//以下凸包相关
const int MAXN = 10001;

//逆时针排序
bool cmp(const P& p1, const P& p2) {
    return sgn(p1.y - p2.y) < 0 || (sgn(p1.y - p2.y) == 0 && sgn(p1.x - p2.x) < 0);
}

//极角排序
bool polarangle(const P& p1, const P& p2) {
    return sgn((p1 * p2)) >= 0;
}

struct polygon { //从0..n-1
    P p[MAXN], ch[MAXN];
    int n, num;//点数n及凸包中的点数num
    
    //凸包graham算法
    //对点集p求凸包，返回凸包点数，凸包存在ch中，凸包的点数存在num中，求得点集按逆时针排序
    int graham() {
        sort(p, p + n, cmp);
        if (n == 0) {num = 0; return 0;} ch[0] = p[0];
        if (n == 1) {num = 1; return 1;} ch[1] = p[1];
        if (n == 2) {num = 2; return 2;} ch[2] = p[2];
        int top = 1;
        for (int i = 2;i < n;i++) {
            while (top && sgn(cross(ch[top - 1], p[i], ch[top])) >= 0)
                top--;
            ch[++top] = p[i];
        }
        int len = top;
        ch[++top] = p[n - 2];
        for (int i = n - 3; i >= 0; i--) {
            while (top != len && sgn(cross(ch[top - 1], p[i], ch[top])) >= 0)
                top--;
            ch[++top] = p[i];
        }
        num = top;
        return top;//返回凸包中点的个数,点逆时针
    }
    
    //返回凸包面积
    double area() {
        double S = 0;
        for (int i = 1;i < num - 1;i++)
            S += cross(ch[0], ch[i], ch[i + 1]) / 2;
        return S;
    }
    
    //返回凸包周长
    double perimeter() {
        double L = 0;
        ch[num] = ch[0];
        for (int i = 0; i < num; i++)
            L += dist(ch[i], ch[i + 1]);
        return L;
    }
    
    //O(n)返回凸包直径
    //利用旋转卡壳O(n)求平面点集上的最远点对
    double diameter() {
        int top = 1;
        double d = 0;
        ch[num] = ch[0];
        for (int i = 0; i < num; i++) {
            while (sgn(cross(ch[i], ch[i + 1], ch[top + 1]) - cross(ch[i], ch[i + 1], ch[top])) > 0)
                top = (top + 1) % num;
            d = max(d, dist(ch[i], ch[top]));
            d = max(d, dist(ch[i + 1], ch[top + 1]));//处理平行边
        }
        return d;
    }
    
    //凸多边形重心
    P gravitycenter() {
        double area = 0;
        P g;
        for (int i = 0; i < num; i++) {
            area += (ch[i] * ch[(i + 1) % num]) / 2;
            g.x += (ch[i] * ch[(i + 1) % num]) * (ch[i].x + ch[(i + 1) % num].x);
            g.y += (ch[i] * ch[(i + 1) % num]) * (ch[i].y + ch[(i + 1) % num].y);
        }
        //注意area不为0
        g.x /= 6 * area;
        g.y /= 6 * area;
        return g;
    }
    
    //O(n)判断点是否在凸多边形内
    //凸多边形内的点三角剖分后面积和等于凸多边形面积和
    friend bool inconvex(P& p, polygon& ch) {
        double area = 0;
        ch.ch[ch.num] = ch.ch[0];
        for (int i = 0; i < ch.num; i++)
            area += fabs(cross(p, ch.ch[i], ch.ch[i + 1]));
        area /= 2;
        return sgn(area - ch.area()) == 0;
    }
    
    //O(logn)判断点是否在凸多边形内
    //注意是否为凸多边形以及点数小于3时是否要特殊考虑
    friend bool inconvex2(P p, P ch[], int n) {
        P p1  = ch[0], p2 = ch[1];
        for (int i = n - 1; sgn(cross(ch[0], ch[1], ch[i])) == 0; i--)
            p1 = ch[i];
        for (int i = 2; sgn(cross(ch[0], ch[1], ch[i])) == 0; i++)
            p2 = ch[i];
        double sign = sgn(cross(p1, p2, p));
        if (sign < 0) return false;
        if (sign == 0) return sgn(dot(p, p1, p2)) <= 0;
        int l = 1, r = n - 1;
        while (l != r) {
            int mid = (l + r + 1) / 2;
            if (sgn(cross(ch[0], ch[mid], p)) >= 0) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        if (l == n - 1)
            return sgn(cross(p, ch[0], ch[l])) == 0 && dot(p, ch[0], ch[l]) <= 0;
        return sgn(cross(p, ch[l], ch[l + 1])) >= 0;
    }

    //O(n^2)凸多边形1、2交出凸多边形3
    friend void intersection(polygon& CH1, polygon& CH2, polygon &CH3) {
        CH1.ch[CH1.num] = CH1.ch[0];
        CH2.ch[CH2.num] = CH2.ch[0];
        CH3.n = 0;
        P inter;
        for (int i = 0; i < CH1.num; i++) {
            int cnt = 0;
            //插入凸包1上的线段与凸包2上的线段的交点
            for (int j = 0; j < CH2.num && cnt < 2; j++) {
                int num = intersection(seg(CH1.ch[i], CH1.ch[i + 1]), seg(CH2.ch[j], CH2.ch[j + 1]),inter);
                if (num == 6) {//线段重合
                    CH3.p[CH3.n++] = CH1.ch[i];
                    CH3.p[CH3.n++] = CH1.ch[i + 1];
                    cnt += 2;
                }
                else if (num) {//有交点
                    CH3.p[CH3.n++] = inter;
                    cnt++;
                }
            }
            //插入凸包1上的在凸包2内的点
            if (inconvex2(CH1.ch[i], CH2.ch, CH2.num))
                CH3.p[CH3.n++] = CH1.ch[i];
            if (inconvex2(CH1.ch[i + 1], CH2.ch, CH2.num))
                CH3.p[CH3.n++] = CH1.ch[i + 1];
        }
        //插入凸包2上的在凸包1内的点
        for (int i = 0; i < CH2.num; i++) {
            if (inconvex2(CH2.ch[i], CH1.ch, CH1.num))
                CH3.p[CH3.n++] = CH2.ch[i];
            if (inconvex2(CH2.ch[i + 1], CH1.ch, CH1.num))
                CH3.p[CH3.n++] = CH2.ch[i + 1];
        }
    }
}CH;

//以下旋转卡壳相关
struct rotatecalipers {
    //O(n)求凸多边形的直径
    //可以用于对普通点集求最远距离：先求点集凸包，再调用此函数
    double convexdiameter(P ch[], int n) {
        double miny = 1e20, maxy = -1e20;
        int p, q, nextp, nextq;
        for (int i = 0; i < n; i++) {
            if (miny > ch[i].y) {
                miny = ch[i].y;
                p = i;
            }
            if (maxy < ch[i].y) {
                maxy = ch[i].y;
                q = i;
            }
        }
        double d = dist(ch[q], ch[p]);
        for (int i = 0; i <= n; i++) { //是等号=
            nextp = (p + 1) % n;
            nextq = (q + 1) % n;
            int sign = sgn((ch[nextp] - ch[p]) * (ch[nextq] - ch[q]));
            if (sign < 0) {
                p = nextp;
                d = max(d, dist(ch[p], ch[q]));
            }
            else if (sign > 0) {
                q = nextq;
                d = max(d, dist(ch[p], ch[q]));
            }
            else {
                d = max(d, dist(ch[p], ch[nextq]));
                d = max(d, dist(ch[nextp], ch[q]));
                d = max(d,dist(ch[nextp], ch[nextq]));
                p = nextp;
                q = nextq;
            }
        }
        return d;
    }
    
    //O(n)求两个凸多边形的最短距离
    double mintwoconvexdist(P ch1[], int n, P ch2[], int m) {
        double miny = 1e20, maxy = -1e20;
        int p, q, nextp, nextq;
        for (int i = 0; i < n; i++) {
            if (ch1[i].y < miny) {
                miny = ch1[i].y;
                p = i;
            }
        }
        for (int i = 0; i < m; i++) {
            if (ch2[i].y > maxy) {
                maxy = ch2[i].y;
                q = i;
            }
        }
        double d = dist(ch1[p], ch2[q]);
        for (int i = 0; i <= n + m; i++) { //是等号=
            nextp = (p + 1) % n;
            nextq = (q + 1) % m;
            int sign = sgn((ch1[nextp] - ch1[p]) * (ch2[nextq] - ch2[q]));
            if (sign < 0) {
                seg s(ch1[p], ch1[nextp]);
                p = nextp;
                d = min(d, dist(ch2[q], s));
            } else if (sign > 0) {
                seg s(ch2[q], ch2[nextq]);
                q = nextq;
                d = min(d, dist(ch1[p], s));
            } else {
                seg s(ch1[p], ch1[nextp]);
                d = min(d, dist(ch2[q], s));
                d = min(d, dist(ch2[nextq], s));
                s = seg(ch2[q], ch2[nextq]);
                d = min(d, dist(ch1[p], s));
                d = min(d, dist(ch1[nextp], s));
                p = nextp;
                q = nextq;
            }
        }
        return d;
    }

    //O(n)求最大面积三角形
    double maxtrianglearea(P ch[], int n) {
        if (n < 3) return 0;
        double S = 0, area, prev;
        ch[n] = ch[0];
        for (int i = 0; i < n; i++) {
            int j = i + 1, k = j + 1;
            if (k >= n) break;
            prev = 0;
            while (j < n - 1) {
                area = cross(ch[i], ch[j], ch[k]);
                while (k < n - 1) {
                    if (sgn(cross(ch[i], ch[j], ch[k + 1]) - area) > 0) {
                        area = cross(ch[i], ch[j], ch[k + 1]);
                        k++;
                    } else {
                        break;
                    }
                }
                if (area < prev) break;
                prev = area;
                S = max(S, area);
                j++;
                if (j >= k) {
                    k = j + 1;
                    if (k >= n) break;
                }
            }
        }
        return S / 2;
    }
}G;

//以下是常用函数

//O(n)判点在任意多边形内,顶点按顺时针或逆时针给出
//修改参数on_edge可以判断点是否在多边形上, offset为多边形坐标上限
int inpolygon(const P& q, int n, P p[], int on_edge = 1) {
    P q2;
    p[n] = p[0];
    int cnt;
    double offset = 1e4 + 4;
    for (int i = 0; i < n; ) {
        for (cnt = i = 0, q2.x = rand() + offset, q2.y = rand() + offset; i < n; i++) {
            if (sgn(cross(q, p[i], p[i + 1])) == 0
                    && sgn((p[i].x - q.x) * (p[i + 1].x - q.x)) <= 0
                    && sgn((p[i].y - q.y) * (p[i + 1].y - q.y)) <= 0) {
                return on_edge;
            } else if (sgn(cross(q, q2, p[i])) == 0) {
                break;
            } else if (sgn(cross(q, p[i], q2) * cross(q, p[i + 1], q2)) < 0
                       && sgn(cross(p[i], q, p[i + 1]) * cross(p[i], q2, p[i + 1])) < 0) {
                cnt++;
            }
        }
    }
    return cnt & 1;
}

//counterclockwise 可以判别三点关系
int ccw(const P& a, const P& b, const P& c) {
    if (sgn((b - a) * (c - a)) > 0) return 1;         //顺时针
    if (sgn((b - a) * (c - a)) < 0) return -1;        //逆时针
    if (sgn((b - a) ^ (c - a)) < 0) return +2;        //c--a--b共线
    if (sgn((b - a).len() < (c - a).len())) return -2;//a--b--c共线
    return 0;                                          //a--c--b共线
}

//求向量v的极角，角度范围为 [0,2*pi)
double angle(const P& v) {
    double t = atan2(v.y, v.x);
    return sgn(t) >= 0 ? t : t + 2 * pi;
}

//求两向量之间的夹角[0,pi] , 乘以cross(a,b)后便成了有向夹角。
double angle(const P& a, const P& b) {
    return acos((a ^ b) / sqrt(sqr(a.len()) * sqr(b.len())));
    //return (a * b > 0) * (acos(a ^ b / sqrt(sqr(a.len()) * sqr(b.len()));)
}

// 角度修正函数，根据不同的题目有不同写法和功能
void fixangle(double & rad) { //默认转化到(-pi,pi]
    if (sgn(rad - pi) > 0) rad -= 2 * pi;
    if (sgn(rad + pi) < 0) rad += 2 * pi;
}

//将弧度角规范化到[0,2 * pi)
double adjust(double d) {
    d = fmod(d, 2 * pi);
    if (d < 0)
        d += 2 * pi;
    return d;
}

//计算∠bac余弦值 如果想从余弦求夹角的话,注意反余弦函数的定义域是从0到pi 
double cos(const P& a, const P& b, const P& c) { //计算角bac余弦值
    double ab = dist(a, b), ac = dist(a, c), bc = dist(b, c);
    return (sqr(ab) + sqr(ac) + sqr(bc)) / (2 * ab * ac);
    //return (b - a) ^ (c - a) / (dist(a, b) * dist(a, c));
}

//返回顶点在a,起始边为ab,终止边为ac的夹角(弧度)
//角度小于pi,返回正值 角度大于pi返回负值 可以用于求线段之间的夹角
//r = cross(o,a,b) / (dist(o,a) * dist(o,b))
//r' = cross(o,a,b)
//r >= 1 angle = 0;
//r <= -1 angle = -pi;
//-1 < r < 1 && r' > 0 angle = acos(r);
//-1 < r < 1 && r' <= 0 angle = -acos(r);
double angle(const P& o, const P& a, const P& b) { //夹角aob的弧度
    double C = (a - o) ^ (b - o) / (dist(o, a) * dist(o, b));
    if (sgn(C - 1) >= 0) return 0;
    if (sgn(C + 1) <= 0) return -pi;
    if (sgn((a - o) * (b - o)) > 0) return acos(C);//oa在ob顺时针方向
    return -acos(C);
}

//求多边形面积 可凹可凸
double area(P p[], int n) { //求多边形面积逆时针正 顺时针负
    double S = 0;
    for (int i = 0; i < n; i++)
        S += p[i] * p[(i + 1) % n];
    return S / 2;
}

//判断顶点是否按逆时针排列
bool isanticlockwise(P p[], int n) { //如果输入顶点按逆时针排列,返回true 
    return area(p, n) > 0; 
}

//判断是否为简单多边形
bool issimple(P p[], int n) { //判断是否为简单多边形
    P t;
    seg s1, s2;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i - 2; j++) {
            s1.a = p[i], s1.b = p[i - 1];
            s2.a = p[j], s2.b = p[j + 1];
            if (intersection(s1, s2, t)) return 0;
        }
    }
    s2.a = p[0], s2.b = p[n - 1];
    for (int i = 1; i < n - 2; i++) {
        s1.a = p[i], s1.b = p[i + 1];
        if (intersection(s1, s2, t)) return 0;
    }
    return 1;
}

//已知入射线和镜面,求镜面反射线.
//mirror为镜面直线方程(a x + b y + c = 0 ,下同)系数;
//light为入射光直线方程系数;
//返回反射光直线方程系数.
//光有方向,使用时注意:入射光向量:<-light.b,light.a>；反射光向量:<ret.b,-ret.a>.
//不要忘记结果中可能会有"negative zeros-0.000"
L reflect(const L& mirror, const L& light) { 
    double b = mirror.b * light.b + mirror.a * light.a,
           a = light.a * mirror.b - mirror.a * light.b;
    double m = (b * mirror.b + a * mirror.a) / (sqr(mirror.a) + sqr(mirror.b)),
           n = (a * mirror.b - b * mirror.a) / (sqr(mirror.a) + sqr(mirror.b));
    if (sgn(mirror.a * light.b - light.a * mirror.b - 1e-20) == 0) //平行
        return light;
    P p;//p是入射线与镜面的交点
    p.x = (mirror.b * light.c - light.b * mirror.c) / (mirror.a * light.b - light.a * mirror.b);
    p.y = (light.a * mirror.c - mirror.a * light.c) / (mirror.a * light.b - light.a * mirror.b);
    return L(n, -m, m * p.y - p.x * n);
}

//判断2个共线向量是否同向
bool samedir(const P& a, const P& b) {
    return sgn(a ^ b) > 0;
}

//光的折射
//传入入射光线，界面直线方程 折射率
//返回是否折射，成功折射返回1，折射光线在l1中，发生全反射返回0
int refraction(line l0, line lp, line &l1, double u) { //入射光线 界面 折射光线 折射率
    P v = l0.b - l0.a, v2, p, o; //入射向量 折射向量
    P vs = (lp.b - lp.a).turn_left(); //法线
    if (!samedir(v, vs)) {
        vs = vs.turn_left().turn_left();
    }
    intersection(l0, lp, p);
    double th = angle(v, vs);
    if (sgn(sin(th) / u - 1) > 0 || sgn(sin(th) / u + 1) < 0) //全反射
        return 0;
    double th2 = asin(sin(th) / u);
    if (sgn(vs * v) >= 0) {
        v2 = vs.rotate(th2, o);
    } else {
        v2 = vs.rotate(-th2, o);
    }
    l1.a = p;
    l1.b = p + v2;
    return 1;
}

//光的反射
//传入平面l及入射点p和方向向量d，返回新p和新d
//返回1表示成功反射，0表示与反射面不相交或相切
int reflection(P& p, P& d, line& l) {
    if (sgn(d * (l.a - l.b)) == 0) return 0;
    line k(p, p + d);
    P x;
    intersection(k, l, x);
    k.a = x, k.b = (l.a - l.b).turn_left() + x;
    double th = atan2(l.a.y - l.b.y, l.a.x - l.b.x);
    th += th - atan2(d.y, d.x);
    p = x;
    d.x = cos(th), d.y = sin(th);
    return 1;
}

//求多边形的重心 可凹可凸
//三角形的重心是中线的交点 平行四边形的重心是对角线的交点
//需要点逆时针(凹的不能直接排序)
P gravitycenter(P p[], int n) {
    double area = 0;
    P g;
    for (int i = 0; i < n; i++) {
        area += (p[i] * p[(i + 1) % n]) / 2;
        g.x += (p[i] * p[(i + 1) % n]) * (p[i].x + p[(i + 1) % n].x);
        g.y += (p[i] * p[(i + 1) % n]) * (p[i].y + p[(i + 1) % n].y);
    }
    //注意area不为0
    g.x /= 6 * area;
    g.y /= 6 * area;
    return g;
}

//传入一个凸多边形以及一条端点不在凸多边形内的直线，传出两个被割开的凸多边形
void cut(const line& li, P p[], int n, P l[], int& ln, P r[], int& rn) {
    ln = rn = 0;
    for (int i = 0; i < n; i++) {
        int sign = sgn((p[i] - li.a) * (li.b - li.a));
        if (sign >= 0) l[ln++] = p[i];
        if (sign <= 0) r[rn++] = p[i];
        P t;
        int flag = intersection(li, line(p[i], p[(i + 1) % n]), t);
        if (flag == 1 && onseg(t, line(p[i], p[(i + 1) % n]))) {//注意要包含端点！
            l[ln++] = r[rn++] = t;
        }
    }
}

//给定凸多边形外一点，求在该点能将凸多边形切割成面积相等的两部分的方向向量
//传入一个凸多边形以及多边形外一点，返回方向向量 复杂度O(NlogN)
P find_equal(P p[], int n, P o) {
    for (int i = 0; i < n; i++) {//先将基准点平移到原点
        p[i].x -= o.x;
        p[i].y -= o.y;
    }
    o = P(0.0, 0.0);
    P* all = new P[n], *ll = new P[n], *rr = new P[n];
    int ln, rn;
    for (int i = 0; i < n; i++) all[i] = p[i];
    sort(all, all + n, polarangle);
    double l = 1e100, r = -1e100;
    l = angle(all[0]), r = angle(all[n - 1]);
    if (l > r) r += 2 * pi;
    while (sgn(r - l) > 0) {
        double mid = (l + r) / 2;
        line li(o, P(cos(mid), sin(mid)));
        cut(li, p, n, ll, ln, rr, rn);
        if (sgn(area(ll, ln) - area(rr, rn)) < 0) {
            l = mid;
        } else {
            r = mid;
        }
    }
    delete all; delete ll; delete rr;
    return P(cos(l), sin(l));
}

//主函数   
int main() {
    seg s1(P(2,2), P(3,4));
    seg s2 = left(s1, 1);
    s2.out();
    //待写：点在多边形内，线段在多边形内，半平面交
}

/*
公式: 
球坐标公式: 
直角坐标为 P(x, y, z) 时,对应的球坐标是(rsinφcosθ, rsinφsinθ, rcosφ),
其中φ是向量OP与Z轴的夹角,范围[0,π];是OP在XOY面上的投影到X轴的旋角,范围[0,2π] 
直线的一般方程转化成向量方程: 
ax+by+c=0 
 x-x0    y-y0 
----- = ------ // (x0,y0)为直线上一点,m,n为向量 
  m       n 
转换关系: 
a=n;b=-m;c=m*y0-n*x0; 
m=-b;n=a; 

三点平面方程:
三点为P1, P2, P3 
设向量  M1=P2-P1; M2=P3-P1; 
平面法向量:M=M1 x M2
平面方程:M.i(x-P1.x)+M.j(y-P1.y)+M.k(z-P1.z)=0

经纬度
假设地球是球体， 
设地球上某点的经度为lambda,纬度为phi， 
则这点的空间坐标是 
x = cos(phi)*cos(lambda) 
y = cos(phi)*sin(lambda) 
z = sin(phi) 
设地球上两点的空间坐标分别为(x1,y1,z1),(x2,y2,z2) 
直线距离即为R*sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1)),
则它们的夹角为A = acos(x1 * x2 + y1 * y2 + z1 * z2)
球面距离为 A*R/2(R 即地球半径6378.0)
扇形的重心Xc = 2*R*sinA/3/A A为圆心角的一半
*/

/*
   ㈠   点的基本运算 done
  1.平面上两点之间距离 1 done
  2.判断两点是否重合     1 done
  3.矢量叉乘 1 done
  4.矢量点乘 2 done
  5.判断点是否在线段上 2 done
  6.求一点饶某点旋转后的坐标 2 done
  7.求矢量夹角 2 done

  ㈡   线段及直线的基本运算
  1.点与线段的关系 3
  2.求点到线段所在直线垂线的垂足 4
  3.点到线段的最近点 4
  4.点到线段所在直线的距离 4
  5.点到折线集的最近距离 4
  6.判断圆是否在多边形内 5
  7.求矢量夹角余弦 5
  8.求线段之间的夹角 5
  9.判断线段是否相交 6
  10.判断线段是否相交但不交在端点处 6
  11.求线段所在直线的方程 6
  12.求直线的斜率 7
  13.求直线的倾斜角 7
  14.求点关于某直线的对称点 7
  15.判断两条直线是否相交及求直线交点 7
  16.判断线段是否相交,如果相交返回交点 7

  ㈢   多边形常用算法模块
  1.判断多边形是否简单多边形 8
  2.检查多边形顶点的凸凹性 9
  3.判断多边形是否凸多边形 9
  4.求多边形面积 9
  5.判断多边形顶点的排列方向,方法一 10
  6.判断多边形顶点的排列方向,方法二 10
  7.射线法判断点是否在多边形内 10
  8.判断点是否在凸多边形内 11
  9.寻找点集的graham算法 12
  10.寻找点集凸包的卷包裹法 13
  11.判断线段是否在多边形内 14
  12.求简单多边形的重心 15
  13.求凸多边形的重心 17
  14.求肯定在给定多边形内的一个点 17
  15.求从多边形外一点出发到该多边形的切线 18
  16.判断多边形的核是否存在 19

  ㈣   圆的基本运算
  1   .点是否在圆内 20
  2   .求不共线的三点所确定的圆 21

  ㈤   矩形的基本运算
  1.已知矩形三点坐标,求第4点坐标 22

  ㈥   常用算法的描述 22

  ㈦   补充
  1．两圆关系: 24
  2．判断圆是否在矩形内: 24
  3．点到平面的距离: 25
  4．点是否在直线同侧: 25
  5．镜面反射线: 25
  6．矩形包含: 26
  7．两圆交点: 27
  8．两圆公共面积: 28
  9.圆和直线关系: 29
  10.内切圆: 30
  11.求切点: 31
  12.线段的左右旋: 31
  13．公式: 32   
*/
