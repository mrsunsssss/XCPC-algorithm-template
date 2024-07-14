struct Segtree {
#define ls (x << 1)
#define rs (x << 1 | 1)
    struct Info {
        int sz;
        ll sum;//区间和
        ll premax, sufmax, mx;//前缀最大，后缀最大，区间最大
        ll premin, sufmin, mn;//前缀最小，后缀最小，区间最小
        ll bg_res, ed_res;//前缀答案，后缀答案
        ll all_res;//区间整体答案
        ll res;//答案
    };
    struct node {
        Info info;
    };
    Info friend operator +(const Info& l, const Info& r) {
        return { l.sz + r.sz,l.sum + r.sum,
        max(l.sum + r.premax,l.premax),max(l.sufmax + r.sum,r.sufmax),max({l.mx,r.mx,l.sufmax + r.premax}),
        min(l.sum + r.premin,l.premin),min(l.sufmin + r.sum,r.sufmin),min({l.mn,r.mn,l.sufmin + r.premin}),
        max({l.bg_res,l.all_res - r.premin,l.sum - r.premin,l.sum + r.bg_res }), max({r.ed_res,l.sufmax + r.all_res,l.sufmax - r.sum,l.ed_res - r.sum}),
        max({l.sum - r.sum,l.all_res - r.sum,l.sum + r.all_res}),
        max({l.sufmax - r.premin,l.res,r.res,l.ed_res - r.premin,l.sufmax + r.bg_res})
        };
    }
    Info friend operator +(const Info& info, const int x) {
        return { info.sz,x,x,x,x,x,x,x,-inf,-inf,-inf,-inf };
    }
    int n;
    vector<node> tr;
    Segtree(const vector<int>& a, int n) :n(n) {
        tr.resize(n << 2);
        build(a, 1, 1, n);
    }
    void build(const vector<int>& a, int x, int l, int r) {
        tr[x].info.sz = r - l + 1;
        if (l == r) {
            tr[x].info = { 1,a[l],a[l],a[l],a[l],a[l],a[l],a[l],-inf,-inf,-inf,-inf };
            return;
        }
        else {
            int mid = l + r >> 1;
            build(a, ls, l, mid);
            build(a, rs, mid + 1, r);
            pushup(x);
        }
    }
    void pushup(int x) {//从下往上更新
        tr[x].info = tr[ls].info + tr[rs].info;
    }
    void settag(int x, int tag) {
        tr[x].info = tr[x].info + tag;
    }
    //l,r代表操作区间
    void update(int x, int l, int r, int q, int tag) {
        if (l == r) {
            settag(x, tag);
            return;
        }
        int mid = l + r >> 1;
        if (q <= mid) update(ls, l, mid, q, tag);
        else  update(rs, mid + 1, r, q, tag);
        pushup(x);
    }
    Info query(int x, int l, int r, int ql, int qr) {
        if (l == ql && r == qr) return tr[x].info;
        int mid = l + r >> 1;
        if (qr <= mid) return query(ls, l, mid, ql, qr);
        else if (mid < ql) return query(rs, mid + 1, r, ql, qr);
        else return query(ls, l, mid, ql, mid) + query(rs, mid + 1, r, mid + 1, qr);
    }
 
};
 
void Solve(int TIME) {
 
    int n, q;cin >> n >> q;
    vi a(n + 1);for (int i = 1;i <= n;i++) cin >> a[i];
    Segtree tr(a, n);
    while (q--) {
        int op;cin >> op;
        if (op == 1) {
            int x, y;cin >> x >> y;
            tr.update(1, 1, n, x, y);
        }
        else {
            int l, r;cin >> l >> r;
            cout << tr.query(1, 1, n, l, r).res << endl;
        }
    }
 
 
}
