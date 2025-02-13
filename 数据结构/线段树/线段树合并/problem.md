https://www.luogu.com.cn/problem/P4556

值域线段树维护每种数字的数量，以及答案数字是什么。线段树合并 + 树上差分维护路径

```C++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

namespace sgt {
    const int N = 1e5 + 10;
    struct node {
        int l, r;
        int sum = 0;
        int ty = 0;
        int ans = 0;
    }tr[N * 50];
    int tot = 0, root[N];
    vector<int> g[N];
    int dp[N][21], dep[N];
    void init() {
        for (int i = 1;i <= tot;i++) {
            tr[i] = { 0,0,0,0,0 };
        }
        tot = 0;
    }
    void dfs1(int u, int p = 0) {
        dep[u] = dep[p] + 1; dp[u][0] = p;
        for (int i = 1; i <= 20; i++) {
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for (auto v : g[u]) {
            if (v == p) continue;
            dfs1(v, u);
        }
    }
    int lca(int x, int y) { //求lca
        if (dep[x] < dep[y]) swap(x, y);
        for (int i = 20; i >= 0; i--) {
            if (dep[dp[x][i]] >= dep[y]) {
                x = dp[x][i];
            }
        }
        if (x == y) return y;
        for (int i = 20; i >= 0; i--) {
            if (dp[x][i] != dp[y][i]) {
                x = dp[x][i], y = dp[y][i];
            }
        }
        return dp[x][0];
    }
    void pushup(int u) {
        auto& ls = tr[u].l, & rs = tr[u].r;
        //tr[x].sum = tr[ls].sum + tr[rs].sum;
        if (tr[ls].sum >= tr[rs].sum) {
            tr[u].sum = tr[ls].sum;
            tr[u].ty = tr[ls].ty;
        }
        else {
            tr[u].sum = tr[rs].sum;
            tr[u].ty = tr[rs].ty;
        }
    }
    void apply(int& u, int l, int r, int p, int k) {//版本u的p值的数量+=k
        if (!u) u = ++tot;//动态开点
        if (l == r) {
            tr[u].sum += k;
            tr[u].ty = p;
            return;
        }
        int mid = l + r >> 1;
        if (p <= mid) apply(tr[u].l, l, mid, p, k);
        else apply(tr[u].r, mid + 1, r, p, k);
        pushup(u);
    }

    int merge(int x, int y, int l, int r) {
        if (!x or !y) return x + y;
        if (l == r) {
            tr[x].sum += tr[y].sum;
            return x;
        }
        int mid = l + r >> 1;
        tr[x].l = merge(tr[x].l, tr[y].l, l, mid);
        tr[x].r = merge(tr[x].r, tr[y].r, mid + 1, r);
        pushup(x);
        return x;
    }

    void dfs2(int u, int p = 0) {
        for (auto v : g[u]) {
            if (v == p) continue;
            dfs2(v, u);
            root[u] = merge(root[u], root[v], 1, N);
        }
        tr[u].ans = tr[root[u]].sum ? tr[root[u]].ty : 0;//及时保存答案以免被破坏
    }
};


void Prework() {

}
void Solve() {
    sgt::init();
    int n, m;cin >> n >> m;
    for (int i = 1;i < n;i++) {
        int u, v;cin >> u >> v;
        sgt::g[u].push_back(v);
        sgt::g[v].push_back(u);
    }
    sgt::dfs1(1);
    for (int i = 1;i <= m;i++) {
        int x, y, z;cin >> x >> y >> z;
        sgt::apply(sgt::root[x], 1, sgt::N, z, 1);
        sgt::apply(sgt::root[y], 1, sgt::N, z, 1);
        int f = sgt::lca(x, y);
        sgt::apply(sgt::root[f], 1, sgt::N, z, -1);
        sgt::apply(sgt::root[sgt::dp[f][0]], 1, sgt::N, z, -1);
    }
    sgt::dfs2(1);
    for (int i = 1;i <= n;i++) {
        cout << sgt::tr[i].ans << endl;
    }
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



https://codeforces.com/problemset/problem/600/E

值域线段树维护数量最大值mx和答案sum。线段树合并。

```C++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

