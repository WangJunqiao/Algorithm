//hdu2222 ����һ���ֵ�,��һ����,��������������������
//����fail_pointer���Զ�����fail��xָ�붼��������NULL***********
#include<iostream>

using namespace std;

#define CH 26 //������

struct DD {
    int num;
    DD *fail, *x[CH]; //x����next
    void init() {
        num = 0;
        memset(x, NULL, sizeof(x));
    }
} dd[1000000], *que[1000000];

struct ACAutoM {
    int e;
    DD *root;

    DD *_alloc() {
        dd[e].init();
        return &dd[e++];
    }

    void init() {
        e = 0;
        root = _alloc();
    }

    void insert(char *ch) { //����һ������
        DD *p = root;
        for (int i = 0, d; ch[i]; i++) {
            d = ch[i] - 'a';
            if (p->x[d] == NULL) p->x[d] = _alloc();
            p = p->x[d];
        }
        p->num++; //���ʸ���
    }

    void fail_pointer() {
        root->fail = root; //
        int s = 0, t = 0;
        DD *p;
        for (int i = 0; i < CH; i++) { //����root->fail = root����Ҫ���⿼��
            if (root->x[i]) {
                root->x[i]->fail = root;
                que[t++] = root->x[i];
            }
            else
                root->x[i] = root;
        }
        while (s < t) {
            p = que[s++];
            for (int i = 0; i < CH; i++) {
                if (p->x[i]) {
                    p->x[i]->fail = p->fail->x[i];
                    que[t++] = p->x[i];
                }
                else
                    p->x[i] = p->fail->x[i];
            }
        }
    }

} acm;//**************ģ�����*****************

int work(DD *root, char *s) { //����~~~~
    int d, ans = 0;
    DD *p = root, *tmp;
    for (int i = 0; s[i]; i++) {
        d = s[i] - 'a';
        tmp = p = p->x[d];
        while (tmp != root && tmp->num != -1) { //-1��ʾ֮ǰ�Ѿ��ҹ���
            ans += tmp->num;
            tmp->num = -1;
            tmp = tmp->fail;
        }
    }
    return ans;
}

char s[1000005];
char ch[55];

int main() {
    int cas, n;
    scanf("%d ", &cas);
    while (cas--) {
        acm.init();
        scanf("%d ", &n);
        for (int i = 1; i <= n; i++)
            gets(ch), acm.insert(ch);
        acm.fail_pointer();
        gets(s);
        printf("%d\n", work(acm.root, s));
    }
}
