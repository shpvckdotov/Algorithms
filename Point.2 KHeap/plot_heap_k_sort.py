import matplotlib.pyplot as plt

f1 = open("testheapksort.txt")

x = [int(i) for i in f1.readline().split()]

ks = [5,10,25, 50, 100, 200, 300, 400, 500, 1000]

ys = [[int(i) for i in f1.readline().split()] for j in ks]


for i in range(len(ks)):
    plt.plot(x,  ys[i], label="k = " + str(ks[i]))


plt.legend(fontsize=14)
plt.show()