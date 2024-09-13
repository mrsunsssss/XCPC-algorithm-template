//位权法: 倒序计算 如174855可以看作是558471,子串748即(558470-550000)/xp[1]

#define ENABLE_DOUBLE_HASH
const int X1 = 131;
const int X2 = 13331;
const int p1 = 1e9 + 7;//const int p1 = rnd(1e8, 1e9);
const int p2 = 1e9 + 9;//const int p2 = rnd(1e9 + 1, 2e9);
ull xp1[N], xp2[N], xp[N];
void init() {
    xp1[0] = xp2[0] = xp[0] = 1;
    for (int i = 1;i < N;i++) {
        xp1[i] = xp1[i - 1] * X1 % p1;
        xp2[i] = xp2[i - 1] * X2 % p2;
        xp[i] = xp[i - 1] * X1;
    }
}
struct String {
    string s;
    int size, subsize;
    bool sorted;
    vector<ull> h, hl;
    String(string S) :s(S) {
        sorted = subsize = 0;
        size = (int)s.size() - 1;
        h.resize(size + 2);hl.resize(size + 2);
        ull res1 = 0, res2 = 0;
        h[size + 1] = 0;
        for (int j = size;j >= 1;j--) {
#ifdef ENABLE_DOUBLE_HASH
            res1 = (res1 * X1 + s[j]) % p1;
            res2 = (res2 * X2 + s[j]) % p2;
            h[j] = (res1 << 32) | res2;
#else
            res1 = res1 * X1 + s[j];
            h[j] = res1;
#endif
        }
    }
    String(string S, bool t) :s(S) {//这里的t没有用,只是为了和上面区分.构造字符串的反向哈希值
        sorted = subsize = 0;
        size = (int)s.size() - 1;
        h.resize(size + 2);hl.resize(size + 2);
        ull res1 = 0, res2 = 0;
        h[size + 1] = 0;
        for (int j = size;j >= 1;j--) {
#ifdef ENABLE_DOUBLE_HASH
            res1 = (res1 * X1 + s[size - j + 1]) % p1;
            res2 = (res2 * X2 + s[size - j + 1]) % p2;
            h[j] = (res1 << 32) | res2;
#else
            res1 = res1 * X1 + s[size - j + 1];
            h[j] = res1;
#endif
        }
    }
    //获取子串哈希，左闭右闭区间. right-left+1>=0
    ull subs(int left, int right)const {
        int len = right - left + 1;
#ifdef ENABLE_DOUBLE_HASH
        unsigned int mask32 = ~(0u);//111..111
        ull left1 = h[left] >> 32, right1 = h[right + 1] >> 32;
        ull left2 = h[left] & mask32, right2 = h[right + 1] & mask32;
        return(((left1 - right1 * xp1[len] % p1 + p1) % p1) << 32) | (((left2 - right2 * xp2[len] % p2 + p2) % p2));
#else
        return h[left] - h[right + 1] * xp[len];
#endif
    }
    void get_all_subs(int sublen) {
        subsize = size - sublen + 1;
        for (int i = 1;i <= subsize;i++) {
            hl[i] = subs(i, i + sublen - 1);
        }
        sorted = 0;
    }
    void sort_subs() {
        if (!sorted) sort(hl.begin() + 1, hl.begin() + subsize + 1);
        sorted = 1;
    }
    bool match(ull key)const {
        if (!sorted)assert(0);
        if (!subsize)return 0;
        return binary_search(hl.begin() + 1, hl.begin() + subsize + 1, key);
    }
};
//a[ai...]与b[bi...]的最长公共前缀
int LCP(const String& a, const String& b, int ai, int bi) {
    int l = 0, r = min(a.size - ai + 1, b.size - bi + 1);int ans = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (a.subs(ai, ai + mid - 1) == b.subs(bi, bi + mid - 1)) {
            l = mid + 1;
            ans = mid;
        }
        else {
            r = mid - 1;
        }
    }
    return ans;
}
//检查S的所有长度len的子串是否都在T中出现
int check(const String& S, String& T, int len) {
    if (T.size < len) return 0;
    T.get_all_subs(len);T.sort_subs();
    for (int i = 1;i + len - 1 <= S.size;i++) {
        if (!T.match(S.subs(i, i + len - 1))) return 0;
    }
    return 1;
}
ull add(const String& a, int l1, int r1, const String& b, int l2, int r2) {
    ull suba = a.subs(l1, r1), subb = b.subs(l2, r2);
#ifdef ENABLE_DOUBLE_HASH
    unsigned int mask32 = ~(0u);//111..111
    ull a1 = suba >> 32, b1 = subb >> 32;
    ull a2 = suba & mask32, b2 = subb & mask32;
    return(((a1 + b1 * xp1[r1 - l1 + 1] % p1 + p1) % p1) << 32) | (((a2 + b2 * xp2[r1 - l1 + 1] % p2 + p2) % p2));
#else 
    return suba + subb * xp[r1 - l1 + 1];
#endif
}

//1-index
