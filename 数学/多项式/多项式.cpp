const int MOD = 998244353;
const int N = 4e5 + 10;
using uint = unsigned;

namespace Cipolla {
    int mul(int x, int y) { return 1ll * x * y % MOD; }
    uint qp(uint a, int b) { uint res = 1; for (; b; b >>= 1, a = mul(a, a))  if (b & 1)  res = mul(res, a); return res; }
    int sqr_i;
    struct spc_Cp {
        int x, y;
        spc_Cp() { ; }
        spc_Cp(int x, int y) : x(x), y(y) {}
        inline spc_Cp operator * (const spc_Cp& t) const { return (spc_Cp) { (mul(x, t.x) + mul(mul(y, t.y), sqr_i)) % MOD, (mul(x, t.y) + mul(y, t.x)) % MOD }; }
    };
    spc_Cp qp(spc_Cp a, int b) {
        spc_Cp res = spc_Cp(1, 0);
        while (b) {
            if (b & 1) res = res * a;
            b >>= 1, a = a * a;
        }
        return res;
    }
    //解是res和MOD-res
    int Cipolla(int n) {
        srand(time(NULL));
        if (qp(n, MOD >> 1) == MOD - 1) return -1;
        ll t = mul(rand(), rand());
        while (qp((mul(t, t) - n) % MOD + MOD, MOD >> 1) == 1) t = 1ll * rand() * rand() % MOD;//找到非二次剩余的数,期望循环次数为2
        sqr_i = ((mul(t, t) - n) % MOD + MOD) % MOD;
        int res = qp(spc_Cp(t, 1), MOD + 1 >> 1).x;
        //return res;//返回任何一个解
        return min(res, MOD - res);//返回较小解
    }
}


int rev[N];
namespace MTT {//任意模数多项式乘法
    const double PI = acos((double)-1);
    struct Cp {
        double x, y;
        Cp() { ; }
        Cp(double _x, double _y) : x(_x), y(_y) {}
        inline Cp operator + (const Cp& t) const { return (Cp) { x + t.x, y + t.y }; }
        inline Cp operator - (const Cp& t) const { return (Cp) { x - t.x, y - t.y }; }
        inline Cp operator * (const Cp& t) const { return (Cp) { x* t.x - y * t.y, x* t.y + y * t.x }; }
        inline Cp conj() const { return(Cp) { x, -y }; }
        inline Cp operator*(const double& z) const { return (Cp) { x* z, y* z }; }
    }A[N], B[N], C[N], w[N / 2];

#define E(x) ll(x+0.5)%P

    void FFT(int n, Cp* a, int f) {
        for (int i = 0;i <= n - 1;i++) if (rev[i] < i) swap(a[i], a[rev[i]]);
        w[0] = Cp(1, 0);
        for (int i = 1;i < n;i <<= 1) {
            Cp t = Cp(cos(PI / i), f * sin(PI / i));
            for (int j = i - 2;j >= 0;j -= 2) w[j + 1] = t * (w[j] = w[j >> 1]);
            for (int l = 0;l < n;l += 2 * i) {
                for (int j = l;j < l + i;j++) {
                    Cp t = a[j + i] * w[j - l];
                    a[j + i] = a[j] - t;
                    a[j] = a[j] + t;
                }
            }
        }
        if (f == -1) for (int i = 0;i <= n - 1;i++) a[i].x /= n, a[i].y /= n;
    }

    void conv(vector<uint> a, vector<uint> b, vector<uint>& res, int P) {
        // [0,n-1]*[0,m-1]->[0,n+m-2]
        int n = a.size(), m = b.size();res.resize(n + m - 1);
        int S = (1 << 15) - 1;
        int R = 1, cc = -1;
        while (R <= n + m - 1) R <<= 1, cc++;
        for (int i = 1;i <= R;i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << cc);
        for (int i = 0;i <= n - 1;i++) A[i] = Cp((a[i] >> 15), (a[i] & S));
        for (int i = 0;i <= m - 1;i++) B[i] = Cp((b[i] >> 15), (b[i] & S));
        for (int i = n;i <= R - 1;i++) A[i] = Cp(0, 0);
        for (int i = m;i <= R - 1;i++) B[i] = Cp(0, 0);
        FFT(R, A, 1), FFT(R, B, 1);
        Cp ai, aj, xi, yi;
        for (int i = 0, j; i <= R / 2; i++) {
            j = (R - i) % R;
            xi = (B[i] + B[j].conj()) * 0.5;
            yi = (B[j].conj() - B[i]) * Cp(0, 0.5);
            ai = A[i], aj = A[j];
            A[i] = ai * xi;
            B[i] = ai * yi;
            A[j] = aj * xi.conj();
            B[j] = aj * yi.conj();
        }
        FFT(R, A, -1), FFT(R, B, -1);
        for (int i = 0;i <= n + m - 2;i++) {
            ll a = E(A[i].x), b = E(A[i].y), c = E(B[i].x), d = E(B[i].y);
            res[i] = (d + ((b + c) << 15) + (a << 30)) % P;
        }
    }

