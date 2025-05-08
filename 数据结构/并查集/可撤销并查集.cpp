struct Rollback_DSU {
    vector<int> p, siz;
    vector<array<int, 2>> his;
    int n;
    Rollback_DSU(int n) :n(n), p(n), siz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) {
        while (p[x] != x) x = p[x];
        return x;
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
        his.push_back({ x,y });
        siz[x] += siz[y];
        p[y] = x;
        return 1;
    }
    int time() {
        return his.size();
    }
    int size(int x) {
        return siz[find(x)];
    }
    void rollback(int tim) {
        while (his.size() > tim) {
            auto [x, y] = his.back();
            his.pop_back();
            p[y] = y;
            siz[x] -= siz[y];
        }
    }
};
