{{ self.title() }}

{{ s('description') }}

宇宙北大街上新开了一家披萨店。这家披萨店主打使用腊肠的披萨，被顾客亲切地称为“腊肠披萨店”。这种中西合璧的做法听上去很离经叛道，但是品尝过腊肠披萨的顾客都对其称赞有加，吸引了众多食客蜂拥而至。

除了配料极具特色，腊肠披萨店的 Wi-Fi 密码也是它的流量密码。菜单上写着：“本店的 Wi-Fi 密码是

$$
\sum_{i=1}^L \sum_{j=1}^L C^{\left|LCPS\left(s_i, s_j\right)\right|} \bmod{P},
$$

其中 $LCPS\left(s_i, s_j\right)$ 表示 $s_i$ 和 $s_j$ 的最长公共前后缀，即最长的同时是 $s_i$ 前缀和 $s_j$ 后缀的字符串（可能为空，也可能为整个串）；每天的 $s_1,\cdots,s_L$ 都不一样，服务员会在点餐后提供用于当天的 Wi-Fi 密码的字符串。每天将会从前 100 名连上 Wi-Fi 的顾客中随机抽取一位免单。”

你计划下周和朋友一起来这家店聚餐，因此你想设计一个算法，快速求出这家店的 Wi-Fi 密码。

{{ s('input format') }}

{{ self.input_file() }}

输入的第一行包含三个正整数 $L, C, P$，表示字符串的数量、底数及模数。保证 $1\le L\le 10^6$，$2\le C<P<2^{30}$。

接下来 $L$ 行，每行输入一个仅由小写字符构成的字符串 $s_i$。保证 $1\le \left|s_i\right| \le 10^6$，$\sum_{i=1}^L \left|s_i\right| \le 10^6$。

{{ s('output format') }}

{{ self.output_file() }}

输出一个非负整数，表示腊肠披萨店的 Wi-Fi 密码。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

对于 $1\le i,j\le 4, i\ne j$，

- $LCPS($ `pizza` $,$ `shop` $ )=LCPS($ `piazza` $,$ `shop` $)=LCPS($ `pizzala` $,$ `shop` $)=$ `p`；

- $LCPS($ `pizzala` $,$ `pizza` $)=$ `pizza`；

- 其余的 $LCPS\left(s_i, s_j\right)=\varepsilon$。

因此对应的 Wi-Fi 密码为 
$$
2^4 + 2^0 + 2^0 + 2^0 + 2^1 + 2^5 + 2^0 + 2^0 + 2^1 + 2^0 + 2^6 + 2^0 + 2^1 + 2^5 + 2^0 + 2^7 = 286.
$$

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

对于所有数据，保证 $1\le L\le 10^6$，$2\le C<P<2^{30}$，所有 $s_i$ 仅由小写字母组成，$1\le \left|s_i\right|\le 10^6$，且 $\sum_{i=1}^L \left|s_i\right|\le 10^6$。

{{ s('hint') }}

腊肠披萨店在制作披萨时使用了绝密配方。在没有专业人士指导的情况下，请不要轻易模仿。