namespace sgt {
    const int N = 1e5 + 10;
    struct node {
        int l, r;
        int mx = 0;
        int sum = 0;
        int ans = 0;
    }tr[N * 20];//NlogN
    int tot = 0, root[N];
    vector<int> g[N];
    int dp[N][21], dep[N];
    void init(int n) {
        for (int i = 1;i <= tot;i++) {
            tr[i] = { 0,0,0,0 };
            root[i] = 0;
        }
        for (int i = 0;i <= n;i++) {
            g[i].clear();
            dep[i] = 0;
            for (int j = 0;j <= 20;j++) dp[i][j] = 0;
        }
        tot = 0;
    }
    void dfs1(int u, int p = 0) {
        dep[u] = dep[p] + 1; dp[u][0] = p;
        for (int i = 1; i <= 20; i++) {
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for (auto v : g[u]) {
            if (v == p) continue;
            dfs1(v, u);
        }
    }
    int lca(int x, int y) { //求lca
        if (dep[x] < dep[y]) swap(x, y);
        for (int i = 20; i >= 0; i--) {
            if (dep[dp[x][i]] >= dep[y]) {
                x = dp[x][i];
            }
        }
        if (x == y) return y;
        for (int i = 20; i >= 0; i--) {
            if (dp[x][i] != dp[y][i]) {
                x = dp[x][i], y = dp[y][i];
            }
        }
        return dp[x][0];
    }
    void pushup(int u) {
        auto& ls = tr[u].l, & rs = tr[u].r;
        //tr[x].sum = tr[ls].sum + tr[rs].sum;
        if (tr[ls].mx > tr[rs].mx) {
            tr[u].mx = tr[ls].mx;
            tr[u].sum = tr[ls].sum;
        }
        else if (tr[ls].mx < tr[rs].mx) {
            tr[u].mx = tr[rs].mx;
            tr[u].sum = tr[rs].sum;
        }
        else {
            tr[u].mx = tr[ls].mx;
            tr[u].sum = tr[ls].sum + tr[rs].sum;
        }
    }
    void apply(int& u, int l, int r, int p) {
        if (!u) u = ++tot;//动态开点
        if (l == r) {
            tr[u].sum = p;
            tr[u].mx = 1;
            return;
        }
        int mid = l + r >> 1;
        if (p <= mid) apply(tr[u].l, l, mid, p);
        else apply(tr[u].r, mid + 1, r, p);
        pushup(u);
    }

    int merge(int x, int y, int l, int r) {
        if (!x or !y) return x + y;
        if (l == r) {
            tr[x].mx += tr[y].mx;
            return x;
        }
        int mid = l + r >> 1;
        tr[x].l = merge(tr[x].l, tr[y].l, l, mid);
        tr[x].r = merge(tr[x].r, tr[y].r, mid + 1, r);
        pushup(x);
        return x;
    }

    void dfs2(int u, int p = 0) {
        for (auto v : g[u]) {
            if (v == p) continue;
            dfs2(v, u);
            root[u] = merge(root[u], root[v], 1, N);
        }
        tr[u].ans = tr[root[u]].sum;
    }
};


void Prework() {

}
void Solve() {
    int n;cin >> n;
    sgt::init(n);
    vector<int> c(n + 1);
    for (int i = 1;i <= n;i++) {
        cin >> c[i];
    }
    for (int i = 1;i < n;i++) {
        int u, v;cin >> u >> v;
        sgt::g[u].push_back(v);
        sgt::g[v].push_back(u);
    }
    sgt::dfs1(1);
    for (int i = 1;i <= n;i++) {
        sgt::apply(sgt::root[i], 1, sgt::N, c[i]);
    }
    sgt::dfs2(1);
    for (int i = 1;i <= n;i++) {
        cout << sgt::tr[i].ans << ' ';
    }
    cout << endl;
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


https://www.luogu.com.cn/problem/P3899

将询问离线后，再线段树合并。值域线段树维护深度dep作为下标和子树大小-1作为权值。

如果先dfs后询问的话，就需要merge的时候新开节点，否则会对先前的节点有影响。但是这样空间复杂度稍大，应该会大一倍左右。

```C++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'



vector<int> res(300001);
namespace sgt {
    const int N = 3e5 + 10;
    struct node {
        int ls, rs;
        int sum = 0;
        int ans = 0;
    }tr[N * 20];//NlogN
    int tot = 0, root[N];
    vector<int> g[N];
    //int dp[N][21];
    int dep[N], sz[N];
    vector<array<int, 2>> evt[N];
    void init(int n) {
        for (int i = 1;i <= tot;i++) {
            tr[i] = { 0,0,0,0 };
            root[i] = 0;
        }
        for (int i = 0;i <= n;i++) {
            g[i].clear();
            dep[i] = 0;
            sz[i] = 0;
        }
        tot = 0;
    }
    void dfs1(int u, int p = 0) {
        dep[u] = dep[p] + 1;
        for (auto v : g[u]) {
            if (v == p) continue;
            dfs1(v, u);
            sz[u] += sz[v];
        }
        sz[u] += 1;
    }
    void pushup(int u) {
        auto& ls = tr[u].ls, & rs = tr[u].rs;
        tr[u].sum = tr[ls].sum + tr[rs].sum;
    }
    void apply(int& u, int p, int k, int l = 1, int r = N) {
        if (!u) u = ++tot;//动态开点
        if (l == r) {
            tr[u].sum += k;
            return;
        }
        int mid = l + r >> 1;
        if (p <= mid) apply(tr[u].ls, p, k, l, mid);
        else apply(tr[u].rs, p, k, mid + 1, r);
        pushup(u);
    }

    int query(int u, int ql, int qr, int l = 1, int r = N) {
        if (!u) return 0;
        if (ql == l and qr == r) {
            return tr[u].sum;
        }
        int mid = l + r >> 1;
        int res = 0;
        if (ql <= mid and tr[u].ls) {
            res += query(tr[u].ls, ql, min(mid, qr), l, mid);
        }
        if (qr > mid and tr[u].rs) {
            res += query(tr[u].rs, max(mid + 1, ql), qr, mid + 1, r);
        }
        return res;
    }

    int merge(int x, int y, int l, int r) {
        if (!x or !y) return x + y;
        if (l == r) {
            tr[x].sum += tr[y].sum;
            return x;
        }
        int mid = l + r >> 1;
        tr[x].ls = merge(tr[x].ls, tr[y].ls, l, mid);
        tr[x].rs = merge(tr[x].rs, tr[y].rs, mid + 1, r);
        pushup(x);
        return x;
    }

    void dfs2(int u, int p = 0) {
        for (auto v : g[u]) {
            if (v == p) continue;
            dfs2(v, u);
            root[u] = merge(root[u], root[v], 1, N);
        }
        //tr[u].ans = tr[root[u]].sum;
        for (auto [k, id] : evt[u]) {
            res[id] = min(k, sgt::dep[u] - 1) * (sgt::sz[u] - 1) + query(root[u], dep[u] + 1, dep[u] + k);
        }
    }
};


void Prework() {

}
void Solve() {
    int n, q;cin >> n >> q;
    res.resize(q + 1);
    sgt::init(n);
    for (int i = 1;i < n;i++) {
        int u, v;cin >> u >> v;
        sgt::g[u].push_back(v);
        sgt::g[v].push_back(u);
    }
    sgt::dfs1(1);
    for (int i = 1;i <= n;i++) {
        sgt::apply(sgt::root[i], sgt::dep[i], sgt::sz[i] - 1);
    }
    for (int i = 1;i <= q;i++) {
        int p, k;cin >> p >> k;
        sgt::evt[p].push_back({ k,i });
    }
    sgt::dfs2(1);
    for (int i = 1;i <= q;i++) {
        cout << res[i] << endl;
    }
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




https://www.luogu.com.cn/problem/P3224

```C++
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'

struct DSU {
    vector<int> p, siz;
    DSU(int n) :p(n), siz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return 0;
        siz[x] += siz[y];
        p[y] = x;
        return 1;
    }
    int size(int x) {
        return siz[find(x)];
    }
};
namespace sgt {
    const int N = 1e5 + 10;
    struct node {
        int ls, rs;
        int sum = 0;
        int id = 0;
        int ans = 0;
    }tr[N * 50];
    int tot = 0, root[N];
    vector<int> g[N];
    int dp[N][21], dep[N];
    void init(int n) {
        for (int i = 1;i <= tot;i++) {
            tr[i] = { 0,0,0,0 };
            root[i] = 0;
        }
        for (int i = 0;i <= n;i++) {
            g[i].clear();
            dep[i] = 0;
            for (int j = 0;j <= 20;j++) dp[i][j] = 0;
        }
        tot = 0;
    }
    void dfs1(int u, int p = 0) {
        dep[u] = dep[p] + 1; dp[u][0] = p;
        for (int i = 1; i <= 20; i++) {
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for (auto v : g[u]) {
            if (v == p) continue;
            dfs1(v, u);
        }
    }
    int lca(int x, int y) { //求lca
        if (dep[x] < dep[y]) swap(x, y);
        for (int i = 20; i >= 0; i--) {
            if (dep[dp[x][i]] >= dep[y]) {
                x = dp[x][i];
            }
        }
        if (x == y) return y;
        for (int i = 20; i >= 0; i--) {
            if (dp[x][i] != dp[y][i]) {
                x = dp[x][i], y = dp[y][i];
            }
        }
        return dp[x][0];
    }
    void pushup(int u) {
        auto& ls = tr[u].ls, & rs = tr[u].rs;
        tr[u].sum = tr[ls].sum + tr[rs].sum;
    }
    void apply(int& u, int p, int k, int id, int l = 1, int r = N) {
        if (!u) u = ++tot;//动态开点
        if (l == r) {
            tr[u].sum += k;
            tr[u].id = id;
            return;
        }
        int mid = l + r >> 1;
        if (p <= mid) apply(tr[u].ls, p, k, id, l, mid);
        else apply(tr[u].rs, p, k, id, mid + 1, r);
        pushup(u);
    }
    int query(int u, int ql, int qr, int l = 1, int r = N) {
        if (!u) return 0;
        if (ql == l and qr == r) {
            return tr[u].sum;
        }
        int mid = l + r >> 1;
        int res = 0;
        if (ql <= mid and tr[u].ls) {
            res += query(tr[u].ls, ql, min(mid, qr), l, mid);
        }
        if (qr > mid and tr[u].rs) {
            res += query(tr[u].rs, max(mid + 1, ql), qr, mid + 1, r);
        }
        return res;
    }
    int kth(int u, int k, int l = 1, int r = N) {
        if (l == r) {
            return tr[u].id;
        }
        int mid = l + r >> 1;
        if (k <= tr[tr[u].ls].sum) return kth(tr[u].ls, k, l, mid);
        else return kth(tr[u].rs, k - tr[tr[u].ls].sum, mid + 1, r);
    }
    int merge(int x, int y, int l = 1, int r = N) {
        if (!x or !y) return x + y;
        if (l == r) {
            tr[x].sum += tr[y].sum;
            return x;
        }
        int mid = l + r >> 1;
        tr[x].ls = merge(tr[x].ls, tr[y].ls, l, mid);
        tr[x].rs = merge(tr[x].rs, tr[y].rs, mid + 1, r);
        pushup(x);
        return x;
    }

    void dfs2(int u, int p = 0) {
        for (auto v : g[u]) {
            if (v == p) continue;
            dfs2(v, u);
            root[u] = merge(root[u], root[v], 1, N);
        }
        // tr[u].ans = tr[root[u]].sum ? tr[root[u]].ty : 0;//及时保存答案
    }
};



void Prework() {

}


void Solve() {
    int n, m;cin >> n >> m;
    sgt::init(n);
    vector<int> a(n + 1);for (int i = 1;i <= n;i++) cin >> a[i];
    for (int i = 1;i <= n;i++) {
        sgt::apply(sgt::root[i], a[i], 1, i);
    }
    DSU d(n + 1);
    for (int i = 1;i <= m;i++) {
        int u, v;cin >> u >> v;
        u = d.find(u);v = d.find(v);
        if (u == v) continue;
        d.merge(u, v);
        sgt::root[u] = sgt::merge(sgt::root[u], sgt::root[v]);
    }
    int q;cin >> q;
    while (q--) {
        char op;cin >> op;
        int x, y;cin >> x >> y;
        if (op == 'B') {
            x = d.find(x);
            y = d.find(y);
            if (x == y) continue;
            d.merge(x, y);
            sgt::root[x] = sgt::merge(sgt::root[x], sgt::root[y]);
        }
        else {
            x = d.find(x);
            if (d.size(x) < y) cout << -1 << endl;
            else {
                int res = sgt::kth(sgt::root[x], y);
                cout << res << endl;
            }
        }
    }
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








