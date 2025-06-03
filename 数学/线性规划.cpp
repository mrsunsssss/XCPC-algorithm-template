https://uoj.ac/problem/179 有时间测一下这道题！！！
const int maxn = 500, maxm = 500;//约束数目上限,变量数目上限
const double INF = 1e100, eps = 1e-10;
struct Simplex {//单纯形法
    inline static int m = 0; // 变量个数
    inline static int n = 0; // 约束个数
    inline static double a[maxn][maxm]; // 输入矩阵
    inline static int f[maxn], d[maxm]; // 算法辅助变量
    Simplex() { clear(); }
    void clear() {
        for (int i = 0;i <= n;i++) f[i] = 0;
        for (int i = 0;i <= m;i++) d[i] = 0;
        for (int i = 0;i <= n;i++)
            for (int j = 0;j <= m;j++) a[i][j] = 0;
    }
    void pivot(int r, int c) {
        swap(d[c], f[r]);
        a[r][c] = 1 / a[r][c];
        for (int j = 0; j <= m; j++) if (j != c) a[r][j] *= a[r][c];
        for (int i = 0; i <= n; i++) {
            if (i != r) {
                for (int j = 0; j <= m; j++) if (j != c) a[i][j] -= a[i][c] * a[r][j];
                a[i][c] = -a[i][c] * a[r][c];
            }
        }
    }
    bool feasible() {
        for (;;) {
            int r, c;
            double p = INF;
            for (int i = 0; i < n; i++) if (a[i][m] < p) p = a[r = i][m];
            if (p > -eps) return true;
            p = 0;
            for (int i = 0; i < m; i++) if (a[r][i] < p) p = a[r][c = i];
            if (p > -eps) return false;
            p = a[r][m] / a[r][c];
            for (int i = r + 1; i < n; i++) if (a[i][c] > eps) {
                double v = a[i][m] / a[i][c];
                if (v < p)  r = i, p = v;
            }
            pivot(r, c);
        }
    }
    // 解有界返回1,无解返回0,无界返回-1.f[i]为x[i]的值,ret为目标函数的值
    int simplex(int n, int m, double x[maxm], double& ret) {
        this->n = n;
        this->m = m;
        for (int i = 0; i < m; i++) d[i] = i;
        for (int i = 0; i < n; i++) f[i] = m + i;
        if (!feasible()) return 0;
        for (;;) {
            int r, c;
            double p = 0;
            for (int i = 0; i < m; i++) if (a[n][i] > p) p = a[n][c = i];
            if (p < eps) {
                for (int i = 0; i < m; i++) if (d[i] < m) x[d[i]] = 0;
                for (int i = 0; i < n; i++) if (f[i] < m) x[f[i]] = a[i][m];
                ret = -a[n][m];
                return 1;
            }
            p = INF;
            for (int i = 0; i < n; i++) if (a[i][c] > eps) {
                double v = a[i][m] / a[i][c];
                if (v < p)  r = i, p = v;
            }
            if (p == INF) return -1;
            pivot(r, c);
        }
    }
};
