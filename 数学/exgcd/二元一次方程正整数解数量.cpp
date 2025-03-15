//https://www.luogu.com.cn/problem/P5656
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

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
int calc(int a, int b, int c, int& mnx, int& mny, int& mxx, int& mxy) {//ax+by=c的正整数解
    int x, y;
    int d = exgcd(a, b, x, y);
    if (c % d) {
        return -1;
    }
    x *= c / d, y *= c / d;
    int B = b / d, A = a / d;
    mnx = x % B;while (mnx <= 0) mnx += B;
    mxy = (c - a * mnx) / b;
    mny = y % A;while (mny <= 0) mny += A;
    mxx = (c - b * mny) / a;
    int res;
    if (mny > mxy) res = 0;
    else res = (mxy - mny) / A + 1;
    return res;
}

void Prework() {

}
void Solve() {
    int a, b, c;cin >> a >> b >> c;
    int mnx, mny, mxx, mxy;
    int res = calc(a, b, c, mnx, mny, mxx, mxy);
    if (res == -1) cout << res << endl;
    else {
        if (res == 0) {
            cout << mnx << " " << mny << endl;
        }
        else {
            cout << res << ' ';
            cout << mnx << " " << mny << ' ' << mxx << " " << mxy << endl;
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
