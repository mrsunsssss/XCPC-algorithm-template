const int N = 2e5 + 10;
struct Trie {
    static int nxt[N][26];
    inline static int dic[N];//记录字典中的id//记录字典中是否有该串//记录该串在字典中出现次数
    int root = 0, tot = 0;
    Trie() {}
    ~Trie() { clear(); }
    void clear() {
        for (int i = 0;i <= tot;i++) {
            for (int j = 0;j < 26;j++) nxt[i][j] = 0;
        }
        for (int i = 0;i <= tot;i++) dic[i] = 0;
        root = tot = 0;
    }
    int newnode() {
        return ++tot;
    }
    int Insert(int pre, int ch) {
        return nxt[pre][ch] ? nxt[pre][ch] : nxt[pre][ch] = newnode();
    }
    void insert(string s) {
        int now = root;
        for (int i = 1;i < s.size();i++) {
            now = Insert(now, s[i] - 'a');
        }
        dic[now] += 1;
    }
};
int Trie::nxt[N][26];
