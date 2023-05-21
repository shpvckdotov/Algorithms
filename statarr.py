import matplotlib.pyplot as plt
import sys

if __name__ == "__main__":

    f = open("stat_"+ sys.argv[1] + ".txt", "r")

    index = [i for i in range(1000)]
    values = [int(i) for i in f.readline().split()]
    #print(len(index))
    #print(len(values))

    plt.title(sys.argv[1])
    plt.bar(index, values)
    plt.xlabel("hashes")
    plt.ylabel("number of collisions")
    plt.savefig("plot_" + sys.argv[1] + ".png")
    plt.show()