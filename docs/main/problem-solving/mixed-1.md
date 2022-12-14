---
layout: page
title: Mixed (1)
parent: Problem Solving
math: true
---

### Problem MINDSUM

*Source of this problem is [CodeChef](http://codechef.com)*

You are given integers $N$ and $D$. You may
perform the following operations zero or more times
- $N \leftarrow N + D$
- $N \leftarrow f(N)$

where $f(x)$ : digit sum of a non-negative
integer $x$.

Find the minimum value of $N$ which can be
obtained and the minimum number steps to obtain this
value.

We have: $1 \le N, D \le 10^{10}$

**Solution**

We will give a small upper bound on number
of steps to reach the minimum value which will
then allow using a brute force approach to find 
the minimum number of steps to reach the minimum
value.

We will use the concept of digital roots to prove
some claims.
Let $d(x)$ denote the digital root of $x$. That is,

$$
d(x) =
\begin{cases}
x & 0 \le x \le 9 \\
d(f(x)) & \text{otherwise}
\end{cases}
$$

In other words, $d$ is repeated application of
$f$ until a single digit number is obtained. As
a side note, the number of times $f$ is applied
to an integer to get a single digit number is
called its additive persistence.

For some optimal solution let $N = x$ after the
last addition operation (op. 1), then $d(x)$ is
the final value.


*Claim*: Any digit sum operation (op. 2) before the last
addition operation can be removed without changing the
final value (by adding some digit sum operations
at the end).*

Let $N = x$ after some operations.
We have:
- $N = f(x)$ (digit sum operation)
- $N = f(x) + kD$ (last addition operation)
- $N = d(f(x) + kD)$ (applying $f$ possibly multiple times)

We are claiming that the above sequence can be
transformed to the following:
- $N = x + kD$ (last addition operation)
- $N = d(x + kD)$ (applying $f$ possibly multiple times)

To prove this, we have to show that 
$d(f(x) + kD) = d(x + kD)$

For this we use the properties of digital roots:
- $d(x) = d(f(x))$
- $d(a + b) = d(d(a) + d(b))$

We start with $d(f(x) + kD)$

$= d(d(f(x)) + d(kD))$

$= d(d(x) + d(kD))$

$= d(x + kD)$

From this claim, we can convert an optimal
solution into a sequence of addition operations
followed by digit sum operations (until
the digital root has been obtained). Thus,

$ans = min(d(N + kD)), k > 0$

$ans = min(d(d(N) + d(kD)), k > 0$

Using property $d(ab) = d(d(a)d(b))$

$ans = min(d(d(N) + d(d(k)d(D))), k > 0$

By the definition of $d$, $d(k)$ evaluates
to an integer in range $[0, 9]$. This means
for any $k > 9$, we get repeating values. Thus, 

$ans = min(d(N + kD))$ over $0 \le k \le 9$

Now we need an upper bound for number of steps to
reach the digital root for any non-negative
integer $\le 10^{11}$. It can be observed that
no more than 3 steps are required. This is
because in the first step we may get a 2-digit
number (max sum 99). In the second step we may
get a 2-digit number again (max sum 18). Now,
the digit sum is guaranteed to be less than 10.

One may also refer the sequence for 
smallest numbers having additive persistence 0, 1, 2, etc.
The smallest number with additive persistence 4
is $2 \cdot 10^{22} - 1$.

Thus, we have shown that the minimum value can
be atmost obtained in $9 + 3 = 12$ steps by the
above strategy.

We can now find the optimal solution by brute force,
say by recursion (limiting the depth to 12).

***

### Problem 

*Source unknown*

*Jumps* 

You are given integers $a_1,\ldots,a_n$. Find the minimum number of jumps to
reach index $n$ given that when you are at index $i$, you can jump to
$i + j$ (but not beyond $n$) $\forall$  $1 \le j \le a_i$.
Initially you are at index $1$.

Constraints: $1 \le n, a_i \le 10^5$

**Solution**

Let $f_i$ be: Minimum jumps required to reach index $i$ from index $1$

Then $f_i = 1 + \min(f_j)$ $\forall$ $

Let's use a greedy strategy for computing $f_i$:
$f_i = 1 + min(f_j)$ such that $a_j + j \ge i$ and $j$ is minimum possible
Note that the term $a_j + j$ denotes the max reachable index from index $j$.

Base case $f_1 = 0$ and,
$f_i = \infty$ if we can't reach index $i$ by any means

*Claim 1*: $f_i \le f_j$ if $i \lt j$

*Proof*: 

Suppose $f_i \gt f_j$. Now consider the sequence of optimal jumps to reach index $j$ from $1$ as: $x_1,x_2,\ldots,x_k$ where $x_1 = 1$ and $x_k = j$.
Now, it guaranteed that there exists some $p, 1 \le p \lt k$ such that $x_p \le i \lt x_{p+1}$ since $x_1 \lt x_2 \ldots \lt x_k$. Now, we can reach index $i$ in atmost $p+1$ moves and since $p < k$, this implies $p+1 \le k$ which contradicts $f_i \gt f_j$

*Claim 2*: The greedy strategy for $f$ defined above is optimal

*Proof*:

Suppose $k$ is the minimum index from which we can reach index $i$. Suppose $\exists x, k \lt x \lt i$ which is some other index which is the better choice, i.e, $g_k > g_x$ then we could reach index $i$ faster. But by claim 1, $g_k \le g_x$. Hence proved.

Implementation Strategy:
Define another array $b_i = max(a_i + i, b_{i-1}) \quad\forall i, 1 \lt i \le n$.
(For $i = 1$, we have $b_1 = a_1 + 1$)
To find the least index from which index $i$ can be reached, start from $b_i$ and iterate down (possibly to 1).

***

### Problem

*Source unknown*

*Partition String*

A string $s$ of lowercase English letters is given. We want to partition this
string into as many parts as possible so that each letter appears in at most one
part, and return a list of integers representing the size of these parts.

Example:
Input: $s = ababcbacadefegdehijhklij$
Output: $9,7,8$
Explanation:
The partition is $ababcbaca, defegde, hijhklij$.

This is a partition so that each letter appears in at most one part. A partition
like $ababcbacadefegde$, $hijhklij$ is incorrect, because it splits $s$ into
lesser number of parts.

**Solution**

Definition: Let
$f_c$: Index of first occurence of character $c$
$l_c$: Index of last occurence of character $c$

Definition: Partition property - for a partition $s_p,\ldots,s_q$, the following
holds for each character $c$ in this partition:

$$ 
p \le f_c \le l_c \le q
$$

*Claim 1*: Consider the first partition in the optimal partitioning of $s$, let
*it be $s_1,\ldots,s_k$. Then there does not exist any index $p \lt k$ such that
*$s_1,\ldots,s_p$ is a valid partition (i.e, satisfies the partition property)

*Proof*:

Suppose there existed such index $p$, then we show that $s_{p+1},\ldots,s_k$ is
also a valid partition and thus the partitioning is not optimal (since we can
get a better solution).

Let us show that $s_{p+1},\ldots,s_k$ is a valid partition: suppose it is not,
then there exists some character $c$ in $s_{p+1},\ldots,s_k$ such that $f_c \lt
p + 1$ (this is the only way the partition can be not valid), but this is not
possible because this character lies within $s_1,\ldots,s_p$ which satisfies $1
\le f_c \le l_c \le p$ for each character lying within it.

*Claim 2*: Greedy strategy - to find the max number of partitions, find the
*minimum index $k$ for which $s_1,\ldots,s_k$ is a valid partition (then repeat
*the process with that prefix of the string removed)

*Proof*: 

We have shown that in the optimal solution with first partition
$s_1,\ldots,s_k$, there can not exist an index $p$ such that such
$s_1,\ldots,s_p$ is a valid partition, this implies that the only choice for $k$
is the minimum possible index for which $s_1,\ldots,s_k$ is a valid partition.
Removing this first partition from the string, we can obtain the next partition
which is the part of the optimal solution using the same strategy.

***

### Problem

*Source unknown*

*Optimal Distribution*


There is an array $A$ ($A_1,\ldots,A_N$) which has all zeroes initially.

You are given integer ranks of indices $1,\ldots,N$ as $R_1,\ldots,R_N$.

You can perform this operation on the array:
- Pick an index $i$ and perform $A_i \leftarrow A_i + 1$.

This operation must be performed at least once for each index, i.e., 
$A_i \ge 1$  $\forall$ $i, 1 \le i \le N$


What is the minimum number of times this operation should be performed
such that:
$$
R_i > R_j \Rightarrow A_i > A_j \ \forall\ 1 \le i, j \le N \text{ with } \vert i - j \vert = 1
$$

In simpler terms, higher rank index has higher value (than a lower ranked index).

**Solution**

Since each operation increases the sum $A_1 + \ldots + A_N$ by one, the problem
can be restated as minimizing this sum.

If we provide a lower bound for values of $A$ and then show a configuration in
which each $A_i$ is minimum possible, then the sum $A_1+\ldots+A_n$ will be
minimum possible.

Definitions:
- $f_i$: Maximum length of decreasing sequence starting at $i$
- $g_i$: Maximum length of increasing sequence ending at $i$

$f_i$ and $g_i$ can be computed in the following manner:
- For $f$, base case: $f_n = 1$
- If $R_i \le R_{i+1}$ then $f_i = 1$ otherwise $f_i = 1 + f_{i+1} \ ( \forall\ i, 1 \le i \le n-1)$

- For $g$, base case: $g_1 = 1$
- If $R_{i-1} \ge R_i$ then $g_i = 1$ otherwise $g_i = 1 + g_{i-1}$


*Claim 1*: $A_i \ge max(f_i, g_i) \ \forall\ i, 1 \le i \le n$

*Proof*:

Suppose $A_i \lt f_i$, then it is not possible to satisfy the condition $A_i \gt
A_{i+1} \gt \ldots \gt A_{i+f_i-1}$ with $A_{i+f_i-1} \ge 1$.

A similar argument can be provided for $g_i$.

*Claim 2*: The configuration: $A_i = max(f_i, g_i)$ does not violate any condition.

*Proof*:

Since $g_i, f_i \ge 1 \ \forall\ i, 1 \le i \le n$, the condition
$A_i \ge 1$ $\forall$ $i, 1 \le i \le N$
 is satisfied.

For second condition, assume $A_1,\ldots,A_{i-1}$ do not violate any condition.

Now we show that by setting $A_i = max(f_i, g_i)$, no condition is violated.
(Base case of this induction is when we have only $A_1$ which does not violate
this condition because of being a single element)

- Case 1: $R_{i-1} = R_i$

  Trivial case, setting any value of $A_i$ will not violate this condition

- Case 2: $R_{i-1} \lt R_i$

  We have to show $A_{i-1} \lt A_i$

  By definition of $g$, we have: $g_{i-1} + 1 = g_i$.
  Also, by definition of $f$, $f_{i-1} = 1$

  $\Rightarrow A_{i-1} = g_{i-1}$ because $g_{i-1} \ge 1$

  $\Rightarrow A_i \ge 1 + g_{i-1}$ because $A_i = max(f_i,g_{i-1} + 1)$

  $\Rightarrow A_{i-1} \lt A_i$

- Case 3: $R_{i-1} \gt R_i$

  We have to show $A_{i-1} \gt A_i$

  By definition of $f$, we have: $f_{i-1} = 1 + f_i$. Also, by definition of $g$, $g_i = 1$

  $\Rightarrow A_i = f_i$ because $f_i \ge 1$

  $\Rightarrow A_i = f_{i-1} - 1$

  $\Rightarrow A_i \le A_{i-1} - 1$

***
*That is it.*
