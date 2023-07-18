"""
<= N
Then, the string has to be at most
a^b^c characters long

Let's say the string is s = 5555 (with |s| = 4)
Let F(s[:-1], n) be the function to compute stuff
F(555, n) = F(550, n - 1)
F(550, n) = F(500, n - 1) + F(505, n - 1)

<F(555, n), F(550, n), ..., F(000, n)> =
[] * <F(555, n - 1), F(550, n - 1), ..., F(000, n - 1)>
set to zero row = s[:-1], col = s[1:]

Base case:
F(s, 0) = 1

To make this simple, we can treat
the string as a bitmask

vecF(n) = [...some matrix] * vecF(n - 1)

ans = 2^(a^b^c) - F(555, n) - F(550, n) - ... - F(000, n)

if(n < |s|) ans = 2^n = 2^a^b^c
"""
from copy import deepcopy

def zero_mat(n):
    return list(map(lambda _: [0] * n, range(n)))

def id_mat(n):
    return list(map(lambda i: list(map(lambda j: 1 if i == j else 0, range(n))), range(n)))

def matmul(a, b):
    n = len(a)

    res = list(map(lambda _: [0] * n, range(n)))
    for i in range(n):
        for j in range(n):
            res[i][j] = sum(map(lambda k: a[i][k] * b[k][j], range(n)))
    
    return res

def modmatmul(a, b, p):
    n = len(a)

    res = list(map(lambda _: [0] * n, range(n)))
    for i in range(n):
        for j in range(n):
            for k in range(n):
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % p
    
    return res

def modmatpow(a_orig, pw, p):
    if(pw == 0):
        return id_mat(len(a))
    a = deepcopy(a_orig)
    for i in range(len(bin(pw)) - 4, -1, -1):
        a = modmatmul(a, a, p)
        if((pw >> i) & 0b1): a = modmatmul(a_orig, a, p)
    return a

T, p = map(int, input().split(" "))

for _ in range(T):
    s_str = input("")
    s = int(s_str.replace("5", "1"), 2)
    s_n = len(s_str)
    a, b, c = map(int, input().split(" "))
    n = a ** (b ** c)
    if(s_n == 1):
        print((pow(2, n, p) - 1) % p)
        continue

    transition_mat = zero_mat(1 << (s_n - 1))

    for i in range(1 << (s_n - 1)):
        transition_mat[i][(i << 1) & ((1 << (s_n - 1)) - 1)] = 1
        transition_mat[i][((i << 1) & ((1 << (s_n - 1)) - 1)) ^ 0b1] = 1
    
    transition_mat[s >> 1][s & ((1 << (s_n - 1)) - 1)] = 0
    
    if(n < s_n):
        print((1 << n) % p)
    else:
        res_mat = modmatpow(transition_mat, n - s_n + 1, p)
        ans_comp = 0
        for i in range(1 << (s_n - 1)):
            for j in range(1 << (s_n - 1)):
                ans_comp = (ans_comp + res_mat[i][j]) % p
        print((pow(2, n, p) - ans_comp) % p)