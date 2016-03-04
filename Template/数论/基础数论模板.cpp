//ÊıÂÛÉñ°å
/*
Ö»ÓĞÆæËØÊı²ÅÓĞÔ­¸ù,¹²phi(p-1)¸ö...
*/


typedef long long LL;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int lcm(int a, int b) { return a / gcd(a, b) * b; }

//mod P¿x¿¿¿¿¿
// 1/x = pow(x, P - 2), because pow(x, P - 1) % P = 1

//À©Õ¹Å·¼¸ÀïµÃ
LL ext_gcd(LL a, LL b, LL &x, LL &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    LL d = ext_gcd(b, a % b, x, y), temp = x;
    x = y, y = temp - a / b * y;
    return d;
}

//ËãÄæÔª
int get_ni(int a, int p) { //·µ»Øx,ax=1 (mod p) ap»¥ÖÊ
    int x, y;
    ext_gcd(a, p, x, y);
    return x;
}


//¼ÆËãa^b %mod
int power(int a, int b, int mod) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

//¼ÆËãÅ·À­º¯Êıphi
int phi(int n) { //¸´ÔÓ¶ÈO(sqrt(n)) ÒÑ²â
    int ret = 1, i;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            n /= i, ret *= (i - 1);
            while (n % i == 0) n /= i, ret *= i;
        }
    }
    if (n > 1) ret *= n - 1;
    return ret;
}


//½âÄ£·½³Ìax=b(mod n), ·µ»Ø½âµÄ¸öÊı,´æÓÚsolve
//ax+ny=bÓĞ½â(x0,y0),ÄÇÃ´(x0+n/d,y0-a/d)Ò²ÊÇ½â
int modular(LL a, LL b, LL n, LL *solve) {
    assert(b != 0);
    LL x0, y, d = ext_gcd(a, n, x0, y);
    if (b % d != 0) return 0;     //ÎŞ½â
    x0 = x0 * (b / d);
    x0 = (x0 % (n / d) + (n / d)) % (n / d); //x0Îª×îĞ¡µÄ·Ç¸ºÕûÊıÊ¹µÃax=b(mod n)
    for (int i = 0; i < d; i++) solve[i] = (x0 + i * (n / d)) % n;
    return (int) d;    //ÓĞd¸ö½â
}

//Çó½âÄ£ÏßĞÔ·½³Ì×é
//ret=b[i] (mod w[i]) i=0~n-1
//·µ»Ø½â,Èç¹ûÊÇ-1±íÊ¾ÎŞ½â
LL modular_linear_system(int *b, int *w, int n) { // ÒªÇób[i]<w[i]
    LL x0, y, d, ret = b[0], g = 1;
    for (LL i = 1; i < n; i++) {
        g = g / gcd(g, w[i - 1]) * w[i - 1];
        LL B = (b[i] - ret % w[i] + w[i]) % w[i];
        if (B == 0) continue;
        d = ext_gcd(g, w[i], x0, y);
        if (B % d) return -1; //ÎŞ½â
        x0 = x0 * (B / d);
        x0 = (x0 % (w[i] / d) + w[i] / d) % (w[i] / d); //×îĞ¡µÄx0,Ê¹µÃg*x0=B(mod w[i])
        ret += x0 * g;
    }
    return ret;
}

//·Ö½âÒ»¸öÊın={(p,num)...}
typedef pair <int, int> PII;

vector <PII> express(int n) { //¸´ÔÓ¶ÈO(sqrt(n))
    vector <PII> ret;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int num = 0;
            while (n % i == 0) num++, n /= i;
            ret.push_back(PII(i, num));
        }
    }
    if (n != 1) {
        ret.push_back(PII(n, 1));
    }
    return ret;
}

//¸ßĞ§µØ·Ö½â1~nµÄËùÓĞÕûÊı O(n*50)µÄÑù×Ó...
vector <PII> expr[1100000];
int np[1100000];

void decompose(int n) { //·Ö½â1~nµÄËùÓĞÕûÊı
    for (int i = 2; i * i <= n; i++) {
        if (np[i] != 0) continue;
        for (int j = i * i; j <= n; j += i) np[j] = i;
    }
    for (int i = 1; i <= n; i++) {
        if (np[i] == 0) expr[i].push_back(PII(i, 1));
        else {
            int ti = i, j = 0;
            while (ti % np[i] == 0) {
                ti /= np[i];
                j++;
            }
            expr[i] = expr[ti];
            expr[i].push_back(PII(np[i], j));
        }
    }
}//------------------------------------


//¶Ôn/iµÄÖµ½øĞĞ·Ö¶Î¡£    a<=b, {{a, b}, c}±íÊ¾n/a=n/b=c;
vector <pair<PII, int>> div_equal(int n) { //¸´ÔÓ¶Èn^0.5, ret.size()=O(n^0.5)
    vector <pair<PII, int>> ret;
    for (int a = 1, b, c; a <= n;) {
        c = n / a;
        b = n / c;
        ret.push_back(MP(MP(a, b), c));
        a = b + 1;
    }
    return ret;
}//------------------------------------------------------------------


//ÇónµÄÔ¼Êı
vector <int> divisor(int n) { //°üÀ¨n×Ô¼º
    vector <int> ret;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i * i != n) ret.push_back(n / i);
        }
    }
    return ret;
}

//ÇóÔ­¸ù
int primitive_root(int p) {       //±ØĞëÊÇÆæËØÊı²ÅÓĞÔ­¸ù
    vector <int> D = divisor(p - 1);
    for (int rt = 2; ; rt++) {
        bool flag = true;
        for (int i = 0; i < D.size() && flag; i++) {
            if (power(rt, D[i], p) == 1) flag = false;
        }
        if (flag) return rt;
    }
}

int main() {
    int n;
    while (cin >> n && n) {
        cout << primitive_root(n) << endl;
    }
}
