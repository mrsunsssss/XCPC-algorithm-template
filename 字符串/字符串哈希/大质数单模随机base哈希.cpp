using ull = unsigned long long;
const int N = 2e5 + 10;
const ull H_MOD = (1ULL << 61) - 1;
ull add(ull a, ull b) {
    a += b;
    if (a >= H_MOD) a -= H_MOD;
    return a;
}
ull mul(ull a, ull b) {
    __int128_t c = __int128_t(a) * b;
    return add(c >> 61, c & H_MOD);
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ull> dist(H_MOD / 2, H_MOD - 1);
const ull base = dist(rnd);

ull power[N];
void init(const int n = N - 10) {
    power[0] = 1;
    for (int i = 1;i <= n;i++) {
        power[i] = mul(power[i - 1], base);
    }
}
struct String {
    string s;
    vector<ull> h;
    String(string S) :s(S) {
        int sz = s.size();
        h.resize(sz);
        for (int i = 1;i < sz;i++) {
            h[i] = add(mul(h[i - 1], base), s[i]);
        }
    }
    ull subs(int l, int r)const {
        return add(h[r], H_MOD - mul(h[l - 1], power[r - l + 1]));
    }
};

ull merge(ull h1, ull h2, int len2) {
    return add(mul(h1, power[len2]), h2);
}
//init()
//1-index
