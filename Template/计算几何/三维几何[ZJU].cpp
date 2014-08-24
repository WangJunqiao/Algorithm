﻿//三维几何函数库
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
struct point3 {
    double x, y, z;
};
struct line3 {
    point3 a, b;
};
struct plane3 {
    point3 a, b, c;
};
struct planef {
    double a, b, c, d;
}; // ax+by+cz+d=0
//平方
inline double sqr(double d) {
    return d*d;
}
//计算cross product U x V
point3 xmult(point3 u, point3 v) {
    point3 ret;
    ret.x = u.y * v.z - v.y * u.z;
    ret.y = u.z * v.x - u.x * v.z;
    ret.z = u.x * v.y - u.y * v.x;
    return ret;
}
//计算dot product U . V
double dmult(point3 u, point3 v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
}
//矢量差 U - V
point3 subt(point3 u, point3 v) {
    point3 ret;
    ret.x = u.x - v.x;
    ret.y = u.y - v.y;
    ret.z = u.z - v.z;
    return ret;
}
//取平面法向量
point3 pvec(plane3 s) {
    return xmult(subt(s.a, s.b), subt(s.b, s.c));
}
point3 pvec(point3 s1, point3 s2, point3 s3) {
    return xmult(subt(s1, s2), subt(s2, s3));
}
point3 pvec(planef p) {
    point3 ret;
    ret.x = p.a;
    ret.y = p.b;
    ret.z = p.c;
    return ret;
}
//两点距离,单参数取向量大小
double dist(point3 p1, point3 p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z));
}
//向量大小
double vlen(point3 p) {
    return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
}
double sqrlen(point3 p) {
    return dmult(p, p);
}
//判三点共线
int dots_inline(point3 p1, point3 p2, point3 p3) {
    return sqrlen(xmult(subt(p1, p2), subt(p2, p3))) < eps;
}
//判四点共面
int dots_onplane(point3 a, point3 b, point3 c, point3 d) {
    return zero(dmult(pvec(a, b, c), subt(d, a)));
}
//判点是否在线段上,包括端点和共线
int dot_online_in(point3 p, line3 l) {
    return zero(sqrlen(xmult(subt(p, l.a), subt(p, l.b)))) && (l.a.x - p.x)*(l.b.x - p.x) < eps &&
           (l.a.y - p.y)*(l.b.y - p.y) < eps && (l.a.z - p.z)*(l.b.z - p.z) < eps;
}
int dot_online_in(point3 p, point3 l1, point3 l2) {
    return zero(sqrlen(xmult(subt(p, l1), subt(p, l2)))) && (l1.x - p.x)*(l2.x - p.x) < eps &&
           (l1.y - p.y)*(l2.y - p.y) < eps && (l1.z - p.z)*(l2.z - p.z) < eps;
}
//判点是否在线段上,不包括端点
int dot_online_ex(point3 p, line3 l) {
    return dot_online_in(p, l) && (!zero(p.x - l.a.x) || !zero(p.y - l.a.y) || !zero(p.z - l.a.z)) &&
           (!zero(p.x - l.b.x) || !zero(p.y - l.b.y) || !zero(p.z - l.b.z));
}
int dot_online_ex(point3 p, point3 l1, point3 l2) {
    return dot_online_in(p, l1, l2) && (!zero(p.x - l1.x) || !zero(p.y - l1.y) || !zero(p.z - l1.z)) &&
           (!zero(p.x - l2.x) || !zero(p.y - l2.y) || !zero(p.z - l2.z));
}
//判点是否在空间三角形上,包括边界,三点共线无意义
int dot_inplane_in(point3 p, plane3 s) {
    return zero(vlen(xmult(subt(s.a, s.b), subt(s.a, s.c))) - vlen(xmult(subt(p, s.a), subt(p, s.b))) - vlen(xmult(subt(p, s.b), subt(p, s.c))) - vlen(xmult(subt(p, s.c), subt(p, s.a))));
}
int dot_inplane_in(point3 p, point3 s1, point3 s2, point3 s3) {
    return zero(vlen(xmult(subt(s1, s2), subt(s1, s3))) - vlen(xmult(subt(p, s1), subt(p, s2))) -
                vlen(xmult(subt(p, s2), subt(p, s3))) - vlen(xmult(subt(p, s3), subt(p, s1))));
}
//判点是否在空间三角形上,不包括边界,三点共线无意义
int dot_inplane_ex(point3 p, plane3 s) {
    return dot_inplane_in(p, s) && sqrlen(xmult(subt(p, s.a), subt(p, s.b))) > eps && sqrlen(xmult(subt(p, s.b), subt(p, s.c))) > eps && sqrlen(xmult(subt(p, s.c), subt(p, s.a))) > eps;
}
int dot_inplane_ex(point3 p, point3 s1, point3 s2, point3 s3) {
    return dot_inplane_in(p, s1, s2, s3) && sqrlen(xmult(subt(p, s1), subt(p, s2))) > eps && sqrlen(xmult(subt(p, s2), subt(p, s3))) > eps && sqrlen(xmult(subt(p, s3), subt(p, s1))) > eps;
}
//判两点在线段同侧,点在线段上返回0,不共面无意义
int same_side(point3 p1, point3 p2, line3 l) {
    return dmult(xmult(subt(l.a, l.b), subt(p1, l.b)), xmult(subt(l.a, l.b), subt(p2, l.b))) > eps;
}
int same_side(point3 p1, point3 p2, point3 l1, point3 l2) {
    return dmult(xmult(subt(l1, l2), subt(p1, l2)), xmult(subt(l1, l2), subt(p2, l2))) > eps;
}
//判两点在线段异侧,点在线段上返回0,不共面无意义
int opposite_side(point3 p1, point3 p2, line3 l) {
    return dmult(xmult(subt(l.a, l.b), subt(p1, l.b)), xmult(subt(l.a, l.b), subt(p2, l.b))) < -eps;
}
int opposite_side(point3 p1, point3 p2, point3 l1, point3 l2) {
    return dmult(xmult(subt(l1, l2), subt(p1, l2)), xmult(subt(l1, l2), subt(p2, l2))) < -eps;
}
//判两点在平面同侧,点在平面上返回0
int same_side(point3 p1, point3 p2, plane3 s) {
    return dmult(pvec(s), subt(p1, s.a))*dmult(pvec(s), subt(p2, s.a)) > eps;
}
int same_side(point3 p1, point3 p2, point3 s1, point3 s2, point3 s3) {
    return dmult(pvec(s1, s2, s3), subt(p1, s1))*dmult(pvec(s1, s2, s3), subt(p2, s1)) > eps;
}
int same_side(point3 p1, point3 p2, planef s) {
    return (s.a*p1.x + s.b*p1.y + s.c*p1.z + s.d)*(s.a*p2.x + s.b*p2.y + s.c*p2.z + s.d) > eps;
}
//判两点在平面异侧,点在平面上返回0
int opposite_side(point3 p1, point3 p2, plane3 s) {
    return dmult(pvec(s), subt(p1, s.a))*dmult(pvec(s), subt(p2, s.a)) < -eps;
}
int opposite_side(point3 p1, point3 p2, point3 s1, point3 s2, point3 s3) {
    return dmult(pvec(s1, s2, s3), subt(p1, s1))*dmult(pvec(s1, s2, s3), subt(p2, s1)) < -eps;
}
int opposite_side(point3 p1, point3 p2, planef s) {
    return (s.a*p1.x + s.b*p1.y + s.c*p1.z + s.d)*(s.a*p2.x + s.b*p2.y + s.c*p2.z + s.d) < -eps;
}
//判两直线平行
int parallel(line3 u, line3 v) {
    return sqrlen(xmult(subt(u.a, u.b), subt(v.a, v.b))) < eps;
}
int parallel(point3 u1, point3 u2, point3 v1, point3 v2) {
    return sqrlen(xmult(subt(u1, u2), subt(v1, v2))) < eps;
}
//判两平面平行
int parallel(plane3 u, plane3 v) {
    return sqrlen(xmult(pvec(u), pvec(v))) < eps;
}
int parallel(point3 u1, point3 u2, point3 u3, point3 v1, point3 v2, point3 v3) {
    return sqrlen(xmult(pvec(u1, u2, u3), pvec(v1, v2, v3))) < eps;
}
int parallel(planef u, planef v) {
    return sqrlen(xmult(pvec(u), pvec(v))) < eps;
}
//判直线与平面平行
int parallel(line3 l, plane3 s) {
    return zero(dmult(subt(l.a, l.b), pvec(s)));
}
int parallel(point3 l1, point3 l2, point3 s1, point3 s2, point3 s3) {
    return zero(dmult(subt(l1, l2), pvec(s1, s2, s3)));
}
int parellel(line3 l, planef s) {
    return zero(dmult(subt(l.a, l.b), pvec(s)));
}
//判两直线垂直
int perpendicular(line3 u, line3 v) {
    return zero(dmult(subt(u.a, u.b), subt(v.a, v.b)));
}
int perpendicular(point3 u1, point3 u2, point3 v1, point3 v2) {
    return zero(dmult(subt(u1, u2), subt(v1, v2)));
}
//判两平面垂直
int perpendicular(plane3 u, plane3 v) {
    return zero(dmult(pvec(u), pvec(v)));
}
int perpendicular(point3 u1, point3 u2, point3 u3, point3 v1, point3 v2, point3 v3) {
    return zero(dmult(pvec(u1, u2, u3), pvec(v1, v2, v3)));
}
int perpendicular(planef u, planef v) {
    return zero(dmult(pvec(u), pvec(v)));
}
//判直线与平面垂直
int perpendicular(line3 l, plane3 s) {
    return sqrlen(xmult(subt(l.a, l.b), pvec(s))) < eps;
}
int perpendicular(point3 l1, point3 l2, point3 s1, point3 s2, point3 s3) {
    return sqrlen(xmult(subt(l1, l2), pvec(s1, s2, s3))) < eps;
}

