#include <iostream>
#include<vector>
#include<map>
#include<stack>
#include<algorithm>

using namespace std;

char str[10005];

int bro[1005];
bool out[1005];

//多项式去括号!!!
bool dfs(int L, int R) { //返回是否是一个多项式
    if (str[L] == '(' && bro[L] == R) {
        out[L] = out[R] = false;
        return dfs(L + 1, R - 1);
    }
    bool ret = false;
    stack<pair<int, int> > st;
    for (int i = L; i <= R; i++) {
        if (isalpha(str[i])) {
            st.push(make_pair(i, i));
        } else if (str[i] == '+') {
            ret = true;
            if (st.size() == 1) {
                if (st.top().first != st.top().second) {
                    out[st.top().first] = false;
                    out[st.top().second] = false;
                }
                st.pop();
            } else {
                while (!st.empty()) st.pop();
            }
        } else if (str[i] == '(') {
            bool flag = dfs(i + 1, bro[i] - 1);
            if (flag == false) out[i] = out[bro[i]] = false;
            st.push(make_pair(i, bro[i]));
            i = bro[i];
        }
    }
    if (st.size() == 1) {
        if (st.top().first != st.top().second) {
            out[st.top().first] = false;
            out[st.top().second] = false;
        }
    }
    return ret;
}

int main() {
    while (scanf(" %s", str) != EOF) {
        stack<int> st;
        memset(out, true, sizeof(out));
        for (int i = 0; str[i]; i++) { //匹配好
            if (str[i] == '(') {
                st.push(i);
            } else if (str[i] == ')') {
                int s = st.top();
                st.pop();
                bro[s] = i, bro[i] = s;
            } else if (str[i] == '+') {
                bro[i] = -1;
            } else {
                bro[i] = i;
            }
        }
        int len = strlen(str);
        dfs(0, len - 1);
        for (int i = 0; i < len; i++) if (out[i]) putchar(str[i]);
        puts("");
    }
}