{{ self.title() }}

{{ s('description') }}

We define $\operatorname{mex}$ of a set $S$ to be the smallest non-negative integer not in $S$.

Given a sequence $a_1,\dots,a_n$, for each $1\leq k\leq n$, we define $b_k$ as follows:

- For all subintervals of $a$ of length $k$, find the $\operatorname{mex}$ of the set of numbers formed by this subinterval.
- For all $\operatorname{mex}$ found, find $\operatorname{mex}$ of the set of numbers itself, denoted $b_k$.

Find the sequence $b$.

{{ s('input format') }}

{{ self.input_file() }}

The first line enters a positive integer $n$ ($1\leq n\leq 10^5$).

The second line enters $n$ integers $a_1,\dots,a_n$ ($0\leq a_i\leq n$).

{{ s('output format') }}

{{ self.output_file() }}

A line outputs $n$ integers $b_1,\dots,b_n$.

{{ s('sample', 1) }}

{{ self.sample_text() }}
