 struct HLD {//权值如果在边上，先将权值压到深度大的点上，再建立树。
    int idx = 0;
    vector<int> top, dep, fa, sz, son, in, out, dfn, w, nw;//需要初始化w权值数组，需要建图g
    vector<vector<int>> g;
    HLD(int n) : top(n + 1), dep(n + 1), fa(n + 1), sz(n + 1), son(n + 1),
        in(n + 1), out(n + 1), dfn(n + 1), w(n + 1), nw(n + 1), g(n + 1), idx(0) {}
 
    void build(int root) {
        dfs(root, root);
        dfs2(root, root, idx);
    }
 
    void AddEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
 
    void dfs(int u, int p) {
        fa[u] = p;
        dep[u] = dep[p] + 1;
        sz[u] = 1;
        for (int v : g[u]) {
            if (v == p) continue;
            dfs(v, u);
            sz[u] += sz[v];
            if (sz[son[u]] < sz[v]) son[u] = v;//重儿子
        }
    }
 
    void dfs2(int u, int Top, int& idx) {
        top[u] = Top;
        in[u] = ++idx;
        dfn[idx] = u;
        nw[idx] = w[u];
        if (son[u] == 0) return;
        dfs2(son[u], Top, idx);
        for (int v : g[u]) {
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v, idx);
        }
        out[u] = idx;
    }
 
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
 
    // 操作路径上的节点
    void operatePath(int a, int b, function<void(int, int)> op, bool isEdge) {
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            op(in[top[a]], in[a]);
            a = fa[top[a]];
        }
        if (dep[a] > dep[b]) swap(a, b);
        op(in[a] + isEdge, in[b]);
    }
 
    // 操作子树
    void operateSubtree(int x, function<void(int, int)> op, bool isEdge) {
        op(in[x] + isEdge, in[x] + sz[x] - 1);
    }
 
    // 获取两点间的距离
    int distance(int a, int b) {
        return dep[a] + dep[b] - 2 * dep[lca(a, b)];
    }
 
    // 判断节点b是否在节点a的子树中
    bool isAncestor(int a, int b) {
        return in[a] <= in[b] && in[b] <= out[a];
    }
 
    // 获取三个节点的LCA
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
 
    // 从节点u出发，沿着父节点往上跳k层，返回跳到的节点 (k级祖先)
    int kthAncestor(int u, int k) {
        if (dep[u] < k) return -1;
        int d = dep[u] - k;
        while (dep[top[u]] > d) u = fa[top[u]];
        return dfn[in[u] - dep[u] + d];
    }
 
};
