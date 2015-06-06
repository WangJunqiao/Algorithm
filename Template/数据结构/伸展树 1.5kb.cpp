//author: zjut_DD(qq: 774367334)
//��ģ��1.5kb  �Ѳ� hdu 1890, zjut 1708
//prob: ����n����,ÿ�ζ�[a, b]�������ͬʱ+val, ��ѯ[L, R]�ĺ�
/*
����Ҫ��:
1, �޸�֮��һ��Ҫsplay����,��Ϊf�Ķ��ӱ��˵�û�ж�fʵ��update����!!!
2, ֻ��tmp->splay(NULL)���Ǿ��԰�ȫ��,��Ϊnull����update
3, ��find������������֮��,�Ӹ���������·�����Ѿ�û���ӳ���Ϣ��!!!
*/
typedef long long int64;
#define maxn 110000

struct Node {
    int val;
    int64 sum; //ͳ����Ϣ
    int64 add; //�ӳٱ��
    //��������
    Node *ch[2], *f;
    int size;

    void init() {
        f = ch[0] = ch[1] = NULL;
        size = 1;  //����
        add = 0; //�ӳٱ����0
    }

    void rot(int c) {//c=0����,c=1����
        Node *y = f, *z = y->f;
        //y->push_down(); push_down();//y����
        y->ch[!c] = ch[c];
        if (ch[c]) ch[c]->f = y;
        f = z;
        if (z) if (y == z->ch[0]) z->ch[0] = this; else z->ch[1] = this;
        ch[c] = y;
        y->f = this;
        y->update();//x�ڵ�����ά����
    }

    void splay(Node *fa) {//���Լ���ת��father����
        for (push_down(); f != fa;) {
            if (f->f == fa) {
                if (f->ch[0] == this) rot(1);
                else rot(0);
            } else {
                Node *y = f, *z = y->f;
                if (y->ch[0] == this) {
                    if (z->ch[0] == y) {
                        y->rot(1);
                        rot(1);
                    }
                    else {
                        rot(1);
                        rot(0);
                    }
                } else {
                    if (z->ch[0] != y) {
                        y->rot(0);
                        rot(0);
                    }
                    else {
                        rot(0);
                        rot(1);
                    }
                }
            }
        }
        update(); //���ά�����x�ڵ�
    }

    Node *find(int r) { //�ҵ������е�rank��ĵ�ַ    base1
        push_down();
        int L = 0;
        if (ch[0]) L += ch[0]->size;
        if (r <= L) return ch[0]->find(r);
        if (r == L + 1) return this;
        return ch[1]->find(r - L - 1);
    }

    void update() {
        size = 1;
        if (ch[0]) size += ch[0]->size;
        if (ch[1]) size += ch[1]->size; //���ϱ���
        sum = val;
        if (ch[0]) sum += ch[0]->sum;
        if (ch[1]) sum += ch[1]->sum;
    }

    void push_down() {//���ӳ���Ϣpush��ȥ
        if (add) {
            if (ch[0]) {
                ch[0]->add += add;
                ch[0]->val += add;
                ch[0]->sum += ch[0]->size * add;
            }
            if (ch[1]) {
                ch[1]->add += add;
                ch[1]->val += add;
                ch[1]->sum += ch[1]->size * add;
            }
            add = 0;
        }
    }
} dd[maxn];

int e; //��ʼ��
Node *_alloc() {
    dd[e].init();
    return &dd[e++];
}

//*********************��չ��ģ�����***************************
// e=0;  Node *root=_make(0,n+1);
int d[maxn];

Node *_make(int l, int r) {
    if (l > r) return NULL;
    int mid = (l + r) / 2;
    Node *p = _alloc();
    p->val = d[mid];
    p->ch[0] = _make(l, mid - 1);
    if (p->ch[0]) p->ch[0]->f = p;
    p->ch[1] = _make(mid + 1, r);
    if (p->ch[1]) p->ch[1]->f = p;
    p->update();
    return p;
}

int main() {
    int n, m, Te = 1;
    while (scanf("%d %d", &n, &m) != EOF) { //���г��ȣ���������
        for (int i = 1; i <= n; i++) scanf("%d", d + i);
        d[0] = d[n + 1] = 0;
        e = 0;
        Node *root = _make(0, n + 1), *tmp;
        printf("case #%d:\n", Te++);
        for (int i = 1; i <= m; i++) {
            char op;
            int a, b, val;
            scanf(" %c", &op);
            if (op == 'a') {
                scanf("%d %d %d", &a, &b, &val);
                a++, b++;
                tmp = root->find(a - 1);
                tmp->splay(NULL);
                root = tmp;
                tmp = root->find(b + 1);
                tmp->splay(root);
                tmp = tmp->ch[0];
                tmp->val += val;
                tmp->add += val;
                tmp->sum += tmp->size * (int64) val;
                tmp->splay(NULL);
                root = tmp;
            } else {
                scanf("%d %d", &a, &b);
                a++, b++;
                tmp = root->find(a - 1);
                tmp->splay(NULL);
                root = tmp;
                tmp = root->find(b + 1);
                tmp->splay(root);
                tmp = tmp->ch[0];
                printf("%lld\n", tmp->sum);
            }
        }
    }
}


