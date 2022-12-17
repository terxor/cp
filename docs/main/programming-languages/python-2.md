---
layout: page
title: Python (part 2)
parent: Programming Languages
math: true
---

## More concepts

### Subscript notation

For some list or string `x`, subscript notation can be used, to get a sub-list, as `x[start:end:step]`
where `start`, `end` and `step` are integers. `end` is exclusive, meaning that
the range `[start, end - 1]` is considered.

```python
s = "yneos"
print(s, s[:], s[::], s[0:len(s):1])
# yneos yneos yneos yneos
# all 3 arguments are optional
# defaults are 0, len(s), 1

print(s[1:],s[:1])
# neos y
# start is inclusive, end is exclusive

print(s[1::2], s[::2], s[2::9])
# no yes e
# step counts from start

print(s[:-1], s[:len(s)-1])
# yneo yneo
# negative index -i means i-th element from end

print(s[2:4], s[-3:-1])
# eo eo
# more examples of negative index

x = [1, 3, 5, 7]

print(x[-2:], x[:-2])
# [5, 7] [1, 3]
# can be used with lists in the same way
# in first part: start from second last element
# in second part: till second last element, excluding

# For lists, sublist assignment can be done
a = [1, 2, 3, 4]
a[1:3] = [7, 8]
print(a) # [1, 7, 8, 4]
```

### Iterable unpacking operator

Iterable unpacking holds its usual meaning.
We can think of it as substituting the iterable by
comma separated list of elements.

```python
a = [1, 2, 3]
print(a) # [1, 2, 3]
print(*a) # 1 2 3
```

Unpacking function arguments
```python
# a simple function
def calc (u, v, w = 0):
    return u * v + w

a = [1, 2]
b = [2, 3, 4]
# we want to use these iterables as arguments of a function
print(calc(*a)) # 2
print(calc(*b)) # 10
```

Iterable unpacking for flattening iterables
```python
itr1 = range(1, 4)
itr2 = map(int, ["4", "5"])
a = [*itr1, *itr2]
print(a) # [1, 2, 3, 4, 5]
```

Iterable unpacking is done implicitly in assignment
```python
a, b, c = [1, 2, 3]
print(a, b, c) # 1 2 3

a, b, c = (1, 2, 3)
print(a, b, c) # 1 2 3

a, b, c = range(1, 4)
print(a, b, c) # 1 2 3

a, b, c = map(int, ["1", "2", "3"])
print(a, b, c) # 1 2 3
```

There exists a sort of reverse of unpacking - starred expression
```python
a, *b = 1, 2, 3
print(a, b) # 1 [2, 3]

a, *b = [1, 2, 3]
print(a, b) # 1 [2, 3]

a, *b, c = [1, 2, 3, 4]
print(a, b, c) # 1 [2, 3] 4

*a, *b = [1, 2, 3] # ambiguity, not allowed
# Error: Multiple starred expressions

# Note: Starred expression target must be in a list or tuple
```

Unpacking nested iterable in assignment
```python
# normal unpacking just like above
a, b, c = [[1, 2], [3, 4], [5, 6]]
print(a, b, c) # [1, 2] [3, 4] [5, 6]

# unpacking nested iterable
[a, b], c, d = [[1, 2], [3, 4], [5, 6]]
print(a, b, c, d) # 1 2 [3, 4] [5, 6]

# combination
[a, b], *c = [[1, 2], [3, 4], [5, 6]]
print(a, b, c) # 1 2 [[3, 4], [5, 6]]

# combining concepts
[a, *b], c = [[1, 2, 3], [4, 5]]
print(a, b, c) # 1 [2, 3] [4, 5]
```

### Lambdas

Lambdas are light-weight functions that
that be used anonymously, can be passed as variables.

```python
add = lambda a, b: a + b
print(add(2, 3)) # 5

# Passing lambda to map as anonymous function
a = list(map(lambda x: int(x) * 2, ["1", "2", "3"]))
print(a) # [2, 4, 6]

# You can pass around lambdas
def process(f, a, b):
    return [f(a), f(b)]

print(process(lambda x: x * 2, 3, 4)) # [6, 8]

# Generating lambda
def gen(message):
    return lambda s: print(message % (s))

greeter = gen("hello %s")
leaver = gen("bye %s")

greeter("terxor") # hello terxor
leaver("terxor") # bye terxor
```

## For competitive programming

### Input

Even though taking a line of input is as simple as
calling `input()` but from a competitive programming
perspective, there are many input patterns which
usually occur.

```python
# multiple integers in a line
a, b, c = map(int, input().split())

# multiple integers in a line to list
a = list(map(int, input().split()))

# another way of doing the same
b = [*map(int, input().split())]
```

> The `split` method has special behaviour when no separator is specified.
> It treats multiple consecutive spaces as one unit and ignores leading and trailing spaces (or newlines).

Iterate through each line in input:
```python
for s in open(0):
  # Also includes newline character
  print(s)
```

