{{ self.title() }}

{{ s('description') }}

给定一张 $n$ 个点 $m$ 条边的无向图，令 $k=\lceil\frac{m}{n-1}\rceil$，你判断能否找到两个点 $u,v$，满足它们之间存在 $k$ 条**边不相交**路径，如果可以找到这样的 $u,v$，你需要输出这些路径，如果存在多种构造方案，输出任意一种即可。

额外需要注意的是输入**可能存在重边**，也就是对于同一个无序对 $(u,v)$，它们之间可能存在多条边，如果它们之间存在 $k$ 条边那么你可以理解为这条边可以经过 $k$ 次。

不过我们保证输入**不存在自环**。

{{ s('input format') }}

{{ self.input_file() }}

**本题包含多组输入数据。**

输入第一行一个正整数 $T$ 表示数据组数。

对于每组输入数据，第一行输入两个正整数 $n,m$ 表示点数和边数，接下来 $m$ 行每行两个正整数 $u,v$ 描述 $u,v$ 间存在的一条边。

{{ s('output format') }}

{{ self.output_file() }}

对于每组输入数据，如果不存在这样的 $u,v$，那么输出一行一个整数 `-1`，否则先输出一行两个正整数 $u,v$ 表示你找到的两个点，接下来输出 $k=\lceil\frac{m}{n-1}\rceil$ 行，每行描述你选出来的一条路径，形如 $x_1,x_2,\dots,x_t$，表示你选择了 $x_1\to x_2\to\cdots\to x_t$ 这条路径，你需要保证 $x_1=u$ 且 $x_t=v$。且你需要保证输出的 $k$ 条路径满足边不相交的条件。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

这是第一组数据的样例说明。

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

这是第二组数据的样例说明。

{{ s('subtasks') }}

对于所有数据，满足 $1\le T\le 10^4$，$2\le n,\sum n\le 10^5$，$1\le m,\sum m\le 2\times 10^5$。其中 $\sum n,\sum m$ 分别表示同一个测试点内所有输入数据的 $n,m$ 之和。