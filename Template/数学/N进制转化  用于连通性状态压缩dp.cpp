//λ�����һ���

//ÿ��ʵ��������Ӧ���Ƶĺ�������, ������ͨ��״̬ѹ��dp
template<int N>  //Nֻ��Ϊ2,4,8,    2 4 �Ѳ�!!
struct Number {
    int w[30]; //X=b0*w[0]+b1*w[1]+...+b[n]*w[n]
    int L, mask;  //������λ��,
    Number() {   //��ʼ��
        if (N == 2) L = 1;
        else if (N == 4) L = 2;
        else L = 3;
        mask = N - 1;
        w[0] = 1;
        for (int i = 1; i < 30; i++) w[i] = w[i - 1] << L;
    }

    int arr2int(int *d, int t) { //��һ����������һ��N������,ind base0
        int s = 0;
        for (int i = t - 1; i >= 0; i--) s = (s << L) | d[i];
        return s;
    }

    void int2arr(int s, int *d, int &t) { //��һ��N������������һ������
        t = 0;
        while (s) {
            d[t++] = s & mask;
            s >>= L;
        }
        if (t == 0) d[t++] = 0;
    }

    int test(int s, int wei) {   //ȡ��N������s�ĵ�weiλ   wei:base0
        return (s >> (wei * L)) & mask;
    }

    void set(int &s, int wei, int b) { //��N������s�ĵ�weiλ����Ϊb wei:base0
        s += ((b - test(s, wei)) << (wei * L));
    }
};

//************ģ�����***********************************************
Number<4> tool4;


//ÿ��ʵ��������Ӧ���Ƶĺ�������, ������ͨ��״̬ѹ��dp
template<int N> //��������>=2�Ľ���
struct Number {
    int w[30]; //X=b0*w[0]+b1*w[1]+...+b[n]*w[n]
    Number() {   //����ÿ��ʵ�������ȳ�ʼ��
        w[0] = 1;
        for (int i = 1; i < 30; i++) w[i] = w[i - 1] * N;
    }

    int arr2int(int *d, int t) { //��һ����������һ��N������,ind base0
        int s = 0;
        for (int i = 0; i < t; i++) s += d[i] * w[i];
        return s;
    }

    void int2arr(int s, int *d, int &t) { //��һ��N������������һ������
        t = 0;
        while (s) {
            d[t++] = s % N;
            s /= N;
        }
        if (t == 0) d[t++] = 0;
    }

    int test(int s, int wei) {  //ȡ��N������val�ĵ�weiλ
        return s % w[wei + 1] / w[wei];
    }

    void set(int &s, int wei, int b) { //��N������val�ĵ�weiλ����Ϊb
        s += (b - test(s, wei)) * w[wei];
    }
};

//************ģ�����***********************************************
Number<4> tool4;


