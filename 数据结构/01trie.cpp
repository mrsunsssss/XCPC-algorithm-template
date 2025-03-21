const int N = 31*2e5+10;//31n
struct Trie01 {
    static int nxt[N][2];
    inline static int dic[N];//记录字典中的id//记录字典中是否有该串//记录该串在字典中出现次数
    inline static int pre[N];//记录该前缀在字典中出现次数
    int root = 0, tot = 0;
    Trie01() {}
    ~Trie01() { clear(); }
    void clear() {
        for (int i = 0;i <= tot;i++) nxt[i][0] = nxt[i][1] = 0;
        for (int i = 0;i <= tot;i++) dic[i] = pre[i] = 0;
        root = tot = 0;
    }
    int newnode() {
        return ++tot;
    }
    int Insert(int pre, int ch) {
        return nxt[pre][ch] ? nxt[pre][ch] : nxt[pre][ch] = newnode();
    }
    void insert(int x, int ID) {
        int now = root;
        for (int i = 30;i >= 0;i--) {
            now = Insert(now, x >> i & 1);
            pre[now] += 1;
        }
        dic[now] += 1;
    }
    void erase(int x) {
        int now = root;
        for (int i = 30;i >= 0;i--) {
            now = nxt[now][x >> i & 1];
            if (pre[now]) pre[now] -= 1;
        }
        if (dic[now]) dic[now] -= 1;
    }
    int query(int x) {
        int res = 0;
        int now = root;
        for (int i = 30;i >= 0;i--) {
            int t = x >> i & 1;
            if (nxt[now][t ^ 1] && pre[nxt[now][t ^ 1]] > 0) now = nxt[now][t ^ 1], res += 1ll << i;
            else now = nxt[now][t];
        }
        return res;
    }

};
int Trie01::nxt[N][2];


//持久化01trie

const int N = 32 * 2e5 + 10;//N>=31n+n=32*n,31n是每位的空间，n个是持久化trie的根节点

struct PTrie01 {
    static int nxt[N][2];
    static int root[N];
    static int sum[N];
    int tot = 0;
    PTrie01() {}
    ~PTrie01() { clear(); }
    void clear() {
        for (int i = 0;i <= tot;i++) nxt[i][0] = nxt[i][1] = 0;
        for (int i = 0;i <= tot;i++) sum[i] = 0;
        root[0] = tot = 0;
    }
    int newnode() {
        return ++tot;
    }
    void insert(int& now, int pre, int x) {
        now = newnode();sum[now] = sum[pre] + 1;
        int temp = now;
        for (int i = 30;i >= 0;i--) {
            int t = x >> i & 1;
            nxt[temp][0] = nxt[pre][0];
            nxt[temp][1] = nxt[pre][1];
            nxt[temp][t] = newnode();
            temp = nxt[temp][t]; pre = nxt[pre][t];
            sum[temp] = sum[pre] + 1;
        }
    }
    int query(int l, int r, int x) {//数组[l,r]范围与x异或最大值
        int res = 0;
        for (int i = 30;i >= 0;i--) {
            int t = x >> i & 1;
            if (sum[nxt[r][t ^ 1]] - sum[nxt[l][t ^ 1]] > 0) {
                res |= 1ll << i;
                l = nxt[l][t ^ 1], r = nxt[r][t ^ 1];
            }
            else l = nxt[l][t], r = nxt[r][t];
        }
        return res;
    }
};
int PTrie01::nxt[N][2];
int PTrie01::root[N];
int PTrie01::sum[N];
