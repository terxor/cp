---
layout: page
title: Atcoder - abc126
parent: Problem Solving
math: true
---

*Source of these problems is ABC126 from [atcoder](http://atcoder.jp)*

### Problem D

You are given a tree with $N$ vertices. Edges have
integer weights. Color each vertex either black or white
such that the following condition is satisfied.

Condition: For any two vertices of same color, the
the length of the path between them is even.

We have $1 \le N \le 10^5$, $1 \le w_i \le 10^9$ 
where $w_i$ is the weight of edge $i$.

**Solution**

Consider an arbitrary vertex $r$ as the root.
Let $d(x)$ be the distance of vertex $x$ from the root.
A vertex $u$ is colored as:
- If $d(u)$ is even, color it white.
- If $d(u)$ is odd, color it black.

In other words, vertices whose distances have
same parity are assigned same colors.

We now show that the coloring obtained satisfies the
given condition.

Consider any two same colored vertices $u$ and $v$.
Let their lowest common ancestor be $w$. It is possible 
that $w = u$ or $w = v$. 
The distance between $u$ and $v$ is given by
$D = d(u) - d(w) + d(v) - d(w)$ since $w$ is their LCA
(read about lowest common ancestor for details).

$D = d(u) + d(v) - 2d(w)$

$d(u)$ and $d(v)$ have same parity, hence their sum
will be even (say $2k$)

$D = 2k - 2d(w)$

$D = 2(k - d(w))$

Hence $D$ is even.

***

### Problem E

You are given $N$ cards numbered $1$ to $N$. Each card has some value
which is not known to you. However, you know that
each value is either $0$ or $1$. Also, you are given
$M$ relations in form of $(u, v, w)$ meaning cards $u$
and $v$ have same value if $w = 1$, have different value
if $w = 0$.

You can perform a magic operation which will directly
reveal the value of a card.

Find the minimum number of magic operations required
to find values of all the cards.

We have $1 \le N, M \le 10^5$.

**Solution**

Cards can be assumed as vertices and the relations
as undirected edges between them.

If there are two cards with a sequence of relations
connecting them, then we only need to know one of them and we can
determine the other one by the relations.

Thus, we need to find the number of connected components
in the undirected graph formed. The number of connected
components is the answer.

***

### Problem F

Construct a sequence $a$ = $<a_1,\ldots,a_{2^M+1}>$ which satisfies
the following conditions, if such sequence exists.
- Every integer between $0$ and $2^M-1$ (inclusive) occurs twice in $a$.
- For any $i$ and $j$ ($i < j$) such that $a_i = a_j$, the formula
$a_i \oplus \ldots \oplus a_j = K$ holds.

Note: $\oplus$ represents bitwise XOR operation.

We have $0 \le M \le 17$ and $0 \le K \le 10^9$.

**Solution**

First of all, for $K \ge 2^M$ there can't exist such sequence because
we can never get a bit $1$ at any index $i \ge M$ by XORing any sequence
of elements in the given range.

We will analyse $M=0$ and $M=1$ separately.

For $M=0$, the only valid value of $K$ is $0$. We obtain a sequence $<0, 0>$
for the answer.

For $M=1$, the valid values of $K$ are $0, 1$. If $K=0$ we can use sequence
$<0,0,1,1>$ for the answer. If $K=1$, there can't exist any sequence (this can
be easily observed).

For $M \ge 2$, it holds that $0 \oplus 1 \oplus \ldots \oplus (2^M-1) = 0$

A simple explanation for this is: the integers $0,\ldots,2^M-1$ represent
all subsets of a set of size $M$ when viewed as bitmasks. By symmetry,
a bit at index $i$ is $1$ in $2^{M-1}$ subsets.
Since $M \ge 2$, we have $2^{M-1} \ge 2$. Thus, XOR at any bit will evaluate
to $0$ because of even number of $1$s.

We already have $K \le 2^M-1$. Let $b$ be a sequence of length $2^M-1$ 
containing $0,1,\ldots,2^M-1$ except for $K$. Let $X$ be the XOR of all 
elements of $b$. We have:

$0 \oplus 1 \oplus \ldots \oplus (2^M-1) = 0$

$\Rightarrow K \oplus X = 0$

$\Rightarrow K = X$

Thus, we can use $<b', K, b, K>$ as the answer. $b'$ represents $b$ reversed.
It is fairly obvious why the conditions hold.

***

*That is it.*