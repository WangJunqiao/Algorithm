/*
��ƽ�潻 O��nlog��n����
�����⡿�����ܶ����ƽ�棬����ÿ����ƽ�����߶���ɣ�����ָ���߶η������߱�ʾ��
(x1 - x) * (y2 - y) - (x2 - x) * (y1 - y) >=0 ( >=0 ��ʾ��ߣ�<=0 ��ʾ�ұ�)
Ҫ�������ƽ��ĺˣ��������а�ƽ����Χ�ɵ����
���㷨��O(nlogn)�İ�ƽ�潻�㷨�����ͳ�Ƴ��õ��Ķ���εĵ㣬Ȼ�����ò����ʽ������������
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps = 1e-10,big = 10000.0,pi = acos(-1.0);
const int MAXN = 20010;
inline int sgn(double x) { //���ǲ��ǵ���0������-1��0��1���ֱ���С�ڣ����ڣ�����
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
    friend inline double operator ^(const P& p1,const P& p2) { //���
        return p1.x * p2.x + p1.y * p2.y;
    }
    friend inline double operator *(const P& p1,const P& p2) { //���
        return p1.x * p2.y - p1.y * p2.x;
    }
    friend inline double dot(const P& o,const P& a,const P& b) {
        return (a - o) ^ (b - o);
    }
    friend inline double cross(const P& o,const P& a,const P& b) { //2��������oab�������
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
    //������v�ļ��ǣ��Ƕȷ�ΧΪ [0,2*pi)
    double angle() const{
        double t = atan2(y,x);
        return sgn(t) >= 0 ? t : t + 2 * pi;
    }
    P trunc(double l) const {
        l /= len();
        return P(x * l, y * l);
    }
    P turn_left() const { //������
        return P(-y, x);
    }
    P turn_right() const { //������
        return P(y, -x);
    }
    P rotate(double th,const P& p) const { //�Ƶ�p��ʱ��תth����
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

struct polygon { //�������ƽ�潻�����ڱߵĽ��㣬����һ������ε����е�
    P p[MAXN];
    int n;
};
struct line { //��ƽ�棬�������߶�
    P a,b;
};
double at2[MAXN];
int ord[MAXN],dq[MAXN+1],lnum;

polygon pg;

line ls[MAXN]; //��ƽ�漯��
//���>0��������ߣ�<0�������ұߣ�=0������
//e�Ƿ���o->s�����onleft(sgn(cross))>=0
/*inline double cross(P o,P s,P e) { //����������Ȼ�󷵻ز��
    return (s.x-o.x)*(e.y-o.y)-(e.x-o.x)*(s.y-o.y);
}*/
//ֱ���󽻵�
int intersection(line l1,line l2,P& p) { //ֱ����ֱ���ཻ
    if (l1.a == l1.b || l2.a == l2.b) return -1;
    double c1 = (l1.b - l1.a) * (l2.b - l2.a), //cross(l1.a,l1.b,l2.b);
           c2 = (l2.a - l1.a) * (l2.b - l2.a); //cross(l1.a,l2.a,l2.b);
    if (c1 == 0) {
        if (c2 == 0)
            return 2;//�����ص�
        else
            return 0;//����ƽ�в��ص�
    }
    else {
        p = l1.a + (l1.b - l1.a) * (c2 / c1);
        return 1;
    }
}
//��������
inline bool cmp(int u,int v) {
    if (sgn(at2[u] - at2[v]) == 0)
        return sgn(cross(ls[v].a,ls[v].b,ls[u].b)) >= 0;
    return sgn(at2[u] - at2[v]) < 0;
}
//�жϰ�ƽ��Ľ����ڵ�ǰ��ƽ����
bool judgein(int x,int y,int z){
    P p;
    intersection(ls[x],ls[y],p); //�󽻵�
    return sgn(cross(ls[z].a,ls[z].b,p)) < 0; //�жϽ���λ�ã���������棬����true�����Ҫ�ų����㹲�ߣ��ĳ�<=
}
//��ƽ�潻
void HalfPlaneIntersection(polygon &pg) { //Ԥ����
    int n = lnum;
    /* ����atan2(y,x) ���Ϊ����ʾ�� X ����ʱ����ת�ĽǶȣ����Ϊ����ʾ�� X ��˳ʱ����ת�ĽǶȡ�
���� atan2(a, b) �� atan(a/b)���в�ͬ��atan2(a,b)��ȡֵ��Χ���� -pi �� pi ֮�䣨������ -pi����
���� ��atan(a/b)��ȡֵ��Χ����-pi/2��pi/2֮�䣨��������pi)*/
    for (int i = 0 ;i < n;i++) { //atan2(y,x)���ÿ���߶ζ�Ӧ����ϵ�ĽǶ�
        at2[i] = atan2(ls[i].b.y - ls[i].a.y,ls[i].b.x - ls[i].a.x);
        ord[i] = i;
    }
    sort(ord,ord + n,cmp);
    int idx = 1;
    for (int i = 1;i < n;i++) //�������ߵ����
        if (sgn(at2[ord[i-1]] - at2[ord[i]]) != 0)
            ord[idx++] = ord[i];
    n = idx;
    //Ȧ��
    int bot = 1,top = bot + 1; //˫��ջ��botΪջ�ף�topΪջ��
    dq[bot] = ord[0];dq[top] = ord[1]; //��ѹ�����߽�ջ
    for (int i = 2;i < n;i++) {
        //bot < top ��ʾҪ��֤ջ��������2���߶Σ����ʣ��1�����Ͳ�������ջ
        //judgein���ж����ջ�������ߵĽ�������ڵ�ǰ�����ȵ��ұߣ�����ջ
        while (bot < top && judgein(dq[top-1],dq[top],ord[i])) top--;
        //��ջ��Ҫͬ���Ĳ���
        while (bot < top && judgein(dq[bot+1],dq[bot],ord[i])) bot++;
        dq[++top] = ord[i];
    }
    //���Ҫ����һ��ջ������ڵ�ջ��������ջ�׽���ĩβλ�ã�����ջ����ջβ�����ߵ��ұ�
    while (bot < top && judgein(dq[top-1],dq[top],dq[bot])) top--;
    while (bot < top && judgein(dq[bot+1],dq[bot],dq[top])) bot++;
    //���һ�������غϵ�
    dq[--bot] = dq[top];
    //������
    pg.n = 0;
    for (int i = bot + 1;i <= top;i++) //�����������ߵĽ���
        intersection(ls[dq[i-1]],ls[dq[i]],pg.p[pg.n++]);
}

inline void add(double a,double b,double c,double d) { //����߶�
    ls[lnum].a.x = a,ls[lnum].a.y = b;
    ls[lnum].b.x = c,ls[lnum].b.y = d;
    lnum++;
}

int main() {
    int n;
    scanf("%d",&n);
    double a,b,c,d;
    for (int i = 0;i < n;i++) {
        //�������һ������(x = (c - a),y = (d - b));
        scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
        add(a,b,c,d);
    }
    //�����ǹ���һ������α߽�
    add(0,0,big,0);//down
    add(big,0,big,big);//right
    add(big,big,0,big);//up
    add(0,big,0,0);//left
    HalfPlaneIntersection(pg); //���ƽ�潻
    double area = 0;
    n = pg.n;
    ///������εĸ����㱣����pg����
    for(int i = 0;i < n;i++)
        area += pg.p[i].x * pg.p[(i+1)%n].y - pg.p[(i+1)%n].x * pg.p[i].y;//x1 * y2 - x2 * y1�ò�����������
    area = fabs(area) / 2.0; //�������Ӧ�������������֮�ͣ����������������ı��ε�����ͣ�����Ҫ��2
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