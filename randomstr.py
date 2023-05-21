import random

arr = []#["".join(chr(random.randint(33, 125)) for _ in range(random.randint(1, 1000))) for j in range(10**6)]
f = open("rand_str.txt", "w")
for k in range(10**6):

    f.write("".join(chr(random.randint(33, 125)) for _ in range(random.randint(1, 100))) + '\n')
    #print(k)

print(len(arr))
#print(arr)
#with open("rand_str.txt", "w") as f:
#    for i in arr:
#        f.write(i + '\n')