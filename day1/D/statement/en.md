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

The first line of the input contains two positive integers $n$ and $q$ ($2\le n\le 10^5$; $1\le q\le 10^5$), representing the number of vertices in the network $T$ and the number of requests.

Each of the next $n$ lines contains two nonnegative integers $f_i$, $t_i$ and a string $s_i$, separated by a space character, describing the $i$-th vertex of $T$. If $f_i>0$, it represents the parent of $i$ in $T$; otherwise $f_i = 0$, which means $i$ is the root of $T$. $t_i \in \{0, 1\}$ indicates whether the vertex $i$ is a leaf,

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

To better demonstrate the problem, real-world telephone numbers are adopted in this sample. The corresponding telephone network $T$ is shown in the following graph.

{{ img('sample1_en.png', size = 0.25, align = 'middle', inline = False, caption='The Telephone Network Represented by Sample 1.', label='fig:sample') }}

- The first query is from School of Computer Science, Peking University to Logistics Integrated Service Platform / Comprehensive Service Hotline, Tsinghua University. Since the two vertices share the parent vertex $3$ (which represents Beijing), and $d_3 = \varepsilon$, one can dial the original telephone number directly. The second query is the same as the first one, except the area codes are appended before the telephone number, and it is considered invalid to add area codes when unnecessary in this problem.

- The fourth query is made from the Hong Kong University of Science and Technology (Guangzhou) to the admission office of Tsinghua University. Since their parents are different, a prefix $b_9 + d_2 + c_3=$ `010` is adopted for dialing. The third query is similar to the fourth one, but without the prefix, which means the call would not get through.

- The fifth query is a call from the Chinese Computer Federation to Computer Academy of Guangdong, and the telephone number to be dial is computer by $b_3 + d_2 + c_9 + a_{11}$。

- The sixth query is calling the Department of Computer Science and Engineering of the Hong Kong University of Science and Technology from the Hong Kong University of Science and Technology (Guangzhou). When calling, the international direct dial code of mainland China, `00`, and the international subscriber dialing code of Hong Kong, China, `852` should be pressed in order first, before entering the original telephone number $a_{13}$ (the full expression of calculating the entire number is $b_9 + b_2 + d_1 + c_{12} + a_{13}$).

- The seventh query is dialing from the Department of Computer Science, Graduate School of Information Science and Technology, Tokyo University to the admission office of the same graduate school. When using the internal telephone line inside the Hongo campus, a prefix $d_{16} = $ `2` is necessary before the $4$ digit number, so the entire telephone number is `2` $+$ `7926` $=$ `27926`.

- The eighth query is the Department of Computer Science, Graduate School of Information Science and Technology, Tokyo University calling the Graduate School of Information Science and Technology, Osaka University. When calling across cities in Japan, the desired prefix can be obtained by concatenating the long-distance trunk $d_{14}=$ `0`, the area code for Osaka $c_{19}=$ `6`, a secondary area code for the secondary area to which the Suita campus belongs $c_{20}=$ `6879`. The entire telephone number can be derived by $b_{16}+b_{15}+d_{14}+c_{19}+c_{20}+a_{21}$.

- The ninth query is making a call from the Graduate School of Information Science and Technology, Osaka University to the Graduate School of Frontier Biosciences which is also located in the Suita campus. Since $d_{20}=\varepsilon$, dialing using the internal telephone line of the Suita campus requires no prefix, which means dialing the corresponding $4$ digit number is sufficient.

- The tenth query is a call to the Department of Information and Computer Science of Osaka University, made by the Graduate School of Information Science and Technology. Since the undergraduate department is located in Toyonaka campus instead of Suita campus, the secondary area code to which the Toyonaka campus belongs, $c_{23}=$ `6850`, is necessary when calling (or actually you may use the prefix of the internal telephone line to Toyonaka campus, which is `172`, but not available in this problem).

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

Dialing `0100` from any terminal within the subtree of vertex $2$ matches vertex $3$ and vertex $5$, while dialing `0101` matches vertex $4$ and vertex $6$. Since a telephone number dialed from a terminal cannot match the terminal itself, only the second and the sixth queries correspond to exactly one terminal.

{{ s('sample', 3) }}

{{ self.sample_file() }}