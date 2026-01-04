mt19937_64 gen(random_device{}());
vector<ll> res;
inline ll qp(ll a, ll n, ll mod) {//判较小的数字需要去掉int128卡常
    ll res = 1;
    while (n) {
        if (n & 1) res = (__int128)1 * res * a % mod;
        a = (__int128)1 * a * a % mod;
        n = n >> 1ll;
    }
    return res;
}
int base[] = { 0,2,3,5,7,11,13,17,19,23,29,31,37 };
inline bool test(ll n, ll a, ll b, ll x) {
    ll v = qp(x, a, n);
    if (v == 1) return 1;
    int j = 1;
    while (j <= b) {
        if (v == n - 1) break;
        v = (__int128)1 * v * v % n;
        j++;
    }
    if (j > b) return 0;
    return 1;
}
inline bool MR(ll n) {
    if (n < 3 || n % 2 == 0) return n == 2;
    if (n > 37) {
        ll a = n - 1, b = 0;
        while (a % 2 == 0) a >>= 1, b++;
        for (int i = 1; i <= 12; i++) if (!test(n, a, b, base[i])) return 0;
        return 1;
    }
    else {
        for (int i = 1; i <= 12; i++) if (n == base[i]) return 1;
        return 0;
    }
}
inline ll f(ll x, ll c, ll mod) { return ((__int128)1 * x * x % mod + c) % mod; }
inline ll PR(ll n) {
    if (n == 4) return 2;
    uniform_int_distribution<ll> Rand(3, n - 1);
    ll x = Rand(gen), y = x, c = Rand(gen);
    x = f(x, c, n), y = f(f(y, c, n), c, n);
    for (int lim = 1; x != y; lim = min(lim << 1, 128ll)) {
        ll cnt = 1;
        for (int i = 0; i < lim; i++) {
            cnt = (__int128)1 * cnt * abs(x - y) % n;
            if (!cnt) break;
            x = f(x, c, n), y = f(f(y, c, n), c, n);
        }
        ll d = gcd(cnt, n);
        if (d != 1) return d;
    }
    return n;
}
inline void find(ll x) {
    if (x == 1) return;
    if (MR(x)) { res.push_back(x); return; }
    ll p = x;
    while (p == x) p = PR(x);
    while (x % p == 0) x /= p;
    find(p);find(x);
}
inline vector<int> Prime_factor(int x) {//可能重复，需要去重
    res.resize(0);
    find(x);
    return res;
}
//复杂度分别是log(n),n^{1/4}

