vector<int> dp(N, -1);
auto DP = [&](int x) {
    auto s = to_string(x);
    int n = s.size();
    auto dfs = [&](auto&& dfs, int i, int isn, int lim)->ll {
        if (i == n) return isn;
        if (!lim && isn && dp[i] >= 0) return dp[i];
        int res = 0;
        int mx = lim ? s[i] - '0' : 9;
        if (!isn) res += dfs(dfs, i + 1, 0, 0);
        for (int d = isn ^ 1;d <= mx;d++) {//d = digit, i = pos
            res += dfs(dfs, i + 1, 1, lim && (d == mx));
        }
        if (!lim && isn) dp[i] = res;
        return res;
        };
    return dfs(dfs, 0, 0, 1);
    };
