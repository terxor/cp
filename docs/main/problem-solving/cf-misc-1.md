---
layout: page
title: Codeforces - misc. (1)
parent: Problem Solving
math: true
---

*Source of these problems is [codeforces](http://codeforces.com)*

### Problem 1133F2

*Spanning Tree with one fixed degree*

You are given an undirected connected graph having vertices $1,\ldots,n$ with
$m$ edges (with no self loops or multiple edges). Find any spanning tree of this
graph such that degree of the vertex $1$ is equal to $D$ or report if it is not
possible.

Constraints:
- $2 \le n \le 2 \cdot 10^5$
- $n-1 \le m \le min(2 \cdot 10^5, \frac{n(n-1)}{2})$
- $1 \le D \lt n$

**Solution**

We should have $deg(1) \ge D$ to start with.

Now the tricky part is selecting exactly $D$ of these $deg(1)$ vertices adjacent
to $1$ such that the $deg(1) - D$ vertices remain connected to the graph (but
not to vertex $1$). What are the cases when a solution is still not possible?

Let us remove vertex $1$ from the graph. Let there be $C$ connected components
after removing $1$. Then we claim that the degree of $1$ in any spanning tree
will not be less than $C$ because the only way these components can be a part of
the whole graph is through vertex $1$.

*Claim*: No solution is possible if $C \gt D$. Otherwise, a solution is possible

*Proof*:

In case $C \gt D$ degree of $1$ in any spanning tree will be greater than $D$.

In case $C \le D$, we can find a solution: select at least one vertex from each
component (which is connected to $1$, of course). Now select the remaining $D -
C$ vertices from any of the vertices adjacent to $1$ which are not already
selected. By having selected at least one vertex from each component, we ensure
that the graph remains connected. To obtain a spanning tree, we perform DFS or
BFS from the selected vertices.

***

### Problem 1095F

*Make it connected*

There are $n$ vertices $1,\ldots,n$ and integer costs $a_1,\ldots,a_n$
associated with them. Initially there are no edges in this graph. To add an edge
between vertex $u$ and vertex $v$, it costs $a_u + a_v$.

Further, there are $m$ special edges $(p_i, q_i)$ with cost $w_i$ ($i =
1,\ldots,m$) available to use.
Find the minimum cost to make the graph connected.

**Solution**

For simplicity, assume that $a_i \le a_{i+1}$ for $1 \le i \lt n$.

We will use Kruskal's algorithm. But we will not explicitly sort all $\binom{n}{2} + m$ edges.

Assume that we have a sorted list of edges and we are going through it.
If we get a non-special edge, it has to contain $1$ in it (or we can swap some edge of same cost to get this condition). This is because:
- $a_1$ is smallest among all $a_i$, thus cost of edge $(1, u)$ is not greater than cost of $(v, u)$ for any $u, v \neq 1$.
- Suppose the edge is $(u, v)$ where $u \neq 1, v \neq 1$, then at least one of
  $(1, u)$ or $(1, v)$ will be unused and will not cost greater.
- For same cost edges, order doesn't matter (in Kruskal's algorithm)

Thus we can form optimal solution using edges of form $(1, i)$ and special edges only.

***

### Problem 1245D

*Shichikuji and power grid*

We are given $n$ vertices numbered $1,\ldots,n$, initially with no edges.
The goal is to *activate* each vertex. We have the following options:
- Activate a vertex $u$ - this costs $a_u$
- Connect vertices $u$ and $v$ - this costs $w(u, v)$

We are given $a_1,\ldots,a_n$ and 
$w(u, v)$ $\forall$ $1 \le u, v, \le n (u \ne v)$ with $w(u, v) = w(v, u)$.

What is the minimum cost required to activate each vertex?

**Solution**

This problem is a straightforward MST problem if the following is observed:

Activating vertex $u$ is equivalent to connecting $u$ with some universal
source, say vertex $0$ which is activated initially. Imagine this as connecting
vertex $u$ and vertex $0$ with an edge having cost $w(0, u) = a_u$.

Now, we have $\binom{n}{2} + n$ edges and their weights and we need to find the
minimum cost to make the graph connected. Thus, we have reduced this problem to
MST. We can apply Kruskal's algorithm now (feasible for $n \le 10^3$)

***

### Problem 436C

*Dungeons and Candies*

We are given $k$ puzzles ($N \cdot M$ sized grid of characters) and we have to send them over a
network. Each puzzle can be sent in either of these two ways:
- As whole (this has same cost for each puzzle $= N \cdot M$)
- As a difference of some puzzle sent earlier
  (cost of this operation is equal to the number of different cells in these two
  puzzles)

Find the sequence of sending the puzzles (along with ways)
which minimizes the total cost.

**Solution**

> This description can be simplified to:
> You have to activate $k$ nodes where a node $u$ can be activated by one of the following methods:
> - Activate $u$ - this has fixed cost $nm$
> - Connect $u$ to an already activated vertex $v$ - this costs $f(u, v)$ (the difference function)

