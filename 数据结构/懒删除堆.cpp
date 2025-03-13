template <typename T, typename Compare = greater<T>>
struct DHeap {
    priority_queue<T, vector<T>, Compare> heap, del;
    DHeap(const Compare& comp = Compare()) : heap(comp), del(comp) {}
    void push(T x) { heap.push(x); }
    void erase(T x) { del.push(x); }
    T top() {
        while (heap.size() and del.size() && heap.top() == del.top()) {
            heap.pop();
            del.pop();
        }
        if (heap.size() == 0) {
            assert(0);
        }
        else return heap.top();
    }
    int size() {
        while (del.size() && heap.top() == del.top()) {
            heap.pop();
            del.pop();
        }
        return heap.size();
    }
};
