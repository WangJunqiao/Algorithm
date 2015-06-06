//������С��ʾ kmp��ѭ����  hdu 3374
#include<iostream>

using namespace std;

#define maxn 1000005

//������С��ʾ,�±��1��ʼ,�����±�
int min_present(char *ch, int len) {
    int p1 = 1, p2 = 2, k = 0;
    while (p1 <= len && p2 <= len && k < len) { //�Ҳ���������С���� ���� ��ȫƥ������
        int n1 = p1 + k;
        if (n1 > len) n1 -= len;
        int n2 = p2 + k;
        if (n2 > len) n2 -= len;
        if (ch[n1] == ch[n2]) k++; // ��ȵĻ�,��ⳤ�ȼ�1
        else if (ch[n1] > ch[n2]) p1 += k + 1, k = 0; //���ڵĻ�,˵��p1�϶�������С��ʾ(�����)
        else p2 += k + 1, k = 0; //����ͬ��
        if (p1 == p2) p2++;
    }
    return min(p1, p2);
}

//��������ʾ,base1,�����±�
int max_present(char *ch, int len) {
    int p1 = 1, p2 = 2, k = 0;
    while (p1 <= len && p2 <= len && k < len) {
        int n1 = p1 + k;
        if (n1 > len) n1 -= len;
        int n2 = p2 + k;
        if (n2 > len) n2 -= len;
        if (ch[n1] == ch[n2]) k++;
        else if (ch[n1] < ch[n2]) p1 += k + 1, k = 0;
        else p2 += k + 1, k = 0;
        if (p1 == p2) p2++;
    }
    return min(p1, p2);
}

int next[maxn];

int kmp(char *ch, int len) { //��ѭ���ڳ���
    int q = 0;
    next[1] = 0;
    for (int i = 2; i <= len; i++) {
        while (q != 0 && ch[q + 1] != ch[i]) q = next[q];
        if (ch[q + 1] == ch[i]) q++;
        next[i] = q;
    }
    int t = len - next[len];
    if (len % t) return len;
    else return t;
}

char ch[maxn];

int main() {
    while (gets(ch + 1) > 0) {
        int len = strlen(ch + 1);
        int minp = min_present(ch, len);
        int maxp = max_present(ch, len);
        int t = len / kmp(ch, len);
        printf("%d %d %d %d\n", minp, t, maxp, t);
    }
}
