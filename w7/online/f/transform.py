n = 4
for i in range(n << 1):
    group_e = (i // n, i % n)
    base = list(range(n))
    transformed = list(range(n))
    for i in range(0, n):
        if(group_e[0] == 1):
            transformed[(i + group_e[1]) % n] = 0 if i == 0 else n - i
        else:
            transformed[(i + group_e[1]) % n] = i

    print(f"{'F' if group_e[0] == 1 else ''}R{group_e[1]}")
    print(" ".join(map(str, base)))
    print(" ".join(map(str, transformed)))