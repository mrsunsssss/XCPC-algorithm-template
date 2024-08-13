#include <bits/stdc++.h>
using namespace std;

//基数排序离散化
namespace Discretization_Int {
    const int base = (1 << 17) - 1;
    vector<int> c(base + 10);
    vector<pair<int, int>> data, tmp;
    void discretization(vector<int>& input) {
        int n = input.size();
        data.resize(n);
        tmp.resize(n);
        for (int i = 0; i < n; i++) data[i] = { input[i], i };
        for (int i = 0; i < 32; i += 16) {
            fill(c.begin(), c.end(), 0);
            for (int j = 0; j < n; j++) c[(data[j].first >> i) & base]++;
            for (int j = 1; j <= base; ++j) c[j] += c[j - 1];
            for (int j = n - 1; j >= 0; --j) tmp[--c[(data[j].first >> i) & base]] = data[j];
            data.swap(tmp);
        }

        for (int i = 0, j = -1; i < n; i++) {
            if (i == 0 || data[i].first != data[i - 1].first) ++j;
            input[data[i].second] = j;
        }
    }
}

namespace Discretization_LL {
    const int base = (1 << 17) - 1;
    vector<int> c(base + 10);
    vector<pair<long long, int>> data, tmp;

    void discretization(vector<long long>& input) {
        int n = input.size();
        data.resize(n);
        tmp.resize(n);

        for (int i = 0; i < n; i++)
            data[i] = { input[i], i };

        for (int i = 0; i < 64; i += 16) {
            fill(c.begin(), c.end(), 0);
            for (int j = 0; j < n; ++j) c[(data[j].first >> i) & base]++;
            for (int j = 1; j <= base; j++) c[j] += c[j - 1];
            for (int j = n - 1; j >= 0; j--) tmp[--c[(data[j].first >> i) & base]] = data[j];
            data.swap(tmp);
        }

        for (int i = 0, j = -1; i < n; i++) {
            if (i == 0 || data[i].first != data[i - 1].first) ++j;
            input[data[i].second] = j;
        }
    }
}


int main() {
    int n = 1000000;
    default_random_engine e;
    uniform_int_distribution<long long> d(0, LLONG_MAX);
    e.seed(time(0));
    vector<long long> A(n), B(n), tmp(n);
    for (int i = 0; i < n; ++i)
        A[i] = B[i] = tmp[i] = d(e);
    printf("start....\n");
    auto start = clock();
    sort(tmp.begin(), tmp.end());
    int sz = unique(tmp.begin(), tmp.end()) - tmp.begin();
    for (int i = 0; i < n; ++i)
        A[i] = lower_bound(tmp.begin(), tmp.begin() + sz, A[i]) - tmp.begin();
    printf("std::sort: %f\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
    start = clock();
    Discretization_LLong::discretization(B);
    printf("std::sort: %f\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
    for (int i = 0; i < n; ++i)
        if (A[i] != B[i])
            abort();
    return 0;
}
