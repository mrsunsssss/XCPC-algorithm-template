memset(f, -1, sizeof f);
auto dp = [&](int x)->ll {
    auto a = to_string(x);
    reverse(a.begin(), a.end());
    int n = a.size();
    auto dfs = [&](auto&& dfs, int pos, int lead, int lim)->ll {
        if (pos == -1) return;
        int t = f[pos];
        if (!lim && !lead && t != -1) return t;
        t = 0;
        int mx = lim ? a[pos] - '0' : 9;
        if (lead) t += dfs(dfs, pos - 1, 1, 0);
        for (int i = lead;i <= mx;i++) {
            t += dfs(dfs, pos - 1, 0, lim && (i == mx));
        }
        if (!lim && !lead) f[pos] = t;
        return t;
        };
    int res = 0;
    res += dfs(dfs, n - 1, 1, 1);
    return res;
    };
