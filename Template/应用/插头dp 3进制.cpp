#include<iostream>
#include<algorithm>

using namespace std;

//用于连通性状态压缩dp
template<int N>  //N只能为2,4,8,下面全是是用位运算实现的
struct Number {
    static int w[30]; //X=b0*w[0]+b1*w[1]+...+b[n]*w[n]
    static int L;

    static void init() {   //对于每个实例必须先初始化
        L = N / 2;
        w[0] = 1;
        for (int i = 1; i < 30; i++) w[i] = w[i - 1] << L;
    }

    int toInt(int *d, int ind) { //将一个数组计算出一个N进制数,ind base0
        int ret = 0;
        for (int i = ind - 1; i >= 0; i--) ret = (ret << L) | d[i];
        return ret;
    }

    void parse(int val, int *d, int &ind) { //将一个N进制数解析成一个数组
        ind = 0;
        while (val) {
            d[ind++] = val & ((1 << L) - 1);
            val >>= L;
        }
        if (ind == 0) d[ind++] = 0;
    }

    int got(int val, int wei) {     //取出N进制数val的第wei位
        return (val & (w[wei + 1] - 1)) >> (wei << (L >> 1));
    }

    void set(int &val, int wei, int b) { //将N进制数val的第wei位设置为b
        val += ((b - got(val, wei)) << (wei << (L >> 1)));
    }
};

template<int N>
int Number<N>::w[30];
template<int N>
int Number<N>::L;
//************模板结束***********************************************

//映射关系TK -> TV, 映射范围_mod, 总节点数目_n
//默认没有重复的key


template<class TK, class TV, int _mod = 9997, int _n = 50000>
class HashTable {
    struct H {
        TK key;
        TV val;
        int next;
    } h[_n];
    int list[_mod], eid;

    int (*hash)(TK);

public:
    HashTable() { //构造函数
        clear();
    }

    void clear() { //清0
        memset(list, -1, sizeof(list));
        eid = 0;
    }

    void setCallBack(int (*hash)(TK)) { //设置回调函数(哈希函数)
        this->hash = hash;
    }

    int find(TK key) {   //查找关键字是否在哈希表中,没有返回-1
        int ind = hash(key);
        for (int p = list[ind]; p != -1; p = h[p].next) {
            if (h[p].key == key) return p;
        }
        return -1;
    }

    void insert(TK key, TV val) { //插入
        int ind = hash(key);
        h[eid].key = key;
        h[eid].val = val;
        h[eid].next = list[ind];
        list[ind] = eid++;
    }

    TV &operator[](TK key) {  //等同于map的[],必须保证里面有key,否则下标为-1
        return h[find(key)].val;
    }

    void print(TK *out, int &N) {   //0~N-1
        for (int i = 0; i < eid; i++)
            out[i] = h[i].key;
        N = eid;
    }
};

const int mod = 9997;

inline int h(int V) {
    return V % mod;
}//***************模板结束**********************

Number<4> ins;

int n, m;
long long dp[2][41835]; //真正可用的状态时41835个
HashTable<int, int> ht;

int b[20], sta[50000], index;

void dfs(int pos, int val, int bracket) {
    if (pos == m + 1) {
        if (bracket == 0) {
            sta[index++] = val;
        }
        return;
    }
    dfs(pos + 1, val, bracket);
    dfs(pos + 1, val + 1 * b[pos], bracket + 1);
    if (bracket > 0) dfs(pos + 1, val + 2 * b[pos], bracket - 1);
}

void init() {
    b[0] = 1;
    for (int i = 1; i <= 16; i++) b[i] = b[i - 1] * 4;
    index = 0;
    dfs(0, 0, 0);  //搜索所有的有用状态,存在sta数组中********
    sort(sta, sta + index);
    ht.setCallBack(h);
    ht.clear();
    for (int i = 0; i < index; i++) ht.insert(sta[i], i);  //虽然状态数目不多,但是状态值很大,不能用数组直接映射...故用hash表*******
    //cout<<index<<endl;
}

int lx, ly;

