gcd(a,b,c,d,...) = gcd(a,b-a,c-b,d-c,...)

https://qoj.ac/contest/1839/problem/9738
```
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long

array<int, 2> dp_min[17][(int)5e4 + 1];
vector<int> st,nst;

void Solve() {
    st.clear();
    int n, k;cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    auto ck = [&]() {
        for (int i = 2;i <= n;i++) {
            if (a[i] != a[i - 1]) {
                return 0;
            }
        }
        return 1;
        };
    if (ck()) {
        cout << k << " " << k * (k + 1) / 2 << endl;
        return;
    }
    int lgn = __lg(n) + 1;
    for (int i = 1; i <= n; i++) {
        dp_min[0][i] = (array<int, 2>){ a[i], i };
    }
    for (int i = 1; i <= lgn; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            auto [A, B] = dp_min[i - 1][j];
            auto [C, D] = dp_min[i - 1][j + (1 << i - 1)];
            auto& aux = dp_min[i][j];
            if (A <= C) aux = { A, B };
            else aux = { C, D };
        }
    }
    auto ask_pos = [&](int l, int r) {
        int kk = __lg(r - l + 1);
        auto [A, B] = dp_min[kk][l];
        auto [C, D] = dp_min[kk][r - (1 << kk) + 1];
        if (A <= C) return B;
        else return D;
        };
    auto dfs = [&](auto&& dfs, int l, int r)->int {
        if (l >= r) return 0;
        int mid = ask_pos(l, r);
        int GCD = 0;
        if (l == 1 and r == n) {
            for (int i = 2;i <= n;i++) GCD = gcd(GCD, abs(a[i] - a[i - 1]));
            for (int i = 1; i * i <= GCD; i++) {
                if (GCD % i) continue;
                for (auto j : (i* i == GCD ? vector<int>{i} : vector<int>{ i, GCD / i })) {
                    if (j > a[mid] and j - a[mid] <= k) st.push_back(j - a[mid]);
                }
            }
        }
        int g1 = dfs(dfs, l, mid - 1);
        int g2 = dfs(dfs, mid + 1, r);
        if (not(l == 1 and r == n)) {
            GCD = gcd(g1, g2);
            if (mid > l) GCD = gcd(GCD, a[mid] - a[mid - 1]);
            if (mid + 1 <= r) GCD = gcd(GCD, a[mid + 1] - a[mid]);
            nst.clear();
            for (auto j : st) {
                if (GCD % (a[mid] + j) == 0) nst.push_back(j);
            }
            st.swap(nst);
        }
        return GCD;
        };
    dfs(dfs, 1, n);
    int sum = 0;
    for (auto i : st) sum += i;
    cout << st.size() << " " << sum << endl;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while (T--) Solve();
}
```


https://ac.nowcoder.com/acm/contest/97017/F

