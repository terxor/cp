---
layout: page
title: Atcoder - abc287
parent: Problem Solving
math: true
---

### Problem F

There is a tree with nodes numbered $1$ to $n$. You will be given $n-1$
edges of this tree.

For $x = 1$ to $n$ answer:
- Out of $2^n - 1$ non-empty subsets $V$ of nodes $1$ to $n$, how many
  satisfy: subgraph induced by nodes in $V$ has $x$ connected components

Constraints:
- $1 \le N \le 5000$

**Solution**

We can think of a DP solution here based on
subtree. Let node $1$ be the root.

Let $f(u, k, p)$ denote the number of ways
to get $k$ components from subtree rooted at $u$
and $p = 0$ or $1$ indicates whether node $u$ is
present or not.

Parameter $p$ will be helpful in calculating transition
from children.

Let $c_u$ denote the total number of nodes in subtree rooted
at $u$.

Further, suppose node $u$ has $m$ children $v_1,\ldots,v_m$.

$f(u, k, 0)$ is the number of ways to form sum $k$
if we get $x_i$ from child $v_i$ (and $\sum{x_i} = k$ holds).
We will need to use DP here as well.

Let $g(i, x)$ denote the number of ways to form sum $x$
from children $1$ to $i$.
- Initially, $g(i, x) = 0$ for all $i, x$
- Let $g(0, 0) = 1$ for convenience.
- We will compute $g(i, x)$ by using all values $y$ that can be
  obtained from $v_i$:
  - $g(i, x + y) \leftarrow g(i, x + y) + g(i, x) \cdot [f(v_i, y, 0) + f(v_i, y, 1)]$
  - Bounds are important here for time complexity analysis: $y$ will be from $0$ to $c_{v_i}$
    and $x$ will be from $0$ to $c_{v_1} + \ldots + c_{v_{i-1}}$.
  - Let $c_{v_i} = t_i$ for convenience.
    For $i$, we will be doing $(1 + t_i) \cdot (1 + t_1 + \ldots + t_{i-1})$ operations.
  - For $i = 1$ to $m$, this will sum up to:
    $$
    \sum\limits_{1 \le i \le m}{(1 + t_i) \cdot (1 + t_1 + \ldots + t_{i-1}) } \\
    = m + \sum\limits_{1 \le i \le m}{(t_1 + \ldots + t_i) } + \sum\limits_{1 \le i \le m}{t_i \cdot (t_1 + \ldots + t_{i-1}) } \\
    $$
  - First two parts will result into $O(n^2)$ operations overall. We will
    analyze the third part:
    $$
    \sum\limits_{1 \le i \le m}{t_i \cdot (t_1 + \ldots + t_{i-1}) } \\
    $$
    It may not be straightforward to see but when summed over all nodes,
    the value is $\binom{n}{2}$.
    View the term $t_i \cdot (t_1 + \ldots + t_{i-1})$ as making
    links between each node in child $i$ and each node in children $1,\ldots,i-1$ combined.
    Also notice that if this is for some subtree $u$, we will never
    make links among nodes of subtree $u$ as we move up to the parents.
  - Hence, the overall time complexity will be $O(n^2)$ (as opposed to $O(n^3)$, which might be deduced from first glance)

For $f(u, k, 1)$, the computation will be similar except:
- There will be always be $1$ component containing $u$.
- If we are taking some child $v_i$, then $v_i$ will be connected
  to $u$ and we will get $1$ less connected component because
  same component will have $u$ and $v_i$.

Finally, answer for some $x$ will be $f(1, x, 0) + f(1, x, 1)$

This type of tree DP is called **square order tree DP**.

*Tags: Trees, DP, Square order tree DP*

***