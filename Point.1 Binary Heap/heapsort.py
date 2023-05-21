import matplotlib.pyplot as plt

f1 = open("testheapsort.txt")


x = [int(i) for i in f1.readline().split()]

y1 = [int(i)**2 for i in f1.readline().split()]

plt.plot(x, y1, label='heap_sort')
plt.legend(fontsize=14)
plt.show()