
def cons(b, a):
    grid = list(map(lambda j: list(map(lambda i: "-", range(b))), range(a)))
    for j in range(a):
        for i in range(b):
            ni = b - i - 1 if i >= (b >> 1) else i 
            nj = a - j - 1 if j >= (a >> 1) else j

            if(ni == nj):
                grid[j][i] = "C"
    return grid

def cities(b, a):
    # grid = list(map(lambda j: list(map(lambda i: "-", range(b))), range(a)))
    cities = []
    for i in range(b):
        for j in range(a):
            ni = b - i - 1 if i >= (b >> 1) else i 
            nj = a - j - 1 if j >= (a >> 1) else j

            
            cities.append(1 if ni == nj else 0)
    return cities

def grid_to_str(grid):
    return "\n".join(map(lambda row: "".join(row), grid))

print("".join(map(str, cities(3, 2))))