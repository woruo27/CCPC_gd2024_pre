{{ self.title() }}

{{ s('background') }}

Ai wants to take on the challenge of partition multiplication. Ai abstracts the strategy to the following problem:

Now given a target set $T$ which is a subset of $\{1,\dots,n\}$ ($1\leq n\leq 5\times 10^5$). You need to construct some sets to finally get $T$ through a series of operations, specifically the following three operations:

- Create a set of size one $|S|=1$.
- Concatenate two disjoint sets $A, B$ that have already been constructed to get $A\cup B$.
- Translate an already constructed set $A$, i.e. $A+x = \{ a+x : a\in A \}$.

A set that has already been constructed can be used many times later. At the same time you need to ensure that all sets that appear during the operation are subsets of $\{1,\dots,n\}$.

The cost is the sum of the sizes of all the sets constructed, and you don't need to minimize the cost, just keep it to no more than $5\times 10^6$. You should not use more than $10^6$ operations.

{{ s('input format') }}

{{ self.input_file() }}

The first line inputs a positive integer $n$.

The next line inputs a `01` string of length $n$, with the $x$-th bit being `1` to indicate $x\in T$, otherwise $x\notin T$. It's guaranteed that $T$ is not null.

{{ s('output format') }}

{{ self.output_file() }}

The first line outputs a positive integer $m$ indicating the number of operations you used.

The next $m$ lines, each describing one operation, let the set obtained by the $i$th operation be $T_i$:

- `1 x` denotes the creation of a set $\{x\}$ of size one.
- `2 x y` denotes the concatenation of disjoint sets $T_x, T_y$.
- `3 x y` means to translate a set that has already been constructed, i.e. $T_x+y$.

You need to make sure that all operations satisfy the requirements of the topic and that the last operation produces a set $T$.

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

- First operation: create the set $T_1=\{1\}$.
- Second operation: create the set $T_2=\{4\}$.
- Third operation: combine $T_1, T_2$ to get $T_3=\{1,4\}$. Fourth operation: create the set $T_3$.
- Fourth operation: translate $T_3$ by $1$ to get $T_4=\{2,5\}$.
- Fifth operation: combine $T_3, T_4$ to get $T_5=\{1,2,4,5\}$. This gives $T$.

The total cost of this program is $1 + 1 + 2 + 2 + 4 = 10$.

{{ s('hint') }}

If your time complexity is good, trust the time constant.
