{{ self.title() }}

{{ s('description') }}

Ivan is practicing Chinese calligraphy, but when he opens the blank paper, he finds that he had previously bored himself by coloring $n$ line segments black on the paper, while the rest of the paper is white.

These $n$ black line segments are either horizontal or vertical: with the center of the blank paper as the origin, construct the $x$-axis parallel to one edge of the paper and the $y$-axis parallel to the other edge. Then each black line segment with two endpoints $(x_1, y_1)$ and $(x_2, y_2)$ satisfies: exactly one of $x_1 = x_2$ and $y_1 = y_2$ holds true. Additionally, any two horizontal line segments do not intersect, and any two vertical line segments do not intersect.

Although the black line segments frustrates Ivan, he discovers that these black line segments formed several field grids, and he could practice Chinese calligraphy on these field grids.

A field grid can be described by a triplet $(x_0, y_0, d)$. A triplet $(x_0, y_0, d)$ represents a field grid if and only if all the following conditions are met:

- $x_0, y_0 \in \mathbb{R}$, $d \in \mathbb{R}^+$;
- Let $R = [x_0-d,x_0+d] \times [y_0-d,y_0+d]$, representing all points with $x$-coordinates in $[x_0-d,x_0+d]$ and $y$-coordinates in $[y_0-d,y_0+d]$. Then the black part of $R$ precisely forms six line segments, and these six line segments are the intersections of six lines $x=x_0-d,x=x_0,x=x_0+d,y=y_0-d,y=y_0,y=y_0+d$ with $R$.

Ivan wants to calculate how many field grids there are on the blank paper, that is, how many triplets $(x_0,y_0,d)$ satisfy the above conditions. But as usual, Ivan won't do the calculations himself, so he delegates this task to you.

{{ s('input format') }}

{{ self.input_file() }}

The first line contains a single integer $n (1 \le n \le 3 \times 10^5)$ — the number of line segments.

In the next $n$ lines, $i$-th line contains four integers $x_1,y_1,x_2,y_2 (-10^9 \le x_1 \le x_2 \le 10^9, -10^9 \le y_1 \le y_2 \le 10^9)$ — the two endpoints of one line segment.

It is guaranteed that, exactly one of $x_1 = x_2$ and $y_1 = y_2$ holds true for each line segment. Additionally, any two line segments with $x_1 = x_2$ do not intersect, and any two line segments with $y_1 = y_2$ do not intersect.

{{ s('output format') }}

{{ self.output_file() }}

Print a single integer, the number of field patterns.

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

{{ img('pic.png', size = 0.5, align = 'middle', inline = False, label='fig:sample') }}

As shown in the picture above, $(5, 5, 5), (5, 0, 5), (5, -5, 5)$ are all three field patterns. The following triplets are not field patterns: 

- $(0, 0, 10)$, since there are other black points besides the six required segments;
- $(-5, 5, 5)$, since the intersection of the square and $x=-5$ is not black.