{{ self.title() }}


{{ s('description') }}

给定 $n,m$，以及 $m$ 个形如 $a_{x_i}\ge a_{y_i}+a_{z_i}(1 \le i \le m)$ 的条件，为是否有一组正整数 $(a_1,a_2,\cdots,a_n)$ 满足所有条件，并且 $a_1+a_2+\cdots+a_n \le 10^{9}$。如果有，输出 $a_1+a_2+\cdots+a_n$ 的最小值；如果无解，输出 $-1$。

{{ s('input format') }}

{{ self.input_file() }}

第一行两个整数 $n,m(1 \le n,m \le 2\times 10^5)$。

之后 $m$ 行，第 $i$ 行三个整数 $x_i,y_i,z_i$，表示一个限制 $a_{x_i}\ge a_{y_i}+a_{z_i}(1\le x_i,y_i,z_i \le n)$。
{{ s('output format') }}

{{ self.output_file() }}

输出一行一个整数，表示答案。

{{ s('sample', 1) }}

{{ self.sample_text() }}

上面是自动读入样例 `1.in/ans`（存储在 `down` 文件夹内） 然后渲染到题面中；如果只有一组样例，则去掉 `1` 或将其替换成空串，样例仍然保存成 `1.in/ans`。上面的 `1` 可以是字符串。

{{ self.title_sample_description() }}

这是第一组数据的样例说明。

{{ s('sample', 2) }}

{{ self.sample_file() }}

上面是只提示存在第二组样例，但不渲染到题面中。

