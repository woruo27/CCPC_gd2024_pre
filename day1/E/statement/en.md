{{ self.title() }}

{{ s('description') }}

The President of the `T` Association, Big `G`, decides to elect a little `G` to succeed him as President of the T Association. In order to ensure fairness, he appointed Junior `c` as a supervisor.

Considering that there are not too many little `g`'s in the `T` Association, little `c` decides to decide on the winner in the simplest way possible: the $n$ little `g`'s will play each other in a tie-breaker game, with the winner getting a point and the loser getting no points.

At the end of the game, when the scores are tallied, little `c` discovers the "$z$-`gg` law" about this $\frac{n(n-1)}{2}$ matchup, which is that among any $z+1$ little `g`, there always exists a little `g` that can defeat the remaining $z$ little `g`'s, and **at the same time** there exists another little `g` that is defeated by the remaining $z$ little `g`'s.

Due to some mysterious factor from the `T` Association, little `c` suddenly wonders how many different scores the $n$ little `g` **at least** scores in all the duels that fulfill the above "$z$-gg law"? Since little `c` is too (not) busy (very) with (smart) statistics, she decides to leave it to you to answer this question.

{{ s('input format') }}

{{ self.input_file() }}

**This problem has multiple sets of data.**

The first line contains an integer $T$ indicating the number of data sets.

The next $T$ rows, each with two positive integers $n,z$ are as described above.

{{ s('output format') }}

{{ self.output_file() }}

$T$ lines, one positive integer per line for the answer.

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

For $n=2, z=1$, it is clear that the two little `g` scores must be $1$ and $0$, so the answer is $2$.

For $n=3, z=1$, `1=>2, 2=>3, 3=>1` (`a=>b` means "a beats b", henceforth) satisfies the law and everyone scores $1$;

For $n=3, z=2$, by symmetry and the $z$-`gg` law, let `1` and `3` be the winners and losers of the three little `g`, then the game must be `1=>2, 1=>3, 2=>3`, and the score of each of the three players is $2, 1, 0$, so the answer is $3$.

For $n=4, z=1$, consider `1=>3, 1=>4, 2=>1, 2=>3, 3=>4, 4=>2`, the scores of the four players are $2, 2, 1, 1$, and since the sum of the scores of the four players, $\frac{4\times 3}{2}=6$, is not a multiple of $4$, the scores of the four players can't be exactly the same, and so the answer is $2$.

For $n=4, z=3$, let the winners and losers be `1` and `4`, then the sum of the scores of `2` and `3` is $6 - 3 - 0 = 3$, so the scores of these two players can only be $2, 1$ or $3, 0$; it is obviously impossible for two players to score $3$ at the same time, so the scores of `2` and `3` must be $2, 1$, and the answer is $4$.

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ s('数据范围') }}

For all data, there are $1\le T\le 3\times 10^5, 1\le z<n\le 10^{18}$.

{{ s('hint') }}

This problem is not difficult.

