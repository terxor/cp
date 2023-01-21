---
layout: page
title: Atcoder - abc286
parent: Problem Solving
math: true
---

*[atcoder](http://atcoder.jp) beginner contest 286*

### Problem E

There are $N$ cities numbered $1$ to $N$. Each city has an artifact of value $a_i$
which is collected when that city is visited.

It is given for each pair of cities $(u, v)$ whether a flight is available directly
from city $u$ to city $v$.

There will be $Q$ queries of form $(u, v)$ where you should report the minimum
number of flights to reach $v$ from $u$ and the maximum value of artifacts collected.

Constraints:
- $1 \le N \le 300$
- $1 \le a_i \le 10^9$
- $1 \le Q \le N(N-1)$

**Solution**

Finding minimum number of flights is equivalent to finding shortest path.
But among all shortest paths, we need the one with maximum sum of $a_i$.

Since the queries can be for all pairs of vertices, we can use an all pairs shortest
path algorithm like Floyd-Warshall algorithm.

> Floyd-Warshall algorithm works on a simple invariant: on $k$-th iteration,
> we compute shortest paths between all pairs of vertices with intermediate
> vertices from set $\{1, 2, \ldots, k\}$. It runs in $O(n^3)$ in total.
> 
> Let $f(u, v, k)$ denote shortest path between $u$ and $v$ containing all intermediate
> vertices from $1$ to $k$. Then,
> 
> $$
> f(u, v, k) = \min{(f(u, v, k), f(u, k, k - 1) + f(k, v, k - 1))}
> $$

We can modify it to keep minimum path and maximum value.
We should compare minimize path length first and then maximize value
among paths of same length.

Also, be careful about not adding value of intermediate vertex twice.

*Tags: Graph, Shortest paths*

***

### Problem F 

*Interactive problem*

There is a hidden number $N$.

You first provide $M$ and a list of $M$ integers $a_1,\ldots,a_M$
such that $1 \le a_i \le M$.

The judge will then do the following:
- It will have a sequence $b$ of length $M$ such that $b_i = i$ for all $i$.
- For each $i$, it will do $N$ times:
  - $b_i \leftarrow b_{a_i}$

You will be given $b$ after this.

Find $N$.

Constraints:
- $1 \le N \le 10^9$
- $1 \le M \le 110$

**Solution**

The only information we get from $b$ is the cycle length in iterated
function $a$.

Suppose we have a cycle of length $x$ in $a$ at $i$.
Then, from $b_i$ we can infer $N \bmod x$.
We will infer the same piece of information from all elements in the cycle.

If we have independent cycles of length $x_1, x_2, \ldots, x_k$,
we can determine:

$$
r_1 = N \bmod x_1 \\
r_2 = N \bmod x_2 \\
\vdots \\
r_k = N \bmod x_k
$$

If $x_1,\ldots,x_k$ are pairwise coprime,
then we can think about *Chinese Remainder Theorem (CRT)*

We can find $N \bmod (x_1 x_2 \ldots x_k)$ by CRT.

But to find exact $N$, the product $x_1 x_2 \ldots x_k$ should be greater
than $N$.

We need to find $x_1, \ldots, x_k$ such that:
- $x_1 + \ldots + x_k \le M$
- $x_1 x_2 \ldots x_k \gt N$

We have to do some experiments.
- If we take first $9$ primes:
  - Sum is $100$
  - Product is around $2.2 \cdot 10^8$
- If we take first $10$ primes:
  - Sum is $129$
  - Product is around $6.4 \cdot 10^8$

But instead of adding last prime $29$, we can instead change
$2$ to $4$ and $3$ to $9$ (without changing the co-prime status)
to get a multiplier of $6$ for product and only adding $8$ to sum.

Hence, we can use $x = [4, 9, 5, 7, 11, 13, 17, 19, 23]$
which will give sum as $108$ and product around $1.33 \cdot 10^9$
which is well above bounds of $N$ in this problem.

> Note: For such interactive problems, it is always better
> to quickly code a local tester/judge. Otherwise, local
> testing might become difficult.

*Tags: Number theory, Shortest paths*

***