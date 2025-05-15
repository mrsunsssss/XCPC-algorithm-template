struct RMQ_LCA {
    int n, idx;
    vector<int> dfn;
    vector<vector<int>> adj;
    inline static int f[21][N];
    inline static int dep[N];
    int getmin(int x, int y) { return dfn[x] < dfn[y] ? x : y; }
    RMQ_LCA() {}
    RMQ_LCA(int n, vector<vector<int>>& adj, int root) :n(n), adj(adj), idx(0) {
        for (int j = 0, lgn = __lg(n);j <= lgn;j++) {
            for (int i = 0;i <= n;i++) f[j][i] = 0;
        }
        dfn.resize(n + 1);
        dfs(root);
        for (int j = 1, lgn = __lg(n); j <= lgn; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                f[j][i] = getmin(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    void dfs(int u, int p = 0) {
        f[0][dfn[u] = ++idx] = p;
        for (auto v : adj[u]) {
            if (v != p) {
                dep[v] = dep[u] + 1;
                dfs(v, u);
            }
        }
    }

    int query(int l, int r) {
        int len = __lg(r - l + 1);
        return getmin(f[len][l], f[len][r - (1 << len) + 1]);
    }

    int lca(int u, int v) {
        if (u == v) return u;
        u = dfn[u], v = dfn[v];
        if (u > v) swap(u, v);
        return query(u + 1, v);
    }
    int dis(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
};
