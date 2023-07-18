times = 350

with open("output_0.txt", "w+") as f:
    for i in range(times):
        s = []
        imod3 = i % 3
        for j in range(233 if imod3 < 2 else 232):
            s.append(f"{3 * j + 1 + imod3} {3 * j + 2 + imod3} {3 * j + 3 + imod3}")
        if(imod3 == 2): s.append("699 700")

        res = " / ".join(s)
        f.write(f"{res}\n")