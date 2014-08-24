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
    return x < -eps ? -1 : x > eps ? 1 : 0;
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
//以下三维点
struct P {
    double x, y, z;
    P(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {};
    friend P operator +(const P& p1, const P& p2) {
        return P(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
    }
    friend P operator -(const P& p1, const P& p2) {
        return P(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
    }
    friend P operator *(const P& p, double a) {
        return P(p.x * a, p.y * a, p.z * a);
    }
    friend P operator /(const P& p, double a) {
        return P(p.x / a, p.y / a, p.z / a);
    }
    friend P operator *(const P& a, const P& b) { //叉乘
        return P(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }
    friend double operator ^(const P& a, const P& b) { //点乘
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
	friend double dist(const P& a, const P& b) {
		return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z));
	}
	double len() {
		return sqrt(fabs(*this ^ *this));
	}
    double len2() {
        return *this ^ *this;
    }
	bool in() {
		return scanf("%lf %lf %lf", &x, &y, &z) == 3;
	}
	void out() const {
		printf("%lf %lf %lf\n", x, y, z);
	}
};

//点的旋转
//点p绕向量(s->e)顺时针旋转angle弧度(右手定则)
P rotate(P p, P s, P e, double angle) {
    e = e - s, p = p - s;
    double Cos = cos(angle), Sin = sin(angle);
	e  = e / e.len();
    double M[3][3] = {
        e.x*e.x*(1 - Cos) + Cos    , e.x*e.y*(1 - Cos) - e.z*Sin, e.x*e.z*(1 - Cos) + e.y*Sin,
        e.y*e.x*(1 - Cos) + e.z*Sin, e.y*e.y*(1 - Cos) + Cos    , e.y*e.z*(1 - Cos) - e.x*Sin,
        e.x*e.z*(1 - Cos) - e.y*Sin, e.y*e.z*(1 - Cos) + e.x*Sin, e.z*e.z*(1 - Cos) + Cos
    };
    P ret;
    ret.x = p.x * M[0][0] + p.y * M[0][1] + p.z * M[0][2] + s.x;
    ret.y = p.x * M[1][0] + p.y * M[1][1] + p.z * M[1][2] + s.y;
    ret.z = p.x * M[2][0] + p.y * M[2][1] + p.z * M[2][2] + s.z;
    return ret;
}

//坐标系旋转
//把点p所在的法向量v=s->e的平面转到xoy平面后点p的平面坐标
P planarizartion(P p, P s, P e) {
    e = e - s;
    double th1 = atan2(e.y, e.z); //把v转至xoz平面的夹角
    double th2 = 2 * pi - atan2(e.x, sqrt(e.y * e.y + e.z * e.z)); //把v从xoz平面转至z轴
    P o(0, 0, 0), nx(1, 0, 0), ny(0, 1, 0);
    p = rotate(p, o, nx, th1);
    p = rotate(p, o, ny, th2);
    return p;
}

//以下平面相关
struct plane { //平面用一般式表示ax+by+cz+d=0
    double a, b, c, d;
    plane() {}
    plane(double a, double b, double c, double d): a(a), b(b), c(c), d(d) {}
    
    //点到平面的距离
    double dist(const P& p, const plane& f) {
        return fabs(f.a * p.x + f.b * p.y + f.c * p.z + f.d) / sqrt(sqr(a) + sqr(b) + sqr(c));
    }
};

//以下四面体相关
struct tetrahedron { //四面体 默认顶点为A底面三角形BCD
    P a, b, c, d;
    tetrahedron() {}
    tetrahedron(const P&a, const P&b, const P&c, const P&d): a(a), b(b), c(c), d(d) {
    }
    P gravitycenter(const P&a, const P&b, const P&c, const P&d) {
        return (a + b + c + d) / 4;
    }
};
int main() {
    P s(-2, -4, 0), e(-2, 4, 0), p(-2, 4, 4);
    //s = P(0,0,0),e = P(0,2,0);
    rotate(p, s, e, pi / 2).output();
}
