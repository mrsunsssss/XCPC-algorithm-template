#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

void Prework() {

}
void Solve() {
    int n, m;cin >> n >> m;
    vector<int> a(n + 1);for (int i = 1;i <= n;i++) cin >> a[i];
    vector<int> cnt(n + 1);
    const int B = sqrt(n);
    vector<array<int, 3>> q(m + 1);
    for (int i = 1;i <= m;i++) {
        int l, r;cin >> l >> r;
        q[i] = { l,r,i };
    }
    sort(q.begin() + 1, q.end(), [&](auto u, auto v) {
        if (u[0] / B != v[0] / B) return u[0] < v[0];
        return u[1] < v[1];
        });
    int s = 0;
    auto add = [&](int x) {
        s += cnt[x];
        cnt[x]++;
        };
    auto sub = [&](int x) {
        cnt[x]--;
        s -= cnt[x];
        };
    vector<array<int, 2>> res(m + 1);
    for (int i = 1, l = 1, r = 0;i <= m;i++) {
        while (q[i][0] < l) add(a[--l]);
        while (l < q[i][0]) sub(a[l++]);
        while (q[i][1] < r) sub(a[r--]);
        while (r < q[i][1]) add(a[++r]);
        auto id = q[i][2];
        if (r == l) res[id] = { 0,1 };
        else res[id] = { s,(r - l) * (r - l + 1) / 2 };
    }
    for (int i = 1;i <= m;i++) {
        auto [x, y] = res[i];
        int g = gcd(x, y);
        cout << x / g << '/' << y / g << endl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    //cin >> T;
    Prework();
    while (T--) Solve();
}
