from itertools import permutations
from math import factorial

with open("3/perm.in", "w+") as f:
    n = 4
    f.write(f"{factorial(n)}\n")
    for p in permutations(range(n)):
        f.write(f"{n}\n")
        f.write(" ".join(map(str, p)) + "\n")