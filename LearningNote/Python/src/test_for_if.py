
count = 0
for x in range(1, 4):
    for y in range(1, 4):
        for z in range(1, 4):
            if x != y and x != z and y != z :
                print(x, y, z)
                count += 1

print("count is", count)