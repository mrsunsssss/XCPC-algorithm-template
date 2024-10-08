struct DSU {
    vector<int> p, siz;
    DSU(int n) :p(n), siz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return 0;
        if (siz[x] < siz[y]) {
            swap(x, y);
        }
        siz[x] += siz[y];
        p[y] = x;
        return 1;
    }
    int size(int x) {
        return siz[find(x)];
    }
};
