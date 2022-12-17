---
layout: page
title: Codeforces - misc. (3)
parent: Problem Solving
math: true
---

*Source of these problems is [codeforces](http://codeforces.com)*

### Problem 1736C2

We are given an array $a$ of size $n$.

A subarray $b_1,\ldots,b_m$ is good if $b_i \ge i$ for all $1 \le i \le m$.

The first version is to find the number of good subarrays in $a$.
For second version, we will be given $q$ queries of form $p, x$ in which
we need to find the number of good subarrays if $a_p \leftarrow x$ (original array is restored after each query).

Constraints:
- $1 \le n, q \le 2 \cdot 10^{5}$
- $1 \le a_i, p, x \le n$

**Solution**

Let's define a function $f$ as:
if $f(i) = j$ then $j$ is the first index which violates
the good subarray constraint. To handle edge case where $j \gt n$, we can assume $a_{n+1} = 0$.

This means that the subarrays starting from $i$ and ending
at $i, i+1, \ldots, j-1$ will be good. This also gives us
the number of subarrays starting from $i$ as $f(i) - i$.

For the first version, the answer will simply be:
$$
\sum_{1 \le i \le n}{f(i) - i}
$$

The computation of $f$ can be done efficienty by exploiting this property:
if subarray $a_i,\ldots,a_j$ is good, then $a_{i+1},\ldots,a_j$ is also good.

This gives us $f(i) \le f(i+1)$ for all $i$. Implementation wise, we can use a two-pointers approach to compute
$f$ in linear time.

For the second version, let's break down the queries into cases:

**Case 1** $a_p \ge x$

We will observe how $f$ changes if we recompute it after $a_p \leftarrow x$ (we will not actually recompute it).

For $i \in [p, n]$ nothing changes. In case of $i = p$ notice that $a_p = x \ge 1$ always satisfies good subarray constraint for first element.

For $i \in [1, p-1]$:
- If $f(i) \lt p$, it won't change as some element before it violates the constraint.
- If $f(i) \gt p$, it won't change as $a_p$ didn't decrease and hence it can't become a constraint violator.
- If $f(i) = p$ it could be the case that it is no longer a constraint violater due to increase in value. We analyse this further.

Let $[u, v]$ be the range where all $a_i = p$. It is possible that
some $i \in [u, v]$ has $f'(i) \gt f(i)$ ($f'$ is $f$ recomputed after $a_p \leftarrow x$).
To find such indices, notice that since $a_p = x$, for any $i \gt p - x$ we will always have $f'(i) \gt p$.
For the counterpart $i \lt p - x$, we will always have $f'(i) \le p$.

Let $[l, r]$ be intersection of ranges $[u, v]$ and $[p-x+1,p-1]$.
Then all $i \in [l, r]$ will have $f'(i) \gt f(i)$.
If original answer is $S$, the answer for this query becomes:
$$
S - (f(l) + \ldots + f(r)) + (f'(l) + \ldots + f'(r))
$$

But since we can't compute $f'$ for each query, we can have
something pre-computed that we can use for each query. Consider this:
let function $g$ be similar to $f$ except that it ignores the first constraint violation.
In other words it gives the second index at which the good subarray constraint is violated.
To handle edge cases, we can use $a_{n+1} = 0$ and $a_{n+2} = 0$ and setting $g(i) = \max(g(i), n+1)$.

Now definition of $g$ matches with what we compute in $f'$. We have the
answer as:
$$
S - (f(l) + \ldots + f(r)) + (g(l) + \ldots + g(r))
$$

**Case 2** $a_p \lt x$

Similar to case 1, range $[p, n]$ will not be affected.

For $i \in [1, p-1]$:
- If $f(i) \lt p$, it won't change as some element before it violates the constraint.
- If $f(i) \gt p$, it *may* change as $a_p$ decreased. We will analyse this further.
- If $f(i) = p$, it won't change as $a_p$ will still be a constraint violator after decrease.

Let $[u, v]$ be the range where $f(i) \gt p$. It is possible
that some $i \in [u, v]$ has $f'(i) = p$ ($f'$ is $f$ recomputed).
For $i \gt p - x$, $f'(i) \gt p$ as $a_p = x$ will not violate the constraint.
For $i \le p - x$ and $i \in [u, v]$, $f'(i) = p$ (this is the range where before the query $a_p$ didn't violate).

Let $[l, r]$ be intersection of ranges $[u, v]$ and $[1, p - x]$.
Then for each $i \in [l, r]$, $f'(i) = p$.
The answer becomes:
$$
S - (f(l) + \ldots + f(r)) + p \cdot (r - l + 1) 
$$

***

### Problem 1750D

*Abridged statement*: Find number of integers coprime to $X$
in range $[1, N]$.

Constraints:
- $1 \le X, N \le 10^9$

**Solution**

Positive integers $u$ and $v$ are said to be coprime if their
greatest common divisor is 1.

This can also be morphed to: $u$ and $v$ are co-prime if
they have no common prime factor.

Let all primes which are factors of $X$ be $p_1, \ldots, p_k$.

We need to find number of integers in $[1, N]$ which are not divisible by any of
$p_1, \ldots, p_k$.

In terms of sets, let $U = \{1, 2, \ldots, N\}$ and $S_x$ denote the set of numbers divisible by $x$.

Let $V = S_{p_1} \cup S_{p_2} \ldots \cup S_{p_k}$

Then, we need to find $\vert U - V \vert$, or $\vert U \vert - \vert V \vert$ as
$V \subseteq U$

