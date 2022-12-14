---
layout: page
title: Atcoder - abc128
parent: Problem Solving
math: true
---

*Source of these problems is ABC128 from [atcoder](http://atcoder.jp)*

### Problem E

There is a number line with $N$ barriers.
The $i$-th barrier is located at $X_i$ and
blocks this point starting from $t = S_i - 0.5$ seconds
to $t = T_i - 0.5$ seconds.

$Q$ people are standing on coordinate $0$.
The $i$-th person will start walking towards right
(positive $x$) at $t = D_i$ at a rate of 1 unit length
per second and will stop walking upon reaching a blocked
point.

Find distance each of the $Q$ people will walk.
If a person will never stop walking, output distance as $-1$
for them.

Constraints:
- $1 \le N,Q \le 10^5$
- $0 \le S_i < T_i \le 10^9$
- $1 \le X_i \le 10^9$
- $0 \le D_1 < \ldots < D_Q \le 10^9$
- If $i \neq j$ and $X_i = X_j$, the intervals
$[S_i,T_i)$ and $[S_j,T_j)$ do not overlap

**Solution**

Assume that $X_1 \le \ldots \le X_N$.

Barrier $i$ causes person $j$ to stop if:
- Barriers $1,\ldots,i-1$ do not cause person $j$ to stop.
- $S_i \le X_i + D_j < T_i$ since this person will reach
  position $X_i$ at $t = X_i + D_j$.

  $\Rightarrow S_i-X_i \le D_j < T_i-X_i$

Let $P$ be the set of persons who won't be blocked
by any barrier. Initially $P$ contains all persons.

We will analyse barriers in order $1,2,\ldots,N$.
While analysing barrier $i$, we will remove each person $j$
from $P$ which satisfies $S_i-X_i \le D_j < T_i-X_i$
and mark their walked distance as $X_i$.

Finally, all remaining persons in $P$ will walk indefinitely.

From implementation point of view, this problem becomes:
Given a set of $Q$ integers, find (and remove) all integers
lying within a range (for $N$ ranges).

Sample C++ code:
```cpp
/* (x, id) pair */
set<pair<int, int>> S;

/* remove an element with l <= x < r,
 * return removed id (non-negative)
 * return -1 if no such element */
int remove_in_range (int l, int r) {
  if (S.empty()) return -1;
  auto it = S.lower_bound({l, 0});
  if (it != S.end() && it->first <= r) {
    int ans = it->second;
    S.erase(it);
    return ans;
  }
  return -1;
}
```

***

### Problem F

There is a sequence of $N$ integers $s_0,\ldots,s_{N-1}$

Initially:
- You are at index $0$.
- Score is $0$.
- All indices except $0$ are marked unvisited.

You have to choose positive integers $A$ and $B$ in order
to maximize the score after following these steps:
1. Let $p$ denote your current position (index).
Move to $p + A$, i.e., $p \leftarrow p + A$.
. If $p \notin [0, N-1]$ or $p$ is marked visited
then you lose immediately with $-1$ final score. Otherwise
add $s_p$ to your score and mark $p$ as visited.
If $p = N-1$, end the game.
1. Let $p$ denote your current position (index).
Move to $p - B$, i.e., $p \leftarrow p - B$.
. If $p \notin [0, N-1]$ or $p$ is marked visited
then you lose immediately with $-1$ final score. Otherwise
add $s_p$ to your score and mark $p$ as visited.
If $p = N-1$, end the game.
1. Go to step 1

Print the maximum score.

Constraints:
- $3 \le N \le 10^5$ 
- $-10^9 \le s_i \le 10^9$
- $s_0 = s_{N-1} = 0$

**Solution**

To end the game without negative score, position $N-1$ 
must be reached. We can always get $0$ score by choosing
$A = N-1$ (choice of $B$ will not matter) since we will
reach $N-1$ in the first jump (and $s_0 = s_{N-1} = 0$)

If $A < N-1$, then $B < A$ because otherwise we can
never reach $N-1$. Thus, we have $0 < B < A < N-1$.

The sequence of visited indices is:

$0, A, A-B, 2A-B, 2A-2B, \ldots, kA-kB, (k+1)A-kB$

Let $D = A-B$ ($1 \le D \le N-3$). Then this sequence becomes:

$0, A, D, A+D, 2D, A+2D, \ldots, kD, kD+A$

Since we reach $N-1$ at then end, $kD+A=N-1$. Hence,
$A=N-1-kD$. The sequence now becomes:

$0,N-1-kD,D,N-1-(k-1)D,2D,\ldots,kD,N-1$.

Since $A=N-1-kD$ and $A > 2$

$\Rightarrow N-1-kD > 2$

$\Rightarrow kD < N-3$

Notice that this sequence contains:
- $0, D, 2D, \ldots, kD$
- $(N-1), (N-1)-D, \ldots, (N-1)-kD$.

If we check all possible combinations of $k$ and $D$,
we will obtain the answer.

Since we have to remain in range $[0,N-1]$, we have 
$0 \le kD \le N-1$. But we already have $kD < N-3$.
Thus $0 \le k < \frac{N-3}{D}$.

We will find scores for $D=1,\ldots,N-3$ ($N > 3$).
Thus, for some $D$, we have to check
$\lfloor\frac{N-3}{D}\rfloor$ values of $K$.
Note that if $N=3$ then the answer is $0$ (no valid
choice of $D$ exists).

Overall, we have to check:

$$
\left\lfloor\frac{N-3}{1}\right\rfloor +
\left\lfloor\frac{N-3}{2}\right\rfloor +
\ldots +
\left\lfloor\frac{N-3}{N-3}\right\rfloor
= O(N\log{N})
$$

pairs of $D$ and $k$.

Let $f(D, k)$ be the score obtained by choosing
$D$ and $k$ as defined above.
Then,
- $f(D, 0) = s_0 + s_{N-1} = 0$
- $f(D, i) = s_{iD} + s_{N-1-iD} + f(D, i-1)$ for $i > 0$

We can compute $f(D, k)$ in $O(1)$ time by using
$f(D,k-1)$. Thus, $f(D, 1), \ldots, f(D, k)$ can
be computed in $O(k)$. 

Note that any index can't be visited more than once.
If a sequence due to some $D$ and $k$ violates this condition,
then we have to avoid that pair.

There will be no collision among $0, D, 2D,\ldots,kD$.
Similarly, there will be no collision among 
$(N-1), (N-1)-D,\ldots,(N-1)-kD$. However, it might
be the case that $pD = (N-1)-qD$ for some $0 \le p, q \le k$.

$\Rightarrow (p + q) = \frac{N-1}{D}$ for collision.

If $D$ doesn't divide $N-1$, then there will be no collision.
Otherwise, we must have $2k < \frac{N-1}{D}$ because
if $2k \ge \frac{N-1}{D}$, then there will be atleast one collision 
because $0 \le p + q \le 2k$.

***

*That is it.*
