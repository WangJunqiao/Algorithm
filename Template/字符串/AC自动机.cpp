//hdu2222 给你一个字典,和一个串,找这个串里包含几个单词
//调用fail_pointer后，自动机的fail和x指针都不可能是NULL***********
#include<iostream>

using namespace std;

#define CH 26 //几叉树

struct DD {
    int num;
    DD *fail, *x[CH]; //x代表next
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

    void insert(char *ch) { //插入一个单词
        DD *p = root;
        for (int i = 0, d; ch[i]; i++) {
            d = ch[i] - 'a';
            if (p->x[d] == NULL) p->x[d] = _alloc();
            p = p->x[d];
        }
        p->num++; //单词个数
    }

    void fail_pointer() {
        root->fail = root; //
        int s = 0, t = 0;
        DD *p;
        for (int i = 0; i < CH; i++) { //由于root->fail = root故需要特殊考虑
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

} acm;//**************模板结束*****************

int work(DD *root, char *s) { //找起~~~~
    int d, ans = 0;
    DD *p = root, *tmp;
    for (int i = 0; s[i]; i++) {
        d = s[i] - 'a';
        tmp = p = p->x[d];
        while (tmp != root && tmp->num != -1) { //-1表示之前已经找过了
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
