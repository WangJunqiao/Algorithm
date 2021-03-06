//UVALive 5109 Regular Expression Edit Distance
//根据正则表达式,构造一个有限状态非确定自动机(NFA)
/*
1) R is "a" or "b"
2) R is of the form "(R1R2)" where R1 and R2 are regular expressions
3) R is of the form "(R1|R2)" where R1 and R2 are regular expressions
4) R is of the form "(R1*)" where R1 is a regular expression.
*/
struct NFA {
    int s, t, cnt;   //起点,终点, 总点数
    vector <int> f[1000][3]; //因为是不确定的,所以转移函数是个数组 (0表示"a", 1表示"b", 2表示"")
};

//解析一个regex, 给首尾节点号s,t赋值
void _dfs(NFA &nfa, char *buf, int &i, int &s, int &t) {
#define link(a, b, c) nfa.f[a][b].push_back(c)
    if (buf[i] == '(') {
        int s1, t1, s2, t2;
        i++;
        _dfs(nfa, buf, i, s1, t1);
        i++;
        if (buf[i] == '|') {
            i++;
            _dfs(nfa, buf, i, s2, t2);
            s = nfa.cnt++;
            t = nfa.cnt++;
            link(s, 2, s1);
            link(s, 2, s2);
            link(t1, 2, t);
            link(t2, 2, t);
        } else if (buf[i] == '*') {
            s = nfa.cnt++;
            t = nfa.cnt++;
            link(t1, 2, s1);
            link(s, 2, s1);
            link(s1, 2, t);
        } else {
            _dfs(nfa, buf, i, s2, t2);
            s = nfa.cnt++;
            t = nfa.cnt++;
            link(s, 2, s1);
            link(t1, 2, s2);
            link(t2, 2, t);
        }
        i++;
    } else {
        s = nfa.cnt++;
        t = nfa.cnt++;
        link(s, buf[i] - 'a', t);
    }
}

void buildNFA(char *buf, NFA &nfa) {
    nfa.cnt = 0;
    int i = 0;
    _dfs(nfa, buf, i, nfa.s, nfa.t);
}//---------------------------------------

int dis[400][400];
bool inq[400][400];
queue <int> q;

int edit_dist(NFA &nfa1, NFA &nfa2) {
    memset(inq, false, sizeof(inq));
    memset(dis, 0x3f, sizeof(dis));

    dis[nfa1.s][nfa2.s] = 0;
    inq[nfa1.s][nfa2.s] = true;
    q.push(nfa1.s);
    q.push(nfa2.s);

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        int y = q.front();
        q.pop();
        inq[x][y] = false;

        for (int a = 0; a < 3; a++) {
            if (nfa1.f[x][a].size() == 0) continue;
            for (int b = 0; b < 3; b++) {
                if (nfa2.f[y][b].size() == 0) continue;
                vector <int> &v1 = nfa1.f[x][a];
                vector <int> &v2 = nfa2.f[y][b];
                for (int i = 0; i < v1.size(); i++) {
                    for (int j = 0; j < v2.size(); j++) {
                        int ex = v1[i], ey = v2[j], val = dis[x][y] + (a != b);
                        if (dis[ex][ey] > val) {
                            dis[ex][ey] = val;
                            if (inq[ex][ey] == false) {
                                q.push(ex);
                                q.push(ey);
                                inq[ex][ey] = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return dis[nfa1.t][nfa2.t];
}

int main() {
    int cas;
    scanf("%d", &cas);
    char buf1[555], buf2[555];
    while (cas--) {
        scanf(" %s %s", buf1, buf2);
        NFA nfa1, nfa2;
        buildNFA(buf1, nfa1);
        buildNFA(buf2, nfa2);
        for (int i = 0; i < nfa1.cnt; i++) nfa1.f[i][2].push_back(i);
        for (int i = 0; i < nfa2.cnt; i++) nfa2.f[i][2].push_back(i);
        printf("%d\n", edit_dist(nfa1, nfa2));
    }
}
