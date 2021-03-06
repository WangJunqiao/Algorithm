#define ValueType unsigned int
#define maxn 110000

struct StringHash {
    ValueType h[maxn], pow[maxn];

    void calc(char *str, int b = 1000000007, int len = -1) { //base0
        if (len < 0) len = strlen(str);
        h[0] = str[0];
        pow[0] = 1;
        for (int i = 0; i < len; i++) {
            h[i + 1] = h[i] * b + str[i];
            pow[i + 1] = pow[i] * b;
        }
    }

    ValueType get(int i, int j) { //substr[i...j]
        return h[j + 1] - h[i] * pow[j - i + 1];
    }
} ins1, ins2; //最好搞两个, b选大素数