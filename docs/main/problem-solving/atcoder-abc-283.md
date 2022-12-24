---
layout: page
title: Atcoder - abc283
parent: Problem Solving
math: true
---

*Source of these problems is ABC266 from [atcoder](http://atcoder.jp)*

### Problem E

You are given a binary matrix $A$ (contains only 0s and 1s)
of dimension $N \times M$.

Element $A_{i,j}$ is said to be isolated if there is no adjacent element
having same value as itself.

In one operation you can choose a row and flip all elements (flip is equivalent to
$A_{i,j} \leftarrow 1 - A_{i,j}$)

Find minimum number of operations such that no element is isolated.
Report if this is not possibe.

Constraints:
- $2 \le N, M \le 1000$

**Solution**

Important observations:
- Independence of rows:
  Isolated status of cells in row $i$ is only affected by cells in rows $i-1$ and $i+1$.
- A row can have only two states: original or flipped.

We can define a function $f$ as:

$f(r, u, v)$ as minimum number of operations to
make all cells of $1,\ldots,r-1$ good (i.e, not isolated)
where $u, v$ indicate whether row $r-1$ and $r$ have been flipped.
$u, v$ can have values in $\{0, 1\}$.

Flip status of last two rows is required because while computing $f$ for $r+1$,
row $r$ has to be validated which requires information about rows $r-1$ and $r+1$.

Suppose there is a validation function $g$ for row $r$ which takes in flip status of
rows $r-1,r,r+1$ and gives out result $0$ or $1$.

$$
g(r, a, b, c) = \begin{cases}
                1 & \text{if all cells of row $r$ are good} \\
                0 & \text{otherwise}
                \end{cases}
$$

Here $a, b, c$ are flip statuses of rows $r-1,r,r+1$ respectively.
In case of $r=1$, $a$ is ignored and in case of $r=N$, $c$ is ignored.

Thus we have:

$$
f(r+1, u, v) = \min_{x \in \{0, 1\}, g(r, x, u, v) = 1}{\left(v + f(r, x, u)\right)}
$$

The final answer will be given by:
$$
\min_{i, j \in \{0, 1\}, g(N, i, j, 0) = 1}{f(N, i, j)}
$$


### Problem F 

There is a permutation $P_1,\ldots,P_N$ of $1,\ldots,N$.

For each $i$, find

$$
\min_{i \neq j}{\left(\vert P_i - P_j \vert + \vert i - j \vert\right)}
$$


Constraints:
- $1 \le N \le 2 \cdot 10^5$

**Solution**

For some $i$, we can divide this expression into 4 cases:

We will analyse one case. Rest can be solved in a similar manner.

- $P_j \lt P_i$ and $j \lt i$
  - The expression becomes $P_i - P_j + i - j$
  - We can have independence between terms: $(P_i + i) - (P_j + j)$

Suppose for some $i$ we can find maximum $(P_j + j)$ satisfying the constraints.
We need a way to filter out $P_j \gt P_i$ and $j \gt i$.

This can be done by, say, a max segment tree from which we can get max in a range.
Thus we can get for some $l, r$, $\max_{l \le j \le r}{(P_j + j)}$.
- For condition $P_j \lt P_i$, $(l, r)$ can be set to $(1, P_i-1)$
- For condition $j \lt i$, we process elements in order of $i$. Thus on processing
  $i$, the segment tree will only contain elements from $1,\ldots,i-1$.

> Implementation:
> - For each $i$, we can maintain answers and update it if we find a better one. Initial value can be set to $\infty$
> - Initially, each element in segment tree can have value $-\infty$.
> - We will have 4 max segment trees, one for each case.

***