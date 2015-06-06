//dancing link
//pku 3740
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
int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", mat[i] + j);
        adapt(n, m);
        if (search(1))
            cout << "Yes, I found it\n";
        else
            cout << "It is impossible\n";
    }
}