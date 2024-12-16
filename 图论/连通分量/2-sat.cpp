struct Two_SAT {
    int n;SCC scc;
    Two_SAT(int _n) :n(_n) {
        scc = SCC(n * 2);
    }
    void Add(int x, int y) {
        scc.AddEdge(x, y);
    }
    vector<int> operator[](const int& k)const { return scc[k]; }
    vector<int>& operator[](const int& k) { return scc[k]; }
    int size() {
        return scc.size();
    }
    void run() {
        scc.run();
    }
    int belong(int x) {
        return scc.belong(x);
    }

    int inv(int x) {
        if (x <= n) return x + n;
        return x - n;
    }
    void implies(int u, int v) {//u蕴含v，即u为真则v为真
        scc.AddEdge(u, v);
        scc.AddEdge(inv(v), inv(u));
    }
    void either(int u, int v) {//u和v中至少一个为真
        scc.AddEdge(inv(u), v);
        scc.AddEdge(inv(v), u);
    }
    void equal(int u, int v) {//u=v
        implies(u, v);
        implies(inv(u), inv(v));
    }
    void unequal(int u, int v) {//u!=v
        implies(u, inv(v));
        implies(inv(u), v);
    }
    void set(int u) {//u=1
        scc.AddEdge(inv(u), u);
    }

    int solve() {
        run();
        for (int i = 1;i <= n;i++) {
            if (belong(i) == belong(i + n)) return 0;
        }
        return 1;
    }
    int get(int x) {
        return (belong(x) < belong(x + n));
    }
};
