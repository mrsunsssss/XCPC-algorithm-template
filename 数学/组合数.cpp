int fact[N], infact[N];
int qp(int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = 1LL * res * a % MOD;
        n >>= 1, a = 1LL * a * a % MOD;
    }
    return res;
}
int inv(int x) {
    return qp(x, MOD - 2);
}
int comb(int a, int b) {//MOD为质数, a,b<=N
    if (a < 0 || b < 0 || a < b) return 0;
    return 1LL * fact[a] * infact[b] % MOD * infact[a - b] % MOD;
}
int _comb(int a, int b) {//MOD为质数, a较大,b<=N
    if (a < 0 || b < 0 || a < b) return 0;
    int res = infact[b];
    for (int i = 0;i < b;i++) res = 1LL * res * (a - i) % MOD;
    return res;
}

int comb(int a, int b, int P) {
    if (a < 0 || b < 0 || a < b) return 0;
    if (a < P and b < P) return 1LL * fact[a] * infact[b] % MOD * infact[a - b] % MOD;
    return comb(a / P, b / P, P) * comb(a % P, b % P, P) % MOD;
}
int norm(int x) {
    return (x % MOD + MOD) % MOD;
}
void Prework(int n = N - 10) {
    fact[0] = 1;
    for (int i = 1;i <= n;i++) {
        fact[i] = 1LL * fact[i - 1] * i % MOD;
    }
    infact[n] = qp(fact[n], MOD - 2);
    for (int i = n;i >= 1;i--) {
        infact[i - 1] = 1LL * infact[i] * i % MOD;
    }
}
