int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int x1, y1, d;
    d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}

int inv(int a, int b = MOD) {
    int x, y;
    exgcd(a, b, x, y);
    return (x % MOD + MOD) % MOD;
}
