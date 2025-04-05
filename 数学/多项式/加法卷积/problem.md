https://leetcode.cn/problems/find-the-original-typed-string-ii/description/    Log的泰勒展开，调和级数枚举。

https://leetcode.cn/problems/count-the-number-of-inversions/description/      排列与它的逆序对序列的双射关系，Log的泰勒展开，调和级数枚举。

https://codeforces.com/contest/2038/problem/F       经典trick转化max，卷积。

https://acm.hdu.edu.cn/contest/problem?cid=1154&pid=1004 循环卷积

https://www.luogu.com.cn/problem/P3321 原根：对于一个数字 $p$ , $g^0\mod p$  , $g^2\mod p$ , … , $g^{p-2}\mod p$ 刚好取到 $[1,p-1]$ 里的每个数字一次， $g$ 即为原根。原本的多项式乘法是幂次相加，现在我们把每个幂次都映射到对数函数上，相加就变成相乘了。注意底需要取其中一个原根，这样才能保证满射关系。最后跑一个循环卷积即可。