int perpendicular(line3 l, planef s) {
    return sqrlen(xmult(subt(l.a, l.b), pvec(s))) < eps;
}
//判两线段相交,包括端点和部分重合
int intersect_in(line3 u, line3 v) {
    if (!dots_onplane(u.a, u.b, v.a, v.b))
        return 0;
    if (!dots_inline(u.a, u.b, v.a) || !dots_inline(u.a, u.b, v.b))
        return !same_side(u.a, u.b, v) && !same_side(v.a, v.b, u);
    return dot_online_in(u.a, v) || dot_online_in(u.b, v) || dot_online_in(v.a, u) || dot_online_in(v.b, u);
}
int intersect_in(point3 u1, point3 u2, point3 v1, point3 v2) {
    if (!dots_onplane(u1, u2, v1, v2))
        return 0;
    if (!dots_inline(u1, u2, v1) || !dots_inline(u1, u2, v2))
        return !same_side(u1, u2, v1, v2) && !same_side(v1, v2, u1, u2);
    return dot_online_in(u1, v1, v2) || dot_online_in(u2, v1, v2) || dot_online_in(v1, u1, u2) || dot_online_in(v2, u1, u2);
}

//判两线段相交,不包括端点和部分重合
int intersect_ex(line3 u, line3 v) {
    return dots_onplane(u.a, u.b, v.a, v.b) && opposite_side(u.a, u.b, v) && opposite_side(v.a, v.b, u);
}
int intersect_ex(point3 u1, point3 u2, point3 v1, point3 v2) {
    return dots_onplane(u1, u2, v1, v2) && opposite_side(u1, u2, v1, v2) && opposite_side(v1, v2, u1, u2);
}

