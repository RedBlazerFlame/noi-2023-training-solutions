def is_var(s):
    return s[0] == "x"

def var_ind(s):
    return int(s[1])

file_num, num_vars = input().split(" ")
raw = input()
split = raw.split(" ")

vals = [-1] * len(split)
starts = [0] * len(split)
def eval_circ(split, i, val):
    if(vals[i] == -1):
        token = split[i]
        if(is_var(token)):
            vals[i] = val[var_ind(token)]
            starts[i] = i
        else:
            eval_circ(split, i - 1, val)
            i1 = starts[i - 1]
            eval_circ(split, i1 - 1, val)
            if(token == "AND"):
                vals[i] = vals[i1 - 1] & vals[i - 1]
            elif(token == "OR"):
                vals[i] = vals[i1 - 1] | vals[i - 1]
            elif(token == "NAND"):
                vals[i] = 1 ^ (vals[i1 - 1] & vals[i - 1])
            elif(token == "NOR"):
                vals[i] = 1 ^ (vals[i1 - 1] | vals[i - 1])
            starts[i] = min(i1, starts[i1 - 1])
    return vals[i]

def var(n):
    return (f"x{n}", 0)

def make_and(small, large):
    if(small[1] > large[1]):
        small, large = large, small
    return (f"{small[0]} {large[0]} BLAND {large[0]} BLAND", small[1] + 2 * large[1] + 2)

def make_or(small, large):
    if(small == ""):
        return large
    if(small[1] > large[1]):
        small, large = large, small
    return (f"{small[0]} {large[0]} BLOR {large[0]} BLOR", small[1] + 2 * large[1] + 2)

def make_not(circ):
    return (f"{circ[0]} {circ[0]} {circ[0]} BLAND BLOR", 3 * circ[1] + 2)

def gen_sol():
    global file_num, num_vars
    num_vars = int(num_vars)
    truth_table = [0] * (1 << num_vars)
    for i in range(1 << num_vars):
        var_vals = []
        for j in range(num_vars):
            var_vals.append((i >> (num_vars - j - 1)) & 1)
            
        for j in range(len(split)):
            vals[j] = -1
            starts[j] = 0
        truth_table[i] = eval_circ(split, len(split) - 1, var_vals)
        if(truth_table[i] == 1):
            cur = ""
            yield var(0)[0] if var_vals[0] == 1 else make_not(var(0))[0]
            
            for j in range(1, num_vars):
                cur_gate = (var(j) if var_vals[j] == 1 else make_not(var(j)))[0]
                yield f"{cur_gate} BLAND {cur_gate} BLAND"
            yield "OR"

orred_sol = " ".join(gen_sol()).split(" OR ")
orred_sol[-1] = orred_sol[-1][:-3]

def gen_final_sol(orred_sol):
    yield orred_sol[0]
    for i in range(1, len(orred_sol)):
        yield orred_sol[i]
        yield "BLOR"
        yield orred_sol[i]
        yield "BLOR"

with open(f"outs/output_{file_num}.txt", "w+") as f:
    f.write(" ".join(gen_final_sol(orred_sol)) + "\n")