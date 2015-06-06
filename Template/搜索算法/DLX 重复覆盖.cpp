//dancing link
//�ظ��������� NUAA 1507
#include<iostream>

#define MAXR 62//row
#define MAXC 62//column
#define TOTAL (MAXR+1)*(MAXC+1)
using namespace std;

int n, m, mat[MAXR][MAXC];
//��ʼ����0��1����1��1��ʼ��
int cid[TOTAL], rid[TOTAL], s[MAXC];
//��ʾ�кţ��кţ�ÿ�е��ܸ���
int res[MAXR];
//ÿ��ȡ������
int l[TOTAL], r[TOTAL], u[TOTAL], d[TOTAL];
int lastc[MAXC];//��i�е�������һ��Ԫ��

void remove(const int &col) {//��һ����û�ˣ�������ͷ**********
    for (int i = d[col]; i != col; i = d[i]) {
        r[l[i]] = r[i];
        l[r[i]] = l[i];
    }
}

void backtrack(const int &col) {
    for (int i = u[col]; i != col; i = u[i]) {
        r[l[i]] = i;
        l[r[i]] = i;
    }
}

inline void addlr(const int &ln, const int &rn) {//���˺��ǳɻ���
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

//*********************************************************
bool visit[MAXC];

int H() {//���ۺ�������ʾҪ�ظ�����ȫ����������Ҫ����
    int res = 0;
    memset(visit, false, sizeof(visit));
    for (int c = r[0]; c != 0; c = r[c]) {
        if (!visit[c]) {
            res++;
            visit[c] = true;
            for (int i = d[c]; i != c; i = d[i])
                for (int j = r[i]; j != i; j = r[j])
                    visit[cid[j]] = true;
        }
    }
    return res;
}

//******************************************************
int mi;

void search(int k, int sum) {//����ʼ�ڼ�������,k�������������±�,sum�ǵ�ǰ�Ѿ����ٲ���
    if (sum + H() >= mi)
        return;
    if (r[0] == 0) {
        mi = min(mi, sum);
        return;//�ҵ�һ���
    }
    int c, mi = 1000000;
    for (int i = r[0]; i != 0; i = r[i]) {
        if (s[i] < mi) {
            mi = s[i];
            c = i;
        }
    }
    for (int i = d[c]; i != c; i = d[i]) {
        res[k] = rid[i];
        remove(i);
        for (int j = r[i]; j != i; j = r[j])
            remove(j);
        search(k + 1, sum + 1);
        for (int j = l[i]; j != i; j = l[j])
            backtrack(j);
        backtrack(i);
    }
}

/*
�������DLX�Ľ�ģģ�ͣ�0����Ϊ�˷����м��*��,���Ͻǵ��ǣ�0,0��
00000000
 *******
 *******
 *******
 *******
*/

void adapt(int n, int m) {//����01����mat�Ĺ��,���亯������mat����dancing link ��
    memset(s, 0, sizeof(s));//ÿ��Ԫ�ظ�����0
    l[0] = r[0] = 0;   //��ͷ����(0,0)***********
    for (int i = 1; i <= m; i++) { //�ܹ���m�У��ܱ�Ÿ��к���һ����****
        addlr(i - 1, i);
        u[i] = d[i] = i;//�Գ�ѭ��
        lastc[i] = i; //������һ��Ԫ�غ���
    }
    int ind = m + 1;//��m+1��ʼ��
    for (int i = 1; i <= n; i++) {
        bool isfirst = true;
        for (int j = 1; j <= m; j++) {
            if (mat[i][j]) {
                if (isfirst) {
                    isfirst = false;
                    l[ind] = r[ind] = ind;
                } else {
                    addlr(ind - 1, ind);
                }
                addud(lastc[j], ind);
                lastc[j] = ind;
                cid[ind] = j;
                rid[ind] = i;
                s[j]++;
                ind++;
            }
        }
    }
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        int x, k;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            for (int j = 1; j <= x; j++)
                scanf("%d", &k), mat[i][k] = 1;
        }
        adapt(n, m);
        mi = m;
        search(1, 0);
        printf("%d\n", mi);
        memset(mat, 0, sizeof(mat));
    }
}