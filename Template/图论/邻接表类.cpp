#define maxn 220005
#define maxm 3000005
struct Edge {
    int v, val, next;
} E[maxm];
int e; //ÿ��case�����ʼ��
struct AdjList {
    int l[maxn]; //
    void insert(int a, int b, int val = 0) { //�����
        E[e].v = b;
        E[e].val = val;
        E[e].next = l[a];
        l[a] = e++;
    }

    void init() {
        memset(l, -1, sizeof(l));
    }
} adj;
//****************ģ�����***************