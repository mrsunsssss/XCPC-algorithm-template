struct ACAM {
    //basic
    static int tr[N][26];//Trie图边
    inline static int fail[N], root, tot;//fail边(字典串中与当前串的后缀匹配的最长的前缀),根,结点总数
 
    //extend
    inline static int cnt[N];//数量
    inline static int ed[N];//终止节点数量
    inline static vector<int> ID[N];//该节点对应字典串的id
 
    //topo
    inline static int deg[N];//度
 
    //dfs
    inline static vector<int> g[N];//fail[u] -> u
    inline static int l[N], r[N], idx;//dfs序
 
    ACAM() { clear(); }
    void clear() {
        memset(tr[0], 0, sizeof tr[0]);
        for (int i = 0;i <= tot;i++) {
            ID[i].clear();
            g[i].clear();
            deg[i] = ed[i] = fail[i] = cnt[i] = 0;
        }
        root = tot = 0;
    }
    int newnode() {
        tot++;
        memset(tr[tot], 0, sizeof tr[tot]);
        return tot;
    }
    void insert(const string& s, int id) {
        int now = root;
        for (int i = 0;i < s.size();i++) {
            int c = s[i] - 'a';
            if (!tr[now][c]) tr[now][c] = newnode();
            now = tr[now][c];
        }
        //extend
        ID[now].push_back(id);
        ed[now]++;
    }
 
    void build() {
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            if (tr[0][i]) {
                q.push(tr[0][i]);
                g[0].push_back(tr[0][i]);
            }
        }
        while (q.size()) {
            int u = q.front();q.pop();
            for (int i = 0; i < 26; i++) {
                int v = tr[u][i];
                if (v) {
                    fail[v] = tr[fail[u]][i], q.push(v);
                }
                else {
                    tr[u][i] = tr[fail[u]][i];
                }
            }
            //topo
            deg[fail[u]] += 1;
            //dfs
            g[fail[u]].push_back(u);
        }
    }
 
    void query(string s) {
        int now = root;
        int res = 0;
        for (int i = 0;i < s.size();i++) {
            int id = s[i] - 'a';
            now = tr[now][id];
            //do something
            cnt[now] += 1;
        }
    }
    void up() {//拓扑排序
        vector<int> vis(tot + 1);
        queue<int> q;
        for (int i = 1;i <= tot;i++) {
            if (deg[i] == 0)
                q.push(i), vis[i] = 1;
        }
        while (q.size()) {
            auto u = q.front();q.pop();
            if (--deg[fail[u]] == 0)
                q.push(fail[u]), vis[fail[u]] = 1;
            cnt[fail[u]] += cnt[u];
        }
    }
    void dfs(int u = 0) {
        l[u] = ++idx;
        for (auto v : g[u]) dfs(v);
        r[u] = idx;
    }
};
int ACAM::tr[N][26];
//build()
//0-index
