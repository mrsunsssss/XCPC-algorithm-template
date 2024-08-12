//高精度乘法比较慢，其他应该比另一个快一点
const int base = 100000000;
const int num_digit = 8;
const int maxn = 2000000;// 最大位数/8

ll mul_mod(ll x, ll y, ll n) {
    ll T = floor(sqrt(n) + 0.5);
    ll t = T * T - n;
    ll a = x / T; ll b = x % T;
    ll c = y / T; ll d = y % T;
    ll e = a * c / T; ll f = a * c % T;
    ll v = ((a * d + b * c) % n + e * t) % n;
    ll g = v / T; ll h = v % T;
    ll ans = (((f + g) * t % n + b * d) % n + h * T) % n;
    while (ans < 0) ans += n;
    return ans;
}
struct bign {
    int len;
    int s[maxn];
    bign(const std::string& str = "0") { (*this) = str; }
    bign operator= (const std::string& str) {
        int j = str.length() - 1;
        len = j / num_digit + 1;
        for (int i = 0; i <= len; i++) s[i] = 0;
        for (int i = 0; i <= j; i++) {
            int k = (j - i) / num_digit + 1;
            s[k] = s[k] * 10 + str[i] - '0';
        }
        return *this;
    }
    friend istream& operator>>(istream& in, bign& a) {
        string str;
        in >> str;
        a = str;
        return in;
    }

    // 输出操作符重载
    friend ostream& operator<<(ostream& out, const bign& a) {
        out << a.s[a.len];
        for (int i = a.len - 1; i >= 1; i--) {
            out << setw(num_digit) << setfill('0') << a.s[i];
        }
        return out;
    }
};

//比较的前提是整数没有前导0
int compare(const bign& a, const bign& b) {
    if (a.len > b.len) return 1;
    if (a.len < b.len) return -1;
    int i = a.len;
    while ((i > 1) && (a.s[i] == b.s[i])) i--;
    return a.s[i] - b.s[i];
}
inline bool operator< (const bign& a, const bign& b) {
    return compare(a, b) < 0;
}
inline bool operator<= (const bign& a, const bign& b) {
    return compare(a, b) <= 0;
}
inline bool operator== (const bign& a, const bign& b) {
    return compare(a, b) == 0;
}
//加法和减法很容易写出，只需注意不要忽略前导0
bign operator+ (const bign& a, const bign& b) {
    bign c;
    int i;
    for (i = 1; i <= a.len || i <= b.len || c.s[i]; i++) {
        if (i <= a.len) c.s[i] += a.s[i];
        if (i <= b.len) c.s[i] += b.s[i];
        c.s[i + 1] = c.s[i] / base;
        c.s[i] %= base;
    }
    c.len = i - 1;
    if (c.len == 0) c.len = 1;
    return c;
}
//减法的前提是a > b
bign operator- (const bign& a, const bign& b) {
    bign c;
    int i, j;
    for (i = 1, j = 0; i <= a.len; i++) {
        c.s[i] = a.s[i] - j;
        if (i <= b.len) c.s[i] -= b.s[i];
        if (c.s[i] < 0) { j = 1; c.s[i] += base; }
        else j = 0;
    }
    c.len = a.len;
    while (c.len > 1 && !c.s[c.len]) c.len--;
    return c;
}
bign operator* (const bign& a, const bign& b) {
    bign c;
    ll g = 0;
    int i, k;
    c.len = a.len + b.len;
    c.s[0] = 0;
    for (i = 1; i <= c.len; i++) c.s[i] = 0;
    for (k = 1; k <= c.len; k++) {
        ll tmp = g;
        i = k + 1 - b.len;
        if (i < 1) i = 1;
        for (; i <= k && i <= a.len; i++)
            tmp += (ll)a.s[i] * (ll)b.s[k + 1 - i];
        g = tmp / base;
        c.s[k] = tmp % base;
    }
    while (c.len > 1 && !c.s[c.len]) c.len--;
    return c;
}
bign operator/ (const bign& a, int n) {
    ll g = 0;
    bign c;
    c.len = a.len;
    for (int i = a.len; i > 0; i--) {
        ll tmp = g * base + a.s[i];
        c.s[i] = tmp / n;
        g = tmp % n;
    }
    while (c.len > 1 && !c.s[c.len]) c.len--;
    return c;
}
bign operator/ (const bign& a, const bign& b) {
    bign L = "0"s, R = a;
    while (L < R) {
        bign M = L + (R - L + "1"s) / 2;
        if (M * b <= a) L = M;
        else R = M - "1"s;
    }
    return L;
}
ll bigmod(const bign& a, ll m) {
    ll d = 0;
    for (int i = a.len; i > 0; --i) {
        d = mul_mod(d, base, m);
        d = (d + a.s[i]) % m;
    }
    return d;
}
bign sqrt(const bign& n) {
    bign c, d, x, y = n;
    do {
        x = y;
        y = (x + n / x) / 2;
    } while (y < x);
    return x;
}
bign gcd(bign a, bign b) {
    bign c = "1"s;
    for (;;) {
        if (a == b)
            return a * c;
        else if (a.s[1] % 2 == 0 && b.s[1] % 2 == 0) {
            a = a / 2;
            b = b / 2;
            c = c * "2"s;
        }
        else if (a.s[1] % 2 == 0) {
            a = a / 2;
        }
        else if (b.s[1] % 2 == 0) {
            b = b / 2;
        }
        else if (b < a) {
            a = a - b;
        }
        else {
            b = b - a;
        }
    }
}
