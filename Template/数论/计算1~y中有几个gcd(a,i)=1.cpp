int _dfs(vector<int> &p, int d, int x, int y){
    if (d == p.size())
        return y / x;
    return _dfs(p, d + 1, x, y) + _dfs(p, d + 1, x * (-p[d]), y);
}

int cal(int a, int y) { //计算1~y中有几个gcd(a,i)=1,总量减去能整出因数的,容斥原理,复杂度sqrt(a)+2^(p.size())
    vector <int> p;
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) {
            p.push_back(i);
            while (a % i == 0) a /= i;
        }
    }
    if (a != 1) p.push_back(a);
    return _dfs(p, 0, 1, y);
}