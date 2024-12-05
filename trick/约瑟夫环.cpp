//F(n,k) = (F(n - 1, k) + k) % n
auto josephu = [&](int n, int k) {
    int f = 0;
    for (int i = 2;i <= n;i++) {
        f = (f + k) % i;
    }
    return f;
    };//k>=n时使用

auto josephu2 = [&](auto&& josephu2, int n, int k) {
    if (n == 1) return 0;
    if (k == 1) return n - 1;
    if (k > n) return (josephus2(josephu2, n - 1, k) + k) % n;
    int f = josephus2(josephu2, n - n / k, k) - n % k;
    return f + (f < 0 ? n : (f / (k - 1)));
    };//k<n时使用，会比较快
