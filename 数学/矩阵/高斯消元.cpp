const int maxn = 110;
using ld = long double;
using matrix = ld[maxn][maxn];
using vect = array<ld, maxn>;
void matrix_clr(matrix a, int n, int m) {
    for (int i = 0;i <= n;i++) {
        for (int j = 0;j <= m;j++) {
            a[i][j] = 0;
        }
    }
}
void gauss_elimination(matrix A, int n) { //A的大小n*(n+1)，如果方程有唯一解则算出,否则出错
    for (int i = 0; i < n; ++i) {
        int r = i;
        for (int j = i + 1; j < n; ++j)
            if (fabs(A[j][i]) > fabs(A[r][i]))
                r = j;
        if (r != i) for (int j = 0; j <= n; ++j)
            swap(A[r][j], A[i][j]);
        for (int k = i + 1; k < n; ++k)
            for (int j = n; j >= i; --j)
                A[k][j] -= A[k][i] / A[i][i] * A[i][j];
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j)
            A[i][n] -= A[j][n] * A[i][j];
        A[i][n] /= A[i][i];
    }
}
//无解返回-1，有唯一解返回0，有无穷多解返回1。
//在有解的情况下通过ans返回任意一个解。
//矩阵A的大小为n * (m + 1)，表示有n个方程，m个变量。
const double eps = 1e-8;
int row[maxn], var[maxn];
int one_possible(matrix A, int n, int m, vect& ans) {
    memset(row, -1, sizeof(row));
    int r = 0;
    for (int c = 0; c < m && r < n; ++c) {
        int x = r;
        for (int i = x + 1; i < n; ++i)
            if (fabs(A[i][c]) > fabs(A[x][c]))
                x = i;
        if (x != r) for (int j = 0; j <= m; ++j)
            swap(A[x][j], A[r][j]);
        if (fabs(A[r][c]) < eps)
            continue;
        for (int k = r + 1; k < n; ++k)
            for (int j = m; j >= c; --j)
                A[k][j] -= A[k][c] / A[r][c] * A[r][j];
        row[c] = r++;
    }
    for (int i = r; i < n; ++i) if (fabs(A[i][m]) > eps)
        return -1;
    for (int c = m - 1; c >= 0; --c) {
        int x = row[c];
        if (x < 0)
            ans[c] = 0;
        else {
            for (int i = x - 1; i >= 0; --i)
                A[i][m] -= A[i][c] / A[x][c] * A[x][m];
            ans[c] = A[x][m] / A[x][c];
        }
    }
    return r < m;
}
