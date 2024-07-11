int fact[N], infact[N];
int qp(int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = res * a % MOD;
        n >>= 1, a = a * a % MOD;
    }
    return res;
}
int inv(int x) {
    return qp(x, MOD - 2);
}
int comb(int a, int b) {
    if (a < 0 || b < 0 || a < b) return 0;
    return fact[a] * infact[b] % MOD * infact[a - b] % MOD;
}
int __comb(int a, int b) {
    if (a < 0 || b < 0 || a < b) return 0;
    int res = infact[b];
    for (int i = 0;i < b;i++) res = res * (a - i) % MOD;
    return res;
}
int norm(int x) {
    return (x % MOD + MOD) % MOD;
}
void Prework(int n = 2e5) {
    fact[0] = 1;
    for (int i = 1;i <= n;i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    infact[n] = qp(fact[n], MOD - 2);
    for (int i = n;i >= 1;i--) {
        infact[i - 1] = infact[i] * i % MOD;
    }
}
