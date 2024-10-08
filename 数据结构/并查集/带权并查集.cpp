struct DSU {
    vector<int> p, siz, val;
    DSU(int n) :p(n), val(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) {
        if (p[x] != x) {
            int t = find(p[x]);
            val[x] += val[p[x]];
            p[x] = t;
        }
        return p[x];
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y, int z) {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy) {
            if (val[x] - val[y] == z) cout << "Accpet\n";
            else {
                cout << "Bug Detected " << val[x] - val[y] << endl;
            }
        }
        else {
            val[fy] = -val[y] - z + val[x];
            cout << "Accept\n";
        }

        p[fy] = fx;
        return 1;
    }
    int size(int x) {
        return siz[find(x)];
    }
};



void Prework() {

}
void Solve() {
    int n;cin >> n;
    DSU d(n + 1);
    for (int i = 1;i <= n;i++) {
        int l, r, s;cin >> l >> r >> s;
        d.merge(l, r, s);
    }
}
