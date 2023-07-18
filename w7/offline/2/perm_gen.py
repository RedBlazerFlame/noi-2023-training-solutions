from math import factorial
from itertools import permutations

with open("2.in", "w+") as f:
    f.write("720\n")

    for p in permutations(range(6)):
        f.write(" ".join(map(lambda i: str(i + 1), p)) + "\n")