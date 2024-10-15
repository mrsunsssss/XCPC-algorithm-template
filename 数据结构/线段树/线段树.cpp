template <class S,
    S(*op)(S, S),//op must work as S(S,S)
    S(*e)(),//e must work as S()
    class F,
    S(*mapping)(F, S),//mapping must work as F(F, S)
    F(*composition)(F, F),//compostiion must work as F(F, F)
    F(*id)()>//id must work as F()
struct lazy_segtree {
    int ceil_pow2(int n) {
        int x = 0;
        while ((1U << x) < (unsigned int)(n)) x++;
        return x;
    }
public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n((int)(v.size())) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }
 
    void set(int p, S x) {//a[p]=x
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
 
    S get(int p) {//return a[p]
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }
 
    S prod(int l, int r) {
        r++;
        if (l == r) return e();
 
        l += size;
        r += size;
 
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
 
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
 
        return op(sml, smr);
    }
 
    S all_prod() { return d[1]; }//op(a[0],...,a[n-1])
 
    void apply(int p, F f) {
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        r++;
        if (l == r) return;
 
        l += size;
        r += size;
 
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
 
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
 
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }
 
    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {//固定l,第一个不满足g(op(l,l+1,..,r))=1的r
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }
 
    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {//固定r,最后一个l满足g(op(l,l+1,..,r))=1
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
 
private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;
 
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};
//to use it: lazy_segtree<S,op,e,F,mapping,composition,id> tr(vector<S>/int);

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

using segtree = lazy_segtree<S, op, e, F, mapping, composition, id>;


