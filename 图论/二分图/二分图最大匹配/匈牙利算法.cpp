#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

void Prework() {

}
void Solve() {
    int n, m, e;cin >> n >> m >> e;
    vector<vector<int>> g(n + 1);
    while (e--) {
        int u, v;cin >> u >> v;
        g[u].push_back(v);
    }
    vector<int> vis(m + 1), match(m + 1);
    auto dfs = [&](auto&& dfs, int u)->int {
        for (auto v : g[u]) {
            if (vis[v]) continue;
            vis[v] = 1;
            if (match[v] == 0 || dfs(dfs, match[v])) {
                match[v] = u;
                return 1;
            }
        }
        return 0;
        };
    int res = 0;
    for (int i = 1;i <= n;i++) {
        vis.assign(m + 1, 0);
        if (dfs(dfs, i)) res++;
    }
    cout << res << endl;

}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    //cin >> T;
    Prework();
    while (T--) Solve();
}
