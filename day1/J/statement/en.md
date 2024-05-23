{{ self.title() }}

{{ s('description') }}

Given an undirected graph with $n - 1$ vertices, where the vertices are numbered from $2$ to $n$. For all $2 \le u < v \le n$, the edge $(u, v)$ exists if and only if $v$ is a positive integer multiple of $u$. Define $f(u, v)$ as a function that indicates whether $u$ and $v$ are connected: $f(u, v) = 1$ if $u$ and $v$ are connected, and $f(u, v) = 0$ otherwise. Calculate:

$$\left(\sum_{u = 2} ^ {n - 1} \sum_{v = u + 1} ^ n f(u, v) \cdot u \cdot v\right) \bmod {998244353}$$

{{ s('input format') }}

{{ self.input_file() }}

Input a single positive integer $n$. It is guaranteed that $4 \le n \le 10^{11}$.

{{ s('output format') }}

{{ self.output_file() }}

Output a single non-negative integer representing the answer.

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

Since $f(u, v) = 1$ if and only if $u = 2, v = 4$, the answer is $2 \times 4 = 8$.

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

All the pairs $(u, v)$ satisfied that $f(u, v) = 1$ are: $(2, 3), (2, 4), (2, 6), (3, 4), (3, 6), (4, 6)$.

{{ s('sample', 3) }}

{{ self.sample_text() }}