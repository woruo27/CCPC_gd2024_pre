{{ self.title() }}

{{ s('description') }}

Represent a simplified telephone network using a rooted tree $T$. In tree $T$, each leaf represents a specific telephone terminal, while each inner vertex represents a switching node capable of processing dialing requests. Each telephone terminal has its own telephone number $a_i$. However, in order that the switching nodes can process the dialing requests correctly, different types of prefixes are introduced to indicate the locations of the caller and callee within the network. For example, calling a landline in Beijing from elsewhere in mainland China requires a long-distance trunk prefix `0`, and the area code of Beijing `10` added in order before the original telephone number. In the tree $T$, the correct entire telephone number of a terminal $u$ calling another terminal $v$ is defined by connecting corresponding prefixes of all the switching nodes along the shortest path from $u$ to $v$ on $T$ in order (which means the prefix of the vertex closest to $u$ should appear at the beginning, while the prefix of the vertex closest to $v$ at the end), and adding all the prefixes before the original number of $v$.

In tree $T$, there are $3$ different types of prefixes (which could be empty), according to the relationships between the terminal sending the request, the desired terminal, and the current switching node:

- A prefix $b_v$ that is used when calling from inside the subtree of $v$ to outside the subtree of $v$. For example, if calling from mainland China to other countries or regions, an international call prefix, or an international direct dial code (IDD code) of `00` is required.

- A prefix $c_v$ that is used when calling from outside the subtree of $v$ to inside the subtree of $v$. For example, when calling from other countries or regions to mainland China, a country calling code, or an international subscriber dialing (ISD) code of `86` is applied.

- A prefix $d_v$ that is used when calling from any of its child to another child, where both children can be either a terminal or another switching node. For example, if calling from other regions in mainland China to a landline `ABCDEFGH` in Beijing, the correct number is `010`-`ABCDEFGH`, where the first `0` is the long-distance trunk prefix; however, if calling from other countries or regions, the correct number would be `+86`-`10`-`ABCDEFGH`, without the long-distance trunk prefix `0`.

Given several dialing requests within $T$, each of which consists of a vertex dialing out, and a number this terminal dials. Please determine if the number corresponds to exactly one terminal. If so, please also solve for the specific terminal; otherwise, please solve for the number of terminals matching this telephone number.

{{ s('input format') }}

{{ self.input_file() }}

The first line of the input contains two positive integers $n$ and $q$ ($2\le n\le 2\times 10^5$; $1\le q\le 2\times 10^5$), representing the number of vertices in the network $T$ and the number of requests.

Each of the next $n$ lines contains two nonnegative integers $f_i$, $t_i$ and a string $s_i$, separated by a space character, describing the $i$-th vertex of $T$. If $f_i>0$, it represents the father of $i$ in $T$; otherwise $f_i = 0$, which means $i$ is the root of $T$. $t_i \in \{0, 1\}$ indicates whether the vertex $i$ is a leaf,

- if $t_i = 1$, then the vertex $i$ is a leaf, and $s_i$ should be a nonempty string consisting of only digit characters (from `0` to `9`), representing the original telephone number of vertex $i$, which is $a_i$;

- if $t_i = 0$, then the vertex $i$ is a switching node, and $s_i$ should contain three strings $b_i, c_i, d_i$ (which could be empty), separated by a single `/` character.

It is guaranteed that $0\le f_i < i$, and the total length of all $a_i$'s of leaves and all $b_i$'s, $c_i$'s and $d_i$'s of switching nodes does not exceed $3\times 10^6$.

Each of the last $q$ lines contain a positive integer $p_i$ and a nonempty string $r_i$ only consisting of digit characters (`0` to `9`), representing a dialing request from vertex $p_i$ and with the number dialed being $r_i$. It is guaranteed that $p_i$ is always a leaf, and $\sum_{i=1}^q \left|r_i\right| \le 3\times10^6$.

{{ s('output format') }}

{{ self.output_file() }}

For each request, output a single line. If the telephone number corresponds to a single terminal, output `1 x` where the positive integer $x$ is the index of the terminal dialed; otherwise, output `0 y`, where $y$ is a nonnegative integer representing the number of terminals matching the telephone number.

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

为方便理解题意，该样例使用了实际存在的电话号码。其表示的电话网络见下图。

{{ img('sample1.png', size = 0.5, align = 'middle', inline = False, caption='样例 1 表示的电话网络', label='fig:sample') }}

- 第一个询问的通话请求是从北京大学计算机学院至清华大学后勤综合服务热线/校内查号台。因为这两个结点的父结点均为结点 $3$（对应北京市），且父结点 $d_3=\varepsilon$，所以直接拨打对应电话即可。第二个询问为第一个询问加上区号的版本，在本题中认为该询问的电话号码无法拨通。

- 第四个询问为香港科技大学（广州）向清华大学招生办公室发出通话请求。由于两个通话终端的父结点不同，拨打电话时应加上前缀 $b_9 + d_2 + c_3=$ `010`。第三个询问与第四个询问类似，但是没有加上前缀，故无法拨通。

- 第五个询问为中国计算机学会致电广东省计算机学会，计算应拨打电话号码的方式为 $b_3 + d_2 + c_9 + a_{11}$。

- 第六个询问为从香港科技大学（广州）向香港科技大学计算机科学与工程系（Department of Computer Science and Engineering）发出通话请求。拨打电话时，应先按顺序拨打中国大陆的国际冠码 $b_2=$ `00` 和中国香港的国际区码 $c_{12}=$ `852`，然后再键入原始电话号码 $a_{13}$（完整的计算方法为 $b_9 + b_2 + d_1 + c_{12} + a_{13}$）。

- 第七个询问为从东京大学研究生院计算机科学专业办公室拨至情报理工学系研究科招生办公室。由于本乡校区的内部电话需要在 $4$ 位电话之前加上 $d_{16}=$ `2`，正确的电话号码为 `2` $+$ `7926` $=$ `27926`。

- 第八个询问为东京大学研究生院计算机科学专业办公室向大阪大学研究生院信息科学研究科办公室拨打电话。拨打电话时，应先后加上长途冠码 $d_{14}=$ `0`、大阪的区号（市外局番）$c_{19}=$ `6` 和吹田校区所属的子区域区号（市内局番）$c_{20}=$ `6879`。应拨打的电话号码的完整表达式为 $b_{16}+b_{15}+d_{14}+c_{19}+c_{20}+a_{21}$。

- 第九个询问为从大阪大学研究生院信息科学研究科办公室拨打电话给同样位于吹田校区的生命机能研究科。$d_{20}=\varepsilon$ 意味着吹田校区的内部电话不需要加前缀，可以直接拨打对应 $4$ 位电话号码。

- 第十个询问为从大阪大学研究生院信息科学研究科办公室向大阪大学信息科学系的办公室拨打电话。由于本科的信息科学系位于丰中校区，所以需要在原始电话号码前加上丰中校区对应的子区域区号（市内局番）$c_{23}=$ `6850`（实际拨打电话时，也可以使用丰中校区的内部电话前缀 `172`，但这不在本题考虑范围之内）。

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

Dialing `0100` from any terminal within the subtree of vertex $2$ matches vertex $3$ and vertex $5$, while dialing `0101` matches vertex $4$ and vertex $6$. Since a telephone number dialed from a terminal cannot match the terminal itself, only the second and the sixth queries correspond to exactly one terminal.

{{ s('sample', 3) }}

{{ self.sample_file() }}