//单点修改，区间查询
namespace SEG {
    const int N = 2e5 + 10;
    struct S {
        int x = 0;
    };
    S combine(S u, S v) {
        return S{ u.x + v.x };
        //return S{ gcd(u.x , v.x) };
    }
    int n;//[0,n-1],0-index
    S t[2 * N];
    void set_value(int i,int val) {
        i--;
        t[n + i].x = val;
    }
    void build() {  // build the tree
        for (int i = n - 1; i > 0; i--) t[i] = combine(t[i << 1], t[i << 1 | 1]);
    }
    void init(int _n) {
        n = _n;
        for (int i = 0;i <= 2 * n;i++) t[i].x = 0;
        build();
    }
    void modify(int p, const S& value) {
        p--;
        for (t[p += n] = value; p >>= 1; ) t[p] = combine(t[p << 1], t[p << 1 | 1]);
    }
    S query(int l, int r) {//[l,r],1-index
        l--;
        S resl, resr;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = combine(resl, t[l++]);
            if (r & 1) resr = combine(t[--r], resr);
        }
        return combine(resl, resr);
    }
}
using SEG::modify;
using SEG::query;
