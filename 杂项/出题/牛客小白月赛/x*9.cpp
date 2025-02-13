//数字乘以9后的性质

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

void Prework() {

}
void Solve() {
    auto ck = [&](int x) {
        int ret = 0;
        auto s = to_string(x);
        vector<array<int, 2>> a;
        for (int i = 0;i < s.size();) {
            int j = i;i++;
            while (i < s.size() and s[i] == s[i - 1]) i++;
            a.push_back({ s[j] - '0',i - j });
        }
        int n = a.size();
        for (int i = 1;i < n;i++) {
            if (a[i - 1][0] > a[i][0]) {
                ret += a[i - 1][1];
            }
        }
        if (a.back()[0] != 0) ret += a.back()[1];
        return ret;
        };
    auto count = [&](int x) {
        int ret = 0;
        while (x) ret += x % 10, x /= 10;
        return ret;
        };
    int res = 0;
    for (int i = 1;i <= 1e6;i++) {
        int x = i * 9;
        if (count(x) / 9 != ck(i)) {
            cout << "BUG" << ' ' << x << endl;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    cin >> T;
    Prework();
    while (T--) Solve();
}
