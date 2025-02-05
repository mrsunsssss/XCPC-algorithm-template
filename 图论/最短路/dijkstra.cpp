vector<int> dis(n + 1);
auto dijkstra = [&](int s, vector<int>& dis) {
    dis.assign(n + 1, 1e18);
    dis[s] = 0;
    vector<int> vis(n + 1);
    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> q;
    q.push({ dis[s],s });
    while (q.size()) {
        auto [d, u] = q.top();q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : g[u]) {
            //这一步本质上是一个剪枝，防止将更劣的答案存入队列，能快4~5倍
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({ dis[v],v });
            }
        }
    }
    };
dijkstra(s, dis);
