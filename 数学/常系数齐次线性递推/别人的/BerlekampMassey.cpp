
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

const int MOD = 1e9 + 7;
// k 为 m 最高次数 且　a[m] == 1
namespace BerlekampMassey {
    inline void up(ll& a, ll b) { (a += b) %= MOD; }

    vector<ll> mul(const vector<ll>& a, const vector<ll>& b, const vector<ll>& m, int k) {
        vector<ll> r; r.resize(2 * k - 1);
        for (int i = 0;i < k;i++)
            for (int j = 0;j < k;j++)
                up(r[i + j], a[i] * b[j]);
        for (int i = k - 2;i >= 0;i--) {
            for (int j = 0;j < k;j++)
                up(r[i + j], r[i + k] * m[j]);
            r.pop_back();
        }
        return r;
    }
    ll pow_mod(ll x, ll y) {
        ll ret = 1;
        for (;y;y >>= 1) { if (y & 1) ret = ret * x % MOD;x = x * x % MOD; }
        return ret;
    }
    ll get_inv(ll x, ll MOD) {
        return pow_mod(x, MOD - 2);
    }
    vector<ll> pow(ll n, const vector<ll>& m) {
        int k = (int)m.size() - 1; assert(m[k] == -1 || m[k] == MOD - 1);
        vector<ll> r(k), x(k); r[0] = x[1] = 1;
        for (; n; n >>= 1, x = mul(x, x, m, k))
            if (n & 1) r = mul(x, r, m, k);
        return r;
    }
    ll go(const vector<ll>& a, const vector<ll>& x, ll n) {
        // a: (-1, a1, a2, ..., ak).reverse
        // x: x1, x2, ..., xk
        // x[n] = sum[a[i]*x[n-i],{i,1,k}]
        int k = (int)a.size() - 1;
        if (n <= k) return x[n - 1];
        vector<ll> r = pow(n - 1, a);
        ll ans = 0;
        for (int i = 0;i < k;i++)
            up(ans, r[i] * x[i]);
        return ans;
    }

    vector<ll> BM(const vector<ll>& x) {
        vector<ll> a = { -1 }, b = { 233 };
        for (int i = 1;i < x.size();i++) {
            b.push_back(0);
            ll d = 0, la = a.size(), lb = b.size();
            for (int j = 0;j < la;j++) up(d, a[j] * x[i - la + 1 + j]);
            if (d == 0) continue;
            vector<ll> t; for (auto& v : b) t.push_back(d * v % MOD);
            for (int j = 0;j < a.size();j++) up(t[lb - 1 - j], a[la - 1 - j]);
            if (lb > la) {
                b = a;
                ll inv = -get_inv(d, MOD);
                for (auto& v : b) v = v * inv % MOD;
            }
            a.swap(t);
        }
        for (auto& v : a) up(v, MOD);
        return a;
    }
}

void GET(const vector<ll>& x) {
    vector<ll> a = BerlekampMassey::BM(x);
    cout << "a[n] = ";
    for (int i = 0;i < a.size() - 2;i++) {
        cout << a[i] << "*a[n-" << a.size() - 1 - i << "] + ";
    }
    cout << a[a.size() - 2] << "*a[n-1]" << endl;
}

void Prework() {

}
void Solve() {
    vector<int> a = { 1,5,14,30,55,91,140,204,285,385 };
    GET(a);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    //cin >> T;
    Prework();
    while (T--) Solve();
}
