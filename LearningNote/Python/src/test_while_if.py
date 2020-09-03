num = int(input())

res = 16
while num != res:
    if num < 16:
        print("lower!")
    else:
        print("bigger!")

    num = int(input())

print("success!")