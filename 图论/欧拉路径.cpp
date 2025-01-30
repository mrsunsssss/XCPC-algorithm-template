vector<int> path;
vector<vector<int>> g(n + 1, vector<int>(n + 1));
vector<vector<int>> vis(n + 1, vector<int>(n + 1));
vector<int> cur(n + 1, 1);
for (int i = 1;i <= m;i++) {
    int u, v;cin >> u >> v;
    g[u][v] = g[v][u] = 1;
}
auto dfs = [&](auto&& dfs, int u)->void {
    for (;cur[u] <= n;cur[u]++) {
        int v = cur[u];
        if (g[u][v] && !vis[u][v]) {
            vis[u][v] = vis[v][u] = 1;
            dfs(dfs, v);
        }
    }
    path.push_back(u);
    };
dfs(dfs, 1);
