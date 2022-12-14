---
layout: page
title: Atcoder - abc129
parent: Problem Solving
math: true
---

*Source of these problems is ABC129 from [atcoder](http://atcoder.jp)*

### Problem E

You are given a positive integer $L$ in base two. Find the number of pairs
of non-negative integers $(a, b)$ satisfying the following conditions:
- $a + b \le L$
- $a + b = a \oplus b$ (where $\oplus$ denotes bitwise XOR)

Find the answer modulo $10^9 + 7$.

Constraints:
- $L$ will be given in base 2
- $1 \le L \le 2^{100001}$

**Solution**

Let $N$ be the number of bits in $L$ (no leading zeros).
It is clear that $a$ and $b$ will not have
greater than $N$ bits (because of first condition). 
We will consider that both $a$ and $b$ have $N$ bits,
with leading zeros allowed.

Let $a_i,b_i,L_i$ denote $i$-th bit ($1 \le i \le N$) from left
of $a,b,L$ (respectively).

Addition and bitwise XOR are related as:

$$
a + b = (a \oplus b) + 2(a \& b)
$$

where $\&$ denotes bitwise AND operation.

Since $a + b$ = $a \oplus b$ from the second condition, we have $a \& b = 0$
which means there is no $i$ ($1 \le i \le N$) for which $a_i = b_i = 1$.
The possible values of $(a_i,b_i)$ are $(0,1), (1,0), (0,0)$ for all $i$.

We define predicates $LT$ and $EQ$ for some pair $(a, b)$:
- $EQ(i)$ : Considering only bits $1$ to $i$, $a + b = L$.
- $LT(i)$ : Considering only bits $1$ to $i$, $a + b < L$.

Let $f(i)$: Number of pairs of $(a, b)$ satisfying $EQ(i)$.

Let $g(i)$: Number of pairs of $(a, b)$ satisfying $LT(i)$.

Then, we need to find $f(N) + g(N)$.

Definition of $f(i)$:

$$
f(i) =
\begin{cases}
    2 & \text {if }i = 1 \\
    2 * f(i-1) & \text{if } i > 1 \text{ and } L_i = 1 \\
    f(i-1) & \text{if } i > 1 \text{ and } L_i = 0
\end{cases}
$$

We know that $L_1 = 1$. Thus, $f(1) = 2$ because of two choices $(0,1)$
and $(1,0)$ of $(a_1,b_1)$ satisfying $EQ(1)$.

If $i>1$ and $L_i = 1$ then there are two choices $(0,1)$ and $(1,0)$ to fulfil
$EQ(i)$ if we already $EQ(i-1)$. Otherwise there is only one choice $(0,0)$ for $(a_i,b_i)$.

Definition of $g(i)$:

$$
g(i) =
\begin{cases}
    1 & \text {if }i = 1 \\
    3 * g(i-1) + f(i-1) & \text{if } i > 1 \text{ and } L_i = 1 \\
    3 * g(i-1) & \text{if } i > 1 \text{ and } L_i = 0
\end{cases}
$$

Since $L_1 = 1$, $g(1) = 1$ because of a single choice $(0,0)$
of $(a_1,b_1)$ satisfying $LT(1)$.

If $i>1$ and $L_i = 1$, then we can either use $(0,1)$ or $(1,0)$ or $(0,0)$
if $LT(i-1)$ since any combination for bit $i$
will not violate $LT(i)$.
If $EQ(i-1)$ then we can only use $(0,0)$ to make $LT(i)$.

If $i>1$ and $L_i = 0$, then again there are $3$ choices to make $LT(i)$
if $LT(i-1)$. However, there is no choice if $EQ(i-1)$.

***

### Problem F

You are given an arithmetic progression of $N$ terms $X_0,\ldots,X_{N-1}$
with first term $A$ and common difference $B$, i.e., $X_i = A + iB$.

Consider integer $Y$ formed by concatenation of $X_0,\ldots,X_{N-1}$ (written 
in base 10 without leading zeros). For example, $Y = 246810$ formed by
$< 2, 4, 6, 8, 10 >$. Find $Y \mod M$.

Constraints:
- $1 \le N, A, B < 10^{18}$
- $2 \le M \le 10^9$
- All terms in the AP are less than $10^{18}$.

**Solution**

Let $C_i$ be the number of terms having exactly $i$ digits. If $C_i > 0$, 
let $(L_i,R_i)$, $0 \le L_i \le R_i \le N-1$, be the range of indices of such terms. From the given constraints, we have $1 \le i \le 18$.

It holds for each $i$ for which 
$C_i > 0$ that $10^{i-1} \le X_{L_i}$ and $X_{R_i} \le 10^i - 1$.

Let us consider terms having exactly $K$ digits.
Let $f(i)$ be the number formed by terms $X_{L_K},\ldots,i$.
Then $f(X_{R_K})$ would be the number formed by all $C_K$ terms
(having $K$ digits). We have the following relations:
- $f(X_{L_K}) = X_{L_K}$
- For $i > X_{L_K}$, $f(i) = 10^K f(i-1) + A + iB$

Since a range can be huge, we can not calculate $f(X_{R_K})$ in 
a trivial manner.

Matrix exponentiation can be useful here. Notice that we have $iB$ and constant
term $A$ in the recurrence relation, so we have to design the transition
accordingly.

$$
\begin{bmatrix}
f(i) \\
i \\
1 \\
\end{bmatrix}
=
\begin{bmatrix}
10^K & B & A \\
0 & 1 & 1 \\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
f(i-1) \\
i-1 \\
1
\end{bmatrix}
$$

Thus,

$$
\begin{bmatrix}
f(X_{R_K}) \\
X_{R_K} \\
1 \\
\end{bmatrix}
=
\begin{bmatrix}
10^K & B & A \\
0 & 1 & 1 \\
0 & 0 & 1
\end{bmatrix}^{C_K-1}
\begin{bmatrix}
f(X_{L_K}) \\
X_{L_K} \\
1
\end{bmatrix}
$$

But we also need to consider the number digits due to terms 
containing $K+1,\ldots,18$ digits, i.e., we need to multiply
$f(X_{R_K})$ by $10^T$ where $T = (K+1) C_{K+1} + \ldots + 18 C_{18}$.
Calculating $10^T \mod M$ can be challenging since
$T$ may be greater than 64-bit integer limits and $M$ is not necessarily a 
prime. One way to do it is by splitting calculation, i.e,
$10^{iC_i} \mod M = (10^i \mod M)^{C_i} \mod M$. This is possible because
$C_i < 10^{18}$.

We have to consider terms of digits $K = 1,\ldots,18$ and add their
value (mod $M$) to get the answer.

***

*That is it.*
