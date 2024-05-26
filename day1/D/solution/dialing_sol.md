不难想到把 $p_i, q_i$ 转换成单向边上的字符串，则问题即转换为：给定 $u_i$，问有多少个（$0/1/2+$）$v$ 满足从 $u_i$ 到 $v$ 的有向路径上字符串首尾相连可以得到 $s_i$。

可以用点分治做。

这里快速判断字符串相等可以用 Hash 处理，但是每次查询重心的时候需要去掉 $s_i$ 的一个前缀判断。考虑设计一种较为优秀的 Hash，使得：

- $Hash\left(a_1 a_2 \cdots a_k\right) \equiv f^{\left(a_i\right)} \left(Hash\left(a_2 \cdots a_k\right)\right)$；

- $f^{(c)}$ 均可逆。

这样，可以通过逆函数的复合得到 $s_i$ 在重心处应该查询的 Hash 值。最简单的实现方法是使用模意义下可逆的一次函数计算。实现优秀的 Hash 可以 $O(1)$ 在开头加上或删去预处理好的字符串，$O(1)$ 查询是否存在给定的 Hash 值。因此，总复杂度应为 $O\left((n+m) \log m + \left(\sum \left| t_i\right|+\sum \left|p_i\right| + \sum\left|q_i\right| +\sum \left|s_i\right|\right)\right)。$
