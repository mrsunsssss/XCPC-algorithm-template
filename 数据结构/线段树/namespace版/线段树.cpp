namespace sgt {
    int n;
    vector<int> tr;
    vector<int> tag;
    void init(int _n) {
        n = _n;
        tr.assign(4 * n + 10, 0);
        tag.assign(4 * n + 10, 0);
    }

    void apply(int u, int l, int r, int v) {
        tr[u] += (r - l + 1) * v;
        tag[u] += v;
    }

    int Combine(int u, int v) {
        return u + v;
    }

    void Down(int u, int l, int r) {
        if (tag[u]) {
            int mid = (l + r) / 2;
            apply(u * 2, l, mid, tag[u]);
            apply(u * 2 + 1, mid + 1, r, tag[u]);
            tag[u] = 0;
        }
    }

    void _upd(int u, int l, int r, int ql, int qr, int v) {
        if (l > qr or r < ql) return;
        if (ql <= l and r <= qr) {
            apply(u, l, r, v);
            return;
        }
        Down(u, l, r);

        int mid = (l + r) / 2;
        _upd(u * 2, l, mid, ql, qr, v);
        _upd(u * 2 + 1, mid + 1, r, ql, qr, v);

        tr[u] = Combine(tr[u * 2], tr[u * 2 + 1]);
    }

    int _ask(int u, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;//注意设置幺元
        if (l >= ql && r <= qr) return tr[u];
        Down(u, l, r);
        int mid = (l + r) / 2;
        return Combine(_ask(u * 2, l, mid, ql, qr), _ask(u * 2 + 1, mid + 1, r, ql, qr));
    }

    void _set(int u, int l, int r, int pos, int v) {
        if (l > pos or r < pos) return;
        if (l == r) {
            tr[u] = v;
            tag[u] = 0;
            return;
        }
        Down(u, l, r);

        int mid = (l + r) / 2;
        _set(u * 2, l, mid, pos, v);
        _set(u * 2 + 1, mid + 1, r, pos, v);

        tr[u] = Combine(tr[u * 2], tr[u * 2 + 1]);
    }
    void set(int pos, int v) { return _set(1, 1, n, pos, v); }
    void upd(int ql, int qr, int v) { return _upd(1, 1, n, ql, qr, v); };
    void upd(int pos, int v) { return _upd(1, 1, n, pos, pos, v); };
    int ask(int ql, int qr) { return _ask(1, 1, n, ql, qr); };
}
