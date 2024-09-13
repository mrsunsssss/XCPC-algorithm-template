struct KMP {
    string s;
    int len;
    vector<int> nxt;//S[1,i]的非平凡最大Border
    KMP(string s) :s(s) {
        len = s.size() - 1;
        nxt.resize(len + 1);
        init(s);
    }
    void init(string s) {
        for (int i = 2;i <= len;i++) {
            nxt[i] = nxt[i - 1];
            while (nxt[i] && s[i] != s[nxt[i] + 1]) nxt[i] = nxt[nxt[i]];
            nxt[i] += (s[i] == s[nxt[i] + 1]);
        }
    }
    //s在ss中出现的位置
    vector<int> match(string ss, int ONLY_ONE = 0) {
        int len_ss = ss.size() - 1;
        vector<int> res;
        for (int i = 1, j = 1;i <= len_ss;) {
            while (j != 1 && ss[i] != s[j]) j = nxt[j - 1] + 1;
            if (ss[i] == s[j]) i++, j++;
            else i++;
            if (j == len + 1) {
                res.push_back(i - j + 1);
                if (ONLY_ONE) return res;
                j = nxt[len] + 1;
            }
        }
        return res;
    }
    //周期
    vector<int> period() {
        vector<int> res;
        int now = len;
        while (now) {
            now = nxt[now];
            res.push_back(len - now);
        }
        return res;
    }
    //循环节
    vector<int> loop() {
        vector<int> res;
        int now = len;
        for (auto i : period()) {
            if (len % i == 0) res.push_back(i);
        }
        return res;
    }

};
//1-index
