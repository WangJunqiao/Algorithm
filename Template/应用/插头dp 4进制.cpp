// SCU 3994 4进制插头dp, 从(0,0)到(n-1,m-1)的路径有多少条(有障碍)
#include<...>

using namespace std;

//每个实例都是相应进制的函数集合, 用于连通性状态压缩dp
template<int N>  //N只能为2,4,8,
struct Number {
    int w[30]; //X=b0*w[0]+b1*w[1]+...+b[n]*w[n]
    int L, mask;  //二进制位数,
    Number() {   //初始化
        if (N == 2) L = 1;
        else if (N == 4) L = 2;
        else L = 3;
        mask = N - 1;
        w[0] = 1;
        for (int i = 1; i < 30; i++) w[i] = w[i - 1] << L;
    }

    int arr2int(int *d, int t) { //将一个数组计算出一个N进制数,ind base0
        int s = 0;
        for (int i = t - 1; i >= 0; i--) s = (s << L) | d[i];
        return s;
    }

    void int2arr(int s, int *d, int &t) { //将一个N进制数解析成一个数组
        t = 0;
        while (s) {
            d[t++] = s & mask;
            s >>= L;
        }
        if (t == 0) d[t++] = 0;
    }

    int test(int s, int wei) {   //取出N进制数s的第wei位   wei:base0
        return (s >> (wei * L)) & mask;
    }

    void set(int &s, int wei, int b) { //将N进制数s的第wei位设置为b wei:base0
        s += ((b - test(s, wei)) << (wei * L));
    }
};

Number<4> tool4;
//************模板结束***********************************************

/*
插头dp解题步骤:
0, 思考状态的表示
1, 搜索有效状态 (可能需要记录括号的匹配情况,getMatch()函数)
2, 存入hash表中(可用STL map替代)
3, L,U 分情况讨论
4, 每次需要将第i行末的转到第i+1行首
*/

map <int, int> ht;
int sta[9713], ind;
//valid status
int n, m; //n*m的格子 <=10
char mat[12][12]; //地图
int dp[12][12][9713]; // 经过搜索,只有5798个有效状态

int match[9713][12]; // 每个状态的括号序列中的匹配关系
int _buf[20];
stack <int> _st;

bool getMatch() { //对括号进行匹配,顺便测试 独立插头是否被包在一对括号里
    while (!_st.empty()) _st.pop();
    for (int i = 0; i < m + 1; i++) {
        if (_buf[i] == 1) _st.push(i);
        else if (_buf[i] == 2) {
            match[ind][i] = _st.top();
            match[ind][_st.top()] = i;
            _st.pop();
        } else if (_buf[i] == 3 && _st.size()) return false; //返回失败
    }
    return true; //返回成功
}

void dfs(int p, int sum, bool f) {
    if (p == m + 1) {
        if (sum || !f) return;
        if (getMatch()) sta[ind++] = tool4.arr2int(_buf, m + 1);
        return;
    }
    _buf[p] = 0;
    dfs(p + 1, sum, f);
    _buf[p] = 1;
    dfs(p + 1, sum + 1, f);
    if (sum) {
        _buf[p] = 2;
        dfs(p + 1, sum - 1, f);
    }
    if (f == false) {
        _buf[p] = 3;
        dfs(p + 1, sum, true);
    }
}

void findState() {
    ind = 0;
    ht.clear(); //ht.setCallBack(h);
    dfs(0, 0, false); //不能排序了,因为match数组已经确定了
    //printf("total state: %d\n",ind);
    for (int i = 0; i < ind; i++)
        ht[sta[i]] = i;

}

//****************
inline void add(int &a, int b) {
    a = (a + b) % 10007;
}

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < n; i++) scanf(" %s", mat[i]);
        findState();
        for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) for (int k = 0; k < ind; k++) dp[i][j][k] = 0;
        dp[0][0][ht[3]] = 1; //只有一个独立插头
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < ind; k++) {
                    int s = sta[k]; // s: real state

                    int L = tool4.test(s, j), U = tool4.test(s, j + 1);
                    if (mat[i][j] == '#') {
                        if (L == 0 && U == 0) {
                            add(dp[i][j + 1][k], dp[i][j][k]);
                        }
                        continue;
                    }
                    if (L == 0 && U == 0) {
                        add(dp[i][j + 1][k], dp[i][j][k]);
                        int ns = s;
                        tool4.set(ns, j, 1);
                        tool4.set(ns, j + 1, 2);
                        add(dp[i][j + 1][ht[ns]], dp[i][j][k]);
                    } else if (L == 0 || U == 0) {
                        add(dp[i][j + 1][k], dp[i][j][k]);
                        int ns = s;
                        tool4.set(ns, j, U);
                        tool4.set(ns, j + 1, L);
                        add(dp[i][j + 1][ht[ns]], dp[i][j][k]);
                    } else if (L == 1 && U == 1) {
                        int ns = s;
                        tool4.set(ns, j, 0);
                        tool4.set(ns, j + 1, 0);
                        tool4.set(ns, match[k][j + 1], 1);
                        add(dp[i][j + 1][ht[ns]], dp[i][j][k]);
                    } else if (L == 1 && U == 2) {
                        //do nothing
                    } else if (L == 2 && U == 1) {
                        int ns = s;
                        tool4.set(ns, j, 0);
                        tool4.set(ns, j + 1, 0);
                        add(dp[i][j + 1][ht[ns]], dp[i][j][k]);
                    } else if (L == 2 && U == 2) {
                        int ns = s;
                        tool4.set(ns, j, 0);
                        tool4.set(ns, j + 1, 0);
                        tool4.set(ns, match[k][j], 2);
                        add(dp[i][j + 1][ht[ns]], dp[i][j][k]);
                    } else if (L == 1 && U == 3) {
                        //invalid state
                    } else if (L == 2 && U == 3) {
                        int ns = s;
                        tool4.set(ns, j, 0);
                        tool4.set(ns, j + 1, 0);
                        tool4.set(ns, match[k][j], 3);
                        add(dp[i][j + 1][ht[ns]], dp[i][j][k]);
                    } else if (L == 3 && U == 1) {
                        int ns = s;
                        tool4.set(ns, j, 0);
                        tool4.set(ns, j + 1, 0);
                        tool4.set(ns, match[k][j + 1], 3);
                        add(dp[i][j + 1][ht[ns]], dp[i][j][k]);
                    } else if (L == 3 && U == 2) {
                        //invalid state
                    }
                }
            }
            int limit = 0;
            tool4.set(limit, m, 1);
            for (int k = 0; k < ind; k++) {
                int ns = sta[k] * 4;
                if (ht.find(ns) != ht.end()) {
                    dp[i + 1][0][ht[ns]] = dp[i][m][k];
                }
            }
        }
        int final = 0;
        tool4.set(final, m, 3);
        cout << dp[n - 1][m][ht[final]] << endl;
    }
}
