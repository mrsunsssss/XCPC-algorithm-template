struct ST {
    const int LOGN = 20;
    int n;
    vector<vector<int>> f;
    ST() {}
    ST(const vector<int>& a) :n((int)a.size() - 1) {

        f.assign(LOGN + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) {
            f[0][i] = a[i];
        }
        for (int j = 1; j <= LOGN; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                f[j][i] = min(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    void init(const vector<int>& a) {
        n = (int)a.size() - 1;
        f.assign(LOGN + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) {
            f[0][i] = a[i];
        }
        for (int j = 1; j <= LOGN; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                f[j][i] = min(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    int query(int l, int r) {
        int len = __lg(r - l + 1);
        return min(f[len][l], f[len][r - (1 << len) + 1]);
    }

};

struct SA {
    int n, m;//字符串长度,字符集大小
    inline static int s[N];//字符串
    inline static int cnt[N], sa_second[N], oldrank[N];//计数,第二关键字排名为i的后缀,旧排名
    vector<int> sa, rank, height;//第i名的后缀,后缀i的排名,排名为i与排名为i-1的LCP
    ST table;

    bool check(int x, int y, int w) {
        return oldrank[x] == oldrank[y] && x <= n && y <= n && oldrank[x + w] == oldrank[y + w];
    }
    SA(string S) {
        n = S.size() - 1;
        sa.resize(n + 1), rank.resize(n + 1), height.resize(n + 1);
        m = 128;
        for (int i = 1;i <= n;i++) s[i] = S[i];
        getSA();
        getHeight();
    }
    void getHeight() {
        int k = 0;
        for (int i = 1;i <= n;i++) {
            if (k) k--;
            int j = sa[rank[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
            height[rank[i]] = k;
        }
        table.init(height);
    }
    void getSA() {
        for (int i = 0;i <= m;i++) cnt[i] = 0;
        for (int i = 1;i <= n;i++) cnt[rank[i] = s[i]]++;
        for (int i = 1;i <= m;i++) cnt[i] += cnt[i - 1];
        for (int i = n;i >= 1;i--) sa[cnt[rank[i]]--] = i;

        //双关键字基数排序,每次倍增添加关键字
        for (int w = 1, p;w <= n;w <<= 1, m = p) {
            p = 0;
            //尾部第二关键字为空的元素,排名设为最小
            for (int i = n;i > n - w;i--) sa_second[++p] = i;

            for (int i = 1;i <= n;i++) {
                if (sa[i] > w) sa_second[++p] = sa[i] - w;
            }
            for (int i = 0;i <= m;i++) cnt[i] = 0;
            for (int i = 1;i <= n;i++) cnt[rank[sa_second[i]]]++;
            for (int i = 1;i <= m;i++) cnt[i] += cnt[i - 1];
            for (int i = n;i >= 1;i--) sa[cnt[rank[sa_second[i]]]--] = sa_second[i];

            for (int i = 0;i <= n;i++) oldrank[i] = rank[i];
            rank[sa[1]] = p = 1;
            for (int i = 2;i <= n;i++) {
                rank[sa[i]] = check(sa[i], sa[i - 1], w) ? p : ++p;
            }
            if (p == n) {
                for (int i = 1; i <= n; i++) sa[rank[i]] = i;
                break;
            }
        }
    }
    int lcp(int x, int y) {
        int rkx = rank[x], rky = rank[y];
        if (rkx > rky) swap(rkx, rky);
        rkx++;
        return table.query(rkx, rky);
    }
};

//1-index
