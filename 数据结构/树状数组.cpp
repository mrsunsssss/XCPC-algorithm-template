struct BIT {
    int n;
    vector<int> tr;
    BIT(int n) : n(n), tr(n + 1) {}

    inline int lbt(int x) { return x & -x; }

    void add(int i, int val) {
        i++;
        for (; i <= n; i += lbt(i)) {
            tr[i] += val;
        }
    }
    int sum(int i) {
        i++;
        int res = 0;
        for (; i > 0; i -= lbt(i)) {
            res += tr[i];
        }
        return res;
    }
    int query(int l, int r) {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
    int find(int val) {//find k such that a[1~k] >= val
        int x = 0, res = 0;
        for (int i = __lg(n); i >= 0; --i) {
            if (x + (1 << i) <= n && tr[x + (1 << i)] < val) {
                x += 1 << i;
                val -= tr[x];
                res += 1 << i;
            }
        }
        return res + 1;
    }
};


//1-index
