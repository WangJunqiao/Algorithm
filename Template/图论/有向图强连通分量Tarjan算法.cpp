/*
����ͼǿ��ͨ����Tarjan�㷨
���һ���ڵ��Ǹ�,��ôDFN(����������)==Low(�ܴﵽ����ͱ��)
*/
#define maxn 11000

struct Tarjan {
    vector <int> *adj;
    bool in[maxn];
    int DFN[maxn], Low[maxn], st[maxn], top, *label, compo, deep; //��ȱ�����һ��ȫ����!!!!
    //����0~N-1,�������label������,label[i]��ʾi����ڵ�����˭,�����������м�����base0
    int dirGraphShrink(int N, vector <int> *adj, int *label) {
        this->adj = adj;
        this->label = label;
        memset(in, false, sizeof(in));
        memset(DFN, 0, sizeof(DFN));
        top = compo = deep = 0;
        for (int i = 0; i < N; i++) if (DFN[i] == 0) _tarjan(i);
        return compo;
    }

    void _tarjan(int u) {
        DFN[u] = Low[u] = ++deep;
        st[top++] = u;
        in[u] = true;
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (DFN[v] == 0) {
                _tarjan(v);
                Low[u] = min(Low[u], Low[v]);
            } else if (in[v])//��ֹuv�Ǻ���****������ջ��
                Low[u] = min(Low[u], DFN[v]);
        }
        if (Low[u] == DFN[u]) {
            int v;
            do {
                v = st[--top];
                label[v] = compo;
                in[v] = false;
            } while (v != u);
            compo++;
        }
    }
} dir_tarjan;//**************ģ�����************************