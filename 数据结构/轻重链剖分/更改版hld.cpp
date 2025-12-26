#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

namespace sgt {
    int n;
    vector<int> tr;
    vector<int> tag;
    void init(int _n) {
        n = _n;
        tr.assign(4 * n + 10, 0);
        tag.assign(4 * n + 10, 0);
    }

    void apply(int u, int l, int r, int v) {
        tr[u] += (r - l + 1) * v;
        tag[u] += v;
    }

    int Combine(int u, int v) {
        return u + v;
    }

    void Down(int u, int l, int r) {
        if (tag[u]) {
            int mid = (l + r) / 2;
            apply(u * 2, l, mid, tag[u]);
            apply(u * 2 + 1, mid + 1, r, tag[u]);
            tag[u] = 0;
        }
    }

    void _upd(int u, int l, int r, int ql, int qr, int v) {
        if (l > qr or r < ql) return;
        if (ql <= l and r <= qr) {
            apply(u, l, r, v);
            return;
        }
        Down(u, l, r);

        int mid = (l + r) / 2;
        _upd(u * 2, l, mid, ql, qr, v);
        _upd(u * 2 + 1, mid + 1, r, ql, qr, v);

        tr[u] = Combine(tr[u * 2], tr[u * 2 + 1]);
    }

    int _ask(int u, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;//注意设置幺元
        if (l >= ql && r <= qr) return tr[u];
        Down(u, l, r);
        int mid = (l + r) / 2;
        return Combine(_ask(u * 2, l, mid, ql, qr), _ask(u * 2 + 1, mid + 1, r, ql, qr));
    }

    void _set(int u, int l, int r, int pos, int v) {
        if (l > pos or r < pos) return;
        if (l == r) {
            tr[u] = v;
            tag[u] = 0;
            return;
        }
        Down(u, l, r);

        int mid = (l + r) / 2;
        _set(u * 2, l, mid, pos, v);
        _set(u * 2 + 1, mid + 1, r, pos, v);

        tr[u] = Combine(tr[u * 2], tr[u * 2 + 1]);
    }
    void set(int pos, int v) { return _set(1, 1, n, pos, v); }
    void upd(int ql, int qr, int v) { return _upd(1, 1, n, ql, qr, v); };
    void upd(int pos, int v) { return _upd(1, 1, n, pos, pos, v); };
    int ask(int ql, int qr) { return _ask(1, 1, n, ql, qr); };
}


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


void Prework() {

}
void Solve() {
    int n;cin >> n;
    sgt::init(n);
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
    auto modify_V = [&](int u, int v) {//修改u的权值为v
        sgt::set(hld.dfn[u], v);
        };
    auto query_V = [&](int u, int v) {//查询u到v的路径点权和
        return hld.get_pat(u, v, [&](int l, int r) {return sgt::ask(l, r);}, 0);
        };
    auto init = [&](int isEdge) {//如果是边权:将边权寄存在较深的节点
        if (!isEdge) {
            for (int i = 1; i <= n; i++) {
                sgt::set(hld.dfn[i], a[i]);
            }
        }
        else {
            for (int i = 1;i <= n - 1;i++) {
                auto [u, v, w] = edg[i];
                if (hld.dep[u] < hld.dep[v]) sgt::set(hld.dfn[v], w);
                else sgt::set(hld.dfn[u], w);
            }
        }
        };
    auto modify_E = [&](int u, int v, int w) {//修改边(u,v)的权值为w
        if (hld.dep[u] < hld.dep[v]) swap(u, v);
        sgt::set(hld.dfn[u], w);
        };
    auto query_E = [&](int u, int v) {//查询u到v的路径边权和
        return hld.get_pat(u, v, [&](int l, int r) {return sgt::ask(l, r);}, 1);
        };
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    // cin >> T;
    Prework();
    while (T--) Solve();
}
