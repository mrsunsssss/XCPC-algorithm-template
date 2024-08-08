array<int, 2> approx(int p, int q, int A) {//模数p,还原q,分子最大值A
    int x = q, y = p, a = 1, b = 0;
    while (x > A) {
        swap(x, y);swap(a, b);
        a -= x / y * b;
        x %= y;
    }
    return { x,a };//q = x/a(mod p)
}