//判线段与空间三角形相交,包括交于边界和(部分)包含
int intersect_in(line3 l, plane3 s) {
    return !same_side(l.a, l.b, s) && !same_side(s.a, s.b, l.a, l.b, s.c) &&
           !same_side(s.b, s.c, l.a, l.b, s.a) && !same_side(s.c, s.a, l.a, l.b, s.b);
}
int intersect_in(point3 l1, point3 l2, point3 s1, point3 s2, point3 s3) {
    return !same_side(l1, l2, s1, s2, s3) && !same_side(s1, s2, l1, l2, s3) &&
           !same_side(s2, s3, l1, l2, s1) && !same_side(s3, s1, l1, l2, s2);
}

//判线段与空间三角形相交,不包括交于边界和(部分)包含
int intersect_ex(line3 l, plane3 s) {
    return opposite_side(l.a, l.b, s) && opposite_side(s.a, s.b, l.a, l.b, s.c) &&
           opposite_side(s.b, s.c, l.a, l.b, s.a) && opposite_side(s.c, s.a, l.a, l.b, s.b);
}
int intersect_ex(point3 l1, point3 l2, point3 s1, point3 s2, point3 s3) {
    return opposite_side(l1, l2, s1, s2, s3) && opposite_side(s1, s2, l1, l2, s3) &&
           opposite_side(s2, s3, l1, l2, s1) && opposite_side(s3, s1, l1, l2, s2);
}

