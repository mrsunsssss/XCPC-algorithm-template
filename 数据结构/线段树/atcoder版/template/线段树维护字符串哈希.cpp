using ull = unsigned long long;
const int N = 3e5 + 10;
const ull MOD = (1ULL << 61) - 1;
int power[N], sum_power[N];
mt19937_64 gen(random_device{}());//cf换成时间戳，否则概率被hack
uniform_int_distribution<ull> dis(MOD / 2, MOD - 1);
const ull base = dis(gen);
ull add(ull a, ull b) {
    a += b;if (a >= MOD) a -= MOD;return a;
}
ull mul(ull a, ull b) {
    __int128_t c = __int128_t(a) * b;
    return add(c >> 61, c & MOD);
}

struct S {
    ull h, hr;
    int len;
};
S op(S l, S r) {
    return S{
        add(mul(l.h,power[r.len]),r.h),
        add(mul(r.hr,power[l.len]),l.hr),
        l.len + r.len
    };
}
S e() {
    return S{ 0,0,1 };
}
struct F {
    ull ch;
};
S mapping(F f, S x) {//x->f(x)
    if (f.ch != ULLONG_MAX) {
        return S{
            mul(f.ch, sum_power[x.len - 1]),
            mul(f.ch, sum_power[x.len - 1]),
            x.len
        };
    }
    return S{ x.h,x.hr,x.len };
}
F composition(F f, F g) { // f(g(x))
    if (f.ch == ULLONG_MAX) return F{ g.ch };
    return F{ f.ch };
}
F id() {//e of F
    return F{ ULLONG_MAX };
}
using segtree = lazy_segtree<S, op, e, F, mapping, composition, id>;


void Prework(int n = N - 10) {
    power[0] = sum_power[0] = 1;
    for (int i = 1;i <= n;i++) {
        power[i] = mul(power[i - 1], base);
        sum_power[i] = add(sum_power[i - 1], power[i]);
    }
}
