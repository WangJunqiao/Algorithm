#include<memory.h>
#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;

//大数乘 hdu1402  
typedef int type;


const int SIZE = 2;
const int BASE = 100; //10^SIZE


void print(const type *z, int i) {
    i--;
    while (i > 0 && z[i] == 0) i--;
    printf("%d", (int) z[i--]);
    while (i >= 0) printf("%02d", (int) z[i--]);
    printf("\n");
}

type *copy(const type a[], int s, int t) {
    type *ret = new type[t - s];
    memcpy(ret, a + s, (t - s) * sizeof(type));
    return ret;
}

type *fastmul(const type a[], const type b[], int n) {
    //printf("%d\n",a.size());
    if (n <= 16) { //再分下去得不偿失
        type *res = new type[n * 2];
        memset(res, 0, n * 2 * sizeof(type));
        for (int i = 0; i < n; i++)
            if (a[i] != 0) {
                for (int j = 0; j < n; j++)
                    if (b[j] != 0) {
                        res[i + j] += a[i] * b[j];
                    }
            }
        return res;
    } else {
        int k = n >> 1;

        type *x0 = copy(a, 0, k);
        type *x1 = copy(a, k, k * 2);
        type *y0 = copy(b, 0, k);
        type *y1 = copy(b, k, k * 2);

        type *z0 = fastmul(x0, y0, k);
        type *z2 = fastmul(x1, y1, k);

        for (int i = 0; i < k; ++i) x0[i] += x1[i];
        for (int i = 0; i < k; ++i) y0[i] += y1[i];

        type *z1 = fastmul(x0, y0, k);
        for (int i = 0; i < 2 * k; ++i) z1[i] -= (z0[i] + z2[i]);

        type *res = new type[4 * k];
        memset(res, 0, 4 * k * sizeof(type));
        for (int i = 0; i < 2 * k; ++i) res[i] += z0[i];
        for (int i = 0; i < 2 * k; ++i) res[i + k] += z1[i];
        for (int i = 0; i < 2 * k; ++i) res[i + 2 * k] += z2[i];
        delete[] x0;
        delete[] x1;
        delete[] y0;
        delete[] y1;
        delete[] z0;
        delete[] z1;
        delete[] z2;
        return res;
    }
}

type *transform(char *a, int s) {
    type *x = new type[s];
    memset(x, 0, s * sizeof(type));
    int len = strlen(a);
    for (int e = 0, i = len - SIZE; i > -SIZE; i -= SIZE) {
        int val = 0;
        for (int j = i; j < i + SIZE; j++) if (j >= 0) val = 10 * val + a[j] - '0';
        x[e++] = val;
    }
    return x;
}

type *mul(char *a, char *b) {// a="32" b="32" 返回 "1024"
    int s = 1, M = max(strlen(a), strlen(b));
    while (s < M) s <<= 1;
    type *x = transform(a, s);
    type *y = transform(b, s);
    type *z = fastmul(x, y, s);
    delete[] x;
    delete[] y;
    type c = 0;
    for (int i = 0; i < s * 2; i++) {
        c += z[i];
        z[i] = c % BASE;
        c /= BASE;
    }
    print(z, s * 2);
    return z;
}



///////////////////////////////////////////////////////////

// 5425 5435325234534
char ch1[55000], ch2[55000];

int main() {
    //freopen("in.txt","r",stdin);
    //freopen("out9.txt","w",stdout);

    //int t=clock();

    while (scanf(" %s %s", ch1, ch2) != EOF) {
        delete[] mul(ch1, ch2);
    }
    //printf("%d ms\n",clock()-t);
}




