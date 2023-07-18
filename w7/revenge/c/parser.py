def is_var(s):
    return s[0] == "x"

def var_ind(s):
    return int(s[1])

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

num_vars = 10
for i in range(1 << num_vars):
    var_vals = []
    for j in range(num_vars):
        var_vals.append((i >> (num_vars - j - 1)) & 1)
        print(var_vals[-1], end="")
    for i in range(len(split)):
        vals[i] = -1
        starts[i] = 0
    print(f" -> {eval_circ(split, len(split) - 1, var_vals)}")