    void conv_db(vector<double> a, vector<double> b, vector<double>& res) {//答案double类型
        // [0,n-1]*[0,m-1]->[0,n+m-2]
        int n = a.size(), m = b.size();res.resize(n + m - 1);
        int R = 1, cc = -1;
        while (R <= n + m - 1) R <<= 1, cc++;
        for (int i = 1;i <= R;i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << cc);
        for (int i = 0;i <= n - 1;i++) A[i] = Cp(a[i], 0);
        for (int i = 0;i <= m - 1;i++) B[i] = Cp(b[i], 0);
        for (int i = n;i <= R - 1;i++) A[i] = Cp(0, 0);
        for (int i = m;i <= R - 1;i++) B[i] = Cp(0, 0);

        FFT(R, A, 1), FFT(R, B, 1);
        for (int i = 0;i < R;i++) C[i] = A[i] * B[i];
        FFT(R, C, -1);
        for (int i = 0;i <= n + m - 2;i++) res[i] = C[i].x;
    }

#undef E
}

int Add(int x, int y) { return (x + y >= MOD) ? x + y - MOD : x + y; }
int Dec(int x, int y) { return (x - y < 0) ? x - y + MOD : x - y; }
int mul(int x, int y) { return 1ll * x * y % MOD; }
uint qp(uint a, int b) { uint res = 1; for (; b; b >>= 1, a = mul(a, a))  if (b & 1)  res = mul(res, a); return res; }


