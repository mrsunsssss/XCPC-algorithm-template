//op：区间赋值
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
    int add;
};
S mapping(F f, S x) {//x->f(x)
    if (f.add == inf) return S{ x.sum,x.len };
    else {
        return S{ f.add * x.len,x.len };
    }
}
F composition(F f, F g) { // f(g(x))
    if (f.add == inf) return F{ g.add };
    return F{ f.add };
}
F id() {//e of F
    return F{ inf };
}
