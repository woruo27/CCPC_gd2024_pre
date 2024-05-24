{{ self.title() }}

{{ s('description') }}

给定一棵 $n$ 个点的有根树，$1$ 号点为根。每个点有一个权值 $w_i$。

求一个最优的 DFS 序使得 $\sum\limits_{i=1}^n p_iw_i$ 最大。其中 $p_i$ 表示访问第 $i$ 个点的时刻，即第一次访问节点 $i$ 之前访问过多少个不同的节点（包含节点 $i$ 本身）。

{{ s('input format') }}

{{ self.input_file() }}

第一行一个正整数 $n(1\le n \le 2\times 10^5)$。

第二行 $n$ 个正整数，其中第 $i$ 个表示 $w_i(1\le w_i \le 10^8)$。

第三行 $n-1$ 个正整数，其中第 $i$ 个表示 $i+1$ 号节点的父亲，保证取值在 $1\sim i$ 之间。

{{ s('output format') }}

{{ self.output_file() }}

一行一个整数，表示最大的 $\sum\limits_{i=1}^n p_iw_i$。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

按照 $(1,3,5,4,2)$ 的访问顺序可以取得最大值 $1\times 8+2\times 3+3\times 4+4\times 6+5\times 5=75$。

注意 $(1,3,2,4,5)$ 不是一个合法的访问顺序。
