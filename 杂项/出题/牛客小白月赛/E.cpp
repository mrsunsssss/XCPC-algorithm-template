//选定[l,r]区间，问这个区间的set是否相等.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

struct BIT {
    int n;
    vector<int> tr;
    BIT(int n) : n(n), tr(n + 1) {}

    inline int lbt(int x) { return x & -x; }

    void add(int i, int val) {
        for (; i <= n; i += lbt(i)) {
            tr[i] += val;
        }
    }
    int sum(int i) {
        int res = 0;
        for (; i > 0; i -= lbt(i)) {
            res += tr[i];
        }
        return res;
    }
    int query(int l, int r) {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
    int find(int val) {//find k such that a[1~k] >= val
        int x = 0, res = 0;
        for (int i = __lg(n); i >= 0; --i) {
            if (x + (1 << i) <= n && tr[x + (1 << i)] < val) {
                x += 1 << i;
                val -= tr[x];
                res += 1 << i;
            }
        }
        return res + 1;
    }
};

mt19937_64 gen(random_device{}());
uniform_int_distribution<int> dist(1, 1e12);

void Prework() {

}
void Solve() {
    int n;cin >> n;
    vector<int> H(n + 1), a(n + 1);
    for (int i = 1;i <= n;i++) H[i] = dist(gen);
    for (int i = 1;i <= n;i++) cin >> a[i];
    int q;cin >> q;
    vector<array<int, 4>> qur(q);
    vector<vector<int>> eve(n + 1);
    for (int i = 1;i <= q;i++) {
        int l1, r1, l2, r2;cin >> l1 >> r1 >> l2 >> r2;
        qur[i - 1] = { l1,r1,l2,r2 };
        eve[r1].push_back(l1);
        eve[r2].push_back(l2);
    }
    map<array<int, 2>, int> mp;
    BIT bit(n);
    vector<int> lst(n + 1);
    for (int i = 1;i <= n;i++) {
        if (lst[a[i]]) bit.add(lst[a[i]], -H[a[i]]);
        bit.add(i, H[a[i]]);
        lst[a[i]] = i;
        for (auto l : eve[i]) {
            mp[{l, i}] = bit.query(l, i);
        }
    }
    for (auto [l1, r1, l2, r2] : qur) {
        if (mp[{l1, r1}] == mp[{l2, r2}]) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
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
