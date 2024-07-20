struct BIT {
    int n;
    vector<int> tr;
    BIT(int n) : n(n), tr(n + 1) {}
    inline int lbt(int x) { return x & -x; }
    void add(int i, int val) {
        for (; i <= n; i += lbt(i)) {
            tr[i] += val;
        }
    }
    int sum(int i) {
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
};
namespace CDQ {
    struct info {
        int a, b, c;
        int id, res;
        int cnt;
        bool friend operator <(const info& u, const info& v) {
            if (u.a != v.a) return u.a < v.a;
            if (u.b != v.b) return u.b < v.b;
            return u.c < v.c;
        }
        bool friend operator == (const info& u, const info& v) {
            return u.a == v.a && u.b == v.b && u.c == v.c;
        }
    };
    bool cmp(const info& u, const info& v) {
        return u.b < v.b;
    }
    const int MAXN = 2e5;
    BIT tr(MAXN);
    auto run(vector<array<int, 3>> b) {
        int n = b.size();
        vector<info> a(n);
        for (int i = 0;i < n;i++) {
            a[i].a = b[i][0], a[i].b = b[i][1], a[i].c = b[i][2];
            a[i].id = i, a[i].res = 0, a[i].cnt = 1;
        }
        auto CDQ = [&](auto&& CDQ, int l, int r) {
            if (l == r) return;
            int mid = l + r >> 1;
            CDQ(CDQ, l, mid);
            CDQ(CDQ, mid + 1, r);
            sort(a.begin() + l, a.begin() + mid + 1, cmp);
            sort(a.begin() + mid + 1, a.begin() + r + 1, cmp);
            int i, j;
            for (i = l, j = mid + 1;j <= r;j++) {
                while (i <= mid && a[i].b <= a[j].b) {
                    tr.add(a[i].c, a[i].cnt);
                    i++;
                }
                a[j].res += tr.query(1, a[j].c);
            }
            for (int k = l;k < i;k++) tr.add(a[k].c, -a[k].cnt);
            };
        sort(a.begin(), a.end());
        int tot = 0;
        for (int i = 1;i < n;i++) {
            if (a[i] == a[tot]) a[tot].cnt += 1;
            else a[++tot] = a[i];
        }
        a.resize(tot + 1);
        CDQ(CDQ, 0, tot);
        return a;
    }
}
