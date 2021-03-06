//��ɢ��
template<typename T = int>
struct Discretization {
    T data[110000];
    int size;

    void init() {
        size = 0;
    }

    void add(T a) {
        data[size++] = a;
    }

    void uniform() {
        sort(data, data + size);
        size = unique(data, data + size) - data;
    }

    int get_id(T value) {
        int id = lower_bound(data, data + size, value) - data;
        if (id < size && data[id] == value)
            return id;
        return -1;
    }
};

//init(). add(). uniform(); get_id(..);
Discretization<int> disc;