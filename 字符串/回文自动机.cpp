struct PAM {
    inline static int s[N], now;//字符串,当前位置
    static int nxt[N][26]; inline static int fail[N], faildep[N], len[N], last, tot, sum;
    //边,fail边,该节点代表的回文串长度,上一个字母所在节点,结点总数,回文串数
    inline static int num[N];//所有回文串出现次数
    void clear() {
        //奇数长度的root为节点1,偶数长度的root为节点0
        s[0] = -1;
        len[0] = 0, len[1] = -1;
        fail[0] = 1, fail[1] = 0;
        faildep[0] = faildep[1] = 0;
        tot = 1;now = last = 0;
        sum = 0;
        memset(nxt[0], 0, sizeof nxt[0]);
        memset(nxt[1], 0, sizeof nxt[1]);
    }
    PAM() { clear(); }
    PAM(string S) { clear();init(S);build(); }
    int newnode(int Len) {
        tot++;
        memset(nxt[tot], 0, sizeof nxt[tot]);
        fail[tot] = num[tot] = 0;
        len[tot] = Len;
        return tot;
    }
    int jump_fail(int x) {
        //跳fail链(Border链,回文后缀链)直到满足添加当前字符仍为回文.
        while (s[now - len[x] - 1] != s[now]) x = fail[x];
        return x;
    }
    void add(int ch) {
        s[++now] = ch;
        int cur = jump_fail(last);
        if (!nxt[cur][ch]) {
            int t = newnode(len[cur] + 2);
            int from = nxt[jump_fail(fail[cur])][ch];
            fail[t] = from;
            faildep[t] = faildep[from] + 1;
            nxt[cur][ch] = t;
        }
        last = nxt[cur][ch];num[last]++;
        sum += faildep[last];
    }
    void build() {
        //fail[i]<i,可以直接大到小扫描
        for (int i = tot;i >= 2;i--) {
            num[fail[i]] += num[i];
        }
        num[0] = num[1] = 0;
    }
    void init(string s) {
        for (int i = 1;i < (int)s.size();i++) {
            add(s[i] - 'a');
        }
    }
};
int PAM::nxt[N][26];
//1-index