//计算两直线交点,注意事先判断直线是否共面和平行!
//线段交点请另外判线段相交(同时还是要判断是否平行!)
point3 intersection(line3 u, line3 v) {
    point3 ret = u.a;
    double t = xmult(subt(u.a, v.a), subt(v.a, v.b)) / xmult(subt(u.a, u.b), subt(v.a, v.b));
    ret.x += (u.b.x - u.a.x) * t;
    ret.y += (u.b.y - u.a.y) * t;
    ret.z += (u.b.z - u.a.z) * t;
    return ret;
}
point3 intersection(point3 u1, point3 u2, point3 v1, point3 v2) {
    point3 ret = u1;
    double t = xmult(subt(u1, v1), subt(v1, v2)) / xmult(subt(u1, u2), subt(v1, v2));
    ret.x += (u2.x - u1.x) * t;
    ret.y += (u2.y - u1.y) * t;
    ret.z += (u2.z - u1.z) * t;
    return ret;
}
//计算直线与平面交点,注意事先判断是否平行,并保证三点不共线!
//线段和空间三角形交点请另外判断
point3 intersection(line3 l, plane3 s) {
    point3 ret = pvec(s);
    double t = dmult(ret, subt(s.a, l.a)) / dmult(ret, subt(l.b, l.a));
    ret.x = l.a.x + (l.b.x - l.a.x) * t;
    ret.y = l.a.y + (l.b.y - l.a.y) * t;
    ret.z = l.a.z + (l.b.z - l.a.z) * t;
    return ret;
}
point3 intersection(point3 l1, point3 l2, point3 s1, point3 s2, point3 s3) {
    point3 ret = pvec(s1, s2, s3);
    double t = dmult(ret, subt(s1, l1)) / dmult(ret, subt(l2, l1));
    ret.x = l1.x + (l2.x - l1.x) * t;
    ret.y = l1.y + (l2.y - l1.y) * t;
    ret.z = l1.z + (l2.z - l1.z) * t;
    return ret;
}
point3 intersection(line3 l, planef s) {
    point3 ret = subt(l.b, l.a);
    double t = -(dmult(pvec(s), l.a) + s.d) / (dmult(pvec(s), ret));
    ret.x = ret.x * t + l.a.x;
    ret.y = ret.y * t + l.a.y;
    ret.z = ret.z * t + l.a.z;
    return ret;
}
//计算两平面交线,注意事先判断是否平行,并保证三点不共线!
line3 intersection(plane3 u, plane3 v) {
    line3 ret;
    ret.a = parallel(v.a, v.b, u.a, u.b, u.c) ? intersection(v.b, v.c, u.a, u.b, u.c) : intersection(v.a, v.b, u.a, u.b, u.c);
    ret.b = parallel(v.c, v.a, u.a, u.b, u.c) ? intersection(v.b, v.c, u.a, u.b, u.c) : intersection(v.c, v.a, u.a, u.b, u.c);
    return ret;
}
line3 intersection(point3 u1, point3 u2, point3 u3, point3 v1, point3 v2, point3 v3) {
    line3 ret;
    ret.a = parallel(v1, v2, u1, u2, u3) ? intersection(v2, v3, u1, u2, u3) : intersection(v1, v2, u1, u2, u3);
    ret.b = parallel(v3, v1, u1, u2, u3) ? intersection(v2, v3, u1, u2, u3) : intersection(v3, v1, u1, u2, u3);
    return ret;
}
//点到直线距离
double disptoline(point3 p, line3 l) {
    return vlen(xmult(subt(p, l.a), subt(l.b, l.a))) / dist(l.a, l.b);
}
double disptoline(point3 p, point3 l1, point3 l2) {
    return vlen(xmult(subt(p, l1), subt(l2, l1))) / dist(l1, l2);
}
//点到直线最近点
point3 ptoline(point3 p, line3 l) {
    point3 ab = subt(l.b, l.a);
    double t = -dmult(subt(p, l.a), ab) / sqrlen(ab);
    ab.x *= t;
    ab.y *= t;
    ab.z *= t;
    return subt(l.a, ab);
}
//点到平面距离
double disptoplane(point3 p, plane3 s) {
    return fabs(dmult(pvec(s), subt(p, s.a))) / vlen(pvec(s));
}
double disptoplane(point3 p, point3 s1, point3 s2, point3 s3) {
    return fabs(dmult(pvec(s1, s2, s3), subt(p, s1))) / vlen(pvec(s1, s2, s3));
}

