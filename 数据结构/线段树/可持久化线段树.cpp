const int N = 2e5 + 10;

struct PST {
#define ls(x) (tr[x].son[0])
#define rs(x) (tr[x].son[1])
    struct node {
        int son[2] = { 0,0 };
        ll sum_val = 0;
        int sum_cnt = 0;
    };
    static node tr[N << 5];
    vector<int> v;
    inline static int root[N];
    int n, idx;
    PST(int n) :n(n), idx(0) {//值域大小
        v.resize(n + 1);
        build(root[0], 1, n);
    }
    ~PST() {
        for (int i = 1;i <= idx;i++) tr[i].sum_cnt = tr[i].sum_val = 0;
        idx = 0;
    }
    void init(const vector<int>& arr) {
        int m = (int)arr.size() - 1;
        v = arr;
        sort(v.begin() + 1, v.end());
        v.erase(unique(v.begin() + 1, v.end()), v.end());
        n = v.size() - 1;
        build(root[0], 1, n);
        for (int i = 1;i <= m;i++) {
            auto rk = lower_bound(v.begin() + 1, v.end(), arr[i]) - v.begin();
            insert(i, i - 1, rk);
        }
    }
    void build(int& x, int l, int r) {
        x = ++idx;
        if (l == r) return;
        int mid = l + r >> 1;
        build(ls(x), l, mid);
        build(rs(x), mid + 1, r);
    }
    int copy(int x) {
        tr[++idx] = tr[x];
        return idx;
    }
    void pushup(int x) {
        tr[x].sum_val = tr[ls(x)].sum_val + tr[rs(x)].sum_val;
        tr[x].sum_cnt = tr[ls(x)].sum_cnt + tr[rs(x)].sum_cnt;
    }
    //在x版本的基础上给离散化后第k个数字的数量加1
    void insert(int now, int pre, int k) {
        auto run = [&](auto&& run, int& now, int pre, int l, int r, int k) {
            now = copy(pre);
            if (l == r) {
                tr[now].sum_cnt += 1;
                tr[now].sum_val += v[k];
                return;
            }
            int mid = l + r >> 1;
            if (k <= mid) run(run, ls(now), ls(pre), l, mid, k);
            else run(run, rs(now), rs(pre), mid + 1, r, k);
            pushup(now);
            };
        run(run, root[now], root[pre], 1, n, k);
    }
    //数组前缀1~x中值域[ql,qr]的数的数量
    int query(int x, int ql, int qr) {
        if (ql > qr) return 0;
        auto run = [&](auto&& run, int x, int l, int r, int ql, int qr) {
            if (l == ql && r == qr) return tr[x].sum_cnt;
            int mid = l + r >> 1;
            if (qr <= mid) return run(run, ls(x), l, mid, ql, qr);
            else if (mid < ql) return run(run, rs(x), mid + 1, r, ql, qr);
            else return run(run, ls(x), l, mid, ql, mid) + run(run, rs(x), mid + 1, r, mid + 1, qr);
            };
        return run(run, root[x], 1, n, ql, qr);
    }
    //数组vl~vr中值域[ql,qr]的数的数量
    int query_range(int vl, int vr, int ql, int qr) {
        if (ql > qr) return 0;
        auto run = [&](auto&& run, int vl, int vr, int l, int r, int ql, int qr) {
            if (l == ql && r == qr) return tr[vr].sum_cnt - tr[vl].sum_cnt;
            int mid = l + r >> 1;
            if (qr <= mid) return run(run, ls(vl), ls(vr), l, mid, ql, qr);
            else if (mid < ql) return run(run, rs(vl), rs(vr), mid + 1, r, ql, qr);
            else return run(run, ls(vl), ls(vr), l, mid, ql, mid) + run(run, rs(vl), rs(vr), mid + 1, r, mid + 1, qr);
            };
        return run(run, root[vl - 1], root[vr], 1, n, ql, qr);
    }

