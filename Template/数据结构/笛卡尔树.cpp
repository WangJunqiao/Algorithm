/*
笛卡尔树(就是一棵Treap的O(n)构造过程)
zju 1985 一列宽为1高为height[i]的木棍,求最大延伸面积, 
利用了T=i,H=height[i],然后父子之间夹住的区间......类似splay的想法...
*/
#include<iostream>
#include<stdio.h>

using namespace std;
#define maxn 110000

struct DD {
    int T, H;
    DD *ch[2]; //Tree,Heap
    void init(int _T, int _H) {
        T = _T;
        H = _H;
        ch[0] = ch[1] = NULL;
    }

    friend bool operator<(const DD &a, const DD &b) {
        return a.T < b.T;
    }
} dd[maxn], *root;

DD *st[maxn];
int top;

void makeTree(int n) { //节点0~n-1
    top = 0;
    for (int i = 0; i < n; i++) {
        DD *lson = NULL;
        while (top > 0) {
            if (dd[i].H < st[top - 1]->H) {
                lson = st[--top];
            } else break;
        }
        if (top == 0) {
            dd[i].ch[0] = lson;
            root = &dd[i];
        } else {
            st[top - 1]->ch[1] = &dd[i];
            dd[i].ch[0] = lson;
        }
        st[top++] = &dd[i];
    }
}

long long ans;

int dfs(DD *p) {
    if (p == NULL) return 0;
    int num = 1;
    num += dfs(p->ch[0]);
    num += dfs(p->ch[1]);
    ans = max(ans, (long long) num * p->H);
    return num;
}

int main() {
    int n;
    while (scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++) {
            int H;
            scanf("%d", &H);
            dd[i].init(i, H);
        }
        makeTree(n);
        ans = 0;
        dfs(root);
        printf("%lld\n", ans);
    }
}
