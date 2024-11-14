给定 $D$ , $M$ , $L$ , $R$ ，求最小的 $x$ 满足 $L\le Dx \mod M\le R$ .

将 $L\le Dx \mod M\le R$ ，转化为 $yM+L\le Dx \le yM+R$ 。（满足 $L\le R\le M-1$ ）

将它记为 $f(D,M,L,R)$ 

首先假设 $y=0$ ，若此时有解，则 $L\le Dx\le R$ 。

否则 $y>0$ ，由于上面找不到解，则 $tD< L\le R<(t+1)D$ .

移项得到 $Dx-R\le yM \le Dx-L$ ，当 $x=t+1$ 时，满足条件 $0<Dx-R\le Dx-L <D$ .

即可以表示为 $D-R\le y M \mod D \le D-L$ 。

可以改写为 $f(M \mod D,D,D-R,D-L)$ 。



```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dfs(ll D, ll M, ll L, ll R) {
    if (L > R || L >= M || D == 0) return -1LL;
    R = min(R, M - 1);
    ll u = (L + D - 1) / D;
    ll v = R / D;
    if (u <= v) return u;
    ll y = dfs(M % D, D, (D - R % D), (D - L % D));
    if (y == -1) return y;
    return (M * y + L + D - 1) / D;
}

void Prework() {

}
void Solve() {
    ll m, d, l, r;
    cin >> m >> d >> l >> r;
    cout << dfs(d, m, l, r) << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    cin >> T;
    Prework();
    while (T--) Solve();
}

```


模板题

http://poj.org/problem?id=3530

https://darkbzoj.cc/problem/4270


记录初始分数score = 0,ans=0，给定x、y、lim。每次可以选择两个操作。
1.score+=x,ans+=1.
2.score=max(0,score-y).
每次操作后需要满足score<=lim
问ans最大是多少。

找到令 $tx\mod y+x> lim$ 的最小的 $t$ ，此时需要减一个 $y$ 来清零。

即 $lim-x+1\le tx \mod y\le y-1$ 。

```
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

void Prework() {

}
void Solve() {
    auto dfs = [&](auto&& dfs, int D, int M, int L, int R)->int {
        if (L > R || L >= M || D == 0) return -1LL;
        R = min(R, M - 1);
        int u = (L + D - 1) / D;
        int v = R / D;
        if (u <= v) return u;
        int y = dfs(dfs, M % D, D, (D - R % D), (D - L % D));
        if (y == -1) return y;
        return (M * y + L + D - 1) / D;
        };
    int n, lim, x, y;cin >> n >> lim >> x >> y;
    if (x > lim) return cout << "0\n", void();
    int t = dfs(dfs, x, y, lim - x + 1, y - 1);
    auto calc = [&](int nn) {
        int l = 1, r = nn;
        while (l <= r) {
            int mid = l + r >> 1;
            if (mid * x - (nn - mid) * y <= lim) l = mid + 1;
            else r = mid - 1;
        }
        return r;
        };
    if (t == -1) {
        cout << calc(n) << endl;
    }
    else {
        int cnt_y = t * x / y;
        int loop = t + cnt_y + 1;
        cout << n / loop * t + calc(n % loop) << endl;
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
```