namespace NTT {
    int sz;
    uint w[2500005], w_mf[2500005];
    int mf(int x) { return (1ll * x << 32) / MOD; }
    void init(int n) {
        for (sz = 2; sz < n; sz <<= 1);
        uint pr = qp(3u, (MOD - 1) / sz);
        w[sz / 2] = 1; w_mf[sz / 2] = mf(1);
        for (int i = 1; i < sz / 2; i++)  w[sz / 2 + i] = mul(w[sz / 2 + i - 1], pr), w_mf[sz / 2 + i] = mf(w[sz / 2 + i]);
        for (int i = sz / 2 - 1; i; i--)  w[i] = w[i << 1], w_mf[i] = w_mf[i << 1];
    }
    void ntt(vector<uint>& A, int L) {
        for (int d = L >> 1; d; d >>= 1)
            for (int i = 0; i < L; i += (d << 1))
                for (int j = 0; j < d; j++) {
                    uint x = A[i + j] + A[i + d + j];
                    if (x >= 2 * MOD)  x -= 2 * MOD;
                    ll t = A[i + j] + 2 * MOD - A[i + d + j], q = t * w_mf[d + j] >> 32; int y = t * w[d + j] - q * MOD;
                    A[i + j] = x; A[i + d + j] = y;
                }
        for (int i = 0; i < L; i++)  if (A[i] >= MOD)  A[i] -= MOD;
    }
    void intt(vector<uint>& A, int L) {
        for (int d = 1; d < L; d <<= 1)
            for (int i = 0; i < L; i += (d << 1))
                for (int j = 0; j < d; j++) {
                    uint x = A[i + j]; if (x >= 2 * MOD)  x -= 2 * MOD;
                    ll t = A[i + d + j], q = t * w_mf[d + j] >> 32, y = t * w[d + j] - q * MOD;
                    A[i + j] = x + y; A[i + d + j] = x + 2 * MOD - y;
                }
        int k = (L & (-L));
        reverse(A.begin() + 1, A.end());
        for (int i = 0; i < L; i++) {
            ll m = -A[i] & (L - 1);
            A[i] = (A[i] + m * MOD) / k;
            if (A[i] >= MOD)  A[i] -= MOD;
        }
    }
}
int _inv[N];
void Poly_init(int mod = MOD) {
    _inv[1] = 1;
    for (int i = 2;i < N;i++) _inv[i] = 1llu * _inv[MOD % i] * (MOD - MOD / i) % MOD;
}
struct Poly {
    vector<uint> p;
    Poly(int n) { p.resize(n); }
    Poly(int n, int k) { p.resize(n);for (int i = 0;i < n;i++) p[i] = k; }
    Poly(initializer_list<uint> list) : p(list) {}
    Poly() {}
    uint operator[](const int& k)const { return p[k]; }
    uint& operator[](const int& k) { return p[k]; }
    Poly extend(int x) { Poly c = *this;c.p.resize(x);return c; }
    int deg() { return (int)p.size() - 1; }
    void resize(int n) { p.resize(n); }
    int size() { return p.size(); }
    void rev() { reverse(p.begin(), p.end()); }
    void DebugPoly() {
        for (int i = 0;i < p.size();i++) {
            cout << p[i] << "x^" << i;
            if (i + 1 != p.size()) cout << "+";
        }
        cout << endl;
    }
};
Poly operator+ (Poly A, Poly B) {
    int n = A.size(), m = B.size();
    Poly c(max(n, m));
    for (int i = 0; i < n; i++)  c[i] = A[i];
    for (int i = 0; i < m; i++)  c[i] = Add(c[i], B[i]);
    return c;
}
Poly operator- (Poly A, Poly B) {
    int n = A.size(), m = B.size();
    Poly c(max(n, m));
    for (int i = 0; i < n; i++)  c[i] = A[i];
    for (int i = 0; i < m; i++)  c[i] = Dec(c[i], B[i]);
    return c;
}
Poly operator*(Poly A, Poly B) {//MOD=998244353,..a*2^k+1
    int n = A.deg() + B.deg() + 1;
    int lim;for (lim = 1; lim < n; lim <<= 1); NTT::init(lim);
    A.resize(lim); B.resize(lim);
    NTT::ntt(A.p, lim); NTT::ntt(B.p, lim);
    for (int i = 0; i < lim; i++)  A[i] = mul(A[i], B[i]);
    NTT::intt(A.p, lim); return A.extend(n);
}

// Poly operator*(Poly A, Poly B) {//任意模数多项式乘法
//     int n = A.deg() + B.deg() + 1;
//     Poly res(n);
//     MTT::conv(A.p, B.p, res.p, MOD);
//     return res.extend(n);
// }

// Poly operator*(Poly A, Poly B) {//答案double类型||如果答案不取模,改成longdouble即可,注意最后的结果需要ll(res[i]+0.5)取整
//     int n = A.deg() + B.deg() + 1;
//     Poly res(n);
//     MTT::conv_db(A.p, B.p, res.p);
//     return res.extend(n);
// }

