---
layout: page
title: Python (part 1)
parent: Programming Languages
math: true
---

## Basics

### Variables and their types

```python
# Declare and assign
a = "Hello" # str
b = 2 # int
c = 2.5 # float
d = {"a": 1} # dict
e = [1, 2] # list
f = (1, 2) # tuple
g = 1, 2 # tuple (1, 2)
h = {"a", "b", "c"} # set

# type function
print(type(a)) # <class 'str'>
print(type(g)) # <class 'tuple'>

# Un-assign or un-define
del f
print(f) # NameError: name 'f' is not defined

# Swapping variables
a, b = b, a # 2 "Hello"
``` 

### Operators

```python
# Arithmetic
print(7 + 2)  # 9 (Addition)
print(7 * 2)  # 14 (Multiplication)
print(7 - 2)  # 5 (Subtraction)
print(7 / 2)  # 3.5 (Division)
print(7 // 2) # 3 (Integer division)
print(7 % 2)  # 1 (Modulo)
print(7 ** 2) # 49 (Power)

x = 10
x += 2 # Operator shorthand
x //= 2
print(x) # 6

# Logical
print(7 == 2)  # False (equals)
print(7 != 2)  # True  (not equals)
print(7 < 2)   # False (less than)
print(7 > 2)   # True  (greater than)
print(7 <= 2)  # False (less than or equals)
print(7 >= 2)  # True  (greater than or equals)
x, y = [1, 2], [1, 2] # Declare two lists with same value
print(x == y)         # True (equality)
print(x is y)         # False (same object check)
print(x is not y)     # True (same object check)
print(True and False) # False (logical and)
print(True or False)  # True  (logical or)
print("a" in ["a", "b", "c"])   # True
print(1 if 1 != 2 else 2)       # 1 (ternary operator)

# Bitwise
# Utility method to show bits, can be ignored
bits = lambda x: print("".join(reversed(["1" if (x & (1 << i)) else '0' for i in range(10)])))

x, y = 12, 7
bits(x)       # 0000001100
bits(y)       # 0000000111
bits(x << 1)  # 0000011000 (left shift)
bits(x >> 1)  # 0000000110 (right shift)
bits(x & y)   # 0000000100 (bitwise and)
bits(x | y)   # 0000001111 (bitwise or)
bits(x ^ y)   # 0000001011 (bitwise xor)
bits(~x)      # 1111110011 (negation)

```

### Conditional branching

```python
x = 5

# if condition only
if x <= 2:
    print("small")
# nothing happens

# single line equivalent
if x <= 2: print("small")

# if, else
if x <= 2: print("small")
else: print("large")
# large

# if, else if
if x <= 2: print("small")
elif x <= 4: print("moderate")
# nothing happens

# if, else if, else
if x <= 2: print("small")
elif x <= 4: print("moderate")
else: print("large")
# large
```

### Loops / iterating

```python
# while loop
# General format is 'while <condition>: <exec-block>'
a, b = 0, 5
while a < b:
    print(a, end = " ")
    a += 1
print() # newline
# 0 1 2 3 4 

# You can write in a single line too
while a != 0: a -= 1; print(a, end = " ")
print()
# 4 3 2 1 0 

# for loop
# General format is 'for <element> in <iterable>: <exec-block>'
for x in range(5):
    print(x, end = " ")
print()
# 0 1 2 3 4 

# Using break
x = 0
while True:
    x += 1
    if x == 10: break
print(x) # 10

# 'break' in 'for' loop
# You can use the variable used even after exiting the loop
# It will be the value used in last iteration or before breaking out
for y in range(20):
    if y == 10: break
print(y) # 10

# Existing variables can be used in 'for' loop
# Even if the variable is manipulated in 'for' loop, its value
# is restored in next iteration
z = 10; print(z) # 10
for z in range(5):
    z += 10
    print(z, end = " ")
print()
# 10 11 12 13 14 

# Can use a convenient syntax while looping through tuples
t = [(1, "a"), (2, "b")]
for u, v in t: print(f"u = {u}, v = {v}")
# u = 1, v = a
# u = 2, v = b

```

### List comprehension:

```python
print([x for x in range(5)]) # [0, 1, 2, 3, 4]
print([x * 2 for x in range(5)]) # [0, 2, 4, 6, 8]

# with condition
print([x for x in range(5) if x % 2 == 0]) # [0, 2, 4]
# with multiple conditions
print([x for x in range(5) if x % 2 == 0 if x % 4 != 0]) # [2]

# double loop
print([(x, y) for x in range(2) for y in range(2)])
# [(0, 0), (0, 1), (1, 0), (1, 1)]

# correct way of using nested variables in double loop
print([(x, y) for x in range(3) for y in range(x)])
# [(1, 0), (2, 0), (2, 1)]

# incorrect way
print([(x, y) for x in range(y) for y in range(3)])
# NameError: name 'y' is not defined
```

### Functions

User defined:
```python
# A simple function with a return value
def add(a, b):
    return a + b

print(add(2, 3)) # 5

# Function that returns nothing
def show(m):
    if m == "": return
    print(f"Message is {m}")

show("") # nothing happens
show("hello") # Message is hello

# with annotations - type hints
def multiply(a: int, b: int) -> int:
    return a * b

print(multiply(2, 2)) # 4
print(multiply(1.5, 2)) # 3.0 - works but an IDE or a linter might warn

# Default arguments
def calc (x, y, negate = False):
    return -(x + y) if negate else (x + y)

print(calc(1, 2)) # 3
print(calc(1, 2, True)) # -3

def test (u, v = 1, w) # wrong - non default argument can't be after a default one
    return u * v + w
# SyntaxError: non-default argument follows default arg
```

Inbuilt functions involving iterables:
```python
## Involving iterables

x = ["cc", "bbb", "aa", "ddd"]

print(len(x)) # 4 - Length of an iterable

print(sorted(x))
# ['aa', 'bbb', 'cc', 'ddd']

print(list(reversed(x)))
# returns an iterator (here wrapped with list)
# ['ddd', 'aa', 'bbb', 'cc']

print(list(enumerate(x)))
# gives a list of tuple (index, element)
# returns enumerate object (iterable) (here wrapped with list)
# [(0, 'cc'), (1, 'bbb'), (2, 'aa'), (3, 'ddd')]

print(list(map(lambda t: t.upper(), x)))
# calls the given function on each element
# the given function can be in-built or user defined
# returns map object (iterable) (here wrapped with list)
# ['CC', 'BBB', 'AA', 'DDD']

print(list(filter(lambda t: len(t) == 2, x)))
# only keeps elements which return true of given function
# the given function can be in-built or user defined
# returns filter object (iterable) (here wrapped with list)
# ['cc', 'aa']

print(list(range(2, 10, 3)))
# represents a range with start, stop (exclusive) and step
# return range object (iterable) (here wrapped with list)
# [2, 5, 8]

y = [1, 2, 3, 4]

print(list(zip(x, y)))
# zip ties elements of two or more iterables into list of tuples
# returns zip object (iterable) (here wrapped with list)
# [('cc', 1), ('bbb', 2), ('aa', 3), ('ddd', 4)]
```

Inbuilt functions which are type constructors
```python
x, y = bool("true"), bool(0)
print(x, y) # True False

x, y = int("  1 \n"), int("-2")
print(x, y) # 1 -2

x, y = float("Infinity"), float(" .8 ")
print(x, y) # inf 0.8

# other type constructors are dict(), list(), set(), str()
```

This mini-guide may not cover all, even basic, details of python
but at the same time it may serve as a good enough reference for beginners.