import random

arr = [random.uniform(-10**3, 10**3) for i in range(10**6)]
#print(arr)
with open("rand_float.txt", "w") as f:
    for i in arr:
        f.write(str(i) + ' ')