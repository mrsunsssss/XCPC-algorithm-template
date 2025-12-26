    vector<int> tr(4 * n + 10), tag(4 * n + 10);
    auto apply = [&](int p, int len, int v) {
        tr[p] += len * v;
        tag[p] += v;
        };

    auto down = [&](int p, int l, int r) {
        if (tag[p]) {
            int mid = (l + r) / 2;
            apply(p * 2, mid - l + 1, tag[p]);
            apply(p * 2 + 1, r - mid, tag[p]);
            tag[p] = 0;
        }
        };

    auto upd = [&](auto&& upd, int p, int l, int r, int ql, int qr, int v) -> void {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            apply(p, r - l + 1, v);
            return;
        }
        down(p, l, r);
        int mid = (l + r) / 2;
        upd(upd, p * 2, l, mid, ql, qr, v);
        upd(upd, p * 2 + 1, mid + 1, r, ql, qr, v);
        tr[p] = tr[p * 2] + tr[p * 2 + 1];
        };

    auto ask = [&](auto&& ask, int p, int l, int r, int ql = 1, int qr) -> int {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return tr[p];
        down(p, l, r);
        int mid = (l + r) / 2;
        return ask(ask, p * 2, l, mid, ql, qr) + ask(ask, p * 2 + 1, mid + 1, r, ql, qr);
        };
