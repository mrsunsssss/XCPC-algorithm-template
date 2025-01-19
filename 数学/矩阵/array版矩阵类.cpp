const int N = 2e5 + 10;
const int MOD = 1e9 + 7;
template <typename T, int n, int m>
struct matrix {
    array<array<T, m>, n> A;
    matrix() {
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) A[i][j] = 0;
        }
    }
    auto& operator[](int i) { return A[i]; }
    const auto& operator[](int i) const { return A[i]; }
    void I() {
        for (int i = 0; i < min(n, m); i++) {
            A[i][i] = 1;
        }
    }
};

template <typename T, int n, int m>
ostream& operator<<(ostream& os, const matrix<T, n, m>& mat) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            os << mat.A[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}

// 矩阵乘法
template <typename T, int n, int m, int p>
matrix<T, n, p> operator*(const matrix<T, n, m>& A, const matrix<T, m, p>& B) {
    matrix<T, n, p> C;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j] % MOD;
                if (C[i][j] >= MOD) C[i][j] -= MOD;
            }
        }
    }
    return C;
}

// 矩阵加法
template <typename T, int n, int m>
matrix<T, n, m> operator+(const matrix<T, n, m>& A, const matrix<T, n, m>& B) {
    matrix<T, n, m> C;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = A[i][j] + B[i][j];
            if (C[i][j] >= MOD) C[i][j] -= MOD;
        }
    }
    return C;
}

// 矩阵快速幂
template <typename T, int n, int m>
matrix<T, n, m> qp(matrix<T, n, m> A, int k) {
    matrix<T, n, m> ans;
    ans.I();
    while (k) {
        if (k & 1) ans = ans * A;
        k >>= 1;
        A = A * A;
    }
    return ans;
}

// 求矩阵的幂和：qp(A,1) + qp(A,2) + ... + qp(A,k)
template <typename T, int n, int m>
matrix<T, n, m> pow_sum(matrix<T, n, m> A, int k) {
    matrix<T, n, m> ans, B = A;
    while (k) {
        if (k & 1) ans = ans * A + B;
        B = B * A + B;
        A = A * A;
        k >>= 1;
    }
    return ans;
}

// // 矩阵光速幂（处理同底数同模数的幂）
// namespace LP {
//     ll getphi(ll x) {
//         ll res = x;
//         for (int i = 2; i * i <= x; i++) {
//             if (x % i == 0) {
//                 res -= res / i;
//                 while (x % i == 0) x /= i;
//             }
//         }
//         if (x > 1) res -= res / x;
//         return res;
//     }

//     matrix<int, 11, 11> base1[N], basesqrt[N];  // 注意段错误/栈内存不够，要放到外面作为全局变量
//     int Block_len;
//     int Phi;
//     ll maxn = 1e9 + 7;  // 模数的最大值
//     void init(matrix<int, 11, 11> x) {// 初始化底数为x
//         Phi = getphi(MOD);
//         Block_len = sqrt(maxn) + 1;
//         base1[0] = matrix<int, 11, 11>(); base1[0].I();
//         for (int i = 1; i <= Block_len; i++)
//             base1[i] = base1[i - 1] * x;
//         basesqrt[0] = matrix<int, 11, 11>(); basesqrt[0].I();
//         for (int i = 1; i <= Block_len; i++)
//             basesqrt[i] = basesqrt[i - 1] * base1[Block_len];
//     }

//     matrix<int, 11, 11> qp(unsigned long long x) {
//         // x %= Phi; 一般不用，加的时候考虑清楚是否要加。
//         return basesqrt[x / Block_len] * base1[x % Block_len];
//     }
// }
