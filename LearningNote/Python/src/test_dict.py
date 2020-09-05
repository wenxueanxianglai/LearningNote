d = {'cpp' : 1, 'java' : 2}

for lan in d:
    print(lan, d[lan])

bf = 'cpp' in d

if bf : 
    print('here is cpp!')

print(bf)