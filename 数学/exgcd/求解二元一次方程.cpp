const int inf = 1e18;
int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int x1, y1, d;
    d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}
int first_big(int x, int k, int l) {
    if (l == -inf) return -inf;
    x = (l - x) / k * k + x - k;
    while (x < l) x += k;
    while (x - k >= l) x -= k;
    return x;
}
int last_small(int x, int k, int r) {
    if (r == inf) return inf;
    x = (r - x) / k * k + x - k;
    while (x + k <= r) x += k;
    while (x > r) x -= k;
    return x;
}

//ax + by = c 的解的数量,要求 l1<=x<=r1,l2<=y<=r2 .(inf和-inf表示无限制)
int calc(int a, int b, int c, int& mnx, int& mny, int& mxx, int& mxy, int l1, int r1, int l2, int r2) {
    int x, y;
    int d = exgcd(a, b, x, y);
    if (a == 0 and b == 0) {
        if (c) return -1;
        mnx = l1, mxx = r1;
        mny = l2, mxy = r2;
        if (mnx == -inf or mny == -inf or mxx == inf or mxy == inf) return inf;
        return (r1 - l1 + 1) * (r2 - l2 + 1);
    }
    if (a == 0) {
        if (c % b) return -1;
        y = c / b;
        if (y < l2 or y > r2) return 0;
        mnx = l1, mxx = r1;
        mny = mxy = y;
        return r1 - l1 + 1;
    }
    if (b == 0) {
        if (c % a) return -1;
        x = c / a;
        if (x < l1 or x > r1) return 0;
        mny = l2, mxy = r2;
        mnx = mxx = x;
        return r2 - l2 + 1;
    }
    if (c % d) return -1;

    x *= c / d, y *= c / d;
    int B = b / d, A = a / d;

    mnx = first_big(x, B, l1);
    mxx = last_small(x, B, r1);
    mny = first_big(y, A, l2);
    mxy = last_small(y, A, r2);

    if (mny != -inf) mxx = min((c - b * mny) / a, mxx);
    if (mnx != -inf) mxy = min((c - a * mnx) / b, mxy);
    if (mxy != inf) mnx = max((c - b * mxy) / a, mnx);
    if (mxx != inf) mny = max((c - a * mxx) / b, mny);

    if (mxy < mny) return 0;
    return (mxy - mny) / A + 1;//(mxx - mnx) / B + 1
}
