{{ self.title() }}

{{ s('description') }}

给定一个 $n - 1$ 个点的无向图，点的编号为 $2 \sim n$。对于所有的 $2 \le u < v \le n$，边 $(u, v)$ 存在当且仅当 $v$ 是 $u$ 的正整数倍。定义 $f(u, v)$ 表示 $u$ 与 $v$ 是否连通：当 $u, v$ 连通时 $f(u, v) = 1$，否则 $f(u, v) = 0$。求：

$$\left(\sum_{u = 2} ^ {n - 1} \sum_{v = u + 1} ^ n f(u, v) \cdot u \cdot v\right) \bmod {998244353}$$

{{ s('input format') }}

{{ self.input_file() }}

输入一行一个正整数 $n$。保证 $4 \le n \le 10 ^ {11}$。

{{ s('output format') }}

{{ self.output_file() }}

输出一行一个非负整数表示答案。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

$f(u, v) = 1$ 当且仅当 $u = 2, v = 4$，故答案为 $2 \times 4 = 8$。

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

所有满足 $f(u, v) = 1$ 的 $(u, v)$ 为：$(2, 3), (2, 4), (2, 6), (3, 4), (3, 6), (4, 6)$。

{{ s('sample', 3) }}

{{ self.sample_text() }}