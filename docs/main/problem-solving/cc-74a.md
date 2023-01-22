---
layout: page
title: CC - 74A
parent: Problem Solving
math: true
---

### Problem A

Define $f(x)$ for an integer array $x$ of length at least $2$ as
difference between maximum and second maximum elements in $x$.

You will be given an integer array $a$ of length $n$. Find number of
distinct values of $f(x)$ over each subarray $x$ of $a$ having length at least $2$.

Constraints:
- $2 \le n \le 10^5$
- $1 \le a_i \le 10^9$

**Solution**

Let $a_{u, v}$ denote subarray $a_u,\ldots,a_v$.

We will look at cases where $a_i$ is the second maximum value in a subarray
(occuring on right of maximum)
- Let's find largest (closest to $i$ towards right) $j$ such that $j < i$ and $a_j \ge a_i$.
  This will be the maximum of the subarray.
  - It holds true even if $a_i = a_j$ because in that case we can consider either to be maximum.
  - We will add $a_j - a_i$ to set of distinct values.
- If there is some smaller $k$ ($k \lt j$) such that $a_k \ge a_i$, we do not need to consider it as:
  - If $a_j \gt a_i$ and $a_k \gt a_i$, then $a_i$ is the third maximum in subarray $a_{k,i}$.
  - Even if $a_i$ can be taken as second maximum in $a_{k, i}$, it will give the same
    answer as that given by $a_{k, j}$ (in case of $a_i = a_j$) or $a_{j, i}$ (in case of $a_j = a_k$).

We will similarly look at cases where $a_i$ is second maximum value occuring on left of
maximum - meaninng that we will find smallest $j$ such that $j \gt i$ and $a_j \ge a_i$.

*Implementation notes*:

We need to find for each $i$:
- Maximum $l$ such that $l \lt i$ and $a_l \ge a_i$
  - If exists, add $a_l - a_i$ to set of distinct values
- Maximum $r$ such that $i \lt r$ and $a_r \ge a_i$
  - If exists, add $a_r - a_i$ to set of distinct values


We can solve this in this way:
- Keep indices $1,\ldots,n$ in a structure which allows fast deletion and
  lower bound / upper bound search. (C++ `set` for example)
- Process values in ascending order so that at any iteration, only indices
  of greater or equal elements are present.
- When processsing value $x$ (at index $i$), find next and previous index
  in set of indices.
- Then, remove all instances of $x$ and move to next greater value.

*Tags: Implementation, structures*

***