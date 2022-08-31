---
layout: page
title: Atcoder - abc266
parent: Problem Solving
math: true
---

*Source of these problems is ABC266 from [atcoder](http://atcoder.jp)*

### Problem E

There is a game using a 6-sided die having numbers 1 to 6.
You will take a maximum of $N$ turns.
In each turn the die is thrown (each throw independent) and you have these choices:
- Accept the current number on the die as final score and end the game.
- Continue the game (if there are turns remaining)

Find expected value of score if you play to maximize the score.

Constraints:
- $1 \le N \le 100$ 

**Solution**

First we need to find the optimal way to play.

Suppose current number on the die is $x$ and we have $k$ turns left.
We would accept $x$ as final score if expected score in $k$ turns is less than $x$.
Otherwise we would keep playing.

Now, let's define $f(k)$ as expected score in at most $k$ turns.

For a single turn, it is:

$$
f(1) = \sum_{1 \le x \le 6}{x \cdot P(x)}
$$

$P(x)$ is the probability of getting $x$ which same for all $x$, i.e. $\frac{1}{6}$.

For $k > 1$ (each decision is based on expected value for remaining turns),

$$
f(k) = \sum_{1 \le x \le 6}{max(x, f(k - 1)) \cdot P(x)}
$$

The expected score for $N$ turns is $f(N)$.

### Problem F 

A connected unidirected graph with $N$ vertices and $N$ edges
is given.
Answer $Q$ queries of form $u, v$: determine whether
there is a unique simple path from $u$ to $v$.

Constraints:
- $3 \le N \le 2 \cdot 10^5$
- No double edges
- $1 \le Q \le 2 \cdot 10^5$

**Solution**

Observe that exactly $N$ edges are present - meaning that
there is exactly one cycle.

If a simple path from vertex $u$ to $v$ passes through at least
one edge of a cycle, then there is another simple path which goes through
all other edges of that cycle.

Let there be $K$ vertices forming a cycle.
If we remove the edges forming that cycle, we will get $K$ components.
Now if the given query $u, v$ is such that $u$ and $v$
are present in different components, then path has to pass through
cycle and won't be unique. Otherwise (if $u, v$ in same component), the path will be unique.

***