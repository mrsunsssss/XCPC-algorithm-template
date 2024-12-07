//需要满足a和b是凸函数,即差分(a),差分(b)单调
//得到 c[i + j] = max(a[i] + b[j])
vector<int> max_add_convolution(vector<int> a, vector<int> b) {
    for (int i = (int)a.size() - 1; i >= 1; i--) a[i] -= a[i - 1];
    for (int i = (int)b.size() - 1; i >= 1; i--) b[i] -= b[i - 1];
    vector<int> c(a.size() + b.size() - 1);
    c[0] = a[0] + b[0];
    merge(a.begin() + 1, a.end(), b.begin() + 1, b.end(), c.begin() + 1, greater<>());
    for (int i = 1; i < a.size() + b.size() - 1; i++) c[i] += c[i - 1];
    return c;
}
