# 简单的1+。。100之类的
def test_accum(x):
    if x <= 0:
        print('Error!')
        return 

    if x == 1:
        return x
    else:
        return x + test_accum(x-1) 


# 斐波那契
def test_fb(x:int):
    if x <= 2:
        return 1
    else:
        return test_fb(x-1) + test_fb(x-2)

# 汉诺塔
def hn_move(num, a, b, c):
    if(num == 1):
        print(a, '--->', c)
    else:
        hn_move(num-1, a, c, b)
        print(a, '--->', c)
        hn_move(num-1,b, a, c)

# run:
print(test_accum(10))
# test_accum(10)

print(test_fb(6))

hn_move(3, 'a', 'b', 'c')

