const int N = 1e5 + 10;

//BIT套PST
struct PST {
#define ls(x) (tr[x].son[0])
#define rs(x) (tr[x].son[1])
    struct node {
        int son[2] = { 0,0 };
        int sum_cnt = 0;
        int sum_val = 0;
    };
    inline int lbt(int x) { return x & -x; }
    node tr[N * 256];//n+Qlogn
    vector<int> v;//去离散化的原数组
    inline static int root[N * 2];//第i个版本的根节点编号
    inline static int t1[N], t2[N];int n1 = 0, n2 = 0;
    int n, tot, idx;//数组范围,值域,当前节点数
    PST(int n, int tot) :idx(0), n(n), tot(tot) {
        v.resize(tot + 1);
        build(root[0], 1, tot);
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
        tr[x].sum_cnt = tr[ls(x)].sum_cnt + tr[rs(x)].sum_cnt;
        tr[x].sum_val = tr[ls(x)].sum_val + tr[rs(x)].sum_val;
    }
    //在x版本的基础上给离散化后第k个数字的数量加cnt
    void insert(int& now, int pre, int l, int r, int k, int cnt) {
        if (!now) now = copy(pre);//这里只涉及修改自身，所以可以!now节省内存
        if (l == r) {
            tr[now].sum_cnt += cnt;
            tr[now].sum_val += v[k] * cnt;
            return;
        }
        int mid = l + r >> 1;
        if (k <= mid) insert(ls(now), ls(pre), l, mid, k, cnt);
        else insert(rs(now), rs(pre), mid + 1, r, k, cnt);
        pushup(now);
    }

    int kth_min(int l, int r, int k) {//第k小值
        if (l == r) return v[l];
        int mid = l + r >> 1;
        int s = 0;
        for (int i = 1;i <= n1;i++) s += tr[ls(t1[i])].sum_cnt;
        for (int i = 1;i <= n2;i++) s -= tr[ls(t2[i])].sum_cnt;
        if (k <= s) {
            for (int i = 1;i <= n1;i++) t1[i] = ls(t1[i]);
            for (int i = 1;i <= n2;i++) t2[i] = ls(t2[i]);
            return kth_min(l, mid, k);
        }
        else {
            for (int i = 1;i <= n1;i++) t1[i] = rs(t1[i]);
            for (int i = 1;i <= n2;i++) t2[i] = rs(t2[i]);
            return kth_min(mid + 1, r, k - s);
        }
    }

    int kth_min_sum(int l, int r, int k) {//第k小值之和
        if (l == r) return k * v[l];
        int mid = l + r >> 1;
        int s = 0;
        for (int i = 1;i <= n1;i++) s += tr[ls(t1[i])].sum_cnt;
        for (int i = 1;i <= n2;i++) s -= tr[ls(t2[i])].sum_cnt;
        if (k <= s) {
            for (int i = 1;i <= n1;i++) t1[i] = ls(t1[i]);
            for (int i = 1;i <= n2;i++) t2[i] = ls(t2[i]);
            return kth_min_sum(l, mid, k);
        }
        else {
            int ss = 0;
            for (int i = 1;i <= n1;i++) ss += tr[ls(t1[i])].sum_val;
            for (int i = 1;i <= n2;i++) ss -= tr[ls(t2[i])].sum_val;

            for (int i = 1;i <= n1;i++) t1[i] = rs(t1[i]);
            for (int i = 1;i <= n2;i++) t2[i] = rs(t2[i]);
            return kth_min_sum(mid + 1, r, k - s) + ss;
        }
    }

