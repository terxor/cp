---
layout: page
title: Codeforces - misc. (2)
parent: Problem Solving
math: true
---

*Source of these problems is [codeforces](http://codeforces.com)*

### Problem 1612D

*X-Magic Pair*

Given integers $a, b, x$, the following operations can be performed any number of times
1. $a \leftarrow \vert a - b \vert$
1. $b \leftarrow \vert a - b \vert$

Find if it is possible to make $a = x$
or $b = x$.

Constraints:
- $1 \le a, b, x \le 10^{18}$

**Solution**

Let's denote the state with $(p, q)$.
Initially the state is $(a, b)$.
Since $a, b$ are symmetric (operation wise), $(p, q) \equiv (q, p)$.

We want to reach a state where $p = x$ or $q = x$

Assume $p \le q$. We have the following transitions:
1. $(p, q) \rightarrow (q - p, q)$
1. $(p, q) \rightarrow (p, q - p)$

Exploring further in transition 1:
- $(q - p, q) \rightarrow (p, q)$
- $(q - p, q) \rightarrow (p, q - p)$

It is evident that transition 1 is not useful because it only leads to
the original state and the state reached by second transition $(p, q - p)$.
Furthermore it offers no unique value as $q$ is already known in original state and $q - p$ will
be reached by transition 2.

Now we can simplify the transitions:
- $(p, q) \rightarrow (p, q - p) \rightarrow (p, q - 2p) \cdots \rightarrow (p, q - kp)$

where $k = \lfloor \frac{q}{p} \rfloor$.
This can be compacted (operation wise) to:
- $(p, q) \rightarrow (p, q \pmod p)$

Checking if $x$ occurs in this transition chain is simple
and can be done in $O(1)$.

Number of transitions before reaching $p = 0$ or $q = 0$
are small enough (at most $\lg(10^{18})$).

***

### Problem 1542C

*Strange Function*

Define $f(x)$ as minimum positive integer which doesn't
divide $x$ ($x \ge 1$).

Given $N$ and $M$, find $f(1) + f(2) + \ldots + f(N) \pmod M$

Constraints:
- $1 \le N \le 10^{16}$
- $M = 10^9 + 7$

**Solution**

Let $x$ be written as power of primes:

$x = p_1^{k_1} \cdot p_2^{k_2} \ldots p_n^{k_n}$
where $p_1 \lt \ldots \lt p_n$.

Let $f(x) = y$

Then, $y$ must have a prime factor with power greater
than that in $x$ or having a prime factor which is not in $x$.

A sufficient condition is having only one such prime factor.
That is minimum of:
- $y = \min \left( p_i^{k_i + 1} \right)$
- $y = p'$ (a prime not present in $x$)
  - This will be the smallest prime not present in $x$

We now show that smallest prime not present in $x$ is a small
prime with the given constraints. If it is the $K$-th prime in
the list of sorted primes, then all primes before that will be present in $x$.
That is: $x \ge P_1 \cdot P_2 \ldots P_{K-1}$.
With maximum $x = 10^{16}$ we can use a loose upper bound for $K$ as $K \le 40$.

But computing $f(x)$ individually is still not feasible.
Let's analyse the possible values of $f(1), \ldots, f(n)$.
These can be:
- $\{ P_i^1, \ldots,P_i^{t} \}$ where $1 \le i \lt K$ and $P_i^{t} \le n$.

This is still a small set of values which gives us a 
possibility to check for each value how many times it will
occur in $f(1), \ldots, f(n)$.

$f(x) = P_i^t$ when $P_1,\ldots,P_i$  occur in factorization of $x$ with the constraint
that $P_i$ occurs exactly $t-1$ times. Thus,

$$
x = c \left( P_1 \cdot P_2 \cdot \ldots \cdot P_{i-1} \cdot P_i^{t-1} \right)
$$

for all $c$, $c \ge 1$ and $P_i \nmid c$.

Finding the number of $x$ satisfying the above in range $[1, N]$ is trivial.

***