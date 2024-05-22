{{ self.title() }}

{{ s('description') }}

The sea and the tides, the forest and the music. A quiet, peaceful town surrounded by mountains and water, where people rarely have to worry about what's broken in their homes because Kanan, the region's premier mechanic, is still young, but her skill and generosity of character have led to her receiving requests for repairs, and it's rumored that even the Demon King turns to her when he encounters a problem. When helping people with their repairs, Kanan comes into contact with a myriad of manuals. Some of these manuals have a strange folding structure, and Kanan unfolds them before repairing them in order to understand the structure of the machine, but folding them back to the original folds after repairing them is even more difficult than repairing the machine itself.

For a manual with all the folds parallel to each other, each fold can be numbered $1, 2, \cdots, N$ in the order in which the text on the manual is to be read, from top to bottom, and these $N$ folds divide the manual into $(N+1)$ strips of paper. Each crease may take one of two forms: either a vertical paper face protrudes inward, corresponding to folding the top and bottom halves of the paper forward, or a vertical paper face protrudes outward, corresponding to folding the top and bottom halves backward. Depending on the shape of the crease cross-section, lowercase `v` is used to denote inwardly projecting creases, and `^` (ASCII code $94$) is used to denote outwardly projecting creases, respectively. Assuming that all paper strips are of the same width, and that the instructions do not deform during the folding process, then the two sides of the paper can overlap after folding along a crease if and only if the two sides are opposite; that is, if the paper is folded along the $k$th crease, then for all positive integers $m$ that satisfy the requirement that $1\le k-m < k+m\le N$, the $(k-m)$th crease and the $( k+m)$ creases are of opposite shape. For example, an instruction manual with creases `v^v^^^^v` in order can be folded along its $7$th crease. By definition, an instruction sheet can always be folded along the first or last crease. The folded instruction manual can be represented by the crease on the side of the folded crease that has the greater number of remaining creases, e.g., `v^v^^^^v` is folded along the $7$th crease to obtain `v^v^^^`. If there are an equal number of creases on both sides of the folded crease, then it is fine to represent the folded paper by the creases on either side, since the creases are rotationally symmetric in three-dimensional space. In particular, after folding an instruction sheet with only one crease remaining, i.e., `v` or `^`, all $(N+1)$ strips of paper overlap, and the sheet is then said to be neatly folded.

Although folding each crease in sequence always results in a neat fold, Kanan feels that this is not aesthetically pleasing. An aesthetically pleasing fold should be made as few times as possible, and each fold should be as symmetrical as possible on both sides of the crease. Define the degree of asymmetry of a fold as the sum of the differences in the number of creases on either side of the folded crease each time it is folded. Given the folds of an instruction booklet, Kanan wants to know the minimum number of folds needed to fold the booklet neatly, and the minimum amount of asymmetry among all the folds with the fewest number of folds.

{{ s('input format') }}

{{ self.input_file() }}

The first line of the input contains a positive integer $N$ indicating the number of bars in the crease. It's guaranteed $1\le N\le 5000$.

The second line of the input contains a string $s$ representing each crease in order. It is guaranteed that $|s|=N$ and that $s$ consists only of `v` and `^`.

{{ s('output format') }}

{{ self.output_file() }}

The output is one line only and consists of two non-negative integers representing the minimum number of folds and the minimum degree of asymmetry subject to minimizing the number of folds, separated by a space.

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

If you first fold along the center crease, then the two sides of the paper coincide, at which point you can fold the instructions neatly by folding once more.

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ s('sample', 3) }}

{{ self.sample_text() }}

{{ s('sample', 4) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

For all data, it is guaranteed that $1\le N\le 5000$, $|s|=N$ and $s$ consists only of `v` and `^`.
