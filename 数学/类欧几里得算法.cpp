using ull = unsigned long long;
ull floor_sum(ull n, ull m, ull a, ull b) {
    ull ans = 0;
    for (;;) {
        if (a >= m) ans += n * (n - 1) / 2 * (a / m), a %= m;
        if (b >= m) ans += n * (b / m), b %= m;
        ull ymax = a * n + b;//use i128 if it's big
        if (ymax < m) break;
        n = ymax / m;
        b = ymax % m;
        swap(m, a);
    }
    return ans;
}
