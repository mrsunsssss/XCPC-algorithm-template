bool IsPrime(int n) {
    if (n <= 1) return 0;
    for (int i = 2;i * i <= n;i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
int NextPrime(int n) {
    while (!IsPrime(n)) n++;
    return n;
}
template<int M>
struct StringHash {
    static array<int, M> mod;
    static array<int, M> base;
    vector<array<int, M>> xp, h;
    StringHash() = default;
    StringHash(const string& s) {
        int n = s.size() - 1;
        xp.resize(n + 1);
        h.resize(n + 1);
        for (int i = 0;i < M;i++) xp[0][i] = 1;
        for (int i = 1;i <= n;i++) {
            for (int j = 0;j < M;j++) {
                xp[i][j] = 1LL * xp[i - 1][j] * base[j] % mod[j];
            }
        }
        for (int i = 1;i <= n;i++) {
            for (int j = 0;j < M;j++) {
                h[i][j] = (1LL * h[i - 1][j] * base[j] + s[i]) % mod[j];
            }
        }
    }
    array<int, M> subs(int l, int r) {
        array<int, M> ret;
        for (int i = 0;i < M;i++) {
            ret[i] = (h[r][i] - 1LL * h[l - 1][i] * xp[r - l + 1][i] % mod[i] + mod[i]) % mod[i];
        }
        return ret;
    }

};
mt19937 gen(random_device{}());
uniform_int_distribution<int> rnd(1e8, 1e9);

template<> array<int, 2> StringHash<2>::mod = { NextPrime(rnd(gen)), NextPrime(rnd(gen)) };
template<> array<int, 2> StringHash<2>::base{ 131, 13331 };
using String = StringHash<2>;

template<int M>//M = 2
array<int, M> add(const StringHash<M>& u, int a, int b, const StringHash<M>& v, int c, int d) {
    array<int, M> ret;
    auto h1 = u.subs(a, b);
    auto h2 = v.subs(c, d);
    for (int i = 0;i < M;i++) {
        ret[i] = (1LL * h1[i] * xp[(b - a + 1)][i] + h2[i]) % StringHash<2>::mod[i];//这里init没写，懒得补了
    }
    return ret;
}
ll ptoll(array<int, 2> a) {
    ll ret = ((1LL * a[0]) << 30) | a[1];
    return ret;
}

//1-index
