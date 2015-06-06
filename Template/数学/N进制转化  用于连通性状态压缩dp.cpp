//位运算快一点的

//每个实例都是相应进制的函数集合, 用于连通性状态压缩dp
template<int N>  //N只能为2,4,8,    2 4 已测!!
struct Number {
    int w[30]; //X=b0*w[0]+b1*w[1]+...+b[n]*w[n]
    int L, mask;  //二进制位数,
    Number() {   //初始化
        if (N == 2) L = 1;
        else if (N == 4) L = 2;
        else L = 3;
        mask = N - 1;
        w[0] = 1;
        for (int i = 1; i < 30; i++) w[i] = w[i - 1] << L;
    }

    int arr2int(int *d, int t) { //将一个数组计算出一个N进制数,ind base0
        int s = 0;
        for (int i = t - 1; i >= 0; i--) s = (s << L) | d[i];
        return s;
    }

    void int2arr(int s, int *d, int &t) { //将一个N进制数解析成一个数组
        t = 0;
        while (s) {
            d[t++] = s & mask;
            s >>= L;
        }
        if (t == 0) d[t++] = 0;
    }

    int test(int s, int wei) {   //取出N进制数s的第wei位   wei:base0
        return (s >> (wei * L)) & mask;
    }

    void set(int &s, int wei, int b) { //将N进制数s的第wei位设置为b wei:base0
        s += ((b - test(s, wei)) << (wei * L));
    }
};

//************模板结束***********************************************
Number<4> tool4;


//每个实例都是相应进制的函数集合, 用于连通性状态压缩dp
template<int N> //可以任意>=2的进制
struct Number {
    int w[30]; //X=b0*w[0]+b1*w[1]+...+b[n]*w[n]
    Number() {   //对于每个实例必须先初始化
        w[0] = 1;
        for (int i = 1; i < 30; i++) w[i] = w[i - 1] * N;
    }

    int arr2int(int *d, int t) { //将一个数组计算出一个N进制数,ind base0
        int s = 0;
        for (int i = 0; i < t; i++) s += d[i] * w[i];
        return s;
    }

    void int2arr(int s, int *d, int &t) { //将一个N进制数解析成一个数组
        t = 0;
        while (s) {
            d[t++] = s % N;
            s /= N;
        }
        if (t == 0) d[t++] = 0;
    }

    int test(int s, int wei) {  //取出N进制数val的第wei位
        return s % w[wei + 1] / w[wei];
    }

    void set(int &s, int wei, int b) { //将N进制数val的第wei位设置为b
        s += (b - test(s, wei)) * w[wei];
    }
};

//************模板结束***********************************************
Number<4> tool4;


