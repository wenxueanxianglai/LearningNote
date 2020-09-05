from test_function import x


d = {'cpp' : 1, 'java' : 2, 'csharp': 3}

for lan in d:
    print(lan, d[lan])

bf = 'cpp' in d

if bf :
    print('here is cpp!')
print(bf)

print(d['cpp'])

tup = ['mark', 'down', 'come', 'let']

print(tup[3])
print(tup[:3])
print(tup[1:2])

str ='abcdefg'
print(str[0:3])

bchar = lambda x: (x>='a' and x<= 'z') or (x >= 'A' and x <= 'Z') or ( x>= '0' and x <='9')

# trime 
def sub(s:str):
    x = 0
    while (not bchar(s[x])):
        x += 1

    newsss = s[x: ]
    
    x = -1
    while(not bchar(newsss[x])):
        x -= 1
    x += 1

    newsss = newsss[0: x]    # [0, x)
    return newsss


ssss = '   str sdf   '
newss = sub(ssss)
print(newss)

    