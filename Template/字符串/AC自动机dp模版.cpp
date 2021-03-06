#include <iostream>
#include <cstring>

using namespace std;

#define CH 4 //几叉树

struct Node {
    int id, kill; //kill是一个标记
    Node *fail, *x[CH]; //x就是next
    void init() {
        kill = 0;
        memset(x, 0, sizeof(x));
    }
} dd[100000], *que[100000];

Node *ptr[10005]; //ptr[i]表示第i个状态的节点地址
int cnt;          //状态总数

struct ACAutoM {
    int e;
    Node *root;

    Node *_alloc() {
        dd[e].init();
        return &dd[e++];
    }

    void init() {
        cnt = e = 0;
        root = _alloc();
        root->id = cnt;
        ptr[cnt++] = root;  //root的id是0
    }

    void insert(char *ch) { //插入一个单词
        Node *p = root;
        for (int i = 0, d; ch[i]; i++) {
            d = ch[i] - 'a';
            if (p->x[d] == NULL) {
                p->x[d] = _alloc();
                p->x[d]->id = cnt;
                ptr[cnt++] = p->x[d]; //这里记录id
            }
            p = p->x[d];
        }
        p->kill = 1; //记录一个完整的单词
    }

    void get_fail_point() { //构建失败指针
        int s = 0, t = 0;
        Node *p;
        root->fail = root;
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
            if (p->fail->kill) p->kill = 1; //回退的时候可能会包含字符串
            for (int i = 0; i < CH; i++) {
                if (p->x[i]) {
                    p->x[i]->fail = p->fail->x[i];
                    que[t++] = p->x[i];
                } else
                    p->x[i] = p->fail->x[i];
            }
        }
    }
} acm;//**************模板结束*****************
// 用法：acm.init(); acm.insert(...);  acm.get_fail_point();


int main() {
    return 0;
}
