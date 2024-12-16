//op：区间赋值
//ask：区间和
//extra：线段树二分第一个大于/小于某值的位置
struct S {
    int sum, Max, Min, len;
};
S op(S l, S r) {
    return S{ l.sum + r.sum,max(l.Max,r.Max),min(l.Min,r.Min),l.len + r.len };
}
S e() {
    return S{ 0,-inf,inf,1 };
}
struct F {
    int add;
};
S mapping(F f, S x) {//x->f(x)
    if (f.add == inf) return S{ x.sum,x.Max,x.Min,x.len };
    else {
        return S{ f.add * x.len,f.add,f.add, x.len };
    }
}
F composition(F f, F g) { // f(g(x))
    if (f.add == inf) return F{ g.add };
    return F{ f.add };
}
F id() {//e of F
    return F{ inf };
}
//查询l开始向右第一个大于x的位置
auto g = [&](S u) {
    return u.Max <= x;
    };
auto r = seg.max_right(l, g) - 1;
//查询r开始向左最后一个大于等于x的位置
auto g = [&](S u) {
    return u.Min >= x;
    };
auto l = max(1LL, seg.min_left(r, g));
