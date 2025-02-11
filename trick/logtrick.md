给定一个数组，以某个右端点为结尾的所有子数组，其中不同的 或/与/lcm/gcd 值至多只有 logU 个。（注意U指值域）

对于 或/与/gcd 是显然的，而lcm不太显然，但是它可以在lcm大于值域时直接忽略，所以也可以看作这个级别。

gcd

https://codeforces.com/contest/2013/problem/E

https://codeforces.com/contest/2005/problem/D

https://codeforces.com/gym/526652/problem/E

https://codeforces.com/contest/2038/problem/D

https://ac.nowcoder.com/acm/contest/95323/K  logtrick+主席树

https://ac.nowcoder.com/acm/contest/95338/E 数据随机化下的max和min.以max为例,首先不妨固定左端点为1,其他左端点同理。

前缀$[1,i]$位置中，第$i$个位置取得最大值的概率为$\frac1i$,同时这为最大值种类的期望贡献了$\frac1i$.
