template <typename T>
struct set_min {
    priority_queue<T, vector<T>, greater<T>> heap, del;
    void op() {
        while (del.size() and heap.size() and heap.top() == del.top()) {
            heap.pop();
            del.pop();
        }
    }
    void push(T x) { heap.push(x); }
    void erase(T x) { del.push(x); }
    T top() {
        op();
        return heap.top();
    }
    int size() {
        op();
        return heap.size() - del.size();
    }
};

template <typename T>
struct set_max {
    priority_queue<T> heap, del;
    void op() {
        while (del.size() and heap.size() and heap.top() == del.top()) {
            heap.pop();
            del.pop();
        }
    }
    void push(T x) { heap.push(x); }
    void erase(T x) { del.push(x); }
    T top() {
        op();
        return heap.top();
    }
    int size() {
        op();
        return heap.size() - del.size();
    }
};

template<class T>
struct set_mid {
    set_max<T> pq_left;
    set_min<T> pq_right;
    void op() {
        while (pq_left.size() > pq_right.size()) {
            T tmp = pq_left.get();
            pq_left.erase(tmp);
            pq_right.insert(tmp);
        }
        while (pq_left.size() < pq_right.size()) {
            T tmp = pq_right.get();
            pq_right.erase(tmp);
            pq_left.insert(tmp);
        }
    }
    void insert(T a) {
        if (pq_left.size() != 0 && pq_left.get() > a) pq_left.insert(a);
        else pq_right.insert(a);
    }
    void erase(T a) {
        if (pq_left.size() != 0 && pq_left.get() >= a) pq_left.delate(a);
        else pq_right.delate(a);
    }
    pair<T, T> get() {
        op();
        assert(pq_left.size() != 0);
        if (pq_left.size() == pq_right.size()) {
            return { pq_left.get(),pq_right.get() };
        }
        else return { pq_left.get(),pq_left.get() };
    }
    int size() {
        return pq_left.size() + pq_right.size();
    }
};
