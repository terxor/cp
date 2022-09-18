---
layout: page
title: Permutations
parent: Math
math: true
---

### Finding next permutation in lexicographical ordering

You are given $A$ ($A_1 \ldots A_N$) which is a permutation of $1 \ldots N$ ($N \ge 2$).
Find the lexicographically smallest permutation greater than
$A$. Report if it doesn't exist.

**Solution**

We first define lexicographical order in permutations.

For permutations $A$ and $B$ of $1,\ldots,N$ we say 
$A \lt B$ if there exists index $k$ such that 
- $A_i = B_i$ $\forall$ $1 \le i \lt k$
- $A_k \lt B_k$

For convenience in discussion, let's call $k$ defined above as the **deciding index** (in context of comparing two permutations).
There is no deciding index in case the compared permutations are equal.

In simple terms, we compare both permutations starting
from index 1 and we report lesser or greater if we find different
elements at some index. If we reach the end, the permutations are equal.

Now suppose we have permutations $A, B, C$ of $1,\ldots,N$.
Further suppose $A \lt C$ and $B \lt C$ and
let $p$ and $q$ be the deciding indices for comparison of $A,C$ and $B,C$ respectively.

If $p \lt q$  it holds that $B \lt C$ since $B_p = A_p$ but $A_p \lt C_p$
(note that $A_i = C_i$ $\forall$ $1 \le i \lt p$ 
and $A_i = B_i$ $\forall$ $1 \le i \lt q$)
This implies ordering $A \lt B \lt C$.

Thus we come to an important claim:

Claim 1: *Among all permutations greater than a permutation $A$, those with
greatest deciding index (w.r.t. comparison with $A$) are closest
to $A$ in lexicographical ordering.*

Now we come back to the given problem. For the given
permutation $A$, we need to find the next higher permutation
in the ordering. Let that permutation be $B$ (the solution).

Let $k$ be the deciding index w.r.t. comparison of $A$ and $B$
which means $A_i = B_i$ for $i = 1,\ldots,k-1$
and $A_k \lt B_k$.

We need to find the largest $k$ such that sub-permutation $A_k,\ldots,A_N$
is not the greatest among its elements.
- We can start with $i = N$ (down to $2$) and stop at first occurence
of $A_{i-1} \lt A_i$ thus setting $k = i-1$ (proof is simple - for any index $j \gt k$ 
we have $A_j \gt \ldots \gt A_N$)
- If no such $k$ exists, then $A_1 \gt \ldots \gt A_N$ meaning the
  permutation is the largest in lexicographical ordering.

Now, upon finding such $k$, we have:
- $A_k \lt A_{k+1}$
- $A_{k+1} \gt \ldots \gt A_N$

Till now we have $B_i = A_i$ $\forall$ $1 \le i \lt k$.
The remaining elements $B_k,\ldots,B_N$ have to be a permutation
of $A_k,\ldots,A_N$.
- Since it should be the case that $B_k \gt A_k$
  and $B$ being smallest such permutation, we need to have
  $B_k$ least possible, i.e. $B_k$ will be the
  the smallest element $A_t$ among $A_k,\ldots,A_N$ such that $A_t \gt A_k$.
- From the remaining elements, we will form the smallest
  permutation (i.e. elements in sorted order) since we already have
  $B_k \gt A_k$ establishing $B \gt A$.

Hence we obtain the solution $B$.

**Obtaining next permutation in-place in O(n)**

If we want to *modify* $A$ to obtain the solution without
using any auxiliary space, we can do so by adding an observation to
the last part of the solution described above.

After finding the appropriate element $A_t$ for $B_k$
- Swap $A_k$ and $A_t$
- Reverse the part of sequence $A_{k+1},\ldots,A_N$.

After the swap, it still holds that $A_{k+1} \gt \ldots \gt A_N$ and the reverse
step makes it sorted.
Why?
- $A_t \gt A_k$ and it is the smallest such value.
- $A_{t-1} \gt A_k$ is obvious.
- $A_k \gt A_{t+1}$ because either $A_k \gt A_{t+1}$ or $A_k \lt A_{t+1}$ - the second case being impossible by the choice of $A_t$.

***