---
layout: page
title: Mixed (2)
parent: Problem Solving
math: true
---

### Problem

You are given a list $a$ of $n$ integers. You are also given a
non-negative integers $m$ and $k$.

You have to do the following:
- Let $s = 0$
- Select a set $U$ of elements from $a$ such that their sum is
  lesser than $m$, remove them from $a$ and add their sum to $s$
- If $a$ is empty, finish. Otherwise, choose another element from $a$,
  add its value to $s$ and remove it from $a$.
- Select upto $k$ elements from $a$ and add their sum to $s$

Find maximum possible value of $s$ after this process.

Constraints:
- $a_i \ge 1$ and $\sum{a_i} \le 10^9$
- $1 \le m \le 10^4$
- $1 \le n \le 100$
- $0 \le k \le 100$

**Solution**

We can combine the last two steps of the process and select upto
$k+1$ elements from $a$ in the last step.

We can always select maximum $k+1$ elements and from the remaining,
choose the maximum sum possible which is lesser than $m$ to make set $U$.

> Explanation: In the optimal solution, replace all $k+1$ elements by maximum
> $k+1$ elements. Answer will not increase since this is optimal solution,
> we will be exchanging elements from $U$. We will never put greater values in
> $U$ hence the sum will be still less than $m$.

We can define $f(i, x)$ as: whether it is possible to make sum
$x$ using elements $1$ to $i$ in the list without $k+1$ maximum elements.
We can define a base case for $i = 0$ for simplicity:

$$
f(0, x) = \begin{cases}
1 & \text{if } x = 0 \\
0 & \text{otherwise}
\end{cases}

\\

f(i, x) = \begin{cases}
f(i - 1, x) & \text{if } x \lt a_i \\
f(i - 1, x) \vee f(i - 1, x - a_i) & \text{otherwise}
\end{cases}

$$

We will then find the maximum $x$ for which $f(p, x) = 1$ (if there are $p$ elements).

Since bounds of $i$ and $x$ are small, we can do this in time.
Time complexity will be $O(n\lg{n} + nm)$ (as sorting is done).

***