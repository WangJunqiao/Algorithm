//����ʽչ��,����ĸ����չ��****
template<typename T>  //ϵ������������T
struct Polynomial {
    map <int, T> mp; //x����, ϵ��
    //**************************
    Polynomial() {
        mp.clear();
    }

    void add(T c, int p) { //�� c * x^p
        mp[p] += c;
    }

    void get_c(int p) {
        return mp[p];
    }

    void zero() { //��0
        mp.clear();
    }

    //���Ӷ�O(n*n*logn)
    Polynomial<T> operator*(const Polynomial &p) const {
        Polynomial<T> ret;
        for (typename map<int, T>::const_iterator it1 = mp.begin(); it1 != mp.end(); ++it1) {
            for (typename map<int, T>::const_iterator it2 = p.mp.begin(); it2 != p.mp.end(); ++it2) {
                ret.mp[it1->first + it2->first] += it1->second * it2->second;
            }
        }
        return ret;
    }

    //���Ӷ�O(n*logn)
    Polynomial<T> operator+(const Polynomial<T> &p) const {
        Polynomial<T> ret = *this;
        for (typename map<int, T>::const_iterator it = p.mp.begin(); it != p.mp.end(); ++it) {
            ret.mp[it->first] += it->second;
        }
        return ret;
    }

    void print() const {
        typename map<int, T>::const_iterator it1 = mp.end();
        bool first = true;
        do {
            --it1;
            if (!first) putchar('+');
            if (it1->second != 1) cout << it1->second;
            if (it1->first != 1)printf("x^%d", it1->first);
            else putchar('x');
            first = false;
        } while (it1 != mp.begin());
        cout << endl;
    }
};