template<class T> struct StaticTable {
    int n;
    vector<T> a;
    vector<array<T, 31>> dp;
    function<T(T, T)> func;
    StaticTable() {};
    StaticTable(vector<T> a, function<T(T, T)> F) {
        run(a, F);
    }
    void run(vector<T>& a) {
        run(a, [&](T x, T y) { return max(x, y); });
    }
    void run(vector<T>& a, function<T(T, T)> F) {
        this->a = a;
        this->func = F;
        this->n = (int)a.size() - 1;
        this->dp.assign(n + 1, {});
        for (int i = 1; i <= n; i++) dp[i][0] = a[i];
        for (int j = 1; j <= 30; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                dp[i][j] = func(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T query(int l, int r) {
        int k = __lg(r - l + 1);
        return func(dp[l][k], dp[r - (1 << k) + 1][k]);
    }
};
