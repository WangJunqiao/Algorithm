#define maxn 30005
typedef long long LL;

struct Point {
    int id;
    LL x, y;

    Point(int _id = 0, LL _x = 0, LL _y = 0) : id(_id), x(_x), y(_y) { };

    friend double slope(const Point &a, const Point &b) { //斜率
        if (a.x == b.x) {
            if (b.y > a.y) return 9999999999999.0;
            else return -999999999999.0;
        }
        return (double) (a.y - b.y) / (a.x - b.x);
    }
};

struct ConvexQueue { //维护一个下凸队列
    Point que[maxn];
    int s, t;

    void clear() { s = t = 0; }

    void push(Point p) {
        while (t >= s + 2) {
            if (slope(que[t - 2], que[t - 1]) > slope(que[t - 1], p)) //这里决定下凸
                t--;
            else break;
        }
        que[t++] = p;
    }

    Point getFirst() {
        if (s == t) return Point(0, 0, (LL) 1 << 60);//这个要保证不给力,看题目定数字
        return que[s];
    }

    void pop(double _slope) { //斜率不够的弹出
        while (t >= s + 2) {
            if (slope(que[s], que[s + 1]) < _slope) s++;
            else break;
        }
    }

    void pop(int ID) { //去掉下标小于ID的
        while (s < t) {
            if (que[s].id < ID) s++;
            else break;
        }
    }
} cq;