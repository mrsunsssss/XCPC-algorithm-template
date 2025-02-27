#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

int qp(int a, int n, int mod) {
    int res = 1;
    while (n) {
        if (n & 1) res = 1LL * res * a % mod;
        n >>= 1, a = 1LL * a * a % mod;
    }
    return res;
}
int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int x1, y1, d;
    d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}

int inv(int a, int b) {// gcd(a,b)=1;
    int x, y;
    exgcd(a, b, x, y);
    return (x % b + b) % b;
}


namespace exlucas {
    ll fac(int n, int pi, int pk) {//n! % pk  , pk=pi^ki
        if (n == 1 || n == 0)return 1;
        int ans = 1;
        for (int i = 2;i < pk;i++) {
            if (i % pi) ans = ans * i % pk;
        }
        ans = qp(ans, n / pk, pk);
        for (int i = 2;i <= n % pk;i++) {
            if (i % pi) ans = ans * i % pk;
        }
        return ans * fac(n / pi, pi, pk) % pk;
    }
    int comb_pk(ll n, ll m, int pi, int pk) {//C(n,m)%pk ,pk=pi^ki
        int up = fac(n, pi, pk), dl = fac(m, pi, pk), dr = fac(n - m, pi, pk), kk = 0;
        for (int i = n;i;i /= pi) kk += i / pi;
        for (int i = m;i;i /= pi) kk -= i / pi;
        for (int i = n - m;i;i /= pi) kk -= i / pi;
        return up * inv(dl, pk) % pk * inv(dr, pk) % pk * qp(pi, kk, pk) % pk;
    }
    int comb(ll a, ll b, int mod) {
        ll ans = 0, p = mod;
        for (int i = 2;i <= p;i++) {
            if (p % i == 0) {
                int pi = i, pk = 1;
                while (p % i == 0) p /= i, pk *= i;
                ans = (ans + comb_pk(a, b, pi, pk) * (mod / pk) % mod * inv(mod / pk, pk) % mod) % mod;
            }
        }
        return ans % mod;
    }
}

void Solve() {
    int n, m, mod;cin >> n >> m >> mod;
    cout << exlucas::comb(n, m, mod) << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    while (T--) Solve();
}
