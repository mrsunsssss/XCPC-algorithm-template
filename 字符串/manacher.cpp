struct Manacher {
    int n;//扩展后的长度
    string s;//扩展后的回文串
    vector<int> rad;//i为中心的最大回文半径

    char operator[](int k)const { return s[k]; }
    char& operator[](int k) { return s[k]; }

    Manacher(string S) {
        int len = S.size() - 1;
        n = 2 * len + 1;
        s.resize(n + 1);
        rad.resize(n + 1);
        init(S);
        manacher();
    }
    void init(string S) {
        int len = S.size() - 1;
        s[0] = ' ';
        s[n] = '#';
        for (int i = len;i >= 1;i--) {
            s[i * 2] = S[i];s[i * 2 - 1] = '#';
        }
    }
    void manacher() {
        rad[1] = 1;int k = 1;
        for (int i = 2;i <= n;i++) {
            int p = k + rad[k] - 1;
            if (i <= p)  rad[i] = min(rad[2 * k - i], p - i + 1);
            else rad[i] = 1;
            while (i + rad[i] <= n && s[i + rad[i]] == s[i - rad[i]]) rad[i]++;
            if (i + rad[i] > k + rad[k]) k = i;
        }
    }
    int Max(int i) {
        return rad[i] - 1;
    }
};
//注意添加 s=' '+s;
