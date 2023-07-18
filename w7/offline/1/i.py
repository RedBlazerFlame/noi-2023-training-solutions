"""
Let black pen be true and blue pen be false
3-SAT is in NP, so might as well make an exponential time
algo ^^
"""
def pad_0(num):
    return str(num) if num >= 10 else f"0{num}"

maxn = 32

def solve(n, l):
    if(n > maxn): return "PASS"
    for mask in range(1 << n):
        poss = True

        for q in l:
            res = list(map(lambda bitpos: (((mask >> (abs(q[bitpos]) - 1)) & 1) ^ (1 if q[bitpos] < 0 else 0)) == 1, range(3)))
            if(not any(res)):
                poss = False
                break
        
        if(poss):
            return "".join(map(lambda bitpos: "+" if ((mask >> bitpos) & 1 == 1) else "-", range(n)))

for i in range(25):
    # exec(f"touch out/output_{pad_0(i)}.txt")
    with open(f"in/input_{pad_0(i)}.txt", "r+") as f_in, open(f"out/output_{pad_0(i)}.txt", "w+") as f_out:
        t = int(f_in.readline())

        for _ in range(t):
            n, c = map(int, f_in.readline().split(" "))
            l = []
            for _2 in range(c):
                l.append(list(map(int, f_in.readline().split(" "))))
            f_out.write(solve(n, l) + "\n")