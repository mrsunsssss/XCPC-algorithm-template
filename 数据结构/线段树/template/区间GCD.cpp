//op：区间赋值
//ask：区间GCD
struct S {
    int GCD;
};
S op(S l, S r) {
    return S{ gcd(l.GCD , r.GCD) };
}
S e() {
    return S{ 0 };
}
struct F {
    ll add;
};
S mapping(F f, S x) {//x->f(x)
    if (f.add == LLONG_MAX) return S{ x.GCD };
    else {
        return S{ f.add };
    }
}
F composition(F f, F g) { // f(g(x))
    if (f.add == LLONG_MAX) return F{ g.add };
    return F{ f.add };
}
F id() {//e of F
    return F{ LLONG_MAX };
}
