//判断相等用了K的==
template<typename K, typename V, unsigned int(*hash)(const K &k), int MOD>
struct HashMap {

    struct Entry {
        K k;
        V v;
        Entry *p;
    } **l;
    int _size;

    HashMap() {
        l = (Entry **) malloc(MOD * sizeof(Entry *));
        for (int i = 0; i < MOD; i++) l[i] = NULL;
        _size = 0;
    }

    HashMap(const HashMap &map) {
        l = (Entry **) malloc(MOD * sizeof(Entry *));
        for (int i = 0; i < MOD; i++) l[i] = NULL;
        *this = map;
    }

    HashMap &operator=(const HashMap &map) {
        clear();
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

    void clear() {
        Entry *tmp;
        for (int i = 0; i < MOD; i++) {
            while (l[i]) {
                tmp = l[i];
                l[i] = l[i]->p;
                delete tmp;
            }
        }
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
        return p;
    }

    ~HashMap() {
        clear();
        free(l);
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


    //-----------------iterator, thread safe------------------------
    int id;
    Entry *ptr;

    void beginIterate() {
        id = 0;
        ptr = l[0];
    }

    bool hasNext() {
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