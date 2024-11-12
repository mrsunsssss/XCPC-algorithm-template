template<int W = 2, int maxW = 1000010>
int solve(int n, vector<int>& a) {
    if (n >= W) {
        return solve<min(W * 2, maxW)>(n, a);
    }
   //to do something
    bitset<W> f;f[0] = 1;
    for (auto i : a) {
        f |= f << i;
    }
    for (int i = n / 2;i >= 0;i--) {
        if (f[i]) return i * (n - i);
    }
}
