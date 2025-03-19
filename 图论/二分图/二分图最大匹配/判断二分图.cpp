    vector<int> col(n + 1);
    auto dfs = [&](auto&& dfs, int u, int c) {
        col[u] = c;
        for (auto v : g[u]) {
            if (v == p) continue;
            if (col[v] == c) return 0;
            if (col[v] == 0 and dfs(dfs, v, -c) == 0) return 0;
        }
        return 1;
        };
