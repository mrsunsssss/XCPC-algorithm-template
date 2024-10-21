struct BIT {
    BIT(int row, int col) : row(row), col(col) {
        a.resize(row + 5, vector<ll>(col + 5, 0));
        b.resize(row + 5, vector<ll>(col + 5, 0));
        c.resize(row + 5, vector<ll>(col + 5, 0));
        d.resize(row + 5, vector<ll>(col + 5, 0));
    }

    void add(int r1, int c1, int r2, int c2, ll delta) {
        add(r1, c1, delta);
        add(r1, c2 + 1, -delta);
        add(r2 + 1, c1, -delta);
        add(r2 + 1, c2 + 1, delta);
    }

    ll query(int r1, int c1, int r2, int c2) {
        ll res = 0;
        res += query(r2, c2);
        res -= query(r1 - 1, c2);
        res -= query(r2, c1 - 1);
        res += query(r1 - 1, c1 - 1);
        return res;
    }

    int row, col;
    vector<vector<ll>> a, b, c, d;
    void add(int row, int col, ll delta) {
        for (int i = row; i <= this->row; i += i & -i) {
            for (int j = col; j <= this->col; j += j & -j) {
                a[i][j] += delta;
                b[i][j] += delta * row;
                c[i][j] += delta * col;
                d[i][j] += delta * row * col;
            }
        }
    }

    ll query(int row, int col) {
        ll res = 0;
        for (int i = row; i > 0; i -= i & -i) {
            for (int j = col; j > 0; j -= j & -j) {
                res += (row + 1) * (col + 1) * a[i][j];
                res -= (col + 1) * b[i][j];
                res -= (row + 1) * c[i][j];
                res += d[i][j];
            }
        }
        return res;
    }
};
