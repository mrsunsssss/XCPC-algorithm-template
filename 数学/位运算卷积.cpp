#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'
const int MOD = 998244353;

void Solve() {
    int n;cin >> n;
    vector<int> a(1 << n);for (int i = 0;i < (1 << n);i++) cin >> a[i];
    vector<int> b(1 << n);for (int i = 0;i < (1 << n);i++) cin >> b[i];
    {// 与
        auto fmt = [&](vector<int> a) {
            for (int i = 0;i < n;i++) {
                for (int j = 0;j < (1 << n);j++) {
                    if (~j >> i & 1) a[j ^ (1 << i)] = (a[j ^ (1 << i)] + a[j]) % MOD;
                }
            }
            return a;
            };
        auto ifmt = [&](vector<int> a) {
            for (int i = 0;i < n;i++) {
                for (int j = 0;j < (1 << n);j++) {
                    if (~j >> i & 1) a[j ^ (1 << i)] = (a[j ^ (1 << i)] - a[j] + MOD) % MOD;
                }
            }
            return a;
            };
        auto na = fmt(a), nb = fmt(b);
        vector<int> res(1 << n);
        for (int i = 0;i < (1 << n);i++) {
            res[i] = na[i] * nb[i] % MOD;
        }
        res = ifmt(res);
        for (int i = 0;i < (1 << n);i++) cout << res[i] << ' ';cout << endl;
    }

    {// 或
        auto fmt = [&](vector<int> a) {
            for (int i = 0;i < n;i++) {
                for (int j = (1 << n) - 1;j >= 0;j--) {
                    if (j >> i & 1) a[j ^ (1 << i)] = (a[j ^ (1 << i)] + a[j]) % MOD;
                }
            }
            return a;
            };
        auto ifmt = [&](vector<int> a) {
            for (int i = 0;i < n;i++) {
                for (int j = (1 << n) - 1;j >= 0;j--) {
                    if (j >> i & 1) a[j ^ (1 << i)] = (a[j ^ (1 << i)] - a[j] + MOD) % MOD;
                }
            }
            return a;
            };
        auto na = fmt(a), nb = fmt(b);
        vector<int> res(1 << n);
        for (int i = 0;i < (1 << n);i++) {
            res[i] = na[i] * nb[i] % MOD;
        }
        res = ifmt(res);
        for (int i = 0;i < (1 << n);i++) cout << res[i] << ' ';cout << endl;
    }

    {//异或
        auto fwt = [&](vector<int> a) {
            for (int i = 0;i < n;i++) {
                for (int j = 0;j < (1 << n);j++) {
                    if (~j >> i & 1) {
                        int x = a[j], y = a[j ^ (1 << i)];
                        a[j] = (x + y) % MOD, a[j ^ (1 << i)] = (x - y + MOD) % MOD;
                    }
                }
            }
            return a;
            };
        auto ifwt = [&](vector<int> a) {
            const int inv2 = MOD + 1 >> 1;
            for (int i = 0;i < n;i++) {
                for (int j = 0;j < (1 << n);j++) {
                    if (~j >> i & 1) {
                        int x = a[j], y = a[j ^ (1 << i)];
                        a[j] = 1LL * (x + y) * inv2 % MOD, a[j ^ (1 << i)] = 1LL * (x - y + MOD) * inv2 % MOD;
                    }
                }
            }
            return a;
            };
        auto na = fwt(a), nb = fwt(b);
        vector<int> res(1 << n);
        for (int i = 0;i < (1 << n);i++) {
            res[i] = na[i] * nb[i] % MOD;
        }
        res = ifwt(res);
        for (int i = 0;i < (1 << n);i++) cout << res[i] << ' ';cout << endl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    //cin >> T;
    while (T--) Solve();
}
