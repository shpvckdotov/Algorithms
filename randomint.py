import random

arr = [random.randint(-10**6, 10**6) for i in range(10**6)]
#print(arr)
with open("rand_int.txt", "w") as f:
    for i in arr:
        f.write(str(i) + ' ')