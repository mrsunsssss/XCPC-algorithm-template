vector<int> tr(4 * n + 10), tag(4 * n + 10);
    auto apply = [&](int u, int l, int r, int v) {
        tr[u] += (r - l + 1) * v;
        tag[u] += v;
        };

    auto down = [&](int u, int l, int r) {
        if (tag[u]) {
            int mid = (l + r) / 2;
            apply(u * 2, l, mid, tag[u]);
            apply(u * 2 + 1, mid + 1, r, tag[u]);
            tag[u] = 0;
        }
        };

    auto _upd = [&](auto&& _upd, int u, int l, int r, int ql, int qr, int v) -> void {
        if (l > qr or r < ql) return;
        if (ql <= l and r <= qr) {
            apply(u, l, r, v);
            return;
        }
        down(u, l, r);

        int mid = (l + r) / 2;
        _upd(_upd, u * 2, l, mid, ql, qr, v);
        _upd(_upd, u * 2 + 1, mid + 1, r, ql, qr, v);

        tr[u] = tr[u * 2] + tr[u * 2 + 1];
        };

    auto _ask = [&](auto&& _ask, int u, int l, int r, int ql, int qr) -> int {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return tr[u];
        down(u, l, r);
        int mid = (l + r) / 2;
        return _ask(_ask, u * 2, l, mid, ql, qr) + _ask(_ask, u * 2 + 1, mid + 1, r, ql, qr);
        };
    auto upd = [&](int ql, int qr, int v) {return _upd(_upd, 1, 1, n, ql, qr, v);};
    auto ask = [&](int ql, int qr) {return _ask(_ask, 1, 1, n, ql, qr);};
