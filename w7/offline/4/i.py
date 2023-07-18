n = int(input())
l = []
for i in range(n):
    l.append(list(map(int, input().split(" "))))

dpmin = list(map(lambda _: [0] * n, range(n)))
dpmax = list(map(lambda _: [0] * n, range(n)))
minprev = list(map(lambda _: [(0, 0)] * n, range(n)))
maxprev = list(map(lambda _: [(0, 0)] * n, range(n)))

def sequence_to_command(l):
    n = len(l)
    commands = []
    for i in range(n - 1):
        x1, y1 = l[i]
        x2, y2 = l[i + 1]
        dx, dy = x2 - x1, y2 - y1
        if(dx == 1):
            commands.append("S")
        if(dx == -1):
            commands.append("N")
        if(dy == 1):
            commands.append("E")
        if(dy == -1):
            commands.append("W")
    return "".join(commands)

for i in range(n):
    for j in range(n):
        dpmin[i][j] = l[i][j]
        dpmax[i][j] = l[i][j]
        if(i > 0 and j > 0):
            dpmin[i][j] += min(dpmin[i - 1][j], dpmin[i][j - 1])
            minprev[i][j] = (i - 1, j) if dpmin[i - 1][j] < dpmin[i][j - 1] else (i, j - 1)
            dpmax[i][j] += max(dpmax[i - 1][j], dpmax[i][j - 1])
            maxprev[i][j] = (i - 1, j) if dpmax[i - 1][j] > dpmax[i][j - 1] else (i, j - 1)
        elif(i > 0):
            dpmin[i][j] += dpmin[i - 1][j]
            minprev[i][j] = (i - 1, j)
            dpmax[i][j] += dpmax[i - 1][j]
            maxprev[i][j] = (i - 1, j)
        elif(j > 0):
            dpmin[i][j] += dpmin[i][j - 1]
            minprev[i][j] = (i, j - 1)
            dpmax[i][j] += dpmax[i][j - 1]
            maxprev[i][j] = (i, j - 1)

maxpath = [(n - 1, n - 1)]
while(maxpath[-1] != (0, 0)):
    i, j = maxpath[-1]
    maxpath.append(maxprev[i][j])

minpath = [(n - 1, n - 1)]
while(minpath[-1] != (0, 0)):
    i, j = minpath[-1]
    minpath.append(minprev[i][j])

maxpath = list(reversed(maxpath))
minpath = list(reversed(minpath))

maxcommands = sequence_to_command(maxpath)
mincommands = sequence_to_command(minpath)

print(maxcommands)
print(mincommands)