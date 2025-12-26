#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'


struct HLD {
    vector<int> p, dep, sz, hson, dfn, top, last, rnk;
    HLD(vector<vector<array<int, 2>>>& g, int root = 1) {
        int N = g.size();
        p.resize(N, -1);
        dep.resize(N, 0);
        sz.resize(N, 1);
        hson.resize(N, -1);
        function<void(int, int)> dfs = [&](int u, int pa) {
            p[u] = pa;
            if (pa != -1) dep[u] = dep[pa] + 1;
            for (auto& [v, w] : g[u]) {
                if (v == pa) continue;
                dfs(v, u);
                sz[u] += sz[v];
                if (hson[u] == -1 || sz[hson[u]] < sz[v]) {
                    hson[u] = v;
                }
            }
            };
        dfs(root, -1);
        dfn.resize(N, -1);
        top.resize(N, -1);
        last.resize(N, -1);
        rnk.resize(N, -1);
        int tm = 1;
        function<void(int, int)> dfs2 = [&](int u, int tc) {
            top[u] = tc;
            dfn[u] = tm;
            last[tc] = tm;
            rnk[tm] = u;
            tm++;
            if (hson[u] == -1) return;
            dfs2(hson[u], tc);
            for (auto& [v, w] : g[u]) {
                if (v != hson[u] && v != p[u]) dfs2(v, v);
            }
            };
        dfs2(root, root);
    }

    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = p[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    int dis(int u, int v) {
        return dep[u] + dep[v] - dep[lca(u, v)] * 2;
    }

    vector<array<int, 2>> get_path(int u, int v) {//u->v，注意可能出现 [r>l]（表示反过来走）
        vector<array<int, 2>> v1, v2;
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                v1.push_back({ dfn[u], dfn[top[u]] }), u = p[top[u]];
            }
            else {
                v2.push_back({ dfn[top[v]], dfn[v] }), v = p[top[v]];
            }
        }
        v1.reserve(v1.size() + v2.size() + 1);
        v1.push_back({ dfn[u], dfn[v] });
        reverse(v2.begin(), v2.end());
        for (auto v : v2) v1.push_back(v);
        return v1;
    }

    // 操作路径上的节点
    void add_pat(int a, int b, function<void(int, int)> op, bool isEdge) {
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            op(dfn[top[a]], dfn[a]);
            a = p[top[a]];
        }
        if (dep[a] > dep[b]) swap(a, b);
        op(dfn[a] + isEdge, dfn[b]);
    }
    int get_pat(int a, int b, function<int(int, int)> op, bool isEdge) {
        int res = 0;
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            res += op(dfn[top[a]], dfn[a]);
            a = p[top[a]];
        }
        if (dep[a] > dep[b]) swap(a, b);
        res += op(dfn[a] + isEdge, dfn[b]);
        return res;
    }

    // 操作子树
    void add_subt(int x, function<void(int, int)> op, bool isEdge) {
        op(dfn[x] + isEdge, dfn[x] + sz[x] - 1);
    }
    // 操作子树
    int get_subt(int x, function<int(int, int)> op, bool isEdge) {
        return op(dfn[x] + isEdge, dfn[x] + sz[x] - 1);
    }
};

template <class S,
    S(*op)(S, S),//op must work as S(S,S)
    S(*e)(),//e must work as S()
    class F,
    S(*mapping)(F, S),//mapping must work as F(F, S)
    F(*composition)(F, F),//compostiion must work as F(F, F)
    F(*id)()>//id must work as F()
struct lazy_segtree {
    int ceil_pow2(int n) {
        int x = 0;
        while ((1U << x) < (unsigned int)(n)) x++;
        return x;
    }
public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n((int)(v.size())) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {//a[p]=x
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {//return a[p]
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        r++;
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }//op(a[0],...,a[n-1])

    void apply(int p, F f) {
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        r++;
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {//最大的r满足g(op(l,l+1,..,r-1))=1
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {//最小的l满足g(op(l,l+1,..,r))=1
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};
//to use it: lazy_segtree<S,op,e,F,mapping,composition,id> tr(vector<S>/int);
struct S {
    int sum, len;
};
S op(S l, S r) {
    return S{ l.sum + r.sum,l.len + r.len };
}
S e() {
    return S{ 0,1 };
}
struct F {
    int add;
};
S mapping(F f, S x) {//x->f(x)
    return S{ x.sum + f.add * x.len,x.len };
}
F composition(F f, F g) { // f(g(x))
    return F{ g.add + f.add };
}
F id() {//e of F
    return F{ 0 };
}


void Prework() {

}
void Solve() {
    int n;cin >> n;
    vector<vector<array<int, 2>>> g(n + 1);
    vector<array<int, 3>> edg(n);
    for (int i = 1;i <= n - 1;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
        edg[i] = { u, v, w };
    }
    HLD hld(g, 1);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(n + 1);
    auto qr = [&](int x, int y) {
        return seg.prod(x, y).sum;
        };
    for (int i = 1;i <= n - 1;i++) {
        auto [u, v, w] = edg[i];
        if (hld.dep[u] < hld.dep[v]) seg.apply(hld.dfn[v], { w });
        else seg.apply(hld.dfn[u], { w });
    }
    int q;cin >> q;
    while (q--) {
        int op, u, v;cin >> op >> u >> v;
        if (op == 1) {
            int x = edg[u][0], y = edg[u][1];
            if (hld.dep[x] < hld.dep[y]) swap(x, y);
            int bef = seg.prod(hld.dfn[x], hld.dfn[x]).sum;
            seg.apply(hld.dfn[x], { v - bef });
        }
        else {
            cout << hld.get_pat(u, v, qr, 1) << endl;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    //cin >> T;
    Prework();
    while (T--) Solve();
}
