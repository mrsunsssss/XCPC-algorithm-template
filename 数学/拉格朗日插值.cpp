Int Lagrange_Interpolation(vector<pair<int, Int>> a, int x) {//拉格朗日插值
    int n = a.size();
    Int res = 0;
    for (int i = 0;i < n;i++) {
        Int s = a[i].second;int t = 1;
        for (int j = 0;j < n;j++) {
            if (i == j) continue;
            s *= (x - a[j].first);
            t *= (a[i].first - a[j].first);
        }
        res = res + s / t;
    }
    return res;
}
