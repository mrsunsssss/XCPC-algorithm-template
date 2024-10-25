const int N = 2e5 + 10;
const int MOD = 1e9 + 7;
struct matrix {
    int n;
    vector<vector<int>> data;
    matrix() = default;
    matrix(int n) :n(n), data(n + 1, vector<int>(n + 1)) {}
    vector<int>& operator[] (int idx) { return data[idx]; }
    const vector<int>& operator[] (int idx) const { return data[idx]; }

    void dbg() {
        cout << "-----matrix:begin-----\n";
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cout << data[i][j] << ' ';
            }
            cout << endl;
        }
        cout << "-----matrix:end-----\n";
    }
    void I() {
        for (int i = 1; i <= n; i++) {
            data[i][i] = 1;
        }
    }
};

matrix operator*(const matrix& A, const matrix& B) {
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
matrix operator+(const matrix& A, const matrix& B) {
    int n = A.n;
    matrix C;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++) {
                C[i][j] = A[i][j] + B[i][j];
                if (C[i][j] >= MOD) C[i][j] -= MOD;
            }

    return C;
}
matrix qp(matrix A, int m) {
    int n = A.n;
    matrix ans;
    for (int i = 1; i <= n; i++) ans[i][i] = 1;
    while (m) {
        if (m & 1) ans = ans * A;
        m >>= 1;A = A * A;
    }
    return ans;
}
matrix pow_sum(matrix A, int m) {//qp(A,1)+qp(A,2)+...+qp(A,m) 
    int n = A.n;
    matrix ans(n), B = A;
    while (m) {
        if (m & 1) ans = ans * A + B;
        B = B * A + B;A = A * A;m >>= 1;
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
    matrix base1[N], basesqrt[N];//注意段错误/栈内存不够，要放到外面作为全局变量
    int Block_len;
    int Phi;
    ll maxn = 1e9 + 7;//模数的最大值
    void init(matrix x) {//初始化底数为x
        Phi = getphi(MOD);
        Block_len = sqrt(maxn) + 1;
        base1[0] = matrix(11);base1[0].I();
        for (int i = 1;i <= Block_len;i++)
            base1[i] = base1[i - 1] * x;
        basesqrt[0] = matrix(11);basesqrt[0].I();
        for (int i = 1;i <= Block_len;i++)
            basesqrt[i] = basesqrt[i - 1] * base1[Block_len];
    }
    matrix qp(unsigned long long x) {
        x %= Phi;
        return basesqrt[x / Block_len] * base1[x % Block_len];
    }
}

