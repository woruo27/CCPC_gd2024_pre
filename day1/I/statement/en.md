{{ self.title() }}


{{ s('description') }}

Given $n,m$, and $m$ conditions of the form $a_{x_i}\ge a_{y_i}+a_{z_i}(1 \le i \le m)$. Determine if there exists **positive** integers $(a_1,a_2,\cdots,a_n)$ that satisfies all conditions and $a_1+a_2+\cdots+a_n \le 10^{9}$. If yes, output the minimum value of $a_1+a_2+\cdots+a_n$; otherwise output $-1$.

{{ s('input format') }}

{{ self.input_file() }}

The first line conntains two integers $n,m(1 \le n,m \le 2\times 10^5)$.

The following $m$ rows each contain three integers $x_i,y_i,z_i$(in the $i$th row), representing a restriction $a_{x_i}\ge a_{y_i}+a_{z_i}(1\le x_i,y_i,z_i \le n)$.
{{ s('output format') }}

{{ self.output_file() }}

Output a line with an integer that represents the answer.

{{ s('sample', 1) }}

{{ self.sample_text() }}


{{ self.title_sample_description() }}

The solution with the smallest sum is $(3,1,2,1,1)$ and the sum is $8$.

