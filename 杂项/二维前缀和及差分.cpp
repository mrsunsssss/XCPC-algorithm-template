    auto get_sum = [&](vector<vector<int>>& A) {
        int n = (int)a.size() - 1, m = (int)a[0].size() - 1;
        auto b = a;
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
            }
        }
        return b;
        };
    auto get_sum = [&](vector<vector<int>>& a) {
        int n = (int)a.size() - 1, m = (int)a[0].size() - 1;
        auto b = a;
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                b[i][j] += b[i][j - 1];
            }
        }
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                b[i][j] += b[i - 1][j];
            }
        }
        return b;
        };
    auto add_val = [&](vector<vector<int>>& a, int x1, int y1, int x2, int y2, int val) {
        int n = (int)a.size() - 1, m = (int)a[0].size() - 1;
        auto b = a;
        b[x1][y1] += val;
        if (y2 < m) b[x1][y2 + 1] -= val;
        if (x2 < n) b[x2 + 1][y1] -= val;
        if (x2 < n and y2 < m) b[x2 + 1][y2 + 1] += val;
        return b;
        };
    auto sum = [&](vector<vector<int>>& sum, int x1, int y1, int x2, int y2) {
        int n = (int)sum.size() - 1, m = (int)sum[0].size() - 1;
        return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
        };
