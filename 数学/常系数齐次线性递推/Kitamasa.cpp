namespace kitamasa {
    const int MOD = 998244353;
    vector<int> MUL(const vector<int>& A, const vector<int>& B, const vector<int>& C, int k) {//计算(A(x)*B(x)) (mod P(x))
        vector<int> res(2 * k);
        for (int i = 0;i < k;i++) {
            for (int j = 0;j < k;j++) {
                res[i + j] += 1LL * A[i] * B[j] % MOD;
                if (res[i + j] >= MOD) res[i + j] -= MOD;
            }
        }
        for (int i = 2 * k - 2;i >= k;i--) {
            if (res[i] == 0) continue;
            for (int j = 1;j <= k;j++) {
                res[i - j] += 1LL * res[i] * C[j] % MOD;
                if (res[i - j] >= MOD) res[i - j] -= MOD;
            }
        }
        res.resize(k);
        return res;
    }
    vector<int> POW(const vector<int>& C, int n, int k) {//计算x^n (mod P(x))
        vector<int> res(k);res[0] = 1;
        vector<int> base(k);
        if (k > 1) base[1] = 1;
        else base[0] = C[1];
        while (n) {
            if (n & 1) res = MUL(res, base, C, k);
            base = MUL(base, base, C, k);
            n >>= 1;
        }
        return res;
    }
    int RUN(vector<int> C, vector<int> F, int n) {//计算递推数列{Fn}中F[n]
        int k = (int)C.size() - 1;
        if (n < k) return F[n];
        auto t = POW(C, n, k);
        int res = 0;
        for (int i = 0;i < k;i++) res = (res + 1LL * t[i] * F[i] % MOD) % MOD;
        return res;
    }
    //F[n] = C[1]F[n-1]+C[2]F[n-2]+...+C[k]F[n-k] ==> F[k] = C[1]F[k-1]+C[2]F[k-2]+...+C[k]F[0]
}//C:1-index,F:0-index
