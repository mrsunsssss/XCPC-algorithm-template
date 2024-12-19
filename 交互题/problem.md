https://codeforces.com/contest/896/problem/B

$n \cdot \lceil\frac{c}{2}\rceil \le m$ 这个东西具体是干什么？

移项 $\frac{m}{n} \ge \lceil\frac{c}{2}\rceil$ ，发现每个空可以刷新颜色数量的一半次数，这是什么意思？

再考虑，我们最朴素的操作就是，从左到右，遇到空白的纸或者比当前值大的，就更新。

这样需要的操作最多是 $c$ 次，所以我们从两边填即可。
