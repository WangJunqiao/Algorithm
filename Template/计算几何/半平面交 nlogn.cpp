/*
半平面交 O（nlog（n））
【题意】给出很多个半平面，这里每个半平面由线段组成，都是指向线段方向的左边表示有
(x1 - x) * (y2 - y) - (x2 - x) * (y1 - y) >=0 ( >=0 表示左边，<=0 表示右边)
要你求个半平面的核，就是所有半平面所围成的面积
【算法】O(nlogn)的半平面交算法，最后统计出得到的多边形的点，然后利用叉积公式求出面积就行了
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps = 1e-10,big = 10000.0,pi = acos(-1.0);
const int MAXN = 20010;
inline int sgn(double x) { //判是不是等于0，返回-1，0，1，分别是小于，等于，大于
    return x < -eps ? -1 : x > eps ? 1 : 0;//(x < -eps) ? -1: x > eps;
}
struct P {
    double x,y;
    P(double x = 0,double y = 0):x(x),y(y) {};
    friend bool operator ==(const P& p1,const P& p2) {
        return sgn(p1.x - p2.x) == 0 && sgn(p1.y - p2.y) == 0;
    }
    friend bool operator <(const P& p1,const P& p2) {
        return sgn(p1.x - p2.x) == 0 ? sgn(p1.y - p2.y) < 0 : p1.x < p2.x;
    }
    friend bool operator >(const P& p1,const P& p2) {
        return sgn(p1.x - p2.x) == 0 ? sgn(p1.y - p2.y) > 0 : p1.x > p2.x;
    }
    friend P operator +(const P& p1,const P& p2) {
        return P(p1.x + p2.x, p1.y + p2.y);
    }
    friend P operator -(const P& p1,const P& p2) {
        return P(p1.x - p2.x, p1.y - p2.y);
    }
    friend P operator *(const P& p,double a) {
        return P(p.x * a,p.y * a);
    }
    friend P operator /(const P& p,double a) {
        return P(p.x / a,p.y / a);
    }
    friend inline double operator ^(const P& p1,const P& p2) { //点乘
        return p1.x * p2.x + p1.y * p2.y;
    }
    friend inline double operator *(const P& p1,const P& p2) { //叉乘
        return p1.x * p2.y - p1.y * p2.x;
    }
    friend inline double dot(const P& o,const P& a,const P& b) {
        return (a - o) ^ (b - o);
    }
    friend inline double cross(const P& o,const P& a,const P& b) { //2倍三角形oab有向面积
        return (a - o) * (b - o);
    }
    friend double dist(const P& p1, const P& p2) {
        return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }
    friend double dist2(const P& p1,const P& p2) {
        return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    }
    double len() const {
        return sqrt(x * x + y * y);
    }
    double len2() const {
        return x * x + y * y;
    }
    //求向量v的极角，角度范围为 [0,2*pi)
    double angle() const{
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
    P rotate(double th,const P& p) const { //绕点p逆时针转th弧度
        double c = cos(th),s = sin(th);
        return P(c * (x - p.x) - s * (y - p.y) + p.x,s * (x - p.x) + c * (y - p.y) + p.y);
    }
    bool input() {
        return scanf("%lf %lf",&x,&y) == 2;
    }
    void output() const {
        printf("%lf %lf\n",x,y);
    }
};

struct polygon { //存放最后半平面交中相邻边的交点，就是一个多边形的所有点
    P p[MAXN];
    int n;
};
struct line { //半平面，这里是线段
    P a,b;
};
double at2[MAXN];
int ord[MAXN],dq[MAXN+1],lnum;

polygon pg;

line ls[MAXN]; //半平面集合
//叉积>0代表在左边，<0代表在右边，=0代表共线
//e是否在o->s的左边onleft(sgn(cross))>=0
/*inline double cross(P o,P s,P e) { //构造向量，然后返回叉积
    return (s.x-o.x)*(e.y-o.y)-(e.x-o.x)*(s.y-o.y);
}*/
//直线求交点
int intersection(line l1,line l2,P& p) { //直线与直线相交
    if (l1.a == l1.b || l2.a == l2.b) return -1;
    double c1 = (l1.b - l1.a) * (l2.b - l2.a), //cross(l1.a,l1.b,l2.b);
           c2 = (l2.a - l1.a) * (l2.b - l2.a); //cross(l1.a,l2.a,l2.b);
    if (c1 == 0) {
        if (c2 == 0)
            return 2;//两线重叠
        else
            return 0;//两线平行不重叠
    }
    else {
        p = l1.a + (l1.b - l1.a) * (c2 / c1);
        return 1;
    }
}
//象限排序
inline bool cmp(int u,int v) {
    if (sgn(at2[u] - at2[v]) == 0)
        return sgn(cross(ls[v].a,ls[v].b,ls[u].b)) >= 0;
    return sgn(at2[u] - at2[v]) < 0;
}
//判断半平面的交点在当前半平面外
bool judgein(int x,int y,int z){
    P p;
    intersection(ls[x],ls[y],p); //求交点
    return sgn(cross(ls[z].a,ls[z].b,p)) < 0; //判断交点位置，如果在右面，返回true，如果要排除三点共线，改成<=
}
//半平面交
void HalfPlaneIntersection(polygon &pg) { //预处理
    int n = lnum;
    /* 对于atan2(y,x) 结果为正表示从 X 轴逆时针旋转的角度，结果为负表示从 X 轴顺时针旋转的角度。
　　 atan2(a, b) 与 atan(a/b)稍有不同，atan2(a,b)的取值范围介于 -pi 到 pi 之间（不包括 -pi），
　　 而atan(a/b)的取值范围介于-pi/2到pi/2之间（不包括±pi)*/
    for (int i = 0 ;i < n;i++) { //atan2(y,x)求出每条线段对应坐标系的角度
        at2[i] = atan2(ls[i].b.y - ls[i].a.y,ls[i].b.x - ls[i].a.x);
        ord[i] = i;
    }
    sort(ord,ord + n,cmp);
    int idx = 1;
    for (int i = 1;i < n;i++) //处理重线的情况
        if (sgn(at2[ord[i-1]] - at2[ord[i]]) != 0)
            ord[idx++] = ord[i];
    n = idx;
    //圈地
    int bot = 1,top = bot + 1; //双端栈，bot为栈底，top为栈顶
    dq[bot] = ord[0];dq[top] = ord[1]; //先压两根线进栈
    for (int i = 2;i < n;i++) {
        //bot < top 表示要保证栈里至少有2条线段，如果剩下1条，就不继续退栈
        //judgein，判断如果栈中两条线的交点如果在当前插入先的右边，就退栈
        while (bot < top && judgein(dq[top-1],dq[top],ord[i])) top--;
        //对栈顶要同样的操作
        while (bot < top && judgein(dq[bot+1],dq[bot],ord[i])) bot++;
        dq[++top] = ord[i];
    }
    //最后还要处理一下栈里面存在的栈顶的线在栈底交点末尾位置，或者栈顶在栈尾两条线的右边
    while (bot < top && judgein(dq[top-1],dq[top],dq[bot])) top--;
    while (bot < top && judgein(dq[bot+1],dq[bot],dq[top])) bot++;
    //最后一条线是重合的
    dq[--bot] = dq[top];
    //求多边形
    pg.n = 0;
    for (int i = bot + 1;i <= top;i++) //求相邻两条线的交点
        intersection(ls[dq[i-1]],ls[dq[i]],pg.p[pg.n++]);
}