We have $\vert U \vert = N$. It is easy to compute:
- $\vert S_{p_i} \vert$ is number of integers in $[1, N]$ divisible by $p_i$
- $\vert S_{p_i} \cap S_{p_j} \vert$ is ... divisible by $\text{lcm}(p_i, p_j)$
- $\vert S_{p_i} \cap S_{p_j} \cap S_{p_l} \vert$ is ... divisible by $\text{lcm}(p_i, p_j, p_l)$
- and so on

We can use *principle of inclusion and exclusion* to find the
answer.

In general,

$$
\vert A_1 \cup A_2 \ldots \cup A_N \vert = \
\sum{\vert A_i \vert} \
- \sum{\vert A_i \cap A_j \vert} \
+ \sum{\vert A_i \cap A_j \cap A_k \vert} \
- \cdots
$$

Implementation wise, we can iterate over all subsets of $A_1, \ldots, A_N$ and
add or subtract to the final result depending on set size (if odd then add, otherwise subtract).
If computing intersection of $m$ sets takes $O(m)$ time, then
a rough upper bound on overall time taken will be $O(N \cdot 2^N)$.

***

**Problem 1747D**

We are given $N$ integers $A_1,\ldots,A_N$ and $Q$ queries.

In each query integers $l, r$ are
given. We can perform this operation any number of times:
- Choose $L, R$ such that $l \le L \le R \le r$ and if $R-L+1$
  is **odd**, replace $a_L, a_{L+1}, \ldots, a_R$ by $x$ where
  $x = a_L \oplus a_{L+1} \ldots \oplus a_R$ (bitwise XOR).

We need to find the minimum number of operations to make $a_l, \ldots, a_r$
all 0 or report if that is not possible (for each query).

Constraints:
- $0 \le A_i \lt 2^{30}$
- $1 \le N, Q \le 2 \cdot 10^5$
- For each query, $1 \le l \le r \le N$

**Solution**

*Pre-condition*: For any given subarray, the bitwise XOR has to be $0$.
Otherwise we can never make all elements $0$.
Reason is:
- For some bit position:
  - If there are odd number of ones, XOR will be 1 and since
    subarray length has to be odd (given condition), XOR of
    final state will be 1 (all bits 1, odd number of bits).
  - If there are even number of ones, XOR will be 0 and final state
    XOR will be 0 (all bits 0).
  - Thus any operation does not change parity of ones.
- Final state is all zeroes. Hence for each bit position, 
  we need even number of ones (i.e., XOR equals 0).

We will assume that this pre-condition is satisfied.
Now if $l, r$ form odd length subarray, we can simply perform
one operation to make all zeroes (except for the case where
all elements are already zero, then we perform 0 operations).

For *even* length subarray, we need to observe some properties.
Suppose even length subarray $A_l,\ldots,A_r$ is $b_1,\ldots,b_n$

**Claim**: In an even length array $b_1,\ldots,b_n$,
if there is, initially, no odd length prefix with XOR $0$, then
it is not possible, by any sequence of operations, to
change this property.

**Proof**:

We will prove by induction.

Let $f_i = b_1 \oplus \ldots \oplus b_i$ (prefix XOR).

Initially, it holds that:
$f_{2i-1} \neq 0$ $\forall$ $1 \le i \le \frac{n}{2}$

Assume that after $k$ operations, this is true.

**Case 1:** $[L, R] = [2i, 2j]$

Let $u = f_{2i-1}$ and $v = f_{2j+1}$ (before the operation)

Let $x = b_{2i} \oplus b_{2i+1} \oplus \ldots \oplus b_{2j}$

Also, $x = u \oplus v \oplus b_{2j+1}$ (prefix XORs calculation)

After the operation: $b_{2i} = b_{2i+1} = \ldots = b_{2j} = x$
- $f'_{2i+1} = f_{2i-1} \oplus b_{2i} \oplus b_{2i+1} = u \oplus x \oplus x = u$
- $f'_{2i+3} = f'_{2i+1} \oplus x \oplus x = u$
- $\ldots$
- $f'_{2j-1} = f'_{2j-3} \oplus x \oplus x = u$
- $f'_{2j+1} = f'_{2j-1} \oplus b_{2j} \oplus b_{2j+1} = u \oplus x \oplus b_{2j+1} = v$
- Since $f'_{2j+1} = f_{2j+1}$, further indices are unchanged.

**Case 2:**  $[L, R] = [2i-1, 2j-1]$

Let $u = f_{2i-1}$ and $v = f_{2j-1}$ (before the operation)

Let $x = b_{2i-1} \oplus b_{2i} \oplus \ldots \oplus b_{2j-1}$

Also, $x = u \oplus v \oplus b_{2i-1}$ (prefix XORs calculation)

After the operation: $b_{2i-1} = b_{2i+1} = \ldots = b_{2j-1} = x$
- $f'_{2i-1} = f_{2i-1} \oplus b_{2i-1} \oplus x = v$ (removing $b_{2i-1}$ and including $x$)
- $f'_{2i+1} = f_{2i-1} \oplus x \oplus x = v$
- $\ldots$
- $f'_{2j-1} = f_{2j-3} \oplus x \oplus x = v$
- Since $f'_{2j-1} = f_{2j-1}$, further indices are unchanged.

$\blacksquare$

Now if there is no odd length prefix equal $0$ in $b_1,\ldots,b_n$ initially,
we can never get all zeros.

Otherwise, at most 2 operations will be sufficient to make all $b_i = 0$.
First operation can be on odd length prefix having XOR $0$ and second can be
on largest odd length suffix.

***