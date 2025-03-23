template<typename T, typename Compare = less<>>
struct Krsucal_Tree {
    int n;
    vector<int> p, dep, vec;
    vector<T> val;
    vector<tuple<T, int, int>> E;
    vector<array<int, 21>> dp;
    vector<vector<int>> g;
    Krsucal_Tree(int n) : n(n) {
        g.resize(n + 1);
        p.assign(n + 1, 0);
        vec.clear();
        iota(p.begin(), p.end(), 0);
    };
    void addEdge(int u, int v, T w) {
        E.push_back({ w, u, v });
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    T Kruskal(Compare comp = Compare()) {
        sort(E.begin(), E.end(), comp);
        T res = 0;
        int cnt = 0;
        for (int i = 0; i < E.size(); i++) {
            auto [w, u, v] = E[i];
            int pu = find(u), pv = find(v);
            if (pu != pv) {
                p[pv] = pu;
                vec.push_back(i);
                res += w;
                cnt++;
            }
            if (cnt == n - 1) return res;
        }
        return -1;
    }
    void build() {
        Kruskal();
        g.resize(2 * n);
        p.resize(2 * n);
        val.resize(2 * n);
        iota(p.begin(), p.end(), 0);
        for (int i = 0; i < vec.size(); i++) {
            auto [w, u, v] = E[vec[i]];
            int pu = find(u), pv = find(v);
            p[pu] = p[pv] = n + i + 1;
            val[n + 1 + i] = w;
            g[n + 1 + i].push_back(pu);
            g[n + 1 + i].push_back(pv);
        }
        dep.assign(2 * n, 1);
        dp.assign(2 * n, {});
        auto dfs = [&](auto&& dfs, int u)->void {
            for (int i = 1; i <= 20; i++) {
                dp[u][i] = dp[dp[u][i - 1]][i - 1];
            }
            for (auto v : g[u]) {
                if (v == p[u]) continue;
                dep[v] = dep[u] + 1;
                dp[v][0] = u;
                dfs(dfs, v);
            }
            };
        for (int i = 1; i < p.size(); i++) {
            if (p[i] == i) {
                dfs(dfs, i);
            }
        }
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = 20; i >= 0; i--) {
            if (dep[dp[u][i]] >= dep[v]) {
                u = dp[u][i];
            }
        }
        if (u == v) return v;
        for (int i = 20; i >= 0; i--) {
            if (dp[u][i] != dp[v][i]) {
                u = dp[u][i], v = dp[v][i];
            }
        }
        return dp[u][0];
    }

    T dis(int u, int v) {//最小化u到v的最大边权
        return val[lca(u, v)];
    }
};
