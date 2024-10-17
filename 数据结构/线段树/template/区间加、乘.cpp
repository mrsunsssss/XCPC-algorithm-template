//op：区间乘，区间加。
//ask：区间和
struct S {
    int sum, len;
};
S op(S l, S r) {
    return S{ l.sum + r.sum,l.len + r.len };
}
S e() {
    return S{ 0,1 };
}
struct F {
    int mul, add;
};
S mapping(F f, S x) {//x->f(x)
    return S{ f.mul * x.sum + f.add * x.len,x.len };
}
F composition(F f, F g) { // f(g(x))
    return F{ f.mul * g.mul,f.mul * g.add + f.add };
}
F id() {//e of F
    return F{ 1,0 };
}
