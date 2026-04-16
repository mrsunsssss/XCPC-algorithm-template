int qp(int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = res * a % MOD;
        a = a * a % MOD, n >>= 1;
    }
    return res;
}
