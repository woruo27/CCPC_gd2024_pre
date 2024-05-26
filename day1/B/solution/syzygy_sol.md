先考虑在恒星同一侧连成一线的情况。对于给定的周期集合 $S$，可以证明会合周期（从上一次连成一条线到下一次连成一条线之间的时间间隔）为

$$
T(S)=\frac{\mathrm{lcm}\{x|x\in S\}}{\gcd\{\left|x-y\right||x,y\in S, x\ne y\}}
$$

可以这么理解这个公式：以恒星为参考系，$S$ 所对应的行星每次会合在同一个方向上的周期为 $\mathrm{lcm}\{x|x\in S\}$，而在这段时间中，可能相会的地方恰有 $\gcd$ 处。

同理可以得出，如果允许在不同侧连成一线，会合周期为上式给出的时间的一半。故在连续的 $\mathrm{lcm}\{t_1,\cdots,t_n\}$ 时间内，$S$ 在同一条线上的次数为

$$
f(S)=\frac{2\cdot\mathrm{lcm}\{t_1,\cdots,t_n\}}{T(S)}
$$

而恰好只有 $S$ 在一条线上的次数为

$$
g(S)=f(S)-\sum_{S\subset T\subseteq U}g(T)
$$

前(hou)缀作差即可。复杂度不超过 $O\left(2^n(n+\log t_i)\right)$。
