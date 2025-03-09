template <typename T>
struct Multiset {
    multiset<T> st;
    void clear() {
        st.clear();
    }
    void insert(T x) {
        st.insert(x);
    }
    void erase(T x) {
        st.extract(x);
    }
    int size() {
        return st.size();
    }
    T max() {
        return *st.rbegin();
    }
    T kth_max(int k) {
        auto it = st.rbegin();
        k--;
        for (;it != st.rend() and k;it++, k--);
        return *it;
    }
    T min() {
        return *st.begin();
    }
    T kth_min(int k) {
        auto it = st.begin();
        k--;
        for (;it != st.end() and k;it++, k--);
        return *it;
    }
};
