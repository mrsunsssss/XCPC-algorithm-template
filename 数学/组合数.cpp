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
int comb(int a, int b) {//MOD is prime, a,b<=N
    if (a < 0 || b < 0 || a < b) return 0;
    return 1LL * fact[a] * infact[b] % MOD * infact[a - b] % MOD;
}
int __comb(int a, int b) {//MOD is prime, a=1e9,b<=N
    if (a < 0 || b < 0 || a < b) return 0;
    int res = infact[b];
    for (int i = 0;i < b;i++) res = 1LL * res * (a - i) % MOD;
    return res;
}

int comb(int a, int b, int P) {//lucas: a<=N,b<=N
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

int C[N][N];
void Prework(int n = N - 10) {
    C[0][0] = 1;
    for (int i = 0;i < n;i++) {
        C[i][0] = 1;
        for (int j = 1;j <= i;j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }
}
