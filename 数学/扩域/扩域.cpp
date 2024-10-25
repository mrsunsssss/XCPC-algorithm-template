#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

const int MOD = 1e9 + 7;

int cadd(int x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
    return x;
}
int csub(int x, int y) {
    x -= y;
    if (x < 0) x += MOD;
    return x;
}

int qp(int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = 1LL * res * a % MOD;
        n >>= 1, a = 1LL * a * a % MOD;
    }
    return res;
}
int inv(int x) {
    return qp(x, MOD - 2);
}

struct Cp {
    int x, y;
    Cp() { ; }
    Cp(int x, int y) : x(x), y(y) {}
    friend Cp operator + (const Cp& a, const Cp& b) {
        return (Cp) { cadd(a.x, b.x), cadd(a.y, b.y) };
    }
    friend Cp operator + (const Cp& a, int num) {
        return (Cp) { cadd(a.x, num), cadd(a.y, num) };
    }
    friend Cp operator - (const Cp& a, const Cp& b) {
        return (Cp) { csub(a.x, b.x), csub(a.y, b.y) };
    }
    friend Cp operator - (const Cp& a, int num) {
        return (Cp) { csub(a.x, num), csub(a.y, num) };
    }
    friend Cp operator * (const Cp& a, const Cp& b) {
        return (Cp) { cadd(a.x * b.x % MOD, 5 * a.y % MOD * b.y % MOD), cadd(a.x * b.y % MOD, a.y * b.x % MOD) };
    }
    friend Cp operator * (const Cp& a, int num) {
        return (Cp) { a.x* num% MOD, a.y* num% MOD };
    }
    friend Cp operator / (Cp a, Cp b) {
        int d = csub(b.x * b.x % MOD, 5 * b.y % MOD * b.y % MOD);
        if (b.y) b.y = MOD - b.y;
        Cp ret = a * b;
        return ret * inv(d);
    }
};

Cp qp(Cp a, int n) {
    Cp res(1, 0);
    while (n) {
        if (n & 1) res = res * a;
        n >>= 1, a = a * a;
    }
    return res;
}

const int inv5 = inv(5), inv2 = inv(2);

void Prework() {

}
void Solve() {
    int n;cin >> n;
    Cp A(0, inv5), B(inv2, inv2), C(inv2, MOD - inv2);
    auto calc = [&](Cp u, int m) {
        if (u.x == 1 && u.y == 0) return Cp(m, 0);
        return u * (Cp(1, 0) - qp(u, m)) / (Cp(1, 0) - u);
        };
    A = A * (qp(B, n) - qp(C, n));
    cout << A.x << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    cin >> T;
    Prework();
    while (T--) Solve();
}
