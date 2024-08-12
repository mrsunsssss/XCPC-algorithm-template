#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long 
#define endl '\n'


template<typename F, typename ...T> inline size_t hash_combine(const F& first, const T&... params) {
    if constexpr (sizeof...(params) == 0) {
        return hash<F>()(first);
    }
    else {
        size_t seed = hash_combine(params...);
        return hash<F>()(first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
}
template<typename A, typename B>
struct hash<pair<A, B>> {
    inline size_t operator() (const pair<A, B>& pr) const {
        return hash_combine(pr.first, pr.second);
    }
};
template<typename ...T>
struct hash<tuple<T...>> {
    inline size_t operator() (const tuple<T...>& tp) const {
        return apply(hash_combine<T...>, tp); // 需要C++17
    }
};
template<size_t N>
struct hash<array<int, N>> {
    inline size_t operator() (const array<int, N>& arr) const {
        size_t seed = 0;
        for (const auto& elem : arr) {
            seed = hash_combine(seed, elem);
        }
        return seed;
    }
};

void Prework() {

}
void Solve() {
    unordered_set<tuple<int, int, string>> S;
    S.insert({ 1, 2, "asd" });
    S.insert({ 4, 5, "zxc" });
    for (auto [a, b, c] : S) {
        cout << a << " " << b << " " << c << endl;
    }
    unordered_set<array<int, 5>> st;
    st.insert({ 1,2,3,4,5 });
    st.insert({ 1,2,4,3,5 });
    st.insert({ 1,2,4,3,15 });
    for (auto [a, b, c, d, e] : st) {
        cout << a << " " << b << " " << c << " " << d << " " << e << endl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T = 1;
    //cin >> T;
    Prework();
    while (T--) Solve();
}
