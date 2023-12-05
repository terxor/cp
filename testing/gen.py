import random
import string

def rand_int (lo, hi):
    return random.randint(lo, hi)

def rand_str (min_len, max_len=None, chars=string.ascii_lowercase):
    if max_len is None:
        max_len = min_len
    n = rand_int(min_len, max_len)
    m = len(chars)
    return "".join([chars[rand_int(0, m - 1)] for i in range(n)])

n = int(input())
for i in range(n):
    print(rand_str(1, 100, "abc"))
