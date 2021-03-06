struct LinearQueue { //单调队列
    int s, t; // [s,t)
    pair <int, int64> buf[maxn]; //index value
    void init() { s = t = 0; }

    int64 getValue(int i, int k) { //距离大于k的不要了
        while (s < t && buf[s].first < i - k) s++;
        if (s == t) return -inf;
        return buf[s].second;
    }

    void push(int i, int64 value) {
        while (s < t && buf[t - 1].second <= value) t--;
        buf[t].first = i, buf[t].second = value;
        t++;
    }
} LQ; //************模板结束****************************