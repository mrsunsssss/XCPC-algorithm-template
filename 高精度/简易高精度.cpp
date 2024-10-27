     auto add = [&](string x, string y) {
        if (x.size() < y.size()) swap(x, y);
        int n = x.size(), m = y.size();
        reverse(x.begin(), x.end());
        reverse(y.begin(), y.end());
        for (auto& i : x) i -= '0';
        for (auto& i : y) i -= '0';
        x.push_back(0);
        for (int i = 0;i < n && i < m;i++) {
            x[i] = x[i] + y[i];
        }
        for (int i = 0;i < n;i++) {
            x[i + 1] += x[i] / 10;
            x[i] %= 10;
        }
        for (auto& i : x) i += '0';
        while (x.size() > 1 && x.back() == '0') x.pop_back();
        reverse(x.begin(), x.end());
        return x;
        };
    auto sub = [&](string x, string y) {
        int n = x.size(), m = y.size();
        reverse(x.begin(), x.end());
        reverse(y.begin(), y.end());
        for (auto& i : x) i -= '0';
        for (auto& i : y) i -= '0';
        for (int i = 0;i < n && i < m;i++) {
            x[i] -= y[i];
        }
        for (int i = 0;i < n;i++) {
            if (x[i] < 0) {
                x[i] += 10, x[i + 1] -= 1;
            }
        }
        for (auto& i : x) i += '0';
        while (x.size() > 1 && x.back() == '0') x.pop_back();
        reverse(x.begin(), x.end());
        return x;
        };
    auto mul = [&](string x, string y) {
        int n = x.size(), m = y.size();
        reverse(x.begin(), x.end());
        reverse(y.begin(), y.end());
        for (auto& i : x) i -= '0';
        for (auto& i : y) i -= '0';
        string res(n * m + 1, 0);
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) {
                res[i + j] += x[i] * y[j];
            }
            for (int j = 0;j < n + m;j++) {
                res[j + 1] += res[j] / 10;
                res[j] %= 10;
            }
        }
        for (auto& i : res) i += '0';
        while (res.size() > 1 && res.back() == '0') res.pop_back();
        reverse(res.begin(), res.end());
        return res;
        };
    auto le = [&](string x, string y)->bool {
        if (x.size() < y.size()) return 1;
        else if (x.size() == y.size()) {
            return x < y;
        }
        return 0;
        };
