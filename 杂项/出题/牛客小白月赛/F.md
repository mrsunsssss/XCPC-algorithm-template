山鸡王喜欢游玩荒野乱斗，他最擅长使用的英雄是大锤弗兰肯。

这天他使用大锤开始了一局单人荒野乱斗，这个模式的规则是，每个人各自为战。

但是也有人进行组队破坏游戏规则，山鸡王就是这样做的，他通过转圈和发送表情和喷漆与别人进行组队，然后等对方放松警惕时，释放极限充能将对方击败。

游戏还有n秒钟进入决赛圈，山鸡王在进入决赛圈前的每秒可以选择两种操作之一：

1.攻击对方：自己获得一点充能，对方会增加x点警惕值。

2.转圈发表情和喷漆：降低对方y点警惕值，注意警惕值不会降低到0以下。

初始山鸡王有0点充能，对方有0点警惕值，如果对方警惕值超过lim，会直接开启大招击杀山鸡王。

请问山鸡王在保住性命的情况下，在决赛圈前最多可以为自己获得多少充能，以便他能够在决赛圈更轻松的获得胜利？

读入：

读入 $T$ ，表示数据组数。每组 $T$ 中，读入 $n$ , $lim$ , $x$ , $y$ 。
其中 $1\le T \le 1e5$ , $1\le n,lim,x,y \le 1e9$

输出：

对于每组T，输出山鸡王最多可以获得的充能数目。


```C++
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




类似的题：poj3530 ， 黑暗爆炸4270




