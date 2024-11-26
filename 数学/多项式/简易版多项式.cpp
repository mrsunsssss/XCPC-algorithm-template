//时间复杂度均为O(n^2)
//https://www.cnblogs.com/tzcwk/p/dxs-sqr.html

const int MOD = 998244353;
int qp(int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = res * a % MOD;
        a = a * a % MOD, n >>= 1;
    }
    return res;
}

int inv(int x) {
    return qp(x, MOD - 2);
}
vector<int> PolyMul(const vector<int>& a, const vector<int>& b) {
    int deg = (int)a.size() + (int)b.size() - 2;
    vector<int> c(deg + 1);
    for (int i = 0;i < a.size();i++) {
        for (int j = 0;j < b.size();j++) {
            c[i + j] += a[i] * b[j] % MOD;
            if (c[i + j] >= MOD) c[i + j] -= MOD;
        }
    }
    return c;
}
vector<int> PolyInv(const vector<int>& a) {
    int n = a.size() - 1;
    vector<int> b(n + 1);
    int inv_a0 = inv(a[0]), neg = (MOD - inv_a0) % MOD;
    b[0] = inv_a0;
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= i;j++) {
            b[i] = (b[i] + neg * a[j] % MOD * b[i - j] % MOD) % MOD;
        }
    }
    return b;
}
vector<int> PolyDiv(vector<int> a, vector<int> b) {
    reverse(a.begin(), a.end());reverse(b.begin(), b.end());
    int n = a.size(), m = b.size();
    a.resize(n - m + 1), b.resize(n - m + 1);
    b = PolyInv(b);
    auto c = PolyMul(a, b);c.resize(n - m + 1);
    reverse(c.begin(), c.end());
    return c;
}
vector<int> PolyLn(const vector<int>& a) {// 不需要保证a[0] = 1
    int n = a.size() - 1;
    vector<int> b(n + 1);
    for (int i = 0;i <= n;i++) {
        b[i] = i * a[i];
        int sum = 0;
        for (int j = 1;j < i;j++) {
            sum = (sum + j * b[j] % MOD * a[i - j] % MOD) % MOD;
        }
        b[i] = (b[i] + MOD - sum) % MOD;
        b[i] = b[i] * inv(a[0] * i % MOD) % MOD;
    }
    return b;
}
vector<int> PolyExp(const vector<int>& a) {// 保证a[0] = 0
    int n = a.size() - 1;
    vector<int> b(n + 1);
    b[0] = 1;
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= i;j++) {
            b[i] = (b[i] + b[i - j] * a[j] % MOD * j % MOD) % MOD;
        }
        b[i] = b[i] * inv(i) % MOD;
    }
    return b;
}
// vector<int> PolyPow(vector<int> a, int k, int n) {
//     if (k == 0) {
//         vector<int> b(n);b[0] = 1;return b;
//     }
//     if (k == 1) return a;
//     auto half = PolyExp(a, k / 2, n);
//     auto res = PolyMul(half, half);res.resize(n);
//     if (k & 1) res = PolyMul(res, a), res.resize(n);
//     return res;
// }
vector<int> PolyPow(vector<int> a, int k) {
    a = PolyLn(a);
    for (int i = 0;i < a.size();i++) a[i] = a[i] * k % MOD;
    a = PolyExp(a);
    return a;
}

