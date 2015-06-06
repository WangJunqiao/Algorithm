template<typename T, unsigned int(*hash)(const T k), int MOD>
struct HashSet {

    struct Entry {
        T k;
        Entry *p;
    } **l;

    HashSet() {
        l = (Entry **) malloc(MOD * sizeof(Entry *));
        for (int i = 0; i < MOD; i++) l[i] = NULL;
        //printf("HashSet.default constructor callled.\n");
    }

    HashSet(const HashSet &set) {
        l = (Entry **) malloc(MOD * sizeof(Entry *));
        for (int i = 0; i < MOD; i++) l[i] = NULL;
        *this = set;
        //printf("HashSet.copy constructor callled.\n");
    }

    HashSet &operator=(const HashSet &set) {
        clear();
        Entry *p, **p1, *p2;
        for (int i = 0; i < MOD; i++) {
            p = set.l[i];
            p1 = &l[i];
            while (p != NULL) {
                //p2 = (Entry*)malloc(sizeof(Entry));
                p2 = new Entry();
                p2->k = p->k;
                p2->p = NULL;
                *p1 = p2;
                p1 = &((*p1)->p);
                p = p->p;
            }
        }
        //printf("HashSet.operator= callled.\n");
        return *this;
    }

    void clear() {
        Entry *tmp;
        for (int i = 0; i < MOD; i++) {
            while (l[i]) {
                tmp = l[i];
                l[i] = l[i]->p;
                //free(tmp);
                delete tmp;
            }
        }
        //printf("HashSet.clear() callled.\n");
    }

    /**********************************************************************
     * 判断相等使用了==操作符 
     **********************************************************************/
    Entry *find(T k) {
        int i = hash(k) % MOD;
        for (Entry *tmp = l[i]; tmp; tmp = tmp->p)
            if (tmp->k == k) return tmp;
        return NULL;
    }

    void insert(T k) { //插入
        if (find(k) != NULL)
            return;
        int i = hash(k) % MOD;
        Entry *tmp = new Entry();
        tmp->k = k;
        tmp->p = l[i];
        l[i] = tmp;
    }

    //-----------------iterator, thread safe------------------------

    struct iterator {
        int id;
        Entry *ptr;
        HashSet *set;

        iterator(HashSet *hs = NULL) {
            set = hs;
            if (hs) {
                id = 0;
                ptr = hs->l[0];
            } else {
                id = -1;
            }
        }

        bool hasNext() {
            assert(id != -1);
            while (ptr == NULL) {
                ++id;
                if (id >= MOD) return false;
                ptr = set->l[id];
            }
            return true;
        }

        T &next() {
            T &t = ptr->k;
            ptr = ptr->p;
            return t;
        }
    };

    iterator get_iterator() {
        return iterator(this);
    }
    //--------------------------------------------------------------

    ~HashSet() {
        clear();
        free(l);
        //printf("HashSet.~HashSet() callled.\n");
    }
};
