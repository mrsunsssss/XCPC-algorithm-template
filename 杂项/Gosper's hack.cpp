//Gosper's hack
//枚举全集U所有大小恰好为k的子集
//或者将k个1和n-k个0塞进vector然后使用next_permutation ,常数略大
//最慢的直接枚举子集,判断1的个数
void GosperHack(int k, int n) {
    int now = (1 << k) - 1;
    int lim = (1 << n);
    while (now < lim) {
        //do something
        int lb = lowbit(now);
        int r = now + lb;
        now = (((r ^ now) >> 2) / lb) | r;
    }
}
