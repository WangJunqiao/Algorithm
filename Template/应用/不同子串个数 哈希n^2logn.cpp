#define maxn 2100
typedef unsigned long long uint64;
typedef pair <uint64, uint64> PUU;

int b1 = 130, b2 = 131; //进制
uint64 pow1[maxn], pow2[maxn]; //幂次
uint64 h1[maxn], h2[maxn];
PUU res[maxn * maxn];

PUU getValue(int l, int r) {
    return PUU(h1[r] - h1[l - 1] * pow1[r - l + 1], h2[r] - h2[l - 1] * pow2[r - l + 1]);
}

int calc(char *str) { //计算一个字符串有多少个不同的子串,base1
    int len = strlen(str + 1);
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i <= len; i++) {
        pow1[i] = pow1[i - 1] * b1;
        pow2[i] = pow2[i - 1] * b2;
    }
    for (int i = 1; i <= len; i++) {
        h1[i] = h1[i - 1] * b1 + str[i];
        h2[i] = h2[i - 1] * b2 + str[i];
    }
    int ind = 0;
    for (int i = 1; i <= len; i++) {
        for (int j = i; j <= len; j++) {
            //if( j-i+1<L || can1[i]==false || can2[j]==false ) continue;
            res[ind++] = getValue(i, j);
        }
    }
    sort(res, res + ind);
    ind = unique(res, res + ind) - res;
    return ind;
}