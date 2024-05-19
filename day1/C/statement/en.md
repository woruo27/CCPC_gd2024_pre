{{ self.title() }}

{{ s('description') }}

Given a tree with $n$ vertices, rooted at vertex $1$. Every vertex is attached with a weight $w_i$.

Find an optimal DFS traversal order such that $\sum\limits_{i=1}^n p_iw_i$ is maximum, where $p_i$ denotes the number of different visited vertices when visiting vertex $i$ the first time (including vertex $i$ itself).

{{ s('input format') }}

{{ self.input_file() }}

The first line contains a single integer $n$.

The second line contains $n$ integers, in which the $i$-th integer denotes $w_i$.

The third line contains $n-1$ integers, in which the $i$-th integer denotes the parent of vertex $i+1$ on the tree. The value of the $i$-th integer is in $[1,i]$.

{{ s('output format') }}

{{ self.output_file() }}

One integer, which denotes the maximum $\sum\limits_{i=1}^n p_iw_i$.

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

It is guaranteed that $1\le n \le 2\times 10^5$，$1\le w_i \le 10^9$.
