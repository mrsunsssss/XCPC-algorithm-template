常用积性函数的 $f(p^e)$

恒等函数 $id_k(n) = n^k$  ， $id_k(p^e) = p^{ek}$

莫比乌斯函数 $\mu(n)$ :  $\mu(p^e)=\begin{cases} -1 & e=1 \\ 0 & e>1  \end{cases}$

欧拉函数 $\varphi(n)$ :  $\varphi(p^e) = p^e-p^{e-1}$

约数个数函数 $d(n)$ : $d(p^e) = e+1$

约数和函数 $\sigma(n)$ : $\sigma(p^e) = \sum\limits_{i=0}^{e}p^i = \frac{p^{e+1}-1}{p-1}$

广义约数和函数 $\sigma_k(n)$ : $\sigma_k(p^k) = \sigma_k(p^e)=\begin{cases}\sum\limits_{i=0}^{e} p^{ik} = \frac{p^{k(e+1) - 1}}{p^k-1} & k\ne 0 \\e+1 &k=0   \end{cases} $

```c++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define endl '\n'

namespace min25 {
    const int MOD = 1e9 + 7;
    const int SIZE = 1e5 + 10;// SIZE*SIZE > n 
    const int EXP_SIZE = 2;
    int primes[SIZE], minFac[SIZE], pfx[SIZE][EXP_SIZE], pcnt, lim;
    ll g[SIZE * EXP_SIZE][EXP_SIZE], dsc[SIZE * EXP_SIZE];
    array<int, 2> indx[SIZE];  // indx[x]: index of <x, n / x>
    vector<array<int, 2>> f_terms;//{coef,exp}
    function<ll(ll p, int e)> f_pe;
    int qp(int a, int n) {
        int res = 1;
        while (n) {
            if (n & 1) res = 1LL * res * a % MOD;
            n >>= 1, a = 1LL * a * a % MOD;
        }
        return res;
    }
    int inv(int x) { return qp(x, MOD - 2); }
    int inv2 = inv(2), inv3 = inv(3);
    int Add(int x, int y) { return (x + y >= MOD) ? x + y - MOD : x + y; }
    int Dec(int x, int y) { return (x - y < 0) ? x - y + MOD : x - y; }
    int mul(int x, int y) { return 1LL * x * y % MOD; }
    void init(ll n) {
        int siz = sqrt(n) + 5;
        fill(minFac, minFac + siz + 1, 0);
        pcnt = 0;
        for (int i = 2; i <= siz; i++) {
            if (minFac[i] == 0) minFac[i] = i, primes[++pcnt] = i;
            for (int j = 1; j <= pcnt && primes[j] <= min(minFac[i], siz / i); j++) minFac[i * primes[j]] = primes[j];
        }

        //f(p)的多项式每一项的前缀和
        for (int i = 1; i <= pcnt; i++) {
            for (int e = 0; e < EXP_SIZE; e++) {//展开写可能变快
                pfx[i][e] = Add(pfx[i - 1][e], qp(primes[i], f_terms[e][1]));
            }
        }
    }
    //i^k前缀和,次数高的话需要拉插
    const auto sum = [](ll n, ll exp) {
        n %= MOD;
        if (exp == 0) return n;
        ll res = n * (n + 1) % MOD * inv2 % MOD;
        if (exp == 2) return res * ((n << 1) + 1) % MOD * inv3 % MOD;
        return res;
        };

    ll sieve(ll x, ll pi, ll n) {
        if (x <= 1 or primes[pi] > x) return 0;
        int k = x <= lim ? indx[x][0] : indx[n / x][1];
        ll res = 0;
        for (int e = 0; e < EXP_SIZE; e++) {//展开写会快很多
            res = Add(res, mul(f_terms[e][0], Dec(g[k][e], pfx[pi - 1][e])));
        }
        for (int i = pi; i <= pcnt and 1LL * primes[i] * primes[i] <= x; i++) {
            ll p = primes[i], pk = p;
            for (int e = 1;;e++) {
                if (pk > x) break;
                ll val1 = f_pe(p, e);
                if (val1 != 0) res = Add(res, mul(val1, sieve(x / pk, i + 1, n)));
                if (pk > x / p) break;
                res = Add(res, f_pe(p, e + 1));
                pk = pk * p;
                if (pk == 0 && pk > 1) break;
            }
        }
        return res;
    }

    void config(const vector<array<int, 2>>& _f_terms,
        function<ll(ll p, int e)> _f_pe) {
        f_terms = _f_terms;
        f_pe = _f_pe;
    }

    ll sol(ll n) {
        lim = sqrt(n);
        int dscPt = 0;
        for (ll l = 1, r; l <= n; l = r + 1) {
            r = n / (n / l);
            ll v = n / l;
            dsc[dscPt] = v;
            for (int e = 0; e < EXP_SIZE; e++) {
                g[dscPt][e] = Dec(sum(dsc[dscPt], f_terms[e][1]), 1);
            }
            if (v <= lim) indx[v][0] = dscPt;
            else indx[n / v][1] = dscPt;
            dscPt++;
        }
        for (int i = 1; i <= pcnt; i++) {
            for (int j = 0; j < dscPt and 1LL * primes[i] * primes[i] <= dsc[j]; j++) {
                ll v = dsc[j] / primes[i];
                int k = v <= lim ? indx[v][0] : indx[n / v][1];
                for (int e = 0; e < EXP_SIZE; e++) {//展开写会快很多
                    g[j][e] = Dec(g[j][e], mul(qp(primes[i], f_terms[e][1]), Dec(g[k][e], pfx[i - 1][e])));
                }
            }
        }
        return Add(sieve(n, 1, n), 1LL);
    }
}
//注意多项式中系数中，需要将负数先取模转为正数再放入
const int MOD = 1e9 + 7;

void Prework() {

}
void Solve() {
    ll n;cin >> n;
    vector<array<int, 2>> coef = { {MOD - 1, 1}, {1, 2} };
    auto f = [&](int p, int k) {//f(p^k) = p^k(p^k-1)
        int t = min25::qp(p, k);
        return 1LL * t * (t - 1) % MOD;
        };
    min25::config(coef, f);
    min25::init(n);
    cout << min25::sol(n) << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    //cin >> T;
    Prework();
    while (T--) Solve();
}
```
