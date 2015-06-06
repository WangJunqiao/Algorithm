//dancing link----------DD
//���� pku3076 pku3074
#include<iostream>
#include<cstdio>
#include<cstring>

#define MAXR 16*16*16//row
#define MAXC 16*16*4//column
#define TOTAL (MAXR+1)*(MAXC+1)
using namespace std;

int mat[MAXR][MAXC];
//��ʼ����0��1����1��1��ʼ��
int cid[TOTAL], rid[TOTAL], s[MAXC];
int l[TOTAL], r[TOTAL], u[TOTAL], d[TOTAL];
int lastc[MAXC];

//��i�е�������һ��Ԫ��
void remove(const int &col) {
    l[r[col]] = l[col];
    r[l[col]] = r[col];
    for (int i = d[col]; i != col; i = d[i]) { //ö��ÿһ��
        for (int j = r[i]; j != i; j = r[j]) { //ö��ÿһ��
            d[u[j]] = d[j];
            u[d[j]] = u[j];
            s[cid[j]]--;
        }
    }
}

void resume(const int &col) { //����
    for (int i = u[col]; i != col; i = u[i]) {
        for (int j = l[i]; j != i; j = l[j]) {
            d[u[j]] = j;
            u[d[j]] = j;
            s[cid[j]]++;
        }
    }
    l[r[col]] = col;
    r[l[col]] = col;
}

inline void addlr(const int &ln, const int &rn) { //���˺��ǳɻ���
    l[r[ln]] = rn;
    r[rn] = r[ln];
    r[ln] = rn;
    l[rn] = ln;
}

inline void addud(const int &un, const int &dn) {
    u[d[un]] = dn;
    d[dn] = d[un];
    d[un] = dn;
    u[dn] = un;
}

int res[MAXR], ind;

//ÿ��ȡ������
bool search(int k) { //����ʼ�ڼ�������
    if (r[0] == 0) {
        ind = k;
        return true;//�ҵ�һ���
    }
    int c, mi = 100000000;
    for (int i = r[0]; i != 0; i = r[i]) {
        if (s[i] <= mi) {  //���죬Ҫ<=,�е�˳������->��->��->���ӣ������Ǻ���Ĺ����Ǹ������������Ľ�һЩ��������ѡ����Ļ��Щ
            mi = s[i];
            c = i;
        }
    }
    if (mi == 0) return false; //���Բ�Ҫ���������������for���
    remove(c);
    for (int i = d[c]; i != c; i = d[i]) {
        res[k] = rid[i];//ѡ������һ�У������������������ѡ������Щ����
        for (int j = r[i]; j != i; j = r[j]) remove(cid[j]);
        if (search(k + 1)) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(cid[j]);
    }
    resume(c);
    return false;
}

/* �������״��������
####### 
 . . ..
 ... .
  . ..
*/
void adapt(int n, int m) { //����01����mat�Ĺ��,���亯������mat����dancing link ��
    memset(s, 0, sizeof(s));//ÿ��Ԫ�ظ�����0
    l[0] = r[0] = 0;
    for (int j = 1; j <= m; j++) {
        addlr(j - 1, j);
        u[j] = d[j] = lastc[j] = j;
    }
    int c = m + 1;//��m+1��ʼ��
    for (int i = 1; i <= n; i++) {
        bool f = true;
        for (int j = 1; j <= m; j++) {
            if (mat[i][j]) {
                if (f) {
                    f = false;
                    l[c] = r[c] = c;
                } else {
                    addlr(c - 1, c);
                }
                addud(lastc[j], c);
                rid[c] = i;
                cid[c] = j;
                s[j]++;
                lastc[j] = c++;
            }
        }
    }
}

//********************ģ�����***********
const int N = 3; //������С��(N^2)*(N^2)   N������2,3,4
const int L = 9; //N^2
const int b0 = 0, b1 = L * L, b2 = 2 * L * L, b3 = 3 * L * L;  //base
inline int block(int i, int j) {
    return (i - 1) / N * N + (j - 1) / N + 1;
}

struct QQ {
    int r, c, val;

    void paint(int i) {
        for (int j = 1; j <= L * L * 4; j++) mat[i][j] = 0; //��ʼ��
        int off;
        off = (r - 1) * L + val;
        mat[i][b0 + off] = 1;
        off = (c - 1) * L + val;
        mat[i][b1 + off] = 1;
        off = (block(r, c) - 1) * L + val;
        mat[i][b2 + off] = 1;
        off = (r - 1) * L + c;
        mat[i][b3 + off] = 1;
    }
} qq[16 * 16 * 16 + 5];

int main() {
    int Te = 0;
    char str[22][22];
    while (scanf(" %9s", str[1] + 1) != EOF) {
        if (str[1][1] == 'e') break;
        for (int i = 2; i <= L; i++) scanf("%9s", str[i] + 1);
        int R = 0;
        for (int i = 1; i <= L; i++) {
            for (int j = 1; j <= L; j++) {
                if (str[i][j] == '.') {
                    for (int k = 1; k <= L; k++) {
                        qq[++R].r = i, qq[R].c = j, qq[R].val = k;
                        qq[R].paint(R);
                    }
                } else {
                    qq[++R].r = i, qq[R].c = j, qq[R].val = str[i][j] - '0';
                    qq[R].paint(R);
                }
            }
        }
        adapt(R, L * L * 4);
        search(0);
        for (int i = 0; i < ind; i++) {
            int d = res[i];
            str[qq[d].r][qq[d].c] = '0' + qq[d].val;
        }
        for (int i = 1; i <= L; i++) for (int j = 1; j <= L; j++) putchar(str[i][j]);
        puts("");
    }
}
