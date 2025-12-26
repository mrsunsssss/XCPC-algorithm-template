vector<int> tr(4 * n + 10), tag(4 * n + 10);
    auto apply = [&](int u, int len, int v) {
        tr[u] += len * v;
        tag[u] += v;
        };

    auto down = [&](int u, int l, int r) {
        if (tag[u]) {
            int mid = (l + r) / 2;
            apply(u * 2, mid - l + 1, tag[u]);
            apply(u * 2 + 1, r - mid, tag[u]);
            tag[u] = 0;
        }
        };

    auto upd = [&](auto&& upd, int u, int l, int r, int ql, int qr, int v) -> void {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            apply(u, r - l + 1, v);
            return;
        }
        down(u, l, r);

        int mid = (l + r) / 2;
        upd(upd, u * 2, l, mid, ql, qr, v);
        upd(upd, u * 2 + 1, mid + 1, r, ql, qr, v);

        tr[u] = tr[u * 2] + tr[u * 2 + 1];
        };

    auto ask = [&](auto&& ask, int u, int l, int r, int ql = 1, int qr) -> int {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return tr[u];
        down(u, l, r);
        int mid = (l + r) / 2;
        return ask(ask, u * 2, l, mid, ql, qr) + ask(ask, u * 2 + 1, mid + 1, r, ql, qr);
        };
