# A. 田字格

## 题目描述

给定平面上与坐标轴平行的 $n \le 3 \times 10^5$ 条黑色线段，求出它们构成多少田字格。一个田字格由三元组 $(x_0,y_0,d)$ 表示，一个三元组是田字格当且仅当正方形 $[x_0-d,x_0+d] \times [y_0-d,y_0+d]$ 与平面上黑色部分的交恰好等于 $x=x_0-d,x=x_0,x=x_0+d,y=y_0-d,y=y_0,y=y_0+d$ 六条直线与这个正方形的交。

## 题目解法

注意到一个田字格由三条等距的、中间没有插入其他横线的横线组，和三条等距的、中间没有插入其他竖线的竖线组构成。考虑先把这样的横线组和竖线组处理出来，然后计算所有横线组和竖线组可以合并出多少的田字格。

考虑第一步，维护出所有的竖线组，横线组类似。按照纵坐标扫描线，每次维护与 $y = y_0$ 有交的竖线集合，按照横坐标排序。那么可能的竖线组在这个序列上一定是连续排列的（因为中间不能有其他竖线）。总共会形成 $O(n)$ 次插入，每次插入只会改变 $O(1)$ 个竖线组的存在情况，使用 `set` 维护。这样我们可以得到 $O(n)$ 个四元组 $(x_0,x_1,y_0,y_1)$，表示从 $y=y_0$ 到 $y = y_1$，三条竖线 $x=x_0,x=\frac{x_0+x_1}{2}, x=x_1$ 存在且中间没有其他竖线。

处理出所有的横线组和竖线组之后，枚举 $d$，此时竖线组的 $x_1-x_0$ 和横线组的 $y_1-y_0$ 是确定的。一个横线组 $(x_0,y_0,y_1)$ 和一个竖线组 $(x_0',x_1',y_0')$ 是一个合法的田字格当且仅当

- $x_0' \le x_0 \le x_1' - 2d$；
- $y_0 \le y_0' \le y_1 - 2d$。

这是一个二维偏序，对一维扫描线另一维树状数组统计即可。复杂度 $O(n \log n)$