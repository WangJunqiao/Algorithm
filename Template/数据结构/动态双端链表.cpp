template<typename T>
struct LinkedList {

    struct Entry {
        T value;
        Entry *pre, *nxt;
    } *head;
    int _size;

    LinkedList() {
        head = new Entry();
        head->pre = head->nxt = head;
        _size = 0;
    }

    LinkedList(const LinkedList &list) {
        head = new Entry();
        head->pre = head->nxt = head;
        *this = list;
    }

    LinkedList &operator=(const LinkedList &list) {
        clear();
        _size = list._size;
        Entry *p = list.head->nxt, *p1 = head, *p2;
        while (p != list.head) {
            p2 = new Entry();
            p2->value = p->value;
            p2->pre = p1;
            p1->nxt = p2;
            p2->nxt = head;
            head->pre = p2;
            p1 = p1->nxt;
            p = p->nxt;
        }
        return *this;
    }

    void push_back(T value) {
        Entry *p = new Entry(), *l = head->pre;
        p->value = value;
        p->pre = l;
        l->nxt = p;
        p->nxt = head;
        head->pre = p;
        _size++;
    }

    void push_front(T value) {
        Entry *p = new Entry(), *l = head->nxt;
        p->value = value;
        p->pre = head;
        head->nxt = p;
        p->nxt = l;
        l->pre = p;
        _size++;
    }

    void pop_front() {
        assert(_size > 0);
        Entry *p = head->nxt, *pp = p->nxt;
        delete p;
        head->nxt = pp;
        pp->pre = head;
        _size--;
    }

    void pop_back() {
        assert(_size > 0);
        Entry *p = head->pre, *pp = p->pre;
        delete p;
        head->pre = pp;
        pp->nxt = head;
        _size--;
    }

    T &front() {
        return head->nxt->value;
    }

    bool empty() {
        return _size == 0;
    }

    int size() {
        return _size;
    }

    void clear() {
        Entry *tmp = head->nxt, *tmp2;
        while (tmp != head) {
            tmp2 = tmp->nxt;
            delete tmp;
            tmp = tmp2;
        }
        head->pre = head->nxt = head;
        _size = 0;
    }

    typedef Entry *iterator;

    iterator begin() {
        return head->nxt;
    }

    iterator end() {
        return head;
    }

    Entry *erase(Entry *p) {
        Entry *pre = p->pre, *nxt = p->nxt;
        delete p;
        pre->nxt = nxt;
        nxt->pre = pre;
        return nxt;
    }
    //--------------------------------------------------------------

    ~LinkedList() {
        clear();
        delete head;
    }
};