Poly Dev(Poly A) {//多项式求导
    int n = A.size();
    for (int i = 1;i < n;i++) A[i - 1] = mul(A[i], i);
    return A[n - 1] = 0, A;
}
Poly Int(Poly A) {//多项式求积分
    int n = A.size();
    for (int i = n - 1;i >= 1;i--) A[i] = mul(A[i - 1], _inv[i]);//预处理逆元降低复杂度
    //for (int i = n - 1;i >= 1;i--) A[i] = mul(A[i - 1], qp(i, MOD - 2));//直接求逆元
    return A[0] = 0, A;
}
Poly Inv(Poly A) {//多项式乘法逆元
    int n = A.size();
    if (n == 1)  return A[0] = qp(A[0], MOD - 2), A;
    Poly B = A; B.resize((n + 1) >> 1); B = Inv(B);
    int lim; for (lim = 1; lim < (n << 1); lim <<= 1); NTT::init(lim);
    A.resize(lim); B.resize(lim);
    NTT::ntt(A.p, lim); NTT::ntt(B.p, lim);
    for (int i = 0; i < lim; i++)  A[i] = mul(Dec(2, mul(A[i], B[i])), B[i]);
    NTT::intt(A.p, lim); return A.extend(n);
}
Poly __Inv(Poly A) {//任意模数多项式乘法逆元
    int n = A.size();
    if (n == 1) return A[0] = qp(A[0], MOD - 2), A;
    Poly B = A;B.resize((n + 1) >> 1); B = __Inv(B).extend(n);
    Poly C(1), D(1);
    MTT::conv(A.p, B.p, C.p, MOD);C.resize(n);
    MTT::conv(C.p, B.p, D.p, MOD);D.resize(n);
    for (int i = 0;i < n;i++) B[i] = Dec(Add(B[i], B[i]), D[i]);
    return B.extend(n);
}
Poly operator/(Poly A, Poly B) {
    A.rev(), B.rev();
    int n = A.size(), m = B.size();
    A.resize(n - m + 1), B.resize(n - m + 1);
    B = Inv(B);
    Poly C = A * B;C.resize(n - m + 1);C.rev();
    return C;
}
Poly operator%(Poly A, Poly B) {
    Poly C = A / B;
    return (A - (B * C).extend(A.size())).extend((int)B.size() - 1);
}
//保证[x ^ 0]f(x) = 1
Poly Ln(Poly A) {//多项式对数
    Poly B; int n = A.size(); B.resize(n);
    for (int i = 1; i < n; i++)  B[i - 1] = mul(A[i], i); B[n - 1] = 0;
    B = (B * Inv(A)).extend(n);
    B = Int(B);
    return B;
}
//保证[x ^ 0]f(x) = 0
Poly Exp(Poly A) {//多项式指数
    int n = A.size();
    if (n == 1) return A[0] = 1, A;
    Poly B = A; B.resize((n + 1) >> 1); B = Exp(B).extend(n);
    Poly C = Ln(B);
    for (int i = 0; i < n; i++)  C[i] = Dec(A[i], C[i]); C[0] = Add(C[0], 1);
    return (B * C).extend(n);
}
Poly __Exp(Poly A) {//任意首项多项式指数
    int n = A.size();
    if (n == 1) return A[0] = 1, A;
    Poly B = A;B.resize((n + 1) >> 1); B = __Exp(B).extend(n);
    Poly C = Ln(B);
    Poly D(1), E(1);
    MTT::conv(B.p, C.p, D.p, MOD);D.resize(n);
    MTT::conv(B.p, A.p, E.p, MOD);E.resize(n);
    for (int i = 0;i < n;i++) B[i] = Add(Dec(B[i], D[i]), E[i]);
    return B.extend(n);
}

//保证[x ^ 0]f(x) = 1
Poly Sqrt(Poly A) {//多项式开根
    int n = A.size();
    if (n == 1) return A[0] = 1, A;
    Poly B = A;B.resize((n + 1) >> 1); B = Sqrt(B).extend(n);
    Poly C = Inv(B).extend(n);
    int lim; for (lim = 1; lim < (n << 1); lim <<= 1); NTT::init(lim);
    A.resize(lim); B.resize(lim);C.resize(lim);
    NTT::ntt(A.p, lim);NTT::ntt(B.p, lim);NTT::ntt(C.p, lim);
    for (int i = 0;i < lim;i++) B[i] = mul(mul(Add(mul(B[i], B[i]), A[i]), _inv[2]), C[i]);
    NTT::intt(B.p, lim);
    return B.extend(n);
}
Poly Sqrt_pro(Poly A) {//任意首项多项式开根
    int n = A.size();
    if (n == 1) return A[0] = Cipolla::Cipolla(A[0]), A;
    Poly B = A;B.resize((n + 1) >> 1); B = Sqrt_pro(B).extend(n);
    Poly C = (B * B).extend(n);
    for (int i = 0;i < n;i++) B[i] = mul(2, B[i]);
    for (int i = 0;i < n;i++) C[i] = Add(C[i], A[i]);
    C = C * Inv(B);
    return C.extend(n);
}

