https://ac.nowcoder.com/acm/contest/98256/F

对于线段树的懒标记，我们需要自己指定它的优先级。

例如本题，我们可以指定执行顺序为 sub1,rev，分别表示赋值1和反转。

那么，考虑如何合并L和R的懒标记。假如R的sub1为1，之后如果有rev就赋值0，否则赋值1.

sub1为0，则先把两者的rev异或一下，然后再获取L.sub1.

```
struct S {
    int sum0, sum1, len;
    S(int a, int b, int c) {
        sum0 = a, sum1 = b, len = c;
    }
    S(int v, int _len) {
        len = _len;
        sum0 = v == 0 ? len / 2 : (len + 1) / 2;
        sum1 = v == 1 ? len / 2 : (len + 1) / 2;
    }
};
S op(S l, S r) {
    if (l.len == 0) return r;
    else if (r.len == 0) return l;
    return S{ l.sum0 + (l.len % 2 == 0 ? r.sum0 : r.sum1),l.sum1 + (l.len % 2 == 0 ? r.sum1 : r.sum0) ,l.len + r.len };
}
S e() {
    return S{ 0,0,0 };
}
struct F {
    int sub1, rev;
};
S mapping(F f, S x) {//x->f(x)
    if (f.sub1) {
        x = S(!f.rev, x.len);
    }
    else if (f.rev) {
        swap(x.sum0, x.sum1);
    }
    return x;
}
F composition(F f, F g) { // f(g(x))
    if (f.sub1) {
        return f;
    }
    else {
        f.rev ^= g.rev, f.sub1 = g.sub1;
    }
    return f;
}
F id() {//e of F
    return F{ 0,0 };
}
```

如果是执行顺序 rev sub1，发现还需要引入变量sub0表示赋值为0.

不妨这样执行 rev sub0 sub1 

如果R.sub1=1，则直接返回。否则看R.sub2=1，也直接返回。再否则，就只有R.rev了，再看L.sub1和L.sub2，给它翻转了，如果都没有就异或两者的rev。

```
struct S {
    int sum0, sum1, len;
    S(int a, int b, int c) {
        sum0 = a, sum1 = b, len = c;
    }
    S(int v, int _len) {
        len = _len;
        sum0 = v == 0 ? len / 2 : (len + 1) / 2;
        sum1 = v == 1 ? len / 2 : (len + 1) / 2;
    }
};
S op(S l, S r) {
    if (l.len == 0) return r;
    else if (r.len == 0) return l;
    return S{ l.sum0 + (l.len % 2 == 0 ? r.sum0 : r.sum1),l.sum1 + (l.len % 2 == 0 ? r.sum1 : r.sum0) ,l.len + r.len };
}
S e() {
    return S{ 0,0,0 };
}
struct F {
    int sub0, sub1, rev;
};
S mapping(F f, S x) {//x->f(x)
    if (f.sub1) {
        x = S(1, x.len);
    }
    else if (f.sub0) {
        x = S(0, x.len);
    }
    else if (f.rev) {
        swap(x.sum0, x.sum1);
    }
    return x;
}
F composition(F f, F g) { // f(g(x))
    if (f.sub1) {
        return f;
    }
    else if (f.sub0) {
        return f;
    }
    else if (f.rev) {
        if (g.sub1) {
            return { 1,0,0 };
        }
        else if (g.sub0) {
            return { 0,1,0 };
        }
        f.rev ^= g.rev;
        return f;
    }
    else return g;
}
F id() {//e of F
    return F{ 0,0 ,0 };
}
```






