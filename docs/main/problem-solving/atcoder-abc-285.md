---
layout: page
title: Atcoder - abc285
parent: Problem Solving
math: true
---

*[atcoder](http://atcoder.jp) beginner contest 285*

### Problem E

*Tags: DP*

For a week of $n$ days, you need to mark each day as working or holiday
in order to maximize productivity.
A week should have at least 1 holiday.

Productivity is defined as:
- $0$ for a holiday.
- $a_k$ if nearest holiday is (or was) $k$ days after (or before)

Constraints:
- $1 \le n \le 5000$
- $1 \le a_i \le 10^9$

**Solution**

Since there is at least 1 holiday, let it keep it at day $1$.
This also means that next week starts from a holiday. So, we
have $n-1$ potential working days.

Let us call a consecutive stretch of working days as segment.

If there is no other holiday, we get a segment of size $n-1$.
If we keep a holiday at day $k$, we get a segment of size $k-2$
we can then reduce this to a subproblem of size $n - k + 1$ (as we also include
day $k$ as first day, which is holiday)

Let $f_k$ denote the productivity of segment of size $k$.
Then:

$$
f_k = \begin{cases}
0 & \text{if } k = 0 \\
f_{k-1} + a_{\lceil\frac{k}{2}\rceil} & \text{otherwise}
\end{cases}
$$

For example:
- $f_2 = a_1 + a_1$
- $f_3 = a_1 + a_2 + a_1$
- $f_4 = a_1 + a_2 + a_2 + a_1$

Let $g_k$ denote the maximum productivity for $k$ days given
that there is a holiday at day $1$ and there will be a holiday after day $k$.
Then:

$$
g_k = \begin{cases}
0 & \text{if } k = 0 \\
\max\limits_{0 \le i \le k-1}{f_i + g_{k-i-1}} & \text{otherwise}
\end{cases}
$$

In second part $i$ denotes the length of segment.

$g_n$ will be the answer and it can be calculated in $O(n^2)$.

### Problem F 

*Tags: Strings, Range structures*

We are given a string $s$ of length $n$.

We will be given two types of queries:
1. Update $(i, x)$: $s_i \leftarrow x$
2. Given $(l, r)$ check if $s_{l, r}$ is a substring of $t$
  where $t$ is $s$ sorted.

Note: Here $s_{i, j}$ denotes
substring of $s$ starting from index $i$ and ending at index $j$.

Constraints:
- $1 \le n \le 10^5$
- $s_i$ is a lowercase letter
- At most $10^5$ queries

**Solution**

We will analyze second query closely. $s_{l, r}$ being
substring to $t$ means:
- $s_{l, r}$ is sorted
- Except for first and last distinct characters (let them be $u, v$) in $s_{l,r}$,
  the frequency of all characters from $u+1$ to $v-1$ should be exactly as in $t$.
  - For example, if $s_{l, r}$ is `abbbdde` then `b` should
    occur exactly $3$ times in overall string, `c` should
    occur $0$ times and `d` should occur $2$ times.

We do not care about first and last characters because
we may be taking lesser number of those (than in overall string).
But if any other character in between has a different frequency, then
it can never be a substring of $t$.

We can use a structure which keeps ranges of same characters
in form $(l, r, c)$.
For example `abbbdde` will have $[(1, 1, \text{a}), (2, 4, \text{b}), (5, 6, \text{d}), (7, 7, \text{e})]$.

We can use an ordered set structure for this (supporting fast $O(\lg n)$ searches)

Then, for update query we may need to split / merge ranges (at most 3 ranges will be affected).

For second query, we will find range containing $l$. Then we will
traverse ranges in order checking if they satisfy the requirements
discussed above. We will traverse at most $26$ ranges in this process.

Sample implementation of such a structure in C++:
```cpp
using T = tuple<int, int, int>;
const int N = 1e5 + 666;

set<T> ranges;
int n;
string s;

// extract range containing i
T extract (int i) {
  auto it = --ranges.upper_bound({i, N, 0});
  T res = *it;
  ranges.erase(it);
  return res;
}

void change (int i, char x) {
  if (s[i] == x) return;
  int l, r, c; tie(l, r, c) = extract(i);
  if (r > i) { // split
    ranges.insert({i + 1, r, c});
    r = i;
  } else if (i + 1 < n && s[i] == s[i + 1]) { // merge
    int l1, r1, c1; tie(l1, r1, c1) = extract(i + 1);
    r = r1;
  }
  if (l < i) { // split
    ranges.insert({l, i - 1, c});
    l = i;
  } else if (i - 1 >= 0 && s[i] == s[i - 1]) { // merge
    int l1, r1, c1; tie(l1, r1, c1) = extract(i - 1);
    l = l1;
  }
  ranges.insert({l, r, s[i]});
}
```

Note that this sample code is incomplete in terms of solving
the whole problem. It simply shows how to update ranges.

***