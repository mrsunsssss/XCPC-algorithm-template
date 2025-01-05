设目标函数 $f(x)$ ，不等式约束为 $g_i(x)\le 0$ ，其中 $i =1,2,...,m$ ，等式约束为 $h_j(x) =0$ ，其中 $j=1,2,...,n$ .需要最小化 $f(x)$ .

定义拉格朗日函数为 $L(x,\lambda,\mu) = f(x) + \sum\limits_{i=1}^{m}\lambda_ig_i(x) + \sum\limits_{j=1}^{n}\mu_jh_j(x)$

根据KKT条件：

1. 拉格朗日函数对于 $x_i$ 和 $b$ 求偏导都是 0

2. $\lambda_i\ge 0$

3. $g_i\le 0$

4. $\lambda_ig_i(x) = 0$
