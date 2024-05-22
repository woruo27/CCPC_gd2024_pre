{{ self.title() }}

{{ s('description') }}

Ran loves random numbers.

Ran first selects a real number $0 < p < 1$ and then generates $n$ random numbers $x_1,\dots,x_n$, each of which is generated independently as follows:

- $x_i$ equals to $p$ with probability $1$, $(1-p)p$ with probability $2$, $(1-p)^2p$ with probability $3$, and so on.

After generating these random numbers, Ai summed the prefixes of this series to get the series $y_1,\dots,y_n$.

Given $1\leq l\leq r\leq n$, Lan wants to know how many $y_i$ are expected to fall within $[l, r]$?

{{ s('input format') }}

{{ self.input_file() }}

Enter four numbers $n, p, l, r$ on a line. Ensure that $1\leq l\leq r\leq n\leq 10^9$ and $p$ has no more than $6$ digits.

{{ s('output format') }}

{{ self.output_file() }}

Output a real number representing the answer. You need to ensure that the absolute or relative error of the answer does not exceed $10^{-6}$.

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

With $1/4$ probability, $x_1=1$ and $x_2>1$, only $y_1$ falls within $[1, 2]$.

With $1/4$ probability, $x_1=1$ and $x_2=1$, then $y_1,y_2$ fall in $[1, 2]$.

There is a $1/4$ probability that $x_1=2$, when only $y_1$ falls within $[1, 2]$.

So the expectation is $1/4\cdot (1 + 2 + 1) = 1$.
