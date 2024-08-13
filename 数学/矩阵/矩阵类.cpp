const int maxn = 210;
const int MOD = 1e9 + 7;
struct matrix {
    int n;
    int data[maxn][maxn];
    matrix() = default;
    matrix(int n) :n(n) {}
    int* operator[] (int idx) { return data[idx]; }
    void dbg() {
        cout << "-----matrix:begin-----\n";
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= n;j++) {
                cout << data[i][j] << ' ';
            }
            cout << endl;
        }
        cout << "-----matrix:end-----\n";
    }
};
matrix operator*(matrix& A, matrix& B) {
    int n = A.n;
    matrix C(n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++) {
                C[i][j] += A[i][k] * B[k][j] % MOD;
                if (C[i][j] >= MOD) C[i][j] -= MOD;
            }

    return C;
}
matrix operator+(matrix& A, matrix& B) {
    int n = A.n;
    matrix C(n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++) {
                C[i][j] = A[i][k] * B[k][j];
                if (C[i][j] >= MOD) C[i][j] -= MOD;
            }

    return C;
}
matrix qp(matrix A, int t) {
    int n = A.n;
    matrix ans(n);
    for (int i = 1; i <= n; i++) ans[i][i] = 1;
    while (t) {
        if (t & 1) ans = ans * A;
        t >>= 1;A = A * A;
    }
    return ans;
}
//矩阵光速幂,处理同底数同模数的幂
namespace LP {
    ll getphi(ll x) {
        ll res = x;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                res -= res / i;
                while (x % i == 0) x /= i;
            }
        }
        if (x > 1) res -= res / x;
        return res;
    }
    matrix base1[N], basesqrt[N];
    int Block_len;
    int Phi;
    ll maxn = 1e10;//模数的最大值
    void init(matrix x) {//初始化底数为x
        Phi = getphi(MOD);
        Block_len = sqrt(maxn) + 1;
        base1[0] = matrix(100);base1[0].I(); for (int i = 1;i <= Block_len;i++) base1[i] = base1[i - 1] * x;
        basesqrt[0] = matrix(100);basesqrt.I(); for (int i = 1;i <= Block_len;i++) basesqrt[i] = basesqrt[i - 1] * base1[Block_len];
    }
    matrix qp(unsigned long long x) {
        x %= Phi;
        return basesqrt[x / Block_len] * base1[x % Block_len];
    }
}