Notice how this description is very similar to that of problem *1245D*.

Activating vertex $u$ is equivalent to connecting $u$ with some universal source, say
vertex $0$ (in fact the solution is output in this form - if a puzzle is sent as
whole then its parent is printed as $0$). Again we have $\binom{n}{2} + n$ edges
and their weights and we need to find the minimum cost to make the graph
connected. Hence, this problem is reduced to finding MST.

To complete the solution, we have to traverse the MST (using DFS or BFS) to obtain directed edges (parent to child)

***

### Problem 821E

You are on a 2D plane.
Your current position is $(0, 0)$ and you have to reach $(k, 0)$ 

If you are at $(x, y)$ then you can move to either $(x+1, y-1)$ or $(x+1,y)$ or
$(x+1,y+1)$ but you can never go below the $x$-axis $(y = 0)$

Also, there are $n$ segments parallel to $x$-axis. Segment $i$ is represented by
$a_i, b_i, c_i$ which means that the end points of this segment are 

$(a_i, c_i)$ and $(b_i, c_i)$. We have $a_i \le b_i$ and $c_i \ge 0$ $\forall$
$i, 1 \le i \le n$. The segments also follow this property:

$a_i = b_{i-1}$ $\forall$ $i, 2 \le i \le n$. Also: $a_1 = 0$ and $b_n = k$.

The constraints on the segments can be understood by this: Suppose you had a
line segment with end points $(0, 0)$ and $(0, k)$ - cut this line segment into
$n$ pieces (by making cuts at $x = b_1,\ldots,b_{n-1}$ and shift each piece up
(in $+y$ direction) by some value (which is $c_i$ for piece $i$).

The segments restrict the movement in $+y$ direction - you can never move above
$y = c_i$ while $x = a_i,\ldots,b_i$.

We need to find the number of ways to reach $(k, 0)$ (modulo $10^9 + 7$)

Constraints:
- $1 \le n \le 100$
- $0 \le c_i \le 15$
- $0 \le a_i, b_i, k \le 10^5$ (subproblem)
- $0 \le a_i, b_i, k \le 10^{18}$ (actual)

**Solution**

For solving the subproblem, we have a straightforward DP solution:

Define $f(x, y)$ : Number of ways to reach $(x, y)$ starting from $(0, 0)$

We have:
- $f(x, y) = 0$ (if $a_i \le x \le b_i$ and $y > c_i$ or $y < 0$)
- $f(x, y) = f(x-1,y-1) + f(x-1, y) + f(x-1,y+1)$ (otherwise)

with base case $f(0, 0) = 1$

Since $x \le 10^5$ and $y \le 15$, the computation would be feasible ($1.5 \cdot 10^6$ table size)

However, we can't apply the same on the actual constraints because of huge upper bound on $x$.

Let us observe how the values $f(x,0), f(x,1), \ldots, f(x, c_i)$ transform as we move from some $x = x$ to $x = x+1$ (in the same segment)

We have:

  $f(x+1,0) = f(x,0) + f(x,1)$

  $f(x+1,1) = f(x,0) + f(x,1) + f(x,2)$

  $f(x+1,2) = f(x,1) + f(x,2) + f(x,3)$

  $\cdots$

  $f(x+1,c_i) = f(x,c_i - 1) + f(x,c_i)$

This transformation can be expressed as matrix multiplication:

$$
\begin{bmatrix} f(x,c_i) \\ f(x,c_i-1) \\ f(x,c_i-2) \\ \vdots \\ f(x,1) \\ f(x,0) \\ \end{bmatrix} \begin{bmatrix} 1 & 1 & 0 & 0 & \dots & 0 & 0 & 0\\ 1 & 1 & 1 & 0 & \dots & 0 & 0 & 0\\ 0 & 1 & 1 & 1 & \dots & 0 & 0 & 0\\ \vdots & \vdots & \vdots & \vdots & \ddots & \vdots & \vdots & \vdots\\ 0 & 0 & 0 & 0 & \dots & 1 & 1 & 1\\ 0 & 0 & 0 & 0 & \dots & 0 & 1 & 1\\ \end{bmatrix} = \begin{bmatrix} f(x+1,c_i) \\ f(x+1,c_i-1) \\ f(x+1,c_i-2) \\ \vdots \\ f(x+1,1) \\ f(x+1,0) \\ \end{bmatrix} 
$$

To propagate through a huge range of $x$ for a same segment, we can use matrix exponentiation (in logarithmic time).

The number to times we have to perform matrix exponentiation is equal to the number of segments which is $n \le 100$

The time complexity becomes $O(n {Y_{MAX}}^3 \lg(X_{MAX}))$ where $Y_{MAX} = 15$ and $X_{MAX} = 10^{18}$ (assuming matrix multiplication in $O(n^3)$ for $n\cdot n$ matrix)

***

*That is it.*