Practical examples:
```python
# Example 1
# a1 a2 ... aN
# b1 b2 ... bN
# c1 c2 ... cN
a, b, c = [list(map(int, s.split())) for s in open(0)]

# Example 2
# N M
# a1 a2 ... aN
# b1 b2 ... bM
# Q
# t1 t2 ... tq
[n, m], a, b, [q], t = [list(map(int, s.split())) for s in open(0)]

# Example 3
# n
# x1 y1
# ...
# xn yn
n = int(input())
p = [tuple(map(int, input().split())) for i in range(n)]
```

### Strings

Strings are immutable. Modifications cause creation of new object.

```python
a = "test"
print(a, id(a)) # test 2239191300656
a += "ing"
print(a, id(a)) # testing 2239191347632, a different object
```

If there is lot of character manipulation needed in a string,
convert to list:
```python
a = "test"
t = list(a) # ['t', 'e', 's', 't']
t[1] = 'a' # all list operations as usual
t += ['e']
a = "".join(t) # taste
```

Subscript notation applies as usual
```python
a = "abcde"
print(a[1:4]) # bcd
print(a[::2]) # ace
print(a[::-1]) # edcba, reverse trick
```

Utility methods
```python
# ascii related
print(chr(97)) # 'a'
print(ord('a')) # 97

# Check number of occurrences of substring
s = "test string"
print(s.count("st")) # 2

# Find first index of substring
print(s.index("st")) # 2
print(s.index("a")) # ValueError: substring not found

# Error safe method of finding substring
print(s.find("st")) # 2
print(s.find("a")) # -1

a = "aBcDe"
print(a.lower()) # abcde
print(a.islower()) # False
print(a.upper()) # ABCDE
print(a.isupper()) # False
print(a.swapcase()) # AbCdE

a = "aggregate"
print(a.partition("reg"))
# ('agg', 'reg', 'ate')

print(a.split("g"))
# ['a', '', 're', 'ate']

a = " a  b  c "
print(a.split()) # ['a', 'b', 'c']
print(a.split(" ")) # ['', 'a', '', 'b', '', 'c', '']
# split behaviour is different when nothing specified

a = "succeeded"
print(a.replace("ed", "s")) # success
```

### Data structures

Lists
```python
# Initializing lists
a = [1, 2, 3]
b = [0] * 5 # [0, 0, 0, 0, 0]
c = [1, 2] * 2 # [1, 2, 1, 2]
d = [i+1 for i in range(3)] # [1, 2, 3]
# 2D lists:
e = [[0] * 5 for i in range(2)]
# [[0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]

# Basic operations
x = [1, 2, 3]
x.append(4) # x = [1, 2, 3, 4]
x.insert(1, 3) # x = [1, 3, 2, 3, 4], insert(index, value)
x.count(3) # 2, number of occurrences
x.index(3) # 1, first index starting from 0
x.pop() # 4, retrieves and removes last element
len(x) # 3
x.clear() # removes all

# Access elements
print(x[0]) # 1
print(x[len(x) - 1]) # 3 (last element)
print(x[-1]) # 3 (equivalent to x[len(x) - 1])

# Concatenation
a, b = [1, 2], [3, 4]
print(a + b) # [1, 2, 3, 4]

# For subarrays / sublists, see subscript notation
a = [1, 2, 3, 4]
print(a[1::2]) # [2, 4]

# Sorting and reverse
a = [2, 4, 3, 1]
a.sort() # a becomes [1, 2, 3, 4]
a.sort(reverse = True) # a becomes [4, 3, 2, 1]
a.reverse() # a becomes [1, 2, 3, 4] again
sorted(a) # returns sorted list but doesn't modify 'a'
# both sort and sorted functions accept key function
sorted([(4, 2), (3, 1)], key = lambda x: x[1])
# [(3, 1), (4, 2)]

# Empty check of a list (same for tuples)
x = [1]
if x: print("Not empty") else: print("Empty")
```

> Be careful while initializing 2D lists this way:
> ```python
> a = [[0] * n] * m
> ```
> This will create same list multiple times (not copies as needed)
> 
> To illustrate this error further:
> ```python
> a = [1, 2, 3]
> b = a
> a[0] = 4
> print(a, b)
> # [4, 2, 3] [4, 2, 3]
> ```

> Sample problem: Given two lists `a` and  `b`, obtain sum of `k` max elements from
> both of them combined
> ```python
> sum(sorted(a + b)[-k:])
> 
> # Note: this very similar expression returns sum excluding max k elements
> sum(sorted(a + b)[:-k])
> ```

Dictionaries
```python
v = {"a": 1,"b": 2} # Initialize values

u = {} # Empty dictionary
u[1] = 2
u["a"], u["b"] = 1, 2 # Can have different key types

# Iterate through keys
k = [x for x in u.keys()] # [1, 'a', 'b']
k = [x for x in u] # Another way to iterate through keys

# Iterate through values
v = [x for x in u.values()] # [2, 1, 2]

# Iterate through key-value pairs
kv=[(k,v) for k, v in u.items()]
# [(1, 2), ('a', 1), ('b', 2)]

# Checking existence of keys
print("a" in u) # True
print("c" in u) # False

# Deleting entries
del u['a']
# {1: 2, 'b': 2}
```

