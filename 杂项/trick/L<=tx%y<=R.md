给定 $D$ , $M$ , $L$ , $R$ ，求最小的 $x$ 满足 $L\le Dx \;mod\; M\le R$ .

将 $L\le Dx \;mod\; M\le R$ ，转化为 $yM+L\le Dx \le yM+R$ 。（满足 $L\le R\le M-1$ ）

将它记为 $f(D,M,L,R)$ 

首先假设 $y=0$ ，若此时有解，则 $L\le Dx\le R$ 。

否则 $y>0$ ，由于上面找不到解，则 $tD< L\le R<(t+1)D$ .

移项得到 $Dx-R\le yM \le Dx-L$ ，当 $x=t+1$ 时，满足条件 $0<Dx-R\le Dx-L <D$ .

即可以表示为 $D-R\le yM \;mod\; D \le D-L$ 。

可以改写为 $f(M \;mod\;D,D,D-R,D-L)$ 。

http://poj.org/problem?id=3530
https://darkbzoj.cc/problem/4270
