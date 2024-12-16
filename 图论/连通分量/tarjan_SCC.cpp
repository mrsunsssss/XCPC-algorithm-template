struct SCC {
    vector<vector<int>> g, scc;//scc的编号满足反拓扑序,倒过来从cnt到1更新即可.
    vector<int> stk, l, id, ins, low, sz;
    int n;
    int cnt, top, idx;
    vector<vector<int>> ng;
    SCC() {}
    SCC(int _n) :n(_n), cnt(0), top(0), idx(0) {
        g.resize(n + 1);
        scc.resize(n + 1);
        stk.resize(n + 1);
        l.resize(n + 1);
        id.resize(n + 1);
        ins.resize(n + 1);
        low.resize(n + 1);
        sz.resize(n + 1);
    }
    void AddEdge(int u, int v) {
        g[u].push_back(v);
    }
    int size() { return cnt; }
    vector<int> operator[](const int& k)const { return scc[k]; }
    vector<int>& operator[](const int& k) { return scc[k]; }
    int belong(int x) { return id[x]; }
    void run() {
        auto dfs = [&](auto&& dfs, int u)->void {
            low[u] = l[u] = ++idx;
            stk[++top] = u;
            ins[u] = 1;
            for (auto v : g[u]) {
                if (!l[v]) dfs(dfs, v);
                if (ins[v]) low[u] = min(low[u], low[v]);
            }
            if (low[u] == l[u]) {
                cnt += 1;
                while (top) {
                    int v = stk[top--];
                    scc[cnt].push_back(v);
                    ins[v] = 0;
                    id[v] = cnt;
                    sz[cnt] += 1;
                    if (u == v) break;
                }
            }
            };
        for (int i = 1;i <= n;i++) {
            if (!l[i]) dfs(dfs, i);
        }
    }
    void build() {
        ng.resize(cnt + 1);
        unordered_set<int> st;
        for (int u = 1;u <= n;u++) {
            for (auto v : g[u]) {
                if (id[u] == id[v]) continue;
                int t = id[u] * 1919810 + id[v];
                if (st.count(t)) continue;
                ng[id[u]].push_back(id[v]);
                st.insert(t);
            }
        }
    }
};