double disptoplane(point3 p, planef s) {
    return fabs((dmult(pvec(s), p) + s.d) / vlen(pvec(s)));
}
//点到平面最近点
point3 ptoplane(point3 p, planef s) {
    line3 l;
    l.a = p;
    l.b = pvec(s);
    l.b.x += p.x;
    l.b.y += p.y;
    l.b.z += p.z;
    return intersection(l, s);
}
//直线到直线距离
double dislinetoline(line3 u, line3 v) {
    point3 n = xmult(subt(u.a, u.b), subt(v.a, v.b));
    return fabs(dmult(subt(u.a, v.a), n)) / vlen(n);
}
double dislinetoline(point3 u1, point3 u2, point3 v1, point3 v2) {
    point3 n = xmult(subt(u1, u2), subt(v1, v2));
    return fabs(dmult(subt(u1, v1), n)) / vlen(n);
}
//直线到直线的最近点对
//p1在u上，p2在v上，p1到p2是uv之间的最近距离
//注意，保证两直线不平行
void linetoline(line3 u, line3 v, point3 &p1, point3 &p2) {
    point3 ab = subt(u.b, u.a), cd = subt(v.b, v.a), ac = subt(v.a, u.a);
    double r = (dmult(ab, cd) * dmult(ac, ab) - sqrlen(ab) * dmult(ac, cd)) /
               (sqrlen(ab) * sqrlen(cd) - sqr(dmult(ab, cd)));
    p2.x = v.a.x + r * cd.x, p2.y = v.a.y + r * cd.y,  p2.z = v.a.z + r * cd.z;
    p1 = ptoline(p2, u);
}
//两直线夹角cos值
double angle_cos(line3 u, line3 v) {
    return dmult(subt(u.a, u.b), subt(v.a, v.b)) / vlen(subt(u.a, u.b)) / vlen(subt(v.a, v.b));
}
double angle_cos(point3 u1, point3 u2, point3 v1, point3 v2) {
    return dmult(subt(u1, u2), subt(v1, v2)) / vlen(subt(u1, u2)) / vlen(subt(v1, v2));
}
//两平面夹角cos值
double angle_cos(plane3 u, plane3 v) {
    return dmult(pvec(u), pvec(v)) / vlen(pvec(u)) / vlen(pvec(v));
}
double angle_cos(point3 u1, point3 u2, point3 u3, point3 v1, point3 v2, point3 v3) {
    return dmult(pvec(u1, u2, u3), pvec(v1, v2, v3)) / vlen(pvec(u1, u2, u3)) / vlen(pvec(v1, v2, v3));
}
double angle_cos(planef u, planef v) {
    return dmult(pvec(u), pvec(v)) / (vlen(pvec(u))*vlen(pvec(v)));
}
//直线平面夹角sin值
double angle_sin(line3 l, plane3 s) {
    return dmult(subt(l.a, l.b), pvec(s)) / vlen(subt(l.a, l.b)) / vlen(pvec(s));
}
double angle_sin(point3 l1, point3 l2, point3 s1, point3 s2, point3 s3) {
    return dmult(subt(l1, l2), pvec(s1, s2, s3)) / vlen(subt(l1, l2)) / vlen(pvec(s1, s2, s3));
}
double angle_sin(line3 l, planef s) {
    return dmult(subt(l.a, l.b), pvec(s)) / (vlen(subt(l.a, l.b)) * vlen(pvec(s)));
}
//平面方程形式转化 plane3 -> planef
planef plane3_to_planef(plane3 p) {
    planef ret;
    point3 m = xmult(subt(p.b, p.a), subt(p.c, p.a));
    ret.a = m.x, ret.b = m.y, ret.c = m.z;
    ret.d = -m.x * p.a.x - m.y * p.a.y - m.z * p.a.z;
    return ret;
}
int main() {
}