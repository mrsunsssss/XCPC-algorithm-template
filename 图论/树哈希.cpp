//https://uoj.ac/problem/763
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

using ull = unsigned long long;
const ull MASK = mt19937_64(time(0))();
ull H(ull x) {
    x ^= MASK;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= MASK;
    return x;
}

void Prework() {

}
void Solve() {
    int n;cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1;i < n;i++) {
        int u, v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> dp(n + 1);
    set<ull> st;
    auto dfs = [&](auto&& dfs, int u, int p)->void {
        dp[u] = 1;
        for (int v : g[u]) {
            if (v == p) continue;
            dfs(dfs, v, u);
            dp[u] += H(dp[v]);
        }
        st.insert(dp[u]);
        };
    dfs(dfs, 1, 1);
    cout << st.size() << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    //cin >> T;
    Prework();
    while (T--) Solve();
}
