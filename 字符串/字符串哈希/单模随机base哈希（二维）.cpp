using ull = unsigned long long;
using Int = __int128_t;
const int N = 2e5 + 10;
const ull H_MOD = (1ULL << 61) - 1;
ull add(ull a, ull b) {
    a += b;
    if (a >= H_MOD) a -= H_MOD;
    return a;
}
ull mul(ull a, ull b) {
    Int c = Int(a) * b;
    return add(c >> 61, c & H_MOD);
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ull> dist(H_MOD / 2, H_MOD - 1);
const ull base1 = dist(rnd);
const ull base2 = dist(rnd);

ull power1[N], power2[N];
void init(const int n = N - 10) {
    power1[0] = power2[0] = 1;
    for (int i = 1;i <= n;i++) {
        power1[i] = mul(power1[i - 1], base1);
        power2[i] = mul(power2[i - 1], base2);
    }
}
struct String2D {
    vector<string> s;
    vector<vector<ull>> H;
    String2D(vector<string>& S) :s(S) {
        int n = s.size() - 1, m = s[1].size() - 1;
        H.assign(n + 1, vector<ull>(m + 1, 0));
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                H[i][j] = add(s[i][j], mul(H[i - 1][j], base1));
            }
        }
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                H[i][j] = add(H[i][j], mul(H[i][j - 1], base2));
            }
        }
    }
    ull subs(int x1, int y1, int x2, int y2) const {
        ull res = H[x2][y2];
        res = add(res, H_MOD - mul(H[x1 - 1][y2], power1[x2 - x1 + 1]));
        res = add(res, H_MOD - mul(H[x2][y1 - 1], power2[y2 - y1 + 1]));
        res = add(res, mul(mul(H[x1 - 1][y1 - 1], power1[x2 - x1 + 1]), power2[y2 - y1 + 1]));
        return res;
    }
};
//init()
//1-index
