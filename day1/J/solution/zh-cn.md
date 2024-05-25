注意到，对于所有 $x \le \lfloor \frac{n + 1}{2} \rfloor$ 的结点 $x$，$x$ 与 $2x$ 间有一条边，而 $2x$ 与 $2$ 之间有一条边，因此所有 $2 \sim \lfloor \frac{n + 1}{2} \rfloor$ 范围内的结点连通。而对于 $x > \lfloor \frac{n + 1}{2} \rfloor$ 的结点 $x$，$x$ 不与 $2 \sim \lfloor \frac{n + 1}{2} \rfloor$ 中的结点连通当且仅当 $x$ 为素数。因此整个图仅包含若干个单独的素数结点与一个大的连通块。

考虑计算不连通的点对之间的贡献。不难发现，只需要求出所有 $> \lfloor \frac{n + 1}{2} \rfloor$ 的素数的和与平方和。使用 Min_25 筛或分块打表均可。
