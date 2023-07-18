"""
1 2 3 4 5 6

(6 choose 3) = 20

1 2 3 4 5 6
|
1<(2 3) 4 5 6
or
2<(1 3) 4 5 6
or
3<(1 2) 4 5 6
[1, 2, 3, 4, 5, 6]
[1, 2, 3, 4, 5, 6]

1 5 2 6 3 4
[1, 2, 3, 4, 5, 6]
3 1 4 2 5 6

T if i < j
< i 1 2 3 4 5 6
j
1 / X X X X X X
2 / < X X X X X
3 / < X X X X X
4 / X X X X X X
5 / X X X X X X
6 / X X X X X X

So this is the state so far
We can count the number of permutations
satisfying this
If it's more than 729 / 3^num_queries_so_far, then oof

=====
Let me rethink the state
Yeah this should work ^^
"""

from itertools import combinations

def perm_satisfies(inf_grid, perm):
    for i in range(6):
        for j in range(6):
            pass

def count_satisfying_perms(inf_grid):
    for

# Iterate through all possible first queries
MAX_Q = 6
def gen_strat(inf_grid, num_q_so_far):
    if(num_q_so_far == MAX_Q): return False
    for comb in combinations(range(6), 3):
        pass