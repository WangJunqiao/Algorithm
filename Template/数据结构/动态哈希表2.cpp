//K判相等用了==操作符
template<typename K, typename V, unsigned int(*hash)(const K &k)>
struct HashMap {
    static const int ALPHA = 4; //MOD增长速率为2*ALPHA
    struct Entry {
        K k;
        V v;
        Entry *p;
    } **l;
    int _size, MOD;

    HashMap(int capcity = 0) {
        int cap = 7;
        while (cap < capcity) cap = cap * 2 + 1;
        _init(cap);
    }

    HashMap(const HashMap &map) {
        *this = map;
    }

    HashMap &operator=(const HashMap &map) {
        _init(map.MOD);
        Entry *p, **p1, *p2;
        for (int i = 0; i < MOD; i++) {
            p = map.l[i];
            p1 = &l[i];
            while (p != NULL) {
                p2 = new Entry();
                p2->k = p->k;
                p2->v = p->v;
                p2->p = NULL;
                *p1 = p2;
                p1 = &((*p1)->p);
                p = p->p;
            }
        }
        _size = map._size;
        return *this;
    }

    int _get_mod(int MOD) {
        int M = MOD * ALPHA * 2;
        while (M--) {
            bool np = false;
            for (int i = 2; i * i <= M; i++)
                if (M % i == 0) {
                    np = true;
                    break;
                }
            if (!np) break;
        }
        return M;
    }

    void _free() {
        if (l) {
            Entry *tmp;
            for (int i = 0; i < MOD; i++) {
                while (l[i]) {
                    tmp = l[i];
                    l[i] = l[i]->p;
                    delete tmp;
                }
            }
            free(l);
            l = NULL;
        }
    }

    void _init(int _MOD) {
        MOD = _MOD;
        l = (Entry **) malloc(MOD * sizeof(Entry *));
        for (int i = 0; i < MOD; i++) l[i] = NULL;
        _size = 0;
    }

    Entry *_find(const K &k) {
        int i = hash(k) % MOD;
        for (Entry *tmp = l[i]; tmp; tmp = tmp->p)
            if (tmp->k == k) return tmp;
        return NULL;
    }

    Entry *_insert(const K &k, const V &v) { //插入
        Entry *p;
        if ((p = _find(k)) != NULL) {
            p->v = v;
            return p;
        }
        _size++;
        int i = hash(k) % MOD;
        p = new Entry();
        p->k = k;
        p->v = v;
        p->p = l[i];
        l[i] = p;

        if (_size > MOD * ALPHA) {
            _rebuild();
            return _find(k);
        } else {
            return p;
        }
    }

    void _rebuild() {
        HashMap map;
        map._init(_get_mod(MOD));
        for (beginIterate(); hasNext();) {
            Entry *e = next();
            map._insert(e->k, e->v);
        }
        *this = map;
    }

    ~HashMap() {
        _free();
    }

    bool contains(const K &k) {
        return _find(k) != NULL;
    }

    V &operator[](const K &k) {
        Entry *p = _find(k);
        if (p) return p->v;
        return _insert(k, V())->v;
    }

    int size() {
        return _size;
    }

    void clear() {
        _free();
        _init();
    }

    //-----iterate------------------------------
    int id;
    Entry *ptr;

    void beginIterate() {
        id = 0;
        ptr = l[0];
    }

    bool hasNext() {
        assert(id != -1);
        while (ptr == NULL) {
            ++id;
            if (id >= MOD) return false;
            ptr = l[id];
        }
        return true;
    }

    Entry *next() {
        Entry *t = ptr;
        ptr = ptr->p;
        return t;
    }
};