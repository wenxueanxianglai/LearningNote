def test_func():
    print('haha, this is function')
    
def test_func_int(x:int):
    print('you need set a value that type is int : ',  x)


def test_func_ret(x:int):
    return x*x


test_func()
test_func_int(2)

x = test_func_ret(2)
print(x)
test_func_int(2.2)

# def test_func_int_3(x:str, y:int):
#     print(x, y)


# tx = 2
# ty = '22'
# tz = 2.2

# test_func_int_3(tx, tz)