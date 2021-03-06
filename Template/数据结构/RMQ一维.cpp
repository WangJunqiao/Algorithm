template<typename T>
struct RMQ { //类型T必须重载operator<
    T mi[65536][16];

    void rmq(T *d, int N) { //预处理，传入一个数组，0~N-1
        int M = get(N);
        for (int i = 0; i < N; i++) mi[i][0] = d[i];
        for (int g = 1; g <= M; g++) {
            int L = N - (1 << g);
            for (int i = 0; i <= L; i++)
                mi[i][g] = min(mi[i][g - 1], mi[i + (1 << (g - 1))][g - 1]);
        }
    }

    int get(int L) { //如果查询太多可以打个表，这个很费时间的
        return int(log(L * 1.0) / log(2.0));
    }

    T query(int &a, int &b) {//询问[a,b]之间的最小值
        if (a > b) swap(a, b);
        int g = get(b - a + 1);
        return min(mi[a][g], mi[b - (1 << (g)) + 1][g]);
    }
};//***************模板结束***************************