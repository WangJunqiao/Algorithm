typedef unsigned int uint;
typedef pair <uint, uint> PUU;
#define P1 1000000007  ///����
#define P2 1000000009
uint pow1[maxn], pow2[maxn];

void _init() {
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i < maxn; i++) {
        pow1[i] = pow1[i - 1] * P1;
        pow2[i] = pow2[i - 1] * P2;
    }
}

void _hash(char *str, int len, PUU *h) { //base1
    h[0] = PUU(0, 0);
    for (int i = 1; i <= len; i++) {
        h[i].first = h[i - 1].first * P1 + str[i];
        h[i].second = h[i - 1].second * P2 + str[i];
    }
}

PUU getH(PUU *h, int l, int r) {///[l,r]��hashֵ
    return PUU(h[r].first - h[l - 1].first * pow1[r - l + 1], h[r].second - h[l - 1].second * pow2[r - l + 1]);
}
///*****************************************