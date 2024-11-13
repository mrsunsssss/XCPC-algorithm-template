给定 $D$ , $M$ , $L$ , $R$ ，求最小的 $x$ 满足 $L\le Dx \% M\le R$ .

将 $L\le Dx \% M\le R$ ，转化为 $yM+L\le Dx \le yM+R$ 。（满足 $L\le R\le M-1$ ）

将它记为 $f(D,M,L,R)$ 

首先假设 $y=0$ ，若此时有解，则 $L\le Dx\le R$ 。

否则 $y>0$ ，由于上面找不到解，则 $tD< L\le R<(t+1)D$ .

移项得到 $Dx-R\le yM \le Dx-L$ ，当 $x=t+1$ 时，满足条件 $0<Dx-R\le Dx-L <D$ .

即可以表示为 $D-R\le y M \% D \le D-L$ 。

可以改写为 $f(M \% D,D,D-R,D-L)$ 。



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
