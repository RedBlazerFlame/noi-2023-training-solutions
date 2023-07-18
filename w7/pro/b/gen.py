for n in range(1, 101):
    count = 0
    for i in range(n + 1):
        curnum = i * (n - i)
        # print(f"{curnum} ", end="")
        if(curnum % n == 0): count += 1
    # print("")
    print(f"ans[{n}] = {count - 2}")