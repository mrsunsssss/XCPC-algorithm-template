using ull = unsigned long long;
const ull MASK = mt19937_64(time(nullptr))();
ull H(ull x) {
    x ^= MASK;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= MASK;
    return x;
}
void dfs(int u, int p) {
    dp[u] = 1;
    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
        dp[u] += H(dp[v]);
    }
}
