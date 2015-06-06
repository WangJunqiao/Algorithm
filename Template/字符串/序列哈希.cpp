template<Typename T, typename ValueType = unsigned int>
struct SequenceHasher {
    ValueType *h, *pow;

    SequenceHasher() {
        h = pow = NULL;
    }

    void calc(T *seq, int len, int b = 1000000007) { //base0
        h = new ValueType[len + 1];
        pow = new ValueType[len + 1];
        h[0] = seq[0];
        pow[0] = 1;
        for (int i = 0; i < len; i++) {
            h[i + 1] = h[i] * b + seq[i];
            pow[i + 1] = pow[i] * b;
        }
    }

    ValueType get(int i, int j) { //substr[i...j]
        return h[j + 1] - h[i] * pow[j - i + 1];
    }

    ~SequenceHasher() {
        if (h) {
            delete h;
        }
        if (pow) {
            delete pow;
        }
    }
}; //最好搞两个, b选大素数

