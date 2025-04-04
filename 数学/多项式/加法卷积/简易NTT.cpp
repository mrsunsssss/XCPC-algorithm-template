const int MOD = 998244353;
const int ROOT = 3;//GET_ROOT(998244353) = 3;GET_ROOT(1e9+7) = 5;

int GET_ROOT(int mod) {//MOD is prime
    int phi = mod - 1;
    for (int i = 2, p = 1; i <= mod; ++i, p = 1) {
        if (gcd(i, mod) != 1) continue;
        for (int a = i; a != 1; (a *= i) %= mod, ++p);
        if (p == phi) return i;
    }
    return -1;
}

int qp(int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        n >>= 1;
    }
    return res;
}

void ntt(vector<int>& a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = qp(ROOT, (MOD - 1) / len);
        if (inv) wlen = qp(wlen, MOD - 2);
        for (int i = 0; i < n; i += len) {
            int w = 1, mid = len / 2;
            for (int j = 0; j < mid; j++) {
                int offset = i + j;
                int u = a[offset], v = 1LL * a[offset + mid] * w % MOD;
                a[offset] = (u + v) % MOD;
                a[offset + mid] = (u - v + MOD) % MOD;
                w = 1LL * w * wlen % MOD;
            }
        }
    }
    if (inv) {
        int invn = qp(n, MOD - 2);
        for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * invn % MOD;
    }
}

vector<int> convolution(vector<int> a, vector<int> b) {
    int sz = 1;
    int n = a.size() + b.size() - 1;
    while (sz < n) sz <<= 1;
    a.resize(sz, 0);b.resize(sz, 0);
    ntt(a, 0); ntt(b, 0);
    for (int i = 0; i < sz; i++) a[i] = 1LL * a[i] * b[i] % MOD;
    ntt(a, 1);
    a.resize(n);
    return a;
}
vector<int> convolution_loop(vector<int> a, vector<int> b, int m) {//C[(i+j)%m]+=A[i]*B[j]
    int sz = 1;
    while (sz < 2 * m) sz <<= 1;
    a.resize(sz, 0); b.resize(sz, 0);
    ntt(a, 0); ntt(b, 0);
    for (int i = 0; i < sz; i++) a[i] = 1LL * a[i] * b[i] % MOD;
    ntt(a, 1);
    vector<int> res(m);
    for (int i = 0; i < sz; i++) res[i % m] = (res[i % m] + a[i]) % MOD;
    return res;
}

vector<int> convolution_loop_qp(vector<int> base, int k, int m) {
    vector<int> res(m, 0);
    res[0] = 1;
    while (k) {
        if (k & 1) res = convolution_loop(res, base, m);
        base = convolution_loop(base, base, m);
        k >>= 1;
    }
    return res;
}
