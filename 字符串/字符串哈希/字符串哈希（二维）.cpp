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
const int N = 2e5 + 10;
mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> rnd(1e8, 1e9);
const int base1 = 131;
const int base2 = 13331;
const int MOD = NextPrime(rnd(gen));
int power1[N], power2[N];
void init(const int n = N - 10) {
    power1[0] = power2[0] = 1;
    for (int i = 1;i <= n;i++) {
        power1[i] = 1LL * power1[i - 1] * base1 % MOD;
        power2[i] = 1LL * power2[i - 1] * base2 % MOD;
    }
}
struct String2D {
    vector<vector<int>> s;
    vector<vector<int>> H;
    String2D(vector<string>& S) {
        int n = s.size() - 1, m = s[1].size() - 1;
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                s[i][j] = S[i][j];
            }
        }
        run();
    }
    String2D(vector<vector<int>>& S) :s(S) { run(); }
    void run() {
        int n = s.size() - 1, m = s[1].size() - 1;
        H.assign(n + 1, vector<int>(m + 1, 0));
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                H[i][j] = (1LL * H[i - 1][j] * base1 % MOD + s[i][j]) % MOD;
            }
        }
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                H[i][j] = (1LL * H[i][j - 1] * base2 % MOD + H[i][j]) % MOD;
            }
        }
    }
    int subs(int x1, int y1, int x2, int y2) const {
        int res = H[x2][y2];
        res = (res + MOD - H[x1 - 1][y2] * power1[x2 - x1 + 1] % MOD) % MOD;
        res = (res + MOD - H[x2][y1 - 1] * power2[y2 - y1 + 1] % MOD) % MOD;
        res = (res + H[x1 - 1][y1 - 1] * power1[x2 - x1 + 1] % MOD * power2[y2 - y1 + 1] % MOD) % MOD;
        return res;
    }
};
//init()
//1-index
