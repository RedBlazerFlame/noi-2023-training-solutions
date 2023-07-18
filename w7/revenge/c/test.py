def bland(a, b):
    return (not a) and b

def blor(a, b):
    return (not a) or b
    

for i in range(4):
    x0 = (i >> 1) & 1 == 1
    x1 = i & 1 == 1
    print(f"{bin(i)} -> {blor(x1, bland(x1, x1))}")