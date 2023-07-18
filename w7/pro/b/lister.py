n = pow(2, 3) * pow(3, 3) * pow(5, 2)      

count = 0
for i in range(n + 1):
    if((i * (n - i)) % n == 0):
        print(f"( {i}, {n - i})")
        count += 1

print(count - 2)