def bit(num, j, i):
    return (num >> (j * 5 + i)) & 1

def print_grid(num):
    for i in range(5):
        for j in range(5):
            print("#" if bit(num, i, j) else ".", end="")
        print("")

for i in range(1 << 25):
    count = 0
    for j in range(3):
        for k in range(3):
            corner_dolomite = bit(i, j, k) + bit(i, j + 2, k) + bit(i, j, k + 2) + bit(i, j + 2, k + 2)
            other_dolomite = bit(i, j, k + 1) + bit(i, j + 1, k) + bit(i, j + 1, k + 1) + bit(i, j + 1, k + 2) + bit(i, j + 2, k + 1)
            if(corner_dolomite == 3 and other_dolomite == 0):
                count += 1
    if(count == 4):
        print_grid(i)
        print("")