inline bool can(int i, int j) {
    if (i != lx) return i > lx;
    return j >= ly;
}

int main() {
    ins.init();
    int d[30], ind;
    int cas, Te = 1;
    char mat[15][15];
    scanf("%d", &cas);
    while (cas-- && scanf("%d %d", &n, &m)) {
        if (n == 0 && m == 0) break;
        memset(dp, 0, sizeof(dp));
        init();
        lx = -1, ly = -1;
        for (int i = n - 1; i >= 0; i--) {
            scanf(" %s", mat[i]);
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) { //寻找最后那个可以左右括号连结的坐标
                if (mat[i][j] == 'O') {
                    lx = i, ly = j;
                }
            }
        dp[0][ht[0]] = 1;
        bool flag = false; //flag -> !flag
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int p = 0; p < index; p++) {
                    int s = sta[p]; //状态值为s,可能是10^8级别*****

                    if (dp[flag][p] == 0) continue;
                    int L = ins.got(s, j), U = ins.got(s, j + 1); //取得相应位置的插头类型****
                    if (mat[i][j] == 'X') {
                        if (L == 0 && U == 0) dp[!flag][p] += dp[flag][p];
                    } else {
                        if (L == 0 && U == 0) {
                            if (mat[i][j] == '*') {
                                dp[!flag][p] += dp[flag][p];
                            }
                            int ns = s;
                            ins.set(ns, j, 1);
                            ins.set(ns, j + 1, 2);
                            dp[!flag][ht[ns]] += dp[flag][p];
                        } else if (L == 0 || U == 0) {
                            dp[!flag][p] += dp[flag][p];
                            int ns = s;
                            ins.set(ns, j, U);
                            ins.set(ns, j + 1, L);
                            dp[!flag][ht[ns]] += dp[flag][p];
                        } else if (L == 1 && U == 1) {
                            ins.parse(s, d, ind);
                            d[j] = d[j + 1] = 0;
                            for (int k = j + 2, num1 = 0; ; k++) { //往后找第一个  没匹配的   右括号!!!
                                if (d[k] == 0) continue;
                                if (d[k] == 1) {
                                    num1++;
                                    continue;
                                };
                                if (num1 == 0) {
                                    d[k] = 1;
                                    break;
                                }
                                if (num1) num1--;
                            }
                            int ns = ins.toInt(d, ind);
                            dp[!flag][ht[ns]] += dp[flag][p];
                        } else if (L == 2 && U == 2) {
                            ins.parse(s, d, ind);
                            d[j] = d[j + 1] = 0;
                            for (int k = j - 1, num2 = 0; ; k--) {
                                if (d[k] == 0) continue;
                                if (d[k] == 2) {
                                    num2++;
                                    continue;
                                };
                                if (num2 == 0) {
                                    d[k] = 2;
                                    break;
                                }
                                if (num2) num2--;
                            }
                            int ns = ins.toInt(d, ind);
                            dp[!flag][ht[ns]] += dp[flag][p];
                        } else if (L == 2 && U == 1) {
                            int ns = s;
                            ins.set(ns, j, 0);
                            ins.set(ns, j + 1, 0);
                            dp[!flag][ht[ns]] += dp[flag][p];
                        } else if (L == 1 && U == 2) {
                            if (can(i, j)) {
                                int ns = s;
                                ins.set(ns, j, 0);
                                ins.set(ns, j + 1, 0);
                                if (ns == 0) ans += dp[flag][p];
                                //dp[!flag][ rnk[ns] ]+=dp[flag][p];
                            }
                        }
                    }
                }
                flag = !flag;
                memset(dp[!flag], 0, sizeof(long long) * index);
            }
            for (int p = 0; p < index; p++) {
                int s = sta[p];
                if ((s << 2) > sta[index - 1]) break;
                dp[!flag][ht[(s << 2)]] = dp[flag][p];
            }
            flag = !flag;
            memset(dp[!flag], 0, sizeof(long long) * index);
        }
        printf("Case %d: ", Te++);
        ans += dp[flag][0];
        cout << ans << endl;
    }
}