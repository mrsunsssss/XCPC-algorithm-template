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
        tr[u].ans = tr[root[u]].sum ? tr[root[u]].ty : 0;//及时保存答案
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