    int less_equall_x_cnt(int l, int r, int x) {//小于等于k的数量（可以用来查排名）
        int ans = 0;
        if (l == r) {
            for (int i = 1;i <= n1;i++) ans += tr[t1[i]].sum_cnt;
            for (int i = 1;i <= n2;i++) ans -= tr[t2[i]].sum_cnt;
            return ans;
        }
        int mid = l + r >> 1;
        if (x <= mid) {
            for (int i = 1;i <= n1;i++) t1[i] = ls(t1[i]);
            for (int i = 1;i <= n2;i++) t2[i] = ls(t2[i]);
            ans += less_equall_x_cnt(l, mid, x);
        }
        else {
            for (int i = 1;i <= n1;i++) ans += tr[ls(t1[i])].sum_cnt;
            for (int i = 1;i <= n2;i++) ans -= tr[ls(t2[i])].sum_cnt;

            for (int i = 1;i <= n1;i++) t1[i] = rs(t1[i]);
            for (int i = 1;i <= n2;i++) t2[i] = rs(t2[i]);
            ans += less_equall_x_cnt(mid + 1, r, x);
        }
        return ans;
    }


    int less_equall_x_sum(int l, int r, int x) {//小于等于k的和
        int ans = 0;
        if (l == r) {
            for (int i = 1;i <= n1;i++) ans += tr[t1[i]].sum_val;
            for (int i = 1;i <= n2;i++) ans -= tr[t2[i]].sum_val;
            return ans;
        }
        int mid = l + r >> 1;
        if (x <= mid) {
            for (int i = 1;i <= n1;i++) t1[i] = ls(t1[i]);
            for (int i = 1;i <= n2;i++) t2[i] = ls(t2[i]);
            ans += less_equall_x_sum(l, mid, x);
        }
        else {
            for (int i = 1;i <= n1;i++) ans += tr[ls(t1[i])].sum_val;
            for (int i = 1;i <= n2;i++) ans -= tr[ls(t2[i])].sum_val;

            for (int i = 1;i <= n1;i++) t1[i] = rs(t1[i]);
            for (int i = 1;i <= n2;i++) t2[i] = rs(t2[i]);
            ans += less_equall_x_sum(mid + 1, r, x);
        }
        return ans;
    }

    void BIT_modify(int i, int k, int cnt) {
        for (;i <= n;i += lbt(i)) insert(root[i], root[i], 1, tot, k, cnt);//处理需要修改的log棵主席树
    }

    int BIT_Query_kthmin(int l, int r, int ql, int qr, int k) {
        n1 = 0, n2 = 0;
        for (int i = qr;i;i -= lbt(i)) t1[++n1] = root[i];
        for (int i = ql - 1;i;i -= lbt(i)) t2[++n2] = root[i];
        return kth_min(l, r, k);
    }

    int BIT_Query_le_cnt(int l, int r, int ql, int qr, int k) {
        n1 = 0, n2 = 0;
        for (int i = qr;i;i -= lbt(i)) t1[++n1] = root[i];
        for (int i = ql - 1;i;i -= lbt(i)) t2[++n2] = root[i];
        return less_equall_x_cnt(l, r, k);
    }
    int query(int x, int l, int r, int ql, int qr) {//版本x的值域为[ql,qr]的数字数量
        if (l == ql && r == qr) return  tr[x].sum_cnt;
        int mid = l + r >> 1;
        if (qr <= mid) return query(ls(x), l, mid, ql, qr);
        else if (mid < ql) return query(rs(x), mid + 1, r, ql, qr);
        else return query(ls(x), l, mid, ql, mid) + query(rs(x), mid + 1, r, mid + 1, qr);
    }
    int BIT_query(int l, int r, int ql, int qr) {//版本[ql,qr]的值域为[l,r]的数字数量
        if (ql > qr or l > r) return 0;
        n1 = n2 = 0;
        for (int i = qr; i; i -= lbt(i)) t1[++n1] = root[i];
        for (int i = ql - 1; i; i -= lbt(i)) t2[++n2] = root[i];
        int s1 = 0;
        for (int i = 1; i <= n1; i++) {
            s1 += query(t1[i], 1, tot, l, r);
        }

        int s2 = 0;
        for (int i = 1; i <= n2; i++) {
            s2 += query(t2[i], 1, tot, l, r);
        }
        return s1 - s2;
    }
};
