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


{{ self.title_sample_description() }}

和最小的解为 $(3,1,2,1,1)$，和为 $8$。

