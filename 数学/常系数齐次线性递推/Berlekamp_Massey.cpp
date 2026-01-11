namespace Berlekamp_Massey {
    const int MOD = 998244353;
    int qpow(int x, int n) {
        int res = 1;
        while (n) {
            if (n & 1) res = 1LL * res * x % MOD;
            x = 1LL * x * x % MOD;
            n >>= 1;
        }
        return res;
    }
    int inv(int x) {
        return qpow(x, MOD - 2);
    }
    vector<int> run(const vector<int>& a) {//求出满足给定序列a的最短线性递推式
        vector<int> c, pre_c, tmp;
        int pre_i = -1, pre_d = 0;
        for (int i = 0;i < a.size();i++) {
            int d = a[i];//d = a[i] - 当前猜测递推式算出的值
            for (int j = 0;j < c.size();j++) {
                d = (d - 1LL * c[j] * a[i - j - 1]) % MOD;
            }
            if (d == 0) continue;//第i项符合猜测递推式
            if (pre_i == -1) {
                c.assign(i + 1, 0);
                pre_i = i;
                pre_d = d;
                continue;
            }
            int ol = c.size();
            int nl = i - pre_i + pre_c.size();
            if (nl > ol) {
                tmp = c;
                c.resize(nl);
            }
            int delta = d * inv(pre_d) % MOD;
            c[i - pre_i - 1] = (c[i - pre_i - 1] + delta) % MOD;
            for (int j = 1;j <= pre_c.size();j++) {
                c[i - pre_i + j - 1] = (c[i - pre_i + j - 1] - delta * pre_c[j - 1]) % MOD;
            }
            if (nl > ol) {
                pre_c = tmp;
                pre_i = i;
                pre_d = d;
            }
        }
        return c;
    }
    //f[n] = c[0]f[n-1]+C[1]F[n-2]+...+C[k]F[n-k] ==> F[k] = C[0]F[k-1]+C[1]F[k-2]+...+C[k-1]F[0]
}//0-based: a
