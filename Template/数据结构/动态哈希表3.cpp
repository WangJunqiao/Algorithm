//K判相等用了==操作符
template<typename K, typename V, int(*hash)(const K &k)>
struct HashMap {
    struct Entry {
        K k;
        V v;
        int _h;
    } **l;
    int _size, _cap;
    double _factor;
    const static int PERCENT = 50; //当元素百分比超过多少时扩张
    const static int MUL = 4; //扩张的倍数，这个值必须是2的倍数

    HashMap(int capcity = 0) {
        _factor = PERCENT / 100.0;
        _cap = 8;
        while (_cap * _factor < capcity) _cap <<= 1;
        _init(_cap);
    }

    HashMap(const HashMap &map) {
        *this = map;
    }

    HashMap &operator=(const HashMap &map) {
        _free();
        _init(map._cap);
        for (int i = 0; i < _cap; i++)
            if (map.l[i]) {
                l[i] = new Entry();
                *l[i] = *map.l[i];
            }
        _size = map._size;
        return *this;
    }

    void _free() {
        for (int i = 0; i < _cap; i++) if (l[i]) delete l[i];
        free(l);
    }

    int _geth(const K &k) {
        int h = hash(k);
        h ^= (h >> 20) ^ (h >> 12);
        return h ^ (h >> 7) ^ (h >> 4);
    }

    void _init(int cap = 8) {
        _cap = cap;
        l = (Entry **) malloc(cap * sizeof(Entry *));
        _size = 0;
        for (int i = 0; i < cap; i++) l[i] = NULL;
    }

    int _find(const K &k) { //return index
        int h = _geth(k);
        for (int i = h & (_cap - 1); l[i]; i = (i + 1) & (_cap - 1))
            if (l[i]->_h == h && l[i]->k == k) return i;
        return -1;
    }

    int _insert(const K &k, const V &v) { //return index
        int i = _find(k);
        if (i >= 0) {
            l[i]->v = v;
            return i;
        }
        _size++;
        int h = _geth(k);
        for (i = h & (_cap - 1); l[i]; i = (i + 1) & (_cap - 1))
            if (l[i]->_h == h && l[i]->k == k) break;
        l[i] = new Entry();
        l[i]->k = k;
        l[i]->v = v;
        l[i]->_h = h;

        if (_size > _cap * _factor) {
            _rebuild();
            return _find(k);
        } else {
            return i;
        }
    }

    void _rebuild() {
        int ocap = _cap;
        _cap *= MUL;
        _size = 0;
        Entry **tl = l;
        l = (Entry **) malloc(_cap * sizeof(Entry *));
        for (int i = 0; i < _cap; i++) l[i] = NULL;
        for (int i = 0; i < ocap; i++)
            if (tl[i]) {
                _insert(tl[i]->k, tl[i]->v);
            }
        for (int i = 0; i < ocap; i++)
            if (tl[i]) {
                delete tl[i];
            }
        free(tl);
    }

    ~HashMap() {
        _free();
    }

    //----------------------以上是内部函数------------------------------------

    void clear() {
        _free();
        _init();
    }

    bool contains(K k) {
        return _find(k) >= 0;
    }

    V &operator[](const K &k) {
        int i = _find(k);
        if (i >= 0) return l[i]->v;
        i = _insert(k, V()); //把这行直接放下面，g++会挂，好神奇
        return l[i]->v;
    }

    int size() {
        return _size;
    }

    //-----iterate------------------------------
    int id;

    void beginIterate() {
        id = 0;
    }

    bool hasNext() {
        while (id < _cap && !l[id]) id++;
        return id < _cap;
    }

    Entry *next() {
        id++;
        return l[id - 1];
    }
};

int h(const int &a) {
    return a;
}












/*
哈希表测试代码：
int main(){
	freopen("e:/in.txt","w",stdout);
	
	srand(time(NULL)); //每次运行都不
	
	int n = 5000000, q = 10000000;
	printf("%d %d\n", n, q);
	for(int i=0;i<n;i++) {
		int a = rand()*rand()%1000000000;
		int b = rand()*rand()%1000000000;
		printf("%d %d\n", a, b);
	}
	for(int i=0;i<q;i++) {
		int a = rand()*rand()%1000000000;
		printf("%d\n", a);
	}
	
	//system("notepad in.txt");
}




int main() {
	freopen("e:/in.txt", "r", stdin);
	
	HashMap<int, int, h> mp(5000000);
	int n, q;
	scanf("%d %d", &n, &q);
	vector<int> a, b, c;
	for(int i=0;i<n;i++) {
		int x, y; scanf("%d %d", &x, &y);
		a.push_back(x);
		b.push_back(y);
	}
	for(int i=0;i<q;i++) {
		int x; 
		scanf("%d", &x);
		c.push_back(x);
	}
	
	
	clock_t t = clock();
	for(int i=0;i<n;i++) {
		mp[a[i]] = b[i];
	}
	printf("create time: %d ms\n", (int)(clock()-t));
	
	t = clock();
	long long sum = 0;
	for(int i=0;i<q;i++) {
		if(mp.contains(c[i]) ) sum += mp[c[i]];
	}
	printf("query time: %d ms\n", (int)(clock()-t));
	
	printf("sum = %lld\n", sum);
}
/*
create time: 922 ms
query time: 504 ms
sum = 131259264960630
*/
*/