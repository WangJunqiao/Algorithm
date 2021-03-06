#define maxn 110000

int next[maxn];

//在str中寻找pattern出现的位置(起始位置)
void kmp(char *str, char *pat, vector <int> &pos) { //base1
    int L = strlen(str + 1), Lp = strlen(pat + 1);
    int q = 0;
    next[1] = q;
    pos.clear();
    for (int i = 2; i <= Lp; i++) {
        while (q && pat[q + 1] != pat[i]) q = next[q];
        if (pat[q + 1] == pat[i]) q++;
        next[i] = q;
    }
    q = 0;
    for (int i = 1; i <= L; i++) {
        while (q && pat[q + 1] != str[i]) q = next[q];
        if (pat[q + 1] == str[i]) q++;
        if (q == Lp) {
            pos.push_back(i - Lp + 1);
            q = next[q];
        }
    }
}
