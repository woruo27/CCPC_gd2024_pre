{{ self.title() }}

{{ s('description') }}

Recently, a new pizza shop opened on Universe North Street. Most pizzas served in this shop are using lap cheong (a kind of Chinese sausages), so customers would like to call this shop "Lap Cheong Pizza Shop". This combination of western cuisine and Chinese cuisine sounds contradictory. However, everyone who has ever tasted this special pizza appreciates it, making its reputation spread quickly among people.

Besides the specialized ingredients, this Lap Cheong Pizza Shop also attracts potential customers by its free Wi-Fi, or more precisely, the password of its free Wi-Fi. The menu says: "The password of the Wi-Fi covering this shop is:

$$
\sum_{i=1}^L \sum_{j=1}^L C^{\left|LCPS\left(s_i, s_j\right)\right|} \bmod{P},
$$

where $LCPS\left(s_i, s_j\right)$ denotes the Longest Common Prefix-Suffix of strings $s_i$ and $s_j$， which means the longest string (could be an empty string or the entire $s_i$ or $s_j$ if possible) that is a prefix of $s_i$, and a suffix of $s_j$. The strings $s_1, \cdots, s_L$ are changed daily, and only provided after ordering. Everyday, one lucky person among the first 100 customers who successfully connected to the Wi-Fi will be chosen for free order."

You plan to have a party with you friends at this shop next week, so you want to design an algorithm that can work out the password efficiently.

{{ s('input format') }}

{{ self.input_file() }}

The first line of input contains three positive integers $L, C, P$ ($1\le L\le 3\times 10^6$, $2\le C < P < 2^{30}$) representing the number of strings, the base and the modulus.

Each of the next $L$ lines contains a single string $s_i$, consisting of only lower-case letters. It is guaranteed that $1\le \left|s_i\right| \le 3\times 10^6$, $\sum_{i=1}^L \left|s_i\right| \le 3\times 10^6$.

{{ s('output format') }}

{{ self.output_file() }}

Output a nonnegative integer representing the password to the Wi-Fi of this Lap Cheong Pizza Shop.

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

For all $1\le i,j\le 4, i\ne j$,

- $LCPS($ `pizza` $,$ `shop` $ )=LCPS($ `piazza` $,$ `shop` $)=LCPS($ `pizzala` $,$ `shop` $)=$ `p`;

- $LCPS($ `pizzala` $,$ `pizza` $)=$ `pizza`;

- for any other pairs, $LCPS\left(s_i, s_j\right)=\varepsilon$.

Thus, the corresponding Wi-Fi password should be:

$$
2^4 + 2^0 + 2^0 + 2^0 + 2^1 + 2^5 + 2^0 + 2^0 + 2^1 + 2^0 + 2^6 + 2^0 + 2^1 + 2^5 + 2^0 + 2^7 = 286.
$$

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ s('hint') }}

The Lap Cheong Pizza Shop uses highly confidential recipes for their pizzas. Please do not imitate on your own.