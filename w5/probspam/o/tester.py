from math import factorial
from os import system

def write_test_case(n, c):
    with open("o/t1.txt", "w+") as f:
        f.write(f"{n}\n{' '.join(map(str, c))}")

n = 1
c = [1] * (n - 1)

for i in range(factorial(n - 1)):
    write_test_case(n, c)

    system(f'o/o <"o/t1.txt" >"o/o1.txt"')
    system(f'o/bruteforcer <"o/t1.txt" >"o/o2.txt"')

    with open("o/o1.txt", "r") as f1, open("o/o2.txt", "r") as f2:
        if(f1.read() != f2.read()):
            exit(0)

    for j in range(n - 2, -1, -1):
        if(c[j] >= j):
            c[j] = 1
        else:
            c[j] += 1
            break

with open("o/o1.txt", "w+") as f1:
    f1.write("No counterexample")