    //数组前缀1~x中值域[ql,qr]的数的和
    int query_sum(int x, int ql, int qr) {
        if (ql > qr) return 0;
        auto run = [&](auto&& run, int x, int l, int r, int ql, int qr) {
            if (l == ql && r == qr) return tr[x].sum_val;
            int mid = l + r >> 1;
            if (qr <= mid) return run(run, ls(x), l, mid, ql, qr);
            else if (mid < ql) return run(run, rs(x), mid + 1, r, ql, qr);
            else return run(run, ls(x), l, mid, ql, mid) + run(run, rs(x), mid + 1, r, mid + 1, qr);
            };
        return run(run, root[x], 1, n, ql, qr);
    }
    //数组vl~vr中值域[ql,qr]的数的和
    int query_range_sum(int vl, int vr, int ql, int qr) {
        if (ql > qr) return 0;
        auto run = [&](auto&& run, int vl, int vr, int l, int r, int ql, int qr) {
            if (l == ql && r == qr) return tr[vr].sum_val - tr[vl].sum_val;
            int mid = l + r >> 1;
            if (qr <= mid) return run(run, ls(vl), ls(vr), l, mid, ql, qr);
            else if (mid < ql) return run(run, rs(vl), rs(vr), mid + 1, r, ql, qr);
            else return run(run, ls(vl), ls(vr), l, mid, ql, mid) + run(run, rs(vl), rs(vr), mid + 1, r, mid + 1, qr);
            };
        return run(run, root[vl - 1], root[vr], 1, n, ql, qr);
    }

    //数组vl~vr内的第k小值
    int kth_min(int vl, int vr, int k) {
        if (vl > vr) return 0;
        auto run = [&](auto&& run, int l, int r, int ql, int qr, int k) {
            if (l == r) return v[l];
            int mid = l + r >> 1;
            int s = tr[ls(qr)].sum_cnt - tr[ls(ql)].sum_cnt;
            if (k <= s) return run(run, l, mid, ls(ql), ls(qr), k);
            else return run(run, mid + 1, r, rs(ql), rs(qr), k - s);
            };
        return run(run, 1, n, root[vl - 1], root[vr], k);
    }
    //数组vl~vr内的第k大值
    int kth_max(int vl, int vr, int k) {
        if (vl > vr) return 0;
        auto run = [&](auto&& run, int l, int r, int ql, int qr, int k) {
            if (l == r) return v[l];
            int mid = l + r >> 1;
            int s = tr[rs(qr)].sum_cnt - tr[rs(ql)].sum_cnt;
            if (k <= s) return run(run, mid + 1, r, rs(ql), rs(qr), k);
            else return run(run, l, mid, ls(ql), ls(qr), k - s);
            };
        return run(run, 1, n, root[vl - 1], root[vr], k);
    }
    //数组vl~vr之间前k小数之和
    ll kth_min_sum(int vl, int vr, int k) {
        if (vl > vr) return 0;
        auto run = [&](auto&& run, int l, int r, int ql, int qr, int k) {
            if (l == r) return 1LL * k * v[l];
            int mid = l + r >> 1;
            int s = tr[ls(qr)].sum_cnt - tr[ls(ql)].sum_cnt;
            if (k <= s) return run(run, l, mid, ls(ql), ls(qr), k);
            else return run(run, mid + 1, r, rs(ql), rs(qr), k - s) + (tr[ls(qr)].sum_val - tr[ls(ql)].sum_val);
            };
        return run(run, 1, n, root[vl - 1], root[vr], k);
    }
    //数组vl~vr之间前k大数之和
    ll kth_max_sum(int vl, int vr, int k) {
        if (vl > vr) return 0;
        auto run = [&](auto&& run, int l, int r, int ql, int qr, int k) {
            if (l == r) return 1LL * k * v[l];
            int mid = l + r >> 1;
            int s = tr[rs(qr)].sum_cnt - tr[rs(ql)].sum_cnt;
            if (k <= s) return run(run, mid + 1, r, rs(ql), rs(qr), k);
            else return run(run, l, mid, ls(ql), ls(qr), k - s) + (tr[rs(qr)].sum_val - tr[rs(ql)].sum_val);
            };
        return run(run, 1, n, root[vl - 1], root[vr], k);
    }

};
PST::node PST::tr[N << 5];
