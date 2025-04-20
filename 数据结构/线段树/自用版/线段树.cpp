const int MOD = 998244353;

template<class Info, class Tag>
struct Segtree {
    int n;
    vector<Info> info;
    vector<Tag> tag;
    Segtree() : n(0) {}
    Segtree(int n, Info a = Info()) { init(n, a); }
    template<class T> Segtree(vector<T> a) { init(a); }
    void init(int n, Info v = Info()) { init(vector(n, v)); }
    template<class T> void init(vector<T> a) {
        n = a.size() - 1;
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        auto build = [&](auto&& build, int p, int l, int r) {
            if (l == r) {
                info[p] = a[l];
                return;
            }
            int m = l + r >> 1;
            build(build, 2 * p, l, m);
            build(build, 2 * p + 1, m + 1, r);
            up(p);
            };
        build(build, 1, 1, n);
    }

    void up(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void tagging(int p, const Tag& v, int l, int r) {
        info[p].tagging(v, r - l + 1);
        tag[p].tagging(v);
    }

    void down(int p, int l, int r) {
        int m = l + r >> 1;
        tagging(2 * p, tag[p], l, m);
        tagging(2 * p + 1, tag[p], m + 1, r);
        tag[p] = Tag();
    }

    Info prod(int p, int l, int r, int ql, int qr) {
        if (l > qr or r < ql) {
            return Info();
        }
        if (ql <= l and r <= qr) {
            return info[p];
        }
        int m = l + r >> 1;
        down(p, l, r);
        return prod(2 * p, l, m, ql, qr) + prod(2 * p + 1, m + 1, r, ql, qr);
    }

    Info prod(int l, int r) {
        return prod(1, 1, n, l, r);
    }

    void apply(int p, int l, int r, int ql, int qr, const Tag& v) {
        if (l > qr or r < ql) {
            return;
        }
        if (ql <= l and r <= qr) {
            tagging(p, v, l, r);
            return;
        }
        int m = l + r >> 1;
        down(p, l, r);
        apply(2 * p, l, m, ql, qr, v);
        apply(2 * p + 1, m + 1, r, ql, qr, v);
        up(p);
    }

    void apply(int l, int r, const Tag& v) {
        return apply(1, 1, n, l, r, v);
    }

    template<class F>
    int findFirst(int p, int l, int r, int ql, int qr, F&& pred) {
        if (l > qr or r < ql) {
            return -1;
        }
        if (ql <= l and r <= qr and !pred(info[p])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        down(p, l, r);
        int res = findFirst(2 * p, l, m, ql, qr, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m + 1, r, ql, qr, pred);
        }
        return res;
    }

    template<class F> int findFirst(int l, int r, F&& pred) {
        return findFirst(1, 1, n, l, r, pred);
    }

    template<class F> int findLast(int p, int l, int r, int ql, int qr, F&& pred) {
        if (l > qr or r < ql) {
            return -1;
        }
        if (ql <= l && r <= qr && !pred(info[p])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        down(p, l, r);
        int res = findLast(2 * p + 1, m + 1, r, ql, qr, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, ql, qr, pred);
        }
        return res;
    }

    template<class F> int findLast(int l, int r, F&& pred) {
        return findLast(1, 1, n, l, r, pred);
    }
};

struct Tag {
    int add = 0, mul = 1;
    Tag(int add = 0, int mul = 1) : add(add), mul(mul) {};
    void tagging(Tag o) {
        add = (add * o.mul + o.add) % MOD;
        mul = (mul * o.mul) % MOD;
    }
};
struct Info {
    int sum = 0;
    Info(int sum = 0) : sum(sum) {}
    void tagging(Tag t, int len) {
        sum = (sum * t.mul + len * t.add) % MOD;
    }
};
Info operator+(Info a, Info b) {
    return { a.sum + b.sum };
}

