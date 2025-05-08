struct Rollback_DSU {
    vector<int> p, siz;
    vector<array<int, 2>> his;
    int n;
    Rollback_DSU() {}
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

Rollback_DSU d;

namespace sgt {
    int n;
    vector<vector<array<int, 2>>> tr;
    void init(int _n) {
        n = _n;
        tr.assign(4 * n + 1, {});
    }
    void insert(int u, int l, int r, int ql, int qr, array<int, 2> x) {
        if (l > qr or r < ql) {
            return;
        }
        if (ql <= l and r <= qr) {
            tr[u].push_back(x);
            return;
        }
        int m = l + r >> 1;
        insert(2 * u, l, m, ql, qr, x);
        insert(2 * u + 1, m + 1, r, ql, qr, x);
    }
    void insert(int ql, int qr, array<int, 2> x) {
        insert(1, 1, n, ql, qr, x);
    }
    void solve(int u, int l, int r) {
        int tim = d.time();
        for (auto [x, y] : tr[u]) {
            d.merge(x, y);
        }
        if (l == r) {
            ;
        }
        else {
            int m = l + r >> 1;
            solve(u * 2, l, m);
            solve(u * 2 + 1, m + 1, r);
        }
        d.rollback(tim);
    }
    void solve() {
        solve(1, 1, n);
    }
}