inline void add(double a,double b,double c,double d) { //添加线段
    ls[lnum].a.x = a,ls[lnum].a.y = b;
    ls[lnum].b.x = c,ls[lnum].b.y = d;
    lnum++;
}

int main() {
    int n;
    scanf("%d",&n);
    double a,b,c,d;
    for (int i = 0;i < n;i++) {
        //输入代表一条向量(x = (c - a),y = (d - b));
        scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
        add(a,b,c,d);
    }
    //下面是构造一个大矩形边界
    add(0,0,big,0);//down
    add(big,0,big,big);//right
    add(big,big,0,big);//up
    add(0,big,0,0);//left
    HalfPlaneIntersection(pg); //求半平面交
    double area = 0;
    n = pg.n;
    ///最后多边形的各个点保存在pg里面
    for(int i = 0;i < n;i++)
        area += pg.p[i].x * pg.p[(i+1)%n].y - pg.p[(i+1)%n].x * pg.p[i].y;//x1 * y2 - x2 * y1用叉积求多边形面积
    area = fabs(area) / 2.0; //所有面积应该是三角形面积之和，而叉积求出来的是四边形的面积和，所以要除2
    printf("%.5f\n",area);
    return 0;
}
/*
5
0 0 4 0
0 3 0 0
4 0 0 2
3 0 0 3
3.26 0 0 2.34
3.46284
*/