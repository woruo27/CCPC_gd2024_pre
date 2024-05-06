{{ self.title() }}

{{ s('description') }}

Menji 喜欢最大公约数，特别是最大公约数大的正整数对。

令 $\gcd(x,y)$ 表示 $x,y$ 的最大公约数，多次给定 $L,R$，保证 $L\leq R$，求 $\max\limits_{L\leq x<y\leq R}\gcd(x,y)$。

{{ s('input format') }}

{{ self.input_file() }}

第一行一个正整数 $T(1\leq T\leq 10)$，表示数据组数。

之后 $T$ 行，每行两个正整数 $L,R(1\leq L<R\leq 10^{12})$，表示一组询问。

{{ s('output format') }}

{{ self.output_file() }}

对于每个询问 $L,R$，输出一行一个正整数 $\max\limits_{L\leq x<y\leq R}\gcd(x,y)$。

{{ s('sample', 1) }}

{{ self.sample_text() }}

