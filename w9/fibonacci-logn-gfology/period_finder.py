n = 1

MOD = 998244353
primitive_root_limit = 998244353
for i in range(23, -1, -1):
    pw = 1 << i
    for num in range(primitive_root_limit):
        if(pow(num, pw, MOD) == 1 and pow(num, pw >> 1, MOD) > 1):
            print(f"{num} (2^{i})")
            exit()