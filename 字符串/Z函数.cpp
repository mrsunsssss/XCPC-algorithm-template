vector<int> Z_function(const string& s) {
    int n = (int)s.size() - 1;
    vector<int> z(n + 1);z[1] = n;
    for (int i = 2, l = 0, r = 0;i <= n;i++) {
        if (i <= r) z[i] = min(z[i - l + 1], r - i + 1);
        while (i + z[i] <= n && s[1 + z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}
vector<int> Z_function(const string& s, const string& t, vector<int>& z) {//先计算出s的z函数
    int n = (int)s.size() - 1;
    int m = (int)t.size() - 1;
    vector<int> p(m + 1);
    for (int i = 1, l = 0, r = 0;i <= m;i++) {
        if (i <= r) p[i] = min(z[i - l + 1], r - i + 1);
        while (1 + p[i] <= n && i + p[i] <= m && s[1 + p[i]] == t[i + p[i]]) p[i]++;
        if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
    }
    return p;
}
//s=' '+s;
//从第i位开始与字符串的最长公共前缀
