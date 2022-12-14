---
layout: page
title: Simpler (1)
parent: Problem Solving
math: true
---

*Some (relatively) simple problems are discussed in this post.*

### Problem 

*Good subarrays*

You are given an array of integers $A_1,\ldots,A_N$.

Find the number of its subarrays having a non-negative sum.

Constraints:
- $1 \le N \le 10^5$
- $-10^9 \le A_i \le 10^9$ $\forall$ $i$

**Solution**

Let $B$ be the *prefix sum array* of $A$. That is:

$B_i = A_1 + \ldots + A_i$ $\forall$ $i, 1 \le i \le N$

Let $B_0 = 0$ for convenience.

First let's find the number of negative sum subarrays.

It holds for all $i, j$ such that $1 \le i \le j \le N$:

$$
(A_i + \ldots + A_j < 0) \Leftrightarrow (B_{i-1} > B_j)
$$

Thus, finding the number of inversions in $B_0, \ldots, B_N$ will
give us the number of negative sum subarrays. Let their
count be $K$.

The number of non-negative subarrays is then given by
$\binom{N}{2} - K$

***

### Problem

*Sorting by moving*

You have a sequence of integers $A_1,\ldots,A_N$.

In one move you can pick up (remove from sequence) any $A_i$
and place it (insert into sequence) at any position.

What is the minimum number of moves required to make the sequence
sorted (in non-decreasing order)?

**Solution**

Let the length of longest non-decreasing subsequence $L$ of 
this sequence be $K$. Then $N - K$ is the answer.

How? We can simply remove the elements not part of $L$ and place
them in their correct position.

There doesn't exist a better solution.

A simple observation helps us:
> Any subsequence of a sorted
  sequence is also sorted

Suppose a better answer $X$ exists. Then $X < N - K$.
Then we will perform the given operation on $X$ elements. Rest
of the $N-X$ elements will be untouched. This means that
they should be sorted. This contradicts the fact the length
of longest non-decreasing subsequence is $K$ because
$K < N - X$.

***

### Problem

*Good prefix sums*

You are given an array of integers $A_1,\ldots,A_N$ with possibly
negative elements. Find a rotation of this array such that every
prefix sum is non-negative, if there exists one.

Constraints
- $1 \le N \le 10^5$
- $-10^9 \le A_i \le 10^9$

**Solution**

Define $P_i = A_1 + \ldots + A_i$ $\forall$ $i = 1 \ldots N$

When does the solution not exist?

*Claim*: If $A_1 + \ldots + A_N < 0$ then no solution exists

*Proof*:

$P_N < 0$ for any rotation.

*Claim*: If $A_1 + \ldots + A_N \ge 0$ then a solution always exists

*Proof*

We have $P_N \ge 0$. 

Let $k$ be the largest such index that $P_k$ is minimum among $P_1,\ldots,P_N$.

If $P_k \ge 0$ then the condition is already satisfied.
Otherwise $P_k < 0$ and thus $k < N$.

Let $S = A_{k+1} + \ldots + A_N$

It should be clear that $P_k + S = P_N$

Following from $P_N \ge 0$ we have $S \ge -P_k$.

Let $A'$ be $A$ left-rotated $k$ times.
- For the $N-k$ elements shifted towards start, $P_k$ is removed from each
$$
P'_i = P_{k + i} - P_k \ \forall\ i = 1,\ldots,N-k
$$

- For the $k$ elements rotated to the end, $S$ is added to each
$$
P'_i = P_{i - N + k} + S \ \forall\ i = N-k+1,\ldots,N
$$

Thus all $P'_i \ge 0$. Why?
- For the first part, all $P'_i \ge 0$ since $P_k$ is minimum among all $P_1,\ldots,P_N$
- For the second part, $P'_i \ge 0$ since $S + P_k \ge 0$ implying $S + P_j \ge 0$ for all $j$
  since $P_k$ is the minimum.

***

### Problem

*Simple optimization?*

You are given postive integer sequences $A$ and $B$, both of length $N$.
You have to choose $K$ indices $t_1\ldots,t_K$ such that the following
value is maximized:

$$
\left(\sum_{1 \le i \le K}{A_{t_j}}\right)
\cdot
\left(\min_{1 \le i \le K}{B_{t_j}}\right)
$$

**Solution**

Assume non-decreasing order of $B_1,\ldots,B_N$.

For the chosen indices, let $t_1 < \ldots < t_K$.

Then our objective function becomes:

$$
\left(\sum_{1 \le i \le K}{A_{t_j}}\right)
\cdot
B_{t_1}
$$

So, if we fix some $B_i$ as minimum, then only those $A_j$ with
$j \ge i$ can be selected. We can take max $K$ of these.

This requires a data structure which supports 
- Addition/deletion of elements (possibly duplicate)
- Getting sum of max $K$ of them.

***

*That is it.*
