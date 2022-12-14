---
layout: page
title: Atcoder - abc127
parent: Problem Solving
math: true
---

*Source of these problems is ABC127 from [atcoder](http://atcoder.jp)*

### Problem E

There is a grid of squares of $N$ rows and $M$ columns.
Let $(i, j)$ denote the square on $i$-th row and $j$-th column.
There are $K$ pieces. We will choose $K$ squares
$(x_1,y_1),\ldots,(x_K,y_K)$ and place one
piece on each square. Cost of this arrangement is:

$$
\sum_{i = 1}^{K-1}
\sum_{j = i+1}^{K}
( \vert x_i - x_j \vert + \vert y_i - y_j \vert )
$$

Compute the sum of costs of all possible arrangements.

Two arrangements are considered different if and
only if there is a square that contains a piece in
one of the arrangement but not in the other.

We have:
- $2 \le N \cdot M \le 2 \cdot 10^5$
- $2 \le K \le N \cdot M$

**Solution**

Let us fix two pieces on squares $(r_1, c_1)$ and
$(r_2, c_2)$. Number of arrangements in which 
these two pieces are fixed are
$X = {NM-2 \choose K-2}$ (we have to choose $K-2$ pieces because $2$ are already placed)

Let $f(p, q) = \vert p_x - q_x \vert + \vert p_y - q_y \vert$
for any two squares $p = (p_x, p_y)$ and $q = (q_x, q_y)$.

Let $Y$ be the sum of $f(p, q)$ over all possible squares $p, q$ ($p \neq q$).
For convenience we will also consider $p, q$ where $p=q$ 
since $f(p, p) = 0$ thus having no effect on $Y$. To compute $Y$ we will 
consider all possible pairs, i.e, $N^2M^2$ pairs of squares.
Also, we can separate the terms for row and columns. We have:

$$
Y =
M^2 \left(\sum_{1 \le i,j \le N}{\vert i - j \vert}\right) +
N^2 \left(\sum_{1 \le i,j \le M}{\vert i - j \vert}\right)
$$

Then the answer is $\frac{XY}{2}$ since $f(p,q) = f(q,p)$ causing
cost for each pair of squares to be added twice.

Let us define $g$ for convenience

$$
g(T) = \sum_{1 \le i < j \le T}{(j - i)}
$$

Observe that:

$$
\left(\sum_{1 \le i,j \le T}{\vert i - j \vert}\right)
= 2 g(T)
$$

Then, we have:

$$
Y = 2 M^2 g(N) + 2 N^2 g(M)
$$

$$
\frac{XY}{2} = {NM-2 \choose K-2} (M^2 g(N) + N^2 g(M))
$$

Note that $g(N)$ can be computed in $O(N)$. Thus, $g(N)$ and $g(M)$
can be computed in $O(N+M)$.


***

### Problem F

You are given a function $f(x)$ which is initially $f(x) = 0$. 

You have to process $Q$ queries of the form:
- Update query `1 a b`: Let $g(x) = f(x) + \vert{x-a}\vert + b$. Replace
$f(x)$ by $g(x)$.
- Evaluation query `2`: Print the minimum value of $f(x)$ and the minimum
such $x$ for which get this value.

We have:
- $1 \le Q \le 10^5$
- $-10^9 \le a,b \le 10^9$
- First query is an update query

It can be proved that the output values are always integers.

**Solution**

After $K$ update queries $(a_1, b_1),\ldots,(a_K,b_K)$
we have:

$$
f(x) = \vert{x-a_1}\vert + \ldots + \vert{x-a_K}\vert + B
$$

where $B = b_1 + \ldots + b_K$. We may ignore $B$ in further
discussion since it is a constant.

First, we review the piecewise definition of $\vert{x-a}\vert$.

$$
\vert{x-a}\vert = 
\begin{cases}
a - x & x < a \\
0 & x = a \\
x - a & x > a
\end{cases}
$$

It may be noted that $\vert{x-a}\vert$ is continous.
Sum of continuous functions is also continous. Thus, $f(x)$ is
a continuous function.

For $x \in (-\infty,a_1]$, we have:

$$
f(x) = (a_1 + \ldots + a_K) - Kx
$$

$f(x)$ is decreasing in this range.

For $x \in [a_K,\infty)$, we have:

$$
f(x) = Kx - (a_1 + \ldots + a_K)
$$

$f(x)$ is increasing in this range.

For $x \in [a_i,a_{i+1}]$ ($1 \le i < K$), we have:

$$
f(x) = (x - a_1) + \ldots + (x - a_i) + (a_{i+1} - x) + \ldots + (a_K - x)
$$

Rearranging terms:

$$
f(x) = (2i - K)x - (a_1 + \ldots + a_i) + (a_{i+1} + \ldots + a_K)
$$

$f(x)$ will be increasing/decreasing based on interval $i$ ($[a_i,a_{i+1}]$).

$f(x)$ will be decreasing when $2i - K < 0$ i.e, $i < \frac{K}{2}$.
Let $P = \lceil\frac{K}{2}\rceil$. We have $P - 1 < \frac{K}{2}$.
Thus, $f(x)$ is decreasing for $i=1,\ldots,P-1$.
We already have $f(x)$ decreasing in range $(-\infty, a_1]$. Since
$f(x)$ is continuous, $f(x)$ is decreasing in interval $(-\infty,a_{P}]$

Similarly, $f(x)$ will be increasing when $2i - K > 0$ i.e, $i > \frac{K}{2}$.
Let $Q = \lfloor\frac{K}{2}\rfloor$. We have $Q + 1 > \frac{K}{2}$.
Thus, $f(x)$ is increasing for $i=Q+1,\ldots,K-1$.
We already have $f(x)$ increasing in range $[a_K,\infty)$. Since
$f(x)$ is continuous, $f(x)$ is increasing in interval $[a_{Q+1},\infty)$.

$f(x)$ will be constant when $2i - K = 0$ i.e, $i = \frac{K}{2}$. This
is possible when $K$ is even. In that case $P = Q$ and $f(x)$ will have
minimum (and constant) value in interval $[a_P,a_{P+1}]$.

If $K$ is odd, $P = Q+1$ thus we will have $f(x)$ decreasing in 
$(-\infty,a_P]$ and increasing in $[a_P,\infty)$. It is obvious
that minimum value of $f(x)$ occurs at $x = a_P$.

We summarize the solution:
- Let $P = \lceil\frac{K}{2}\rceil$
- Output $f(x)$ for $x = a_P$.

Thus, we need to maintain median and sum of lower and upper
half of a sorted sequence (with insertions) in an efficient manner. One way to do is
by using a min-heap for upper half and max-heap for lower half.


***

*That is it.*
