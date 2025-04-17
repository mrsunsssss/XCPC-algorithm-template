单调队列优化dp

https://codeforces.com/contest/2027/problem/D2



dp好题

https://codeforces.com/contest/2039/problem/E

这种题一开始完全没有思路很正常，但是最重要的就是克服恐惧。不断尝试就能找到一条通往胜利的路。

不妨设逆序对的数量为invs。

发现当invs总是单调不减的。于是自然的想到与max(a[i])进行比较。

当invs>max(a[i])，除非放在最后的位置会使invs'=max(a[i])'；否则放在其他地方都会使得invs'增加，而max(a[i])'变成当前invs，于是还是保持invs'>max(a[i])'.

这是个耐人寻味的性质：不妨令dp[i]表示长度为i的并且invs大于max(a[i])的数组数量。这样如果当前为dp[i]，我们就可以为dp[i+1]加上dp[i] * i . 然后再仔细想想这是它的全部转移吗？ 并不是，我们还可以为dp[i+2],…,dp[i+k]都加上dp[i] * i，先在末尾添加若干当前invs，使得invs'=max(a[i])',再在前面的地方加一个invs’即可使得invs''>max(a[i])''.

但是光是dp[n]还不够，我们还需要invs=max(a[i])和invs < max(a[i]).

invs=max(a[i])可以通过所有序列长度小于n的并且invs>max(a[i])的序列，在末尾操作若干次得到。

invs<max(a[i])的情况，只能是最开始的序列01从不进入上面两种的情况得到。

n=6：000001，000010，000101，001011，010111. 手动试一下n=5，6，7这几种长度，会发现这种情况仅有n-1种可能。

最后的问题就很清晰了，只需要让最开始的01序列变成invs>max(a[i])的序列，一切就结束了。

可以发现，只有invs为1的序列可以一步生成这种东西。尝试之后发现，就是若干个0，然后中间是10，然后最后又是若干个1的序列，例如这样000001011111。考虑先忽略最后的一串1，对于0000010这样的序列，我们有n-1次机会插入可以使得该长度为n的序列变成合法的n+1序列。

于是，对于长度为n的序列，我们初始可以找3~n-1的这种序列，操作完后在最后补1即可。

那么就是(2+…+n-2) = n*(n-3)/2.

综上这题就抽丝剥茧的做完了。



https://codeforces.com/contest/441/problem/E

直接做保留末尾8位这种可以做，但是有些麻烦。仔细观察发现，如果操作n次乘2，至少需要2^n次加1才可以产生进位。我们可以在最开始的时候贷款，dp[i][j]表示操作i次之后的x，再加上j之后末尾0的期望。

如果做加1操作，就可以转移dp[i+1][j-1]+=dp[i][j]. 若做乘2操作，就可以有转移dp[i+1][j*2]+=dp[i][j] .很妙的转移方程。


https://codeforces.com/problemset/problem/1906/H

s的每一种排列对应着等价的t'的排列，所以可以先求出sorted(s)的t'的方案数，再乘上多重集组合数求出答案。

用A和B分别存下两个字符串对应的字符数量。用dp[i][j]表示到第i个字符，其中t使用了j个i字符，也就是说还需要A[i]-j个i+1字符。让dp[i][j]转移到dp[i+1][k]，也就是说需要满足A[i]-j+k<=B[i+1]。

那么k<=B[i+1]+j-A[i] , j>=A[i]+k-B[i+1]. 发现是个连续的形式，如果刷表法需要树状数组优化，填表法直接后缀和即可。

也就是固定dp[i+1][k]的k，对于所有j>=A[i]+k-B[i+1]的j，进行转移过来。



背包dp

https://atcoder.jp/contests/abc383/tasks/abc383_f

很容易发现应该按分组分组之后处理。

首先记录一下dp的关键信息：需要记录的是当前到第几组，装的物品的重量，装的物品的权值，该组是否已经装了物品。

首先第一条信息可滚动数组忽略，第三条信息放入dp值中，那么状态就设计为重量和是否装了物品。

https://ac.nowcoder.com/acm/contest/101921/E

将题目转化后变成背包问题，容易发现每种物品的使用次数无限。然后就是完全背包，记录方案即可。注意只有在次数限制的情况下才需要跑多重背包！赛时写了个二进制优化多重背包，脑抽了！




状压dp

https://leetcode.cn/problems/find-minimum-time-to-finish-all-jobs/description/

首先可以二分答案，然后枚举子集进行dp。二分答案可以只枚举子集和中存在的值，于是这样复杂度是 $O(3^n log(2^n)) = O(n 3^n)$ 

而枚举子集这个东西，一般可以用类似高维前缀和优化到 $ O(n2^n)$ ,这里维护一个pair，dp[i] 表示当前子集{用的人数，该人用掉的时间}，最小化该式即可，显然可以dp做到。







决策单调性优化dp
![image](https://github.com/user-attachments/assets/0a243c3e-86df-4e95-b0ec-a91e893db68c)

决策单调性显然。由于只有上层向下层的转移，使用分治即可。

```C++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

using ld = double;

void Prework() {

}
void Solve() {
    int n, k;cin >> n >> k;
    vector<ld> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a.begin() + 1, a.end());
    vector<ld> s(n + 1);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
    vector<vector<ld>> w(n + 1, vector<ld>(n + 1, 0.0));
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int m = (l + r) / 2;
            int mid = a[m];
            ld x = mid * 1.0 * (m - l + 1) - (s[m] - s[l - 1]);
            ld y = (s[r] - s[m]) - mid * 1.0 * (r - m);
            w[l][r] = x + y;
        }
    }
    const int inf = 1e18;
    vector<ld> dp(n + 1, inf);
    for (int i = 0; i <= n; i++) dp[i] = w[1][i];
    for (int i = 2; i <= k; i++) {
        vector<ld> ndp(n + 1, inf);
        auto dfs = [&](auto&& dfs, int l, int r, int L, int R) {
            if (l > r) return;
            int mid = (l + r) / 2;
            ld best = inf;
            int pos = -1;
            for (int j = L; j <= min(R, mid - 1); j++) {
                ld cur = dp[j] + w[j + 1][mid];
                if (cur < best) {
                    best = cur;
                    pos = j;
                }
            }
            if (pos == -1) return;
            ndp[mid] = best;
            dfs(dfs, l, mid - 1, L, pos);
            dfs(dfs, mid + 1, r, pos, R);
            };
        dfs(dfs, i, n, i, n);
        swap(ndp, dp);
    }

    cout << fixed << std::setprecision(4) << dp[n] << endl;
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








