struct LCA {
    int n;
    vector<vector<int>> dp;
    vector<int> dep;
    LCA(int _n) :n(_n) {
        dp.assign(21, vector<int>(n + 1));
        dep.assign(n + 1, 0);
    }
    void dfs(vector<vector<int>>& g, int u, int p) {
        dep[u] = dep[p] + 1;
        for (auto v : g[u]) {
            if (v == p) continue;
            dp[0][v] = u;
            dfs(g, v, u);
        }
    }
    void init(vector<vector<int>>& g) {
        dfs(g, 1, 1);
        for (int i = 1;i <= 20;i++) {
            for (int j = 1;j <= n;j++) {
                dp[i][j] = dp[i - 1][dp[i - 1][j]];
            }
        }
    }
    int query(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = 20;i >= 0;i--) {
            if (dep[dp[i][u]] >= dep[v]) {
                u = dp[i][u];
            }
        }
        if (u == v) return v;
        for (int i = 20;i >= 0;i--) {
            if (dp[i][u] != dp[i][v]) {
                u = dp[i][u], v = dp[i][v];
            }
        }
        return dp[0][u];
    }
};