Sets
```python
# set(iterable)
u = set() # {}
v = set([1, 2, 3, 3]) # {1, 2, 3}

print(u.isdisjoint(v)) # True
u.add(2)
u.add(4)
print(2 in u) # True

print(v.intersection(u)) # {2}
print(u & v) # alternate syntax

print(v.union(u)) # {1, 2, 3, 4}
print(v | u) # alternate syntax

print(v.difference(u)) # {1, 3}
print(v - u) # {1, 3}

# shorthand assignment
v |= {5, 6} # {1, 2, 3, 5, 6}
v &= {1, 2, 3, 4} # {1, 2, 3}

# removing elements
v.remove(2) # {1, 3}
v.discard(1) # {3}, won't throw error if element not present unlike remove
v.clear() # {}

```

Queue
```python
from collections import deque
d = deque([1, 2, 3]) # deque(iterable)
# deque([1, 2, 3])

d.append(4) # O(1)
# deque([1, 2, 3, 4])

d.appendleft(0) # O(1)
# deque([0, 1, 2, 3, 4])

d.pop() # remove from right, O(1)
# deque([0, 1, 2, 3])

d.popleft() # remove from left, O(1)
# deque([1, 2, 3])

d.rotate(1) # rotate n steps to right, negative n means left
# deque([3, 1, 2])

len(d) # 3

# allows random access but only front/back access is O(1)
print(d[0]) # 3
print(d[-1]) # 2

d.clear() # Remove all

d.extend([1, 2, 3]) # Bulk add to right
# deque([1, 2, 3])

d.extendleft([4, 5]) # Bulk add to left
# deque([5, 4, 1, 2, 3])

for x in d: print(x) # deque is an iterable

```

### Utility

#### Permutations and combintations
```python
from itertools import permutations, combinations

# permutations(iterable, [length])
print([p for p in permutations([1, 2, 3])])
# [(1, 2, 3), (1, 3, 2), (2, 1, 3), (2, 3, 1), (3, 

print([p for p in permutations([1, 2, 3], 2)])
# [(1, 2), (1, 3), (2, 1), (2, 3), (3, 1), (3, 2)]

# combinations(iterable, length)
print([c for c in combinations([1, 2, 3], 2)])
# [(1, 2), (1, 3), (2, 3)]

print(["".join(c) for c in combinations("abc", 2)])
# ['ab', 'ac', 'bc']

```

#### Counter
```python
# A special kind of dictionary for
# computing frequencies
from collections import Counter
a = [2, 1, 4, 5, 4, 5, 4]
c = Counter(a)
print(c.keys())
# dict_keys([2, 1, 4, 5])
print(c.values())
# dict_values([1, 1, 3, 2])
print(c.items())
# dict_items([(2, 1), (1, 1), (4, 3), (5, 2)])
print(c.most_common(2))
# [(4, 3), (5, 2)]
```

#### Min/max with iterables
```python
x = [-1, 2, -3]
m = min(abs(t) for t in x)
# m = 1

# Or with lists
m = min([-1, 2, -3])
# m = -3

# With custom key function
m = min([1, 2, 3, 4], key = lambda x: x if x % 2 == 0 else -x)
# Note: this is the sorted order with given lambda [3, 1, 2, 4]
# a = [1, 2, 3, 4]
# a.sort(key = lambda x: x if x % 2 == 0 else -x)
```

#### Utility method `any`:
```python
x = any([False, True, False])
# x = True

# Check if at least one number in a list is even
a = [1, 3, 5, 4]
y = any(t % 2 == 0 for t in a)
# y = True
```

#### Utility methods `all`:
```python
x = all([False, True, False])
# x = False

# Check if all numbers in list are odd
a = [1, 3, 5, 7]
y = all(t % 2 != 0 for t in a)
# y = True

# Empty iterable has all true - vacuous truth
x = []
y = all(x)
# y = True
```

#### Math:
```python
# inbuilt functions
print(abs(-2)) # 2, int
print(abs(-2.5)) # 2.5, float

print(divmod(13, 5)) # (2, 3), quotient and remainder
print(pow(10, 2)) # 100
print(pow(10, 2, 55)) # 45,  pow(base, exponent, mod)

print(sum([1, 2, 3])) # 6

print(round(-1.5)) # -2
print(round(1.4), round(1.5), round(1.6)) # 1, 2, 2
print(round(2.4), round(2.5), round(2.6)) # 2, 2, 3
# rounds to nearest even number if .5

print(round(1.5684, 2)) # 1.57, 2 decimal places

# Use math lib
import math
a = math.floor(1.5) # 1
b = math.ceil(1.5) # 2
c = math.sqrt(16) # 4.0
```

#### Dealing with deep recursive problems:

Suppose you are dealing with recursion of high depth like $10^5$, you have
to use this snipper otherwise `RecursionError: maximum recursion depth exceeded in comparison`
will be thrown during execution.
```python
import sys
sys.setrecursionlimit(100000)
```