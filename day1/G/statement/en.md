{{ self.title() }}

{{ s('description') }}

Menji likes GCDs(greatest common divisor), especially positive integer pairs with a big GCD.

Let $\gcd(x,y)$ denote the GCD of $x,y$. There are multiple queries, in each query you are given $L,R$, with $L<R$, find $\max\limits_{L\leq x<y\leq R}\gcd(x,y)$.

{{ s('input format') }}

{{ self.input_file() }}

The first line contains a positive integer $T(1\leq T\leq 10)$, the number of testcases.

The following $T$ lines, each line contains two integers $L,R(1\leq L<R\leq 10^{12})$, a single query.

{{ s('output format') }}

{{ self.output_file() }}

For each query $L,R$, output $\max\limits_{L\leq x<y\leq R}\gcd(x,y)$ in a single line.

{{ s('sample', 1) }}

{{ self.sample_text() }}