//保证[x ^ 0]f(x) = 1
//k很大时,可以计算前对k模p (注意数论中是费马小定理,模p-1)
Poly Qpow(Poly A, int k) {//多项式快速幂
    int n = A.size();Poly B = Ln(A);
    for (int i = 0;i < n;i++) B[i] = mul(B[i], k);
    return Exp(B);
}
//k很大时,可以计算前对k模p和p-1记录在k1和k2(注意数论中是费马小定理,模p-1)
Poly Qpow_pro(Poly a, int k) {//任意首项多项式快速幂
    int k1 = k % MOD, k2 = k % (MOD - 1);
    int n = a.size();
    int shift = 0;
    for (int i = 0;i < n && a[i] == 0;i++) shift++;
    if (1ll * shift * k1 >= n) {
        for (int i = 0;i < n;i++) a[i] = 0;
        return a;
    }
    int inv_first = qp(a[shift], MOD - 2);int t = qp(a[shift], k2);
    for (int i = 0;i < n;i++) {
        if (i + shift < n) a.p[i] = mul(a[i + shift], inv_first);
        else a[i] = 0;
    }
    a = Ln(a);
    for (int i = 0;i < n;i++) a[i] = mul(a[i], k1);
    a = Exp(a);
    shift *= k1;
    for (int i = n - 1;i >= shift;i--) a[i] = mul(a[i - shift], t);
    for (int i = 0;i < shift;i++) a[i] = 0;
    return a;
}

//i^2=-1(mod p),对-1用二次剩余算出i
//i = 86583718 (mod 998244353)
//保证[x ^ 0]f(x) = 0
const int I = 86583718;
Poly Sin(Poly A) {//多项式sin
    int n = A.size();
    int inv_2i = qp(mul(2, I), MOD - 2);
    for (int i = 0;i < n;i++) A[i] = mul(A[i], I);
    Poly B = Exp(A), C = Inv(B);
    for (int i = 0;i < n;i++) B[i] = mul(Dec(B[i], C[i]), inv_2i);
    return B;
}
//保证[x ^ 0]f(x) = 0
Poly Cos(Poly A) {//多项式cos
    int n = A.size();
    for (int i = 0;i < n;i++) A[i] = mul(A[i], I);
    Poly B = Exp(A), C = Inv(B);
    for (int i = 0;i < n;i++) B[i] = mul(Add(B[i], C[i]), _inv[2]);
    return B;
}
//保证[x ^ 0]f(x) = 0
Poly Arcsin(Poly A) {
    int n = A.size();
    Poly B = Dev(A);
    A = (A * A).extend(n);
    for (int i = 0;i < n;i++) A[i] = Dec(0, A[i]);A[0] = Add(1, A[0]);
    A = Sqrt(A);
    B = (B * Inv(A)).extend(n);
    B = Int(B);
    return B;
}
//保证[x ^ 0]f(x) = 0
Poly Arccos(Poly A) {
    int n = A.size();
    Poly B = Dev(A);for (int i = 0;i < n;i++) B[i] = Dec(0, B[i]);
    A = (A * A).extend(n);
    for (int i = 0;i < n;i++) A[i] = Dec(0, A[i]);A[0] = Add(1, A[0]);
    A = Sqrt(A);
    B = (B * Inv(A)).extend(n);
    B = Int(B);
    return B;
}
//保证[x ^ 0]f(x) = 0
Poly Arctan(Poly A) {
    int n = A.size();
    Poly B = Dev(A);
    A = (A * A).extend(n);
    A[0] = Add(1, A[0]);
    B = (B * Inv(A)).extend(n);
    B = Int(B);
    return B;
}

Poly Stiring_2_row(int n) {//SC(n,i)
    Poly A(n + 1);for (int i = 0, infact_i = 1;i <= n;i++, infact_i = mul(infact_i, _inv[i])) A[i] = mul(((i & 1) ? MOD - 1 : 1), infact_i);
    Poly B(n + 1);for (int i = 0, infact_i = 1;i <= n;i++, infact_i = mul(infact_i, _inv[i])) B[i] = mul(qp(i, n), infact_i);
    A = A * B;
    return A;
}

Poly Stiring_1_col(int n, int m) {//SA(i,m)
    int infact_m = 1;for (int i = 1;i <= m;i++) infact_m = mul(infact_m, _inv[i]);
    Poly A(n + 1);for (int i = 0;i <= n;i++) A[i] = qp(i, MOD - 2);
    A = Qpow_pro(A, m);
    for (int i = 0, fact_i = 1;i <= n;i++, fact_i = mul(fact_i, i)) A[i] = mul(mul(A[i], infact_m), fact_i);
    return A;
}

//记得Poly_init, 如果仅是乘法则不需要
//Poly读入和初始化时,记得取模. f[i] = -1  ==> f[i] = MOD-1 
//MTT的rev开lim大小,为方便一般3~4倍即可
//做多项式逆元等操作之前记得是否需要resize到所需范围
