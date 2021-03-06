//树状数组，维护数组a的前缀和
template<typename T, int MAXN>
struct BinaryIndexedTree {
    T s[MAXN + 1]; //s是隐形数组T a[]的部分和
    int N;

    void init(int n) {
        N = n;
        fill(s, s + n + 1, 0);
    }

    int lowbit(int t) {
        return t & (-t);
    }

    void add(int i, T val) { //a[i] += val
        for (; i <= N; i += lowbit(i)) {
            s[i] += val;
        }
    }

    T get_sum(int i) { //返回s[1]+s[2]+...+s[i]
        T ret = 0;
        for (; i > 0; i -= lowbit(i)) {
            ret += s[i];
        }
        return ret;
    }
};

BinaryIndexedTree<int, 20> bit;