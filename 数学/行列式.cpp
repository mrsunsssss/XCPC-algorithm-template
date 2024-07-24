using matrix = vector<vector<int>>;

ll det(matrix& A, int n) {
    ll res = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            while (A[j][i]) { //辗转相除法
                ll t = A[i][i] / A[j][i];
                for (int k = i; k <= n; ++k) {
                    A[i][k] = (A[i][k] - t * A[j][k]);
                    swap(A[i][k], A[j][k]);
                }
                res = -res;
            }
        }
        if (!A[i][i]) return 0;
        res = res * A[i][i];
    }
    return res;
}
