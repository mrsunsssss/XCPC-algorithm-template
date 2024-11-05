vector<int> dp(N, -1);
auto DP = [&](int x)->ll {
    auto s = to_string(x);
    int n = s.size();
    auto dfs = [&](auto&& dfs, int i, int isn, int lim)->ll {
        if (i == n) return isn;
        if (!lim && isn && dp[i] != -1) return dp[i];
        int res = 0;
        int mx = lim ? s[i] - '0' : 9;
        if (!isn) res += dfs(dfs, i + 1, 0, 0);
        for (int i = 1;i <= mx;i++) {
            res += dfs(dfs, i + 1, 1, lim && (i == mx));
        }
        if (!lim && isn) dp[i] = res;
        return res;
        };
    return dfs(dfs, 0, 0, 1